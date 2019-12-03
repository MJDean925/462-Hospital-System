#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../../Domain/Sessions/Session.hpp"
#include "../../TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "../../TechnicalServices/Persistence/SimpleDB.hpp"

namespace Domain::Sessions{
    class DoctorSession : public Domain::Sessions::SessionHandler{
        public:
            //Constructors
            using SessionHandler::SessionHandler;
            DoctorSession();

            //Operations
            std::vector<std::string> getCommands() override;

            //Destructor
            ~DoctorSession() noexcept override;
        private:
    };

    inline DoctorSession::~DoctorSession() noexcept
    {}

    inline DoctorSession::DoctorSession(){}

    inline std::vector<std::string> DoctorSession::getCommands(){
        return {"Create Record", "Write Prescription", "View All Records", "Logout", "Shutdown"};
    }
}