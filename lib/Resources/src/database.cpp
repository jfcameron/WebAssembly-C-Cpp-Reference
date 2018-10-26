// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/database.h>
#include <gdk/exception.h>
#include <gdk/logger.h>
#include <gdkresources/buildinfo.h>

#include <sqlite/sqlite3.h>

#include <iostream>
#include <queue>

namespace
{
    constexpr char TAG[] = "Database";

    bool is_number(const std::string& s)
    {
        return !s.empty() && std::find_if(s.begin(), s.end(), [](const char c) 
        { 
            return !std::isdigit(c); 
        }) == s.end();
    }
}

namespace gdk
{
    Database::Data::Data(const Database::Data::integer_type &value)
    : m_Type(Type::Integer)
    {
        m_Value.v_Integer = value;
    }

    Database::Data::Data(const Database::Data::real_type &value)
    : m_Type(Type::Real)
    {
        m_Value.v_Real = value;
    }

    Database::Data::Data(const Database::Data::text_type &value)
    : m_Type(Type::Text)
    {
        m_Value.v_Text = value;
    }

    Database::Data::Data(const Database::Data::blob_type &value)
    : m_Type(Type::Blob)
    {
        m_Value.v_Blob = value;
    }

    Database::Data::integer_type Database::Data::getInteger() const 
    { 
        return m_Value.v_Integer; 
    }
    
    Database::Data::real_type Database::Data::getReal() const 
    { 
        return m_Value.v_Real; 
    }
    
    Database::Data::text_type Database::Data::getText() const 
    { 
        return m_Value.v_Text; 
    }
    
    Database::Data::blob_type Database::Data::getBlob() const 
    { 
        return m_Value.v_Blob; 
    }

    std::string Database::Data::TypeToSQLiteTypeString(const Data::Type &aType)
    {
        std::string rval;

        switch (aType)
        {
            case Data::Type::Integer: rval = "INT";  break;
            case Data::Type::Real:    rval = "REAL"; break;
            case Data::Type::Text:    rval = "TEXT"; break;
            case Data::Type::Blob:    rval = "BLOB"; break;
        }

        return rval;
    }

    Database::Data::Type Database::Data::SQLiteTypeStringToType(const std::string &aSQLTypeString)
    {
        if (aSQLTypeString == "INT")  return Data::Type::Integer;
        if (aSQLTypeString == "REAL") return Data::Type::Real;
        if (aSQLTypeString == "TEXT") return Data::Type::Text;
        if (aSQLTypeString == "BLOB") return Data::Type::Blob;

        throw std::runtime_error(std::string("unsupported SQL type: ").append(aSQLTypeString));
    }

    Database::Data::Type Database::Data::getType() const 
    { 
        return m_Type; 
    }
}

namespace gdk
{
    Database::Database(const ConstructionMode &aConstructionMode, const ReadMode &aReadMode, const std::string &aPathToDatabase)
    : m_pDatabase([&]()
    {
        //TODO: call "PRAGMA query_only = true;" if in readonly mode The query_only pragma prevents all changes to database files when enabled.

        gdk::log(TAG, "aConstructionMode and aReadMode are currently ignored!!! a OPEN_OR_CREATE and READWRITE is forced!");

        sqlite3 *pDatabase;

        if (SQLITE_OK == sqlite3_open(aPathToDatabase.c_str(), &pDatabase))
        {
            return (sqlite_db_ptr_type){pDatabase, [](sqlite3 * ptr)
            {
                sqlite3_close(ptr);
            }};
        }
        else throw std::runtime_error(std::string("sqlite could not initialize the database: ").append(sqlite3_errmsg(pDatabase)));
    }())
    {
        gdk::log(TAG, "sqlite version: ", sqlite3_libversion());
    }

    bool Database::formats_are_same(const Database::row_format_type &a, const Database::row_format_type &b)
    {
        if (a.size() != b.size()) return false;

        for (size_t i = 0, s = a.size(); i < s; ++i)
        {
            if (a[i].first != b[i].first) return false;

            if (a[i].second != b[i].second) return false;
        }

        return true;
    }

    //
    // Reduce code duplication in these overloads
    //
    void Database::execute(const std::string &aSQL)
    {
        char *err_msg = NULL;

        if (SQLITE_OK != sqlite3_exec(m_pDatabase.get(), aSQL.c_str(), NULL, 0, &err_msg))
        {
            throw std::runtime_error(std::string("SQLite Error: ").append(err_msg));
    
            sqlite3_free(err_msg);
        }
    }
    void Database::execute(const std::string &aSQL, exec_callback_type aCallback, void *pUserData)
    {
        char *err_msg = NULL;

        if (SQLITE_OK != sqlite3_exec(m_pDatabase.get(), aSQL.c_str(), aCallback, pUserData, &err_msg))
        {
            throw std::runtime_error(std::string("SQLite Error: ").append(err_msg));
    
            sqlite3_free(err_msg);
        }
    }

    Database::row_format_type Database::getTableFormat(const std::string &aTableName)
    {
        const int columnCount = [&]()
        {
            sqlite3_stmt *pCompiledStatementHandle;

            if (SQLITE_OK != sqlite3_prepare_v2(m_pDatabase.get(), std::string("SELECT * FROM ").append(aTableName).c_str(), -1, &pCompiledStatementHandle, NULL))
            {
                throw std::string(std::string("SQLite Error: ").append(sqlite3_errmsg(m_pDatabase.get())));
            }

            return sqlite3_column_count(pCompiledStatementHandle);
        }();

        using response_buffer_type = std::queue<std::string>;

        response_buffer_type responseBuffer;

        execute(std::string("PRAGMA table_info(") + aTableName + std::string(")"), [](void *pUserData, int argc, char **argv, char **azColName)
        {
            for (int i = 0; i < argc; i++)
            {
                if (argv[i])
                {
                    std::string currentLine = std::string(argv[i]);

                    if (!is_number(currentLine)) static_cast<response_buffer_type *>(pUserData)->push(currentLine);
                }
            }

            return 0;
        }
        , &responseBuffer);

        if (responseBuffer.size() != 2 * columnCount) throw std::runtime_error("cannot determine dabase table type. Response buffer is malformed: " + aTableName);

        row_format_type format;

        while(responseBuffer.size() > 0)
        {
            format.push_back([&]()
            {
                std::pair<std::string, Data::Type> buffer;

                buffer.first = responseBuffer.front();
                responseBuffer.pop();

                buffer.second = Data::SQLiteTypeStringToType(responseBuffer.front());
                responseBuffer.pop();

                return buffer;
            }());
        }

        return format;
    }

    void Database::createTable(const std::string &aTableName, std::vector<std::pair<std::string, Data::Type>> aRowFormat)
    {
        std::string sql = "DROP TABLE IF EXISTS " + aTableName + ";CREATE TABLE " + aTableName + "(";

        for (int i = 0, s = aRowFormat.size(); i < s; ++i)
        {
            const auto &item = aRowFormat[i];

            sql += item.first + " ";

            switch (item.second)
            {
                case Data::Type::Integer: sql += "INT";  break;
                case Data::Type::Real:    sql += "REAL"; break;
                case Data::Type::Text:    sql += "TEXT"; break;
                case Data::Type::Blob:    sql += "BLOB"; break;

                default: throw std::runtime_error("this text should be more meaningful"); break;
            }

            if (i < s - 1) sql += ", ";
        }

        sql += ");";

        execute(sql);
    }

    std::vector<Database::row_data_type> Database::getTableContents(const std::string &aTable) //const
    {
        const std::string sqlPrefix = std::string("SELECT * FROM ").append(aTable).append(" LIMIT 1 OFFSET ");

        /// \brief POD supplies table format to the sql_execute callback 
        /// and provides a place to write the statically typed row data
        struct UserData
        {
            const row_format_type in_RowDataFormat; //!< provides column type info

            table_data_type out_TableDataBuffer; //!< write area for table data taken from database
        }
        userData = {
            .in_RowDataFormat = getTableFormat(aTable)
        };

        for(int i = 0, s = getNumberOfRows(aTable); i < s; ++i) // for each row in table
        {
            //std::cout << "row: " << i << ":\n";

            execute(sqlPrefix + std::to_string(i), [](void *vpUserData, int argc, char **argv, char **azColName)
            {
                UserData *const pUserData = static_cast<UserData *>(vpUserData);

                if (argc != pUserData->in_RowDataFormat.size()) throw std::runtime_error(std::string("Row format does not match row format associated with table!"));

                Database::row_data_type rowDataBuffer;

                // For each value in row
                for (int j = 0, t = argc; j < t; ++j)
                {
                    std::string currentLine = std::string(argv[j]);
                        
                    // This shows that a hashmap view onto the data could be returend: format: map<id_name{std::string}, typed_data{type enum, variant accessors}>
                    std::cout << "id: " << pUserData->in_RowDataFormat[j].first 
                    << ", type: " << Database::Data::TypeToSQLiteTypeString(pUserData->in_RowDataFormat[j].second) 
                    << ", val: " << currentLine << std::endl;

                    switch (pUserData->in_RowDataFormat[j].second)
                    {
                        case Data::Type::Integer: 
                        {
                            rowDataBuffer.push_back(Database::Data(
                                Data::integer_type(std::stol(currentLine))
                            )); 
                        } break;
                        
                        case Data::Type::Real:    
                        {
                            rowDataBuffer.push_back(Database::Data(
                                Data::real_type(std::stod(currentLine))
                            ));
                        } break;

                        case Data::Type::Text:    
                        {
                            rowDataBuffer.push_back(Database::Data(
                                Data::text_type(currentLine)
                            ));
                        } break;

                        case Data::Type::Blob:
                        {
                            /*pUserData->out_TableDataBuffer.push_back(Database::Data(
                                
                            ));*/
                            throw std::runtime_error("getTableContents does not currently support blob");
                        } break;
                    }
                }

                pUserData->out_TableDataBuffer.push_back(rowDataBuffer);

                return 0;
            }
            , &userData);
        }

        return userData.out_TableDataBuffer;
    }

    size_t Database::getNumberOfRows(const std::string &aTableName)
    {
        size_t numberOfRows;

        execute(std::string("SELECT Count(*) FROM ").append(aTableName), [](void *pUserData, int argc, char **argv, char **azColName)
        {
            if (argc != 1) throw std::runtime_error(std::string("numberOfRows sql response is incorrect."));

            std::string currentLine = std::string(argv[0]);

            *static_cast<size_t *>(pUserData) = std::stoi(currentLine);

            return 0;
        }
        , &numberOfRows);

        return numberOfRows;
    }

    std::vector<std::string> Database::getTableNames()
    {
        std::vector<std::string> tableNames;

        execute(std::string("SELECT name FROM sqlite_master WHERE type = \"table\";"), [](void *pUserData, int argc, char **argv, char **azColName)
        {
            for (int i = 0; i < argc; i++) static_cast<std::vector<std::string> *>(pUserData)->push_back(std::string(argv[i]));

            return 0;
        }
        , &tableNames);

        return tableNames;
    }

    size_t Database::getNumberOfTables()
    {
        size_t tableCount;

        execute(std::string("SELECT Count(*) FROM sqlite_master WHERE type = \"table\";"), [](void *pUserData, int argc, char **argv, char **azColName)
        {
            if (argc != 1) throw std::runtime_error("getNumberOfTables response malformed! Expected 1 line in response!");

            *static_cast<size_t *>(pUserData) = std::stoul(argv[0]);

            return 0;
        }
        , &tableCount);

        return tableCount;
    }

    void Database::writeToTable(const std::string &aTableName, std::vector<Database::Data> aRow)
    {
        //Should assert format here...
        //TODO TODO TODO

        std::string commandBuffer = "INSERT INTO " + aTableName + " VALUES(";

        for (int i = 0, s = aRow.size(); i < s; ++i)
        {
            const auto &item = aRow[i];

            std::string valueBuffer;

            switch (item.getType())
            {
                case Data::Type::Integer: valueBuffer += std::to_string(item.getInteger()); break;
                case Data::Type::Real:    valueBuffer += std::to_string(item.getReal()); break;
                case Data::Type::Text:    valueBuffer += item.getText(); break;

                case Data::Type::Blob:    throw std::runtime_error("Blob write is unsupported");
            }

            if (item.getType() == Data::Type::Text) valueBuffer.insert(0, "'").append("'");

            if (i < s - 1) valueBuffer += ", ";

            commandBuffer += valueBuffer;
        }

        commandBuffer += ");";

        execute(commandBuffer);
    }

    void Database::writeToTable(const std::string &aTableName, table_data_type aRows)
    {
        for (const auto &row : aRows) writeToTable(aTableName, row);
    }

    bool Database::doesTableExist(const std::string &aTableName)
    {
        bool tableExists;

        execute(std::string("SELECT name FROM sqlite_master WHERE name = \"").append(aTableName).append("\";"), [](void *pUserData, int argc, char **argv, char **azColName)
        {
            switch (argc)
            {
                case 0:
                {
                    *static_cast<bool *>(pUserData) = false;
                } break;

                case 1:
                {
                    *static_cast<bool *>(pUserData) = true;
                } break;

                default: throw std::runtime_error("doesTableExist sql response malformed! Expected 1 or 0 line response, received n>1");
            }

            return 0;
        }
        , &tableExists);

        return tableExists;
    }
}
