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
        initializeData();
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

    void SimpleDB::initializeData() {
        _users = { 
            {"DoctorAccount", "password", "Doctor"},
            {"ReceptionistAccount", "password", "Receptionist"},
            {"AnalystAccount", "password", "Analyst"}
        };

        tm inTime;
        tm outTime;

        _visitRecords = {
            {"Name", "Doctor", inTime, outTime, "Testimony", "Diagnosis", "Treatment", "Referral", "Prescription"}
        };
        _logger << "Simple DB has been successfully initialized";
    }

    void SimpleDB::addRecord(const VisitRecords & v){
        _visitRecords.push_back(v);
    }

    void SimpleDB::debugVisits(){
        for (unsigned int i = 0; i < _visitRecords.size(); i++){
            _logger << _visitRecords[i].patientName + " " + asctime(&_visitRecords[i].inDate) + " " + asctime(&_visitRecords[i].outDate);
        }
    }
}