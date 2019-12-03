#pragma once

#include <memory>
#include <vector>
#include <string>

#include "../../Domain/Sessions/Session.hpp"

namespace Domain::Sessions{
    class ReceptionistSession : public Domain::Sessions::SessionHandler{
        public:
            using SessionHandler::SessionHandler;

            //Operations
            std::vector<std::string> getCommands() override;

            //Destructor
            ~ReceptionistSession() noexcept override;
    };

    inline ReceptionistSession::~ReceptionistSession() noexcept
    {}

    inline std::vector<std::string> ReceptionistSession::getCommands(){
        return {"Create Appointment", "Logout", "Shutdown"};
    }
}