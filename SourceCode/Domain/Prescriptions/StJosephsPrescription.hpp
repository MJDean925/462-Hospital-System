#pragma once

#include <memory>
#include <string>

#include "Domain/Prescriptions/PrescriptionHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::Prescriptions{
    class StJosephsPrescription : public Domain::Prescriptions::PrescriptionHandler{
        public:
            using PrescriptionHandler::PrescriptionHandler;
            StJosephsPrescription();

            //Operations
            void newPrescription(std::string pName, std::string presc) override;

            //Destructors
            ~StJosephsPrescription() noexcept override;
        private:
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
    };

    inline StJosephsPrescription::~StJosephsPrescription() noexcept 
    {}
}