#include <memory> 
#include <string>

#include "Domain/Prescriptions/PrescriptionHandler.hpp"

#include "Domain/Prescriptions/CVSPrescription.hpp"

namespace Domain::Prescriptions{
    std::unique_ptr<PrescriptionHandler> PrescriptionHandler::newService(){
        std::string type = "CVS";

        if (type == "CVS") return std::make_unique<Domain::Prescriptions::CVSPresctiption>();
    }
}