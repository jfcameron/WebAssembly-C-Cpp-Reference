// © 2018 Joseph Cameron - All Rights Reserved
//! Resources provides APIs to load different resource files (images, text) from disk

#ifndef GDK_RESOURCES_H
#define GDK_RESOURCES_H

#include <string>
#include <vector>

namespace gdk::resources
{
    //! loads a text file at aPath to a string
    /// \exception if file does not exist
    std::string load_text_file(const std::string &aPath);

    //! loads a png file of format RGBA32 at aPath to a vector of bytes
    /// \exception if file does not exist
    /// \exception if file is not a PNG of form RGBA32
    std::vector<unsigned char> load_RGBA32png_file(const std::string &aPath);
}

#endif
