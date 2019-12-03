#pragma once

#include <memory>
#include <string>

#include "../../Domain/Prescriptions/PrescriptionHandler.hpp"
#include "../../TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::Prescriptions{
    class CVSPresctiption : public Domain::Prescriptions::PrescriptionHandler{
        public:
            using PrescriptionHandler::PrescriptionHandler;
            CVSPresctiption();

            //Operations
            void newPrescription(std::string pName, std::string presc) override;

            //Destructors
            ~CVSPresctiption() noexcept override;
        private:
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
    };

    inline CVSPresctiption::~CVSPresctiption() noexcept 
    {}
}