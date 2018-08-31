// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_DEBUG_LOGGER_H
#define GDK_DEBUG_LOGGER_H

#include <functional>
#include <sstream>
#include <string>

namespace gdk
{
        template<typename ...Args> void log(const char aTag[], Args &&...args);
        template<typename ...Args> void error(const char aTag[], Args &&...args);
                
        /// \brief Used to render debug messages in some form. 
        ///
        /// \detailed The default behaviour is to send the data to std::clog,
        /// however this can be changed by passing a function of sig void(const std::string&) to the constructor. 
        /// In this way, Logger can be used to output to files, pipes, over the network, etc.
        /// This header also declares the free standing functions log and error, which are gdk wrappers for
        /// std::clog and std::cerr respectively.        
        class Logger final
        {
            template<typename ...Args> friend void gdk::log(const char aTag[], Args &&...args);
            template<typename ...Args> friend void gdk::error(const char aTag[], Args &&...args);
            
            static Logger s_gdkLogger;      //!< Logger that wraps std::cout
            static Logger s_gdkErrorLogger; //!< Logger rhat wraps std::cerr
            
            std::function<void(const std::string &)> m_LoggingBehaviourCallback;
            
            void log(std::ostringstream &stringStream)
            {
                m_LoggingBehaviourCallback(stringStream.str());
            }
            
            template<typename First, typename ...Rest>
            void log(std::ostringstream &stringStream, First &&first, Rest &&...rest)
            {
                stringStream << first;
                log(stringStream, std::forward<Rest>(rest)...);
            }
            
        public:
            //! variadic logging function
            /// e.g: log("blar", 123, true, nullptr, 3.1415f)
            template<typename First, typename ...Rest>
            void log(First &&first, Rest &&...rest)
            {
                std::ostringstream stringStream;
                stringStream << first;
                
                log(stringStream, std::forward<Rest>(rest)...);
            }
            
            Logger &operator=(const Logger &) = default;
            Logger &operator=(Logger &&) = default;
            
            //! Change log behavior by passing a function pointer to your own logging function.
            /// Default behaviour is for the logger to display the debug message via std::clog
            Logger(const std::function<void(const std::string &)> &aLoggingBehaviourCallback = nullptr);
            Logger(const Logger &) = default;
            Logger(Logger &&) = default;
            ~Logger() = default;
        };
        
        template<typename ...Args>
        void log(const char aTag[], Args &&...args)
        {
            Logger::s_gdkLogger.log(aTag, ": ", std::forward<Args>(args)...);
        }
        
        template<typename ...Args>
        void error(const char aTag[], Args &&...args)
        {
            Logger::s_gdkErrorLogger.log(aTag, ": ", std::forward<Args>(args)...);
        }
}

#endif
