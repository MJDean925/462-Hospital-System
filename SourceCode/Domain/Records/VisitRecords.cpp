#include <memory>

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
    void VisitRecords::createNewRecord(){
        TechnicalServices::Persistence::VisitRecords v = {};
        _persistentData->addRecord(v);
    }
}