#include <memory>
#include <ctime>

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

    //Operations
    std::vector<std::string> AppointmentRecords::requestNew(){
        return {"Patient Name", "Doctor Name", "Appointment Time (MM/DD/YYYY HH:MM 24h Format)", "Patient Testimony", "Export"};
    }

    void AppointmentRecords::createNew(std::string pName, std::string dName, tm appTime, std::string pTestimony, std::string output){
        TechnicalServices::Persistence::AppointmentRecord a = {pName, dName, appTime, pTestimony};
        _persistentData->addAppointment(a);
        if (output == "Y" || output == "y"){
            //Export to file
        }
        _logger << "Appointment created successfully";
        //_persistentData->debugApp();
    }

    std::vector<TechnicalServices::Persistence::AppointmentRecord> AppointmentRecords::getARecords(){
        return _persistentData->getAllAppRecords;
    }
}