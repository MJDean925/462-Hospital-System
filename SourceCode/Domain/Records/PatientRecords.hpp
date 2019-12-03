#pragma once

#include <vector>
#include <memory>

#include "../../Domain/Records/RecordHandler.hpp"

#include "../../TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "../../TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::Records{
    class PatientRecords : public Domain::Records::RecordHandler{
        public:
            using RecordHandler::RecordHandler;
            PatientRecords();

            //Operations
            std::vector<TechnicalServices::Persistence::PatientRecord> getPRecords() override;

            //Destructor
            ~PatientRecords() noexcept override;

        private:
            std::unique_ptr<TechnicalServices::Persistence::PersistenceHandler> _persistentData;
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
    };
}