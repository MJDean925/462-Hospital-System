#include <memory>

#include "Domain/Records/AppointmentRecords.hpp"

#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"

namespace Domain::Records{
    AppointmentRecords::AppointmentRecords():
    _persistentData(std::make_unique<TechnicalServices::Persistence::SimpleDB>()),
    _loggerPtr(std::make_unique<TechnicalServices::Logging::SimpleLogger>())
    {
        _logger << "Appointment Records has been successfully initialized";
    }

    AppointmentRecords::~AppointmentRecords() noexcept{
        _logger << "Appointment Records shutdown successfully";
    }
}