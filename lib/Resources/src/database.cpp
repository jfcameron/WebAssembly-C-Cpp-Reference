// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/database.h>
#include <gdk/exception.h>
#include <gdk/logger.h>
#include <gdkresources/buildinfo.h>

#include <sqlite/sqlite3.h>

static constexpr char TAG[] = "Database";

namespace gdk
{
    Database::Database(const ConstructionMode &aConstructionMode, const ReadMode &aReadMode, const std::string &aPathToDatabase)
    : m_pDatabase([&]()
    {
        gdk::log(TAG, "aConstructionMode and aReadMode are currently ignored!!! a OPEN_OR_CREATE and READWRITE is forced!");

        sqlite3 *pDatabase;

        if (sqlite3_open(aPathToDatabase.c_str(), &pDatabase) == SQLITE_OK)
        {
            return (sqlite_db_ptr_type){pDatabase, [](sqlite3 * ptr)
            {
                sqlite3_close(ptr);
            }};
        }
        else throw gdk::Exception(TAG, "sqlite could not initialize the database: ", sqlite3_errmsg(pDatabase));
    }())
    {
        gdk::log(TAG, "sqlite version: ", sqlite3_libversion());
    }
}
