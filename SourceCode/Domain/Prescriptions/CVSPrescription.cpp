#include <memory>

#include "Domain/Prescriptions/CVSPrescription.hpp"

#include "TechnicalServices/Logging/SimpleLogger.hpp"

namespace Domain::Prescriptions{
    CVSPresctiption::CVSPresctiption():
    _loggerPtr(std::make_unique<TechnicalServices::Logging::SimpleLogger>())
    {
        _logger << "CVS Prescription service has been successfully initialized.";
    }

    void CVSPresctiption::newPrescription(){
        //Call to external service to create prescription
        _logger << "CVS has accepted the prescription.";
    }
}