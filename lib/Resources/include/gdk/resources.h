// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_RESOURCES_H
#define GDK_RESOURCES_H

#include <functional>
#include <memory>
#include <string>
#include <vector>

//! Resources provides APIs to load different resource files (images, text) from disk
namespace gdk::resources
{
    /// signature for resource aquisition callbacks. bool indicates success or failure. vector of bytes contains data.
    using response_handler_type = std::function<void(const bool, std::vector<unsigned char>)>;

    //! fetch data from the local filesystem
    namespace local
    {
        //! loads a file at aPath to an array of bytes
        /// \note this function is asynchronous
        void fetchFile(const std::string aPath, response_handler_type aResponse);
    }

    //! fetch data over the network or internet
    namespace remote
    {
        //! loads a file at aURL to an array of bytes
        /// \note this function is asynchronous
        void fetchFile(const std::string aURL, response_handler_type aResponse /*, aTimeoutMS*/ /*, aAuthToken? etc.*/);
    }
}

#endif
