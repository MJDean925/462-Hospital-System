#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Domain/Sessions/Session.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"

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
            std::unique_ptr<TechnicalServices::Persistence::PersistenceHandler> _pData;
    };

    inline DoctorSession::~DoctorSession() noexcept
    {}

    inline DoctorSession::DoctorSession():
    _pData (std::make_unique<TechnicalServices::Persistence::SimpleDB>()){}

    inline std::vector<std::string> DoctorSession::getCommands(){
        return {"Create Record", "View All Records", "Logout", "Shutdown"};
    }
}