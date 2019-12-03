#include <vector>
#include <memory>

#include "../../Domain/Records/PatientRecords.hpp"

#include "../../TechnicalServices/Logging/SimpleLogger.hpp"
#include "../../TechnicalServices/Persistence/SimpleDB.hpp"

namespace Domain::Records{
    PatientRecords::PatientRecords():
    _persistentData(std::make_unique<TechnicalServices::Persistence::SimpleDB>()),
    _loggerPtr(std::make_unique<TechnicalServices::Logging::SimpleLogger>())
    {
        _logger << "Patient Records has been successfully initialized.";
    }
    PatientRecords::~PatientRecords() noexcept{
        _logger << "Patient Records shutdown successfully.";
    }

    //Operations
    std::vector<TechnicalServices::Persistence::PatientRecord> PatientRecords::getPRecords(){
        return _persistentData->getAllPatientRecords();
    }
}