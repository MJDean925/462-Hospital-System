#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Domain::Sessions{
    class SessionHandler{
        public:
            //Constructors
            SessionHandler() = default;
            SessionHandler(const SessionHandler & original) = default;
            SessionHandler(SessionHandler && original) = default;

            //Operations
            virtual std::vector<std::string> getCommands() = 0; //Retrieve list of available commands

            //Session creator, returns a smart pointer for the session being created
            static std::unique_ptr<SessionHandler> createSession(const std::string & role);

            //Destructors
            virtual ~SessionHandler() noexcept = 0;

        protected:
            //Copy assignments
            SessionHandler & operator=(const SessionHandler & rhs) = default;
            SessionHandler & operator=(SessionHandler && rhs) = default;
    };

    inline SessionHandler::~SessionHandler() noexcept
    {}

}