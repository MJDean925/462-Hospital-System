#include <memory>
#include <vector>
#include <string>
#include <ctime>

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
    std::vector<std::string> VisitRecords::requestNewRecord(){
        return {"Patient Name", "Doctor Name", "Patient Testimony", "Diagnosis", "Treatment Plan", "Referral", "Prescription", "In Time", "Out Time", "Export"};
    }

    void VisitRecords::createNewRecord(std::string pName, std::string dName, std::string pTestimony, std::string diag, std::string treatment, std::string ref, std::string presc, tm inDate, tm outDate, std::string output){
        TechnicalServices::Persistence::VisitRecords v = {pName, dName, inDate, outDate, pTestimony, diag, treatment, ref, presc};
        _persistentData->addRecord(v);
        if (output == "Y" || output == "y"){
            //Code to print to a file
        }
        _logger << "Visit record created successfully";
        //_persistentData->debugVisits();
    }

    std::vector<TechnicalServices::Persistence::VisitRecords> VisitRecords::getRecords(int size) {
        return _persistentData->getRecentVisitRecords(size);
    }
}