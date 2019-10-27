#pragma once

#include <memory>

#include "Domain/Records/RecordHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::Records{
    class VisitRecords : public Domain::Records::RecordHandler{
        public:
            using RecordHandler::RecordHandler;
            VisitRecords();

            //Operations
            //None yet

            //Destructor
            ~VisitRecords() noexcept override;

        private:
            std::unique_ptr<TechnicalServices::Persistence::PersistenceHandler> _persistentData;
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
    };
}