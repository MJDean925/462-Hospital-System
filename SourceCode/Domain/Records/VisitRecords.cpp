#include <memory>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

#include "Domain/Records/VisitRecords.hpp"

#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"

namespace Domain::Records{
    VisitRecords::VisitRecords():
    _persistentData(std::make_unique<TechnicalServices::Persistence::SimpleDB>()),
    _loggerPtr(std::make_unique<TechnicalServices::Logging::SimpleLogger>())
    {
        _logger << "Visit Records has been successfully initialized";
    }

    VisitRecords::~VisitRecords() noexcept{
        _logger << "Visit Records shutdown successfully";
    }

    //Operations
    std::vector<std::string> VisitRecords::requestNew(){
        return {"Patient Name", "Doctor Name", "Patient Testimony", "Diagnosis", "Treatment Plan", "Referral", "Prescription", "In Time", "Out Time", "Export"};
    }

    void VisitRecords::createNew(std::string pName, std::string dName, std::string pTestimony, std::string diag, std::string treatment, std::string ref, std::string presc, tm inDate, tm outDate, std::string output){
        TechnicalServices::Persistence::VisitRecords v = {pName, dName, inDate, outDate, pTestimony, diag, treatment, ref, presc};
        _persistentData->addRecord(v);
        if (output == "Y" || output == "y"){
            //Code to print to a file
        }
        _logger << "Visit record created successfully";
        //_persistentData->debugVisits();
    }

    std::vector<TechnicalServices::Persistence::VisitRecords> VisitRecords::getRecordsByRange(int beginMonth, int beginYear, int endMonth, int endYear) {
        std::vector<TechnicalServices::Persistence::VisitRecords> allRecords =  _persistentData->getAllVisitRecords();

        tm beginDate = { 0, 0, 0, 0, beginMonth - 1, beginYear - 1900, 0, 0, 0 };
        tm endDate = { 0, 0, 0, 0, endMonth - 1, endYear - 1900, 0, 0, 0 };

        std::vector<TechnicalServices::Persistence::VisitRecords> records;
        std::copy_if(allRecords.begin(), allRecords.end(), std::back_inserter(records), [beginDate, endDate](TechnicalServices::Persistence::VisitRecords r) mutable {
            return ( (difftime(mktime(&endDate), mktime(&r.inDate)) > 0.0) && (difftime(mktime(&r.inDate), mktime(&beginDate)) > 0.0) );
        });
        return records;
    }

    std::vector<TechnicalServices::Persistence::VisitRecords> VisitRecords::getRecords(int size) {
        return _persistentData->getRecentVisitRecords(size);
    }
}