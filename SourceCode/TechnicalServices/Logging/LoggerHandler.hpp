#pragma once

#include <iostream>
#include <string>

namespace TechnicalServices::Logging
{
    class LoggerHandler
    {
        public:
            //Constructors
            LoggerHandler(std::ostream & loggingStream = std::clog);
            LoggerHandler(const LoggerHandler & original) = default;
            LoggerHandler(LoggerHandler && original) = default;

            //Operations
            virtual LoggerHandler & operator<< (const std::string & message) = 0;

            //Destructor
            virtual ~LoggerHandler() noexcept = 0;

        protected:
            LoggerHandler & operator=(const LoggerHandler & rhs) = delete;
            LoggerHandler & operator=(LoggerHandler && rhs) = delete;

            std::ostream & _loggingStream;
    };

    inline LoggerHandler::~LoggerHandler() noexcept
    {}

    inline LoggerHandler::LoggerHandler(std::ostream & loggingStream)
    : _loggingStream(loggingStream)
    {}
    
}