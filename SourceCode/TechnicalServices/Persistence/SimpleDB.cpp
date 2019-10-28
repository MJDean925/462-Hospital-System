#include <string>
#include <vector>
#include <memory>
#include <ctime>

#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace TechnicalServices::Persistence
{
    SimpleDB::SimpleDB()
    : _loggerPtr (std::make_unique<TechnicalServices::Logging::SimpleLogger>())
    {
        UserCredentials tmp = {"DoctorAccount", "password", "Doctor"};
        _users.push_back(tmp);
        tmp = {"ReceptionistAccount", "password", "Receptionist"};
        _users.push_back(tmp);
        tmp = {"AnalystAccount", "password", "Analyst"};
        _users.push_back(tmp);
        tm inTime;
        tm outTime;
        VisitRecords t = {"Name", "Doctor", inTime, outTime, "Testimony", "Diagnosis", "Treatment", "Referral", "Prescription"};
        _visitRecords.push_back(t);
        _logger << "Simple DB has been successfully initialized";
    }

    SimpleDB::~SimpleDB() noexcept
    {
        _logger << "Simple DB shutdown successfully";
    }

    std::vector<std::string> SimpleDB::findRoles()
    {
        return {"Doctor", "Receptionist", "Analyst"};
    }

    UserCredentials SimpleDB::findCredentialsByName( const std::string & name)
    {
        for (const auto & user : _users) if (user.userName == name) return {user.userName, user.passPhrase, user.role};
        std::string message = __func__;
        message += " attemt to find user \"" + name + "\" failed";
        _logger <<message;
        throw PersistenceHandler::NoSuchUser(message);
    }

    void SimpleDB::addRecord(const VisitRecords & v){
        _visitRecords.push_back(v);
    }
}