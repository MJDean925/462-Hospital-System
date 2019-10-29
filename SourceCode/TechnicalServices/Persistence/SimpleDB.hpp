#pragma once

#include <memory>
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace TechnicalServices::Persistence
{
    class SimpleDB : public TechnicalServices::Persistence::PersistenceHandler
    {
        public:
            using PersistenceHandler::PersistenceHandler; //Inherit constructors
            SimpleDB();

            //Operations
            std::vector<std::string> findRoles() override;
            UserCredentials findCredentialsByName(const std::string & name) override;
            void addRecord(const VisitRecords & v);
            void debugVisits();

            //Destructor
            ~SimpleDB() noexcept override;

        private:
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;
            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
            std::vector<VisitRecords> _visitRecords;
            std::vector<AppointmentRecords> _appRecords;
            std::vector<UserCredentials> _users;
            void initializeData();
    };//Class SimpleDB


}