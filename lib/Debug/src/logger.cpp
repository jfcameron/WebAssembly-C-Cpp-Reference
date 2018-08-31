// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/logger.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using namespace gdk;

Logger Logger::s_gdkLogger
(
    [](const std::string &aMessage)
    {
        using namespace std::chrono;
        
        milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        
        std::ostringstream stringStream;
        
        stringStream << "Epoch " << ms.count() << " Thread " << std::this_thread::get_id() << " D/" << aMessage << std::endl;
        
        std::clog << stringStream.str();
    }
);

Logger Logger::s_gdkErrorLogger
(
    [](const std::string &aMessage)
    {
        using namespace std::chrono;
        
        milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        
        std::ostringstream stringStream;
        
        stringStream << "Epoch " << ms.count() << " Thread " << std::this_thread::get_id() << " E/" << aMessage << std::endl;
        
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
