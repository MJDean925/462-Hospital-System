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
            void addRecord(const VisitRecord & v) override;
            void addAppointment(const AppointmentRecord & a) override;
            void debugVisits() override;
            void debugApp() override;
            std::vector<VisitRecord> getRecentVisitRecords(int size) override;
            std::vector<VisitRecord> getAllVisitRecords() override;
            std::vector<PatientRecord> getAllPatientRecords() override;
            std::vector<AppointmentRecord> getAllAppRecords() override;

            //Destructor
            ~SimpleDB() noexcept override;

        private:
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;
            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
            std::vector<VisitRecord> _visitRecords;
            std::vector<AppointmentRecord> _appRecords;
            std::vector<UserCredentials> _users;
            std::vector<PatientRecord> _patients;
            void initializeData();
    };//Class SimpleDB


}