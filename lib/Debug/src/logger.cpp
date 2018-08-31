// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/logger.h>

#include <iostream>
#include <string>

using namespace gdk;

Logger Logger::s_gdkLogger
(
    [](const std::string &aMessage)
    {
        std::ostringstream stringStream;
        
        stringStream << "D/" << aMessage << std::endl;
        
        std::clog << stringStream.str();
    }
);

Logger Logger::s_gdkErrorLogger
(
    [](const std::string &aMessage)
    {
        std::ostringstream stringStream;
        
        stringStream << "E/" << aMessage << std::endl;
        
        std::clog << stringStream.str();
    }
);

Logger::Logger(const std::function<void(const std::string &)> &aLoggingBehaviourCallback)
: m_LoggingBehaviourCallback
(
    aLoggingBehaviourCallback == nullptr? [](const std::string &aMessage)
    {
        std::clog << aMessage << std::endl;
    }
    : aLoggingBehaviourCallback
)
{}
