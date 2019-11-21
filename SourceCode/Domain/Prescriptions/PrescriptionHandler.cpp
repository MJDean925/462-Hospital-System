#include <memory> 
#include <string>

#include "Domain/Prescriptions/PrescriptionHandler.hpp"

#include "Domain/Prescriptions/CVSPrescription.hpp"
#include "Domain/Prescriptions/StJosephsPrescription.hpp"

namespace Domain::Prescriptions{
    std::unique_ptr<PrescriptionHandler> PrescriptionHandler::newService(){
        std::string type = "CVS";

        if (type == "CVS") return std::make_unique<Domain::Prescriptions::CVSPresctiption>();
        else if (type == "St Josephs") return std::make_unique<Domain::Prescriptions::StJosephsPrescription>();
    }
}