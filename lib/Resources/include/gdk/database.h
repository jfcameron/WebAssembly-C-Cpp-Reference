// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_DATABASE_H
#define GDK_DATABASE_H

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

struct sqlite3;

namespace gdk
{
    /// \brief extendable RAII wrapper for local sqlite database. Offers basic IO API.
    ///
    /// \detailed database should be preferred for persistent data (savegame data, etc.) because of ACID properties.
    /// provides some simple functions for interacting with the db. 
    /// If you want to do more complicated SQL operations, extend the class and create methods that pass SQL scripts to the protected execute method
    ///
    /// \todo replace Database::Data with std::variant, once libcpp17 is easier to install on (gdk) supported platforms. This will allow me to reduce a whole lot of boilerplate that
    /// lets Database::Data to act as a variant. Less code, more stl, easier to read & maintain.
    ///
    /// \todo refactor work: create a Database::Table object. Many dataypes and toplevel functions work with tables within the database, however the tables are never modeled in OOP way.
    /// refactoring this would make implementation easier to read and maintain.
    ///
    /// \todo cleanup datatypes. There are probably implicit casts from int to long, float to double etc. should clean all this up.
    ///
    /// \todo improve throw messages. currently cryptic.. refer to errors, bad args from the implementation's perspective (eg "row column count exceeds table column count in sqldb"). 
    /// should be reworded from the API's perspective (eg "writeData argument row format {...} does not match table "name"'s row format {...}")
    ///
    /// \todo while individual db interaction is atomic, this atomicity does not stay 1 to 1 with api (eg writeToTable array override). This should be fixed. Additionally, API calls should be groupable so that an entire set of calls all become atomic, to prevent
    /// the user from being able to write incomplete state information to the DB
    /// 
    /// \todo Refactor s.t there is a Table class. std::weak_ptr<Database::Table> getTable()
    class Database
    {
        using sqlite_db_ptr_type = std::unique_ptr<sqlite3, void(*)(sqlite3 *)>;

        sqlite_db_ptr_type m_pDatabase;

    public:
        /// \brief variant type representing data in the database
        ///
        /// \todo replace union with std::variant, when libcpp 17 is easier to work with
        class Data
        {
        public:
            using integer_type = long int;
            using real_type =    double;
            using text_type =    std::string;
            using blob_type =    std::vector<unsigned char>;

            enum class Type
            {
                Integer,
                Real,
                Text,
                Blob
            };

        private:
            Type m_Type;

            struct //should be union
            {
                integer_type v_Integer;
                real_type v_Real;
                text_type v_Text;
                blob_type v_Blob;
            }
            m_Value;

        public:
            Type getType() const;

            integer_type getInteger() const;
            real_type getReal() const;
            text_type getText() const;
            blob_type getBlob() const;

            Data(const integer_type &value);
            Data(const real_type &value);
            Data(const text_type &value);
            Data(const blob_type &value);

            /// \brief converts the enum class "Type" to its sqlite char * equivalent
            static std::string TypeToSQLiteTypeString(const Data::Type &aType);

            /// \brief converts sql type string to Data::Type enum value
            static Data::Type SQLiteTypeStringToType(const std::string &aSQLTypeString);
        };

        using column_name_value_type = std::pair<std::string, Data::Type>;
        using row_format_type = std::vector<column_name_value_type>;
        using row_data_type =   std::vector<Data>;

        static bool formats_are_same(const row_format_type &a, const row_format_type &b);

        using exec_callback_type = std::add_pointer<int(void *pUserData, int argc, char **argv, char **azColName)>::type;

        /// \brief rules about how to open the db file on disk
        enum class ConstructionMode
        {
            OPEN_OR_CREATE, //!< if the file does not exist, create then open
            ONLY_OPEN       //!< if the file does not exist, throw an exception
        };

        /// \brief rules about how to view and or modify the data
        enum class ReadMode
        {
            READONLY, //!< can read but cannot write data \todo (should this be subclassed so that the write method is only available on writeable db?)
            READWRITE //!< can read and write data
        };

    protected:
        /// \brief wrapper for sqlite3_exec; pass well-formed SQL to interact with the database
        void execute(const std::string &aSQL);

        /// \brief wrapper for sqlite3_exec; pass well-formed SQL to interact with the database
        void execute(const std::string &aSQL, exec_callback_type aCallback, void *pUserData = nullptr);

        //void execute(const std::string &aSQL, exec_callback_type aCallback = {}, void *pUserData = nullptr, char **pString = nullptr); //int  (*exec)(sqlite3*,const char*,sqlite3_callback,void*,char**);

    public:
        // -=-==--==- DATABASE WIDE -=-==--==- 

        /// \brief get list of table names contained in database
        std::vector<std::string> getTableNames();

        /// \brief get number of tables contained in database
        size_t getNumberOfTables();

        /// \brief creates a table with the specified name and row format. 
        ///
        /// \warn as currently implemented, will override existing tables.
        ///
        /// \todo should it overwrite? should there be a mode enum? Should it throw?
        void createTable(const std::string &aTableName, row_format_type aRowFormat);

        /// \brief deletes a table

        /// \brief checks if a table with the specified name exists.
        bool doesTableExist(const std::string &aTableName);

        // -=-==--==- TABLE WIDE -=-==--==- 

        /// \brief returns the number of rows in a table
        size_t getNumberOfRows(const std::string &aTableName);

        using table_data_type = std::vector<row_data_type>;

        /// \brief gives the format of a table (list of column NAME and TYPEs)
        row_format_type getTableFormat(const std::string &aTableName);

        /// \brief get all contents of a table as a list of rows (a row is a list of values)
        table_data_type getTableContents(const std::string &aTable);

        /// \brief get a range of values from the table
        //std::vector<row_data_type> getTableContents(const std::string &aTable, offest 0, range 10 etc);

        /// \brief get a row of values from a table at specified index

        /// \brief writes a row of data to a table
        ///
        /// \warn the data format of the row must match the table row format or an exception will be thrown
        void writeToTable(const std::string &aTableName, row_data_type aRow);
        /// \brief writes rows of data to a table
        void writeToTable(const std::string &aTableName, table_data_type aRows);

        Database& operator=(const Database &) = delete;
        Database& operator=(Database &&) = delete;

        /// \brief creates or opens a database file on the local system
        Database(const ConstructionMode &aConstructionMode, const ReadMode &aReadMode, const std::string &aPathToDatabase);

        Database() = delete;
        Database(const Database &) = delete;
        Database(Database &&) = default;
        ~Database() = default;
    };
}

#endif
