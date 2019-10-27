#pragma once

#include <memory>
#include <vector>
#include <string>

#include "Domain/Sessions/Session.hpp"

namespace Domain::Sessions{
    class AnalystSession : public Domain::Sessions::SessionHandler{
        public:
            using SessionHandler::SessionHandler;

            //Operations
            std::vector<std::string> getCommands() override;

            //Destructor
            ~AnalystSession() noexcept override;
    };

    inline AnalystSession::~AnalystSession() noexcept
    {}

    inline std::vector<std::string> AnalystSession::getCommands(){
        return {"View Trends", "Logout", "Shutdown"};
    }
}