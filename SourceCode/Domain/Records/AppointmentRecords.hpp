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
            std::vector<std::string> requestNew() override;
            void createNew(std::string pName, std::string dName, tm appTime, std::string pTestimony, std::string output) override;

            //Destructor
            ~AppointmentRecords() noexcept override;

        private:
            std::unique_ptr<TechnicalServices::Persistence::PersistenceHandler> _persistentData;
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
    };
}