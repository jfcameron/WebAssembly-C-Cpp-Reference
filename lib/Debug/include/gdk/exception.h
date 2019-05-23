// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_EXCEPTION_H
#define GDK_EXCEPTION_H

#include <stdexcept>
#include <string>
#include <sstream>

namespace gdk
{
    /// \brief gdk runtime exception type. This allows users to differentiate between nongdk and gdk exceptions.
    class Exception : public std::runtime_error
    {
        std::string toString(std::ostringstream &sstream)
        {
            return sstream.str();
        }
        
        std::string toString(std::ostringstream &&sstream)
        {
            return sstream.str();
        }
        
        template<typename First, typename ...Rest>
        std::string toString(std::ostringstream &sstream, First &&first, Rest &&...rest)
        {
            sstream << first;

            toString(sstream, std::forward<Rest>(rest)...);

            return sstream.str();
        }
        
        template<typename First, typename ...Rest>
        std::string toString(std::ostringstream &&sstream, First &&first, Rest &&...rest)
        {
            sstream << first;

            toString(sstream, std::forward<Rest>(rest)...);

            return sstream.str();
        }
        
    public:
        Exception &operator=(const Exception &) = default;
        Exception &operator=(Exception &&) = default;

        //! Constructs a gdk exception.
        /// Templated to allow for the exception message to be written in a safe variadic form e.g:
        /// throw gdk::exception("Widget", "fatal error in ctor: height=", uHeight, " width=", uWidth); 
        template<typename First, typename ...Rest>
        Exception(const char aTag[], First &&first, Rest &&...rest)
        : std::runtime_error(std::string(aTag).append(": ").append([&first]()
        {
            std::ostringstream sstream;

            sstream << first;

            return sstream.str();
        }())
        .append(toString(std::ostringstream(), std::forward<Rest>(rest)...)))
        {}
        
        Exception(const Exception &) = default;
        Exception(Exception &&) = default;
        virtual ~Exception() = default;
    };

    std::ostream &operator<< (std::ostream &, const Exception &);
}

#endif

