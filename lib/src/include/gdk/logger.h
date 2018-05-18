// © 2017 Joseph Cameron - All Rights Reserved
// Created on 2017-06-29.
#ifndef GDK_DEBUG_LOGGER_H
#define GDK_DEBUG_LOGGER_H

#include <functional>
#include <sstream>
#include <string>

namespace GDK
{
    namespace Debug
    {
        template<typename ...Args> void log(const char aTag[], Args &&...args);
        template<typename ...Args> void error(const char aTag[], Args &&...args);
        
        /*!
         Used to render debug messages in some form. The default behaviour is to send the data to std::clog,
         however this can be changed by passing a function of sig void(const std::string&) to the constructor. 
         In this way, Logger can be used to output to files, pipes, over the network, etc.
         
         This header also declares the free standing functions Debug::log and Debug::error, which are GDK wrappers for
         std::clog and std::cerr respectively.
         */
        class Logger final
        {
            template<typename ...Args> friend void GDK::Debug::log(const char aTag[], Args &&...args);
            template<typename ...Args> friend void GDK::Debug::error(const char aTag[], Args &&...args);
            
            static Logger s_GDKLogger;
            static Logger s_GDKErrorLogger;
            
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
            template<typename First, typename ...Rest>
            void log(First &&first, Rest &&...rest)
            {
                std::ostringstream stringStream;
                stringStream << first;
                
                log(stringStream, std::forward<Rest>(rest)...);
            }
            
            // Mutating operators
            Logger &operator=(const Logger &) = default;
            Logger &operator=(Logger &&) = default;
            
            // Constructors & destructors
            /// Change log behavior by passing a function pointer to your own logging function.
            /// Default behaviour is for the logger to display the debug message via std::clog
            Logger(const std::function<void(const std::string &)> &aLoggingBehaviourCallback = nullptr);
            Logger(const Logger &) = default;
            Logger(Logger &&) = default;
            ~Logger() = default;
        };
        
        template<typename ...Args>
        void log(const char aTag[], Args &&...args)
        {
            Logger::s_GDKLogger.log(aTag, ": ", std::forward<Args>(args)...);
        }
        
        template<typename ...Args>
        void error(const char aTag[], Args &&...args)
        {
            Logger::s_GDKErrorLogger.log(aTag, ": ", std::forward<Args>(args)...);
        }
    }
}

#endif
