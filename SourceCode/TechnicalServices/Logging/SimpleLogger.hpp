#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>

#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace TechnicalServices::Logging
{
    class SimpleLogger : public TechnicalServices::Logging::LoggerHandler
    {
        public:
            //Constructors
            using LoggerHandler::LoggerHandler;
            SimpleLogger(std::ostream & logggingStream = std::clog);

            //Operations
            SimpleLogger & operator<< (const std::string & message) override;

            //Destructor
            ~SimpleLogger() noexcept override;
    };

    inline SimpleLogger::SimpleLogger(std::ostream & loggingStream)
    :LoggerHandler(loggingStream)
    {
        loggingStream << std::unitbuf;
        *this << "Simple Logger has been successfully initialized";
    }
    inline SimpleLogger::~SimpleLogger() noexcept
    {
        *this << "Simple Logger shutdown successfully";
    }

    inline SimpleLogger & SimpleLogger::operator<< (const std::string & message)
    {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        #pragma warning(suppress : 4996)
        _loggingStream << std::put_time(std::localtime(&now),"%Y-%m-%d %X" ) << " | ";
        _loggingStream << message << '\n';
        return *this;
    }
}