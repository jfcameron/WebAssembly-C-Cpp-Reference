// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_DATABASE_H
#define GDK_DATABASE_H

#include <memory>
#include <string>
#include <tuple>
#include <type_traits>

struct sqlite3;

namespace gdk
{
    /// \brief RAII wrapper for local [sqlite] database
    ///
    /// \detailed sqlite should be preferred for persistent data (savegame data) etc. because of ACID
    class Database final
    {
    public:
        using sqlite_db_ptr_type = std::unique_ptr<sqlite3, void(*)(sqlite3 *)>;

        using integer_type = long int;
        using real_type =    double;
        using text_type =    std::string;
        using blob_type =    std::vector<unsigned char>;

        //! rules about how to open the db file on disk
        enum class ConstructionMode
        {
            OPEN_OR_CREATE, //!< if the file does not exist, create then open
            ONLY_OPEN       //!< if the file does not exist, throw an exception
        };

        //! rules about how to view and or modify the data
        enum class ReadMode
        {
            READONLY, //!< can read but cannot write data \todo (should this be subclassed so that the write method is only available on writeable db?)
            READWRITE //!< can read and write data
        };

    private:
        sqlite_db_ptr_type m_pDatabase;

        /// \brief constrains type arguments to database types 
        template<typename ...T>
        static constexpr bool is_valid_database_type()
        {
            return (std::is_same_v<T, integer_type> || ...)
                || (std::is_same_v<T, real_type>    || ...)
                || (std::is_same_v<T, text_type>    || ...)
                || (std::is_same_v<T, blob_type>    || ...);
        }

    public:
        /*/// \todo MAKE THIS THREADSAFE! It should be readable from any thread
        std::string readText(const std::string &aKey);
        double readReal(const std::string &aKey);
        long int readInteger(const std::string &aKey);
        std::vector<unsigned char> readBlob(const std::string &aKey);

        /// \todo MAKE THREADSAFE! must be locked during a write.
        void write(const std::string &aKey, const std::string &aValue);*/

        /// \brief writes an entry to a table
        template<typename ...T>
        void writeToTable(const std::string &aTableName, std::tuple<T...> aTableContents)
        {
            static_assert(is_valid_database_type<T...>());
        }

        /// \brief Creates a table with specified entry format
        template<typename ...T>
        void createTable(const std::string &aTableName)
        {
            static_assert(is_valid_database_type<T...>());
        }

        //getFrom

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
