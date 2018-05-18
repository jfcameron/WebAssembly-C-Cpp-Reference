// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 2017-06-29.
#include <gdk/logger.h>

#include <iostream>
#include <string>

using namespace GDK;
using namespace Debug;

Logger Logger::s_GDKLogger
(
    [](const std::string &aMessage)
    {
        std::clog << "D/" << aMessage << std::endl;
    }
);

Logger Logger::s_GDKErrorLogger
(
    [](const std::string &aMessage)
    {
        std::cerr << "E/" << aMessage << std::endl;
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
