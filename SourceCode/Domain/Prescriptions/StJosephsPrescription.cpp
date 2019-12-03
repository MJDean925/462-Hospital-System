#include <memory>
#include <string>

#include "../../Domain/Prescriptions/StJosephsPrescription.hpp"

#include "../../TechnicalServices/Logging/SimpleLogger.hpp"

namespace Domain::Prescriptions{
    StJosephsPrescription::StJosephsPrescription():
    _loggerPtr(std::make_unique<TechnicalServices::Logging::SimpleLogger>())
    {
        _logger << "St Joseph's Prescription service has been successfully initialized.";
    }

    void StJosephsPrescription::newPrescription(std::string pName, std::string presc){
        //Call to external service to create prescription
        _logger << "St Joseph's has accepted the prescription of " + presc + " for " + pName;
    }
}