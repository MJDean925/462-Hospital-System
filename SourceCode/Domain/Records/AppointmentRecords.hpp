#pragma once

#include <memory>

#include "Domain/Records/RecordHandler.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::Records{
    class AppointmentRecords : public Domain::Records::RecordHandler{
        public:
            using RecordHandler::RecordHandler;
            AppointmentRecords();

            //Operations
            void createNewRecord() override {}

            //Destructor
            ~AppointmentRecords() noexcept override;

        private:
            std::unique_ptr<TechnicalServices::Persistence::PersistenceHandler> _persistentData;
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
    };
}