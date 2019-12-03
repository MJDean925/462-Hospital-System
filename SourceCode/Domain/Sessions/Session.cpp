#include <memory>
#include <stdexcept>
#include <string>

#include "../../Domain/Sessions/Session.hpp"
#include "../../Domain/Sessions/DoctorSession.hpp"
#include "../../Domain/Sessions/ReceptionistSession.hpp"
#include "../../Domain/Sessions/AnalystSession.hpp"

namespace Domain::Sessions{
    std::unique_ptr<SessionHandler> SessionHandler::createSession(const std::string & role){
        if (role == "Doctor")
            return std::make_unique<Domain::Sessions::DoctorSession>();
        else if (role == "Receptionist")
            return std::make_unique<Domain::Sessions::ReceptionistSession>();
        else if (role == "Analyst")
            return std::make_unique<Domain::Sessions::AnalystSession>();
        else
        {
            //Catch an incorrect role, but should never get here
            throw std::logic_error("Invalid role requested in function " + std::string(__func__));
        }
    }
}