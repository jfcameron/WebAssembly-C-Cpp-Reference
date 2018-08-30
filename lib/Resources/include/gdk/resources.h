// © 2018 Joseph Cameron - All Rights Reserved
//! Resources provides APIs to load different resource files (images, text) from disk

#ifndef GDK_RESOURCES_H
#define GDK_RESOURCES_H

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace gdk::resources
{
    /*namespace local database?? 
    {
        readstring(key)
        writestring(key,value)
    }*/

    namespace local
    {
        //! loads a file at aPath to a vector of bytes
        /// \note this function is synchronous        
        /// \exception if file does not exist
        /// \exception if file is not a PNG of form RGBA32
        std::vector<unsigned char> loadBinaryFile(const std::string &aPath);
    }

    namespace remote
    {
        //! fetch a file at the URL
        /// \note this function is asynchronous
        /// \warn this is not thread safe
        void fetchBinaryFile(const std::string aURL, std::function<void(const bool, std::vector<unsigned char>)> aResponseHandler);
    }

    // ========================================================
    //
    // PROTECTED (used by siblings or middleware; hide from the user for their own good)
    //
    // ========================================================
    void updateFetchQueue(); //!< call from mainthread or worker thread[s], processes the front of the fetch queue

    void updateResponseQueue(); //!< call from mainthread
}

#endif
