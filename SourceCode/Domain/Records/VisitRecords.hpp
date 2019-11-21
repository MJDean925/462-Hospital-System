#pragma once

#include <memory>
#include <vector>
#include <string>
#include <ctime>

#include "Domain/Records/RecordHandler.hpp"
#include "Domain/Prescriptions/PrescriptionHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::Records{
    class VisitRecords : public Domain::Records::RecordHandler{
        public:
            using RecordHandler::RecordHandler;
            VisitRecords();

            //Operations
            std::vector<std::string> requestNew() override;
            void createNew(std::string pName, std::string dName, std::string pTestimony, std::string diag, std::string treatment, std::string ref, std::string presc, tm inDate, tm outDate, std::string output) override;
            std::vector<TechnicalServices::Persistence::VisitRecord> getRecordsByRange(int beginYear, int beginMonth, int endYear, int endMonth) override;
            std::vector<TechnicalServices::Persistence::VisitRecord> getRecords(int size) override;
            std::vector<TechnicalServices::Persistence::VisitRecord> getVRecords() override;

            //Destructor
            ~VisitRecords() noexcept override;

        private:
            //std::unique_ptr<Domain::Prescriptions::PrescriptionHandler> _prescriptionService;
            std::unique_ptr<TechnicalServices::Persistence::PersistenceHandler> _persistentData;
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
    };
}