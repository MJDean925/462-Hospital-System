#include <string>
#include <vector>
#include <memory>
#include <ctime>

#include "TechnicalServices/Persistence/SimpleDB.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace TechnicalServices::Persistence
{
    SimpleDB::SimpleDB()
    : _loggerPtr (std::make_unique<TechnicalServices::Logging::SimpleLogger>())
    {
        initializeData();
        _logger << "Simple DB has been successfully initialized";
    }

    SimpleDB::~SimpleDB() noexcept
    {
        _logger << "Simple DB shutdown successfully";
    }

    std::vector<std::string> SimpleDB::findRoles()
    {
        return {"Doctor", "Receptionist", "Analyst"};
    }

    UserCredentials SimpleDB::findCredentialsByName( const std::string & name)
    {
        for (const auto & user : _users) if (user.userName == name) return {user.userName, user.passPhrase, user.role};
        std::string message = __func__;
        message += " attemt to find user \"" + name + "\" failed";
        _logger <<message;
        throw PersistenceHandler::NoSuchUser(message);
    }

    void SimpleDB::initializeData() {
        _users = { 
            {"DoctorAccount", "password", "Doctor"},
            {"ReceptionistAccount", "password", "Receptionist"},
            {"AnalystAccount", "password", "Analyst"}
        };

        std::time_t t = std::time(0);   // get time now
        std::tm* now = std::localtime(&t);
        tm inTime = *now;
        tm outTime = *now;

        // tm testing
        // std::cout << "inTime initialized to " << inTime.tm_mon << " " << inTime.tm_mday << " " << inTime.tm_hour << " " << inTime.tm_min << " " << inTime.tm_sec;
        // std::cout << "outTime initialized to " << outTime.tm_mon << " " << outTime.tm_mday << " " << outTime.tm_hour << " " << outTime.tm_min << " " << outTime.tm_sec;

        _visitRecords = { 
            // Name, Doctor, inTime, outTime, Testimony, Diagnosis, Treatment, Referral, Prescription
            {"Alex Jones", "Dr. Brown", inTime, outTime, "Experiencing itching, burning sensation and redness in eyes. Vision deteriorating at times.", "Conjuctivitis", "Prescribed antibiotic eye drops", "", "Antibiotic eye drops"},
            {"Peter Parker", "Dr. Phillips", inTime, outTime, "Frequent bowel movements, cramping in the abdomen.", "Diarrhea", "Treatment", "", ""},
            {"Walter White", "Dr. Belknap", inTime, outTime, "While working at the car wash, experienced intense coughing and then suddenly passed out.", "Lung Cancer", "Ongoing chemotherapy", "", ""},
            {"Linus Torvalds", "Dr. Adams", inTime, outTime, "Testimony", "Mononucleosis", "Treatment", "", ""},
            {"Donald Trump", "Dr. Barry", inTime, outTime, "Testimony", "Conjuctivitis", "Prescribed antibiotic eye drops", "", ""},
            {"Barack Obama", "Dr. Chapman", inTime, outTime, "Testimony", "Flu", "Treatment", "", ""},
            {"Alec Baldwin", "Dr. Brown", inTime, outTime, "Testimony", "Diarrhea", "Treatment", "", ""},
            {"Taylor Swift", "Dr. Phillips", inTime, outTime, "Testimony", "Conjuctivitis", "", "", ""},
            {"Ron Swanson", "Dr. Adams", inTime, outTime, "Testimony", "Mononucleosis", "Treatment", "", ""},
            {"Alex Jones", "Dr. Barry", inTime, outTime, "Hay fever", "Allergies", "Treatment", "", ""},
            {"Anthony Fantano", "Dr. Chapman", inTime, outTime, "Testimony", "Flu", "Treatment", "", ""},
            {"Mark Zuckerberg", "Dr. Brown", inTime, outTime, "Testimony", "Mononucleosis", "Treatment", "", ""},
            {"Kanye West", "Dr. Phillips", inTime, outTime, "Testimony", "Conjuctivitis", "", "", ""},
            {"Dennis Ritchie", "Dr. Adams", inTime, outTime, "Testimony", "Flu", "Treatment", "", ""},
            {"Jon Snow", "Dr. Barry", inTime, outTime, "Testimony", "Flu", "Treatment", "", ""}
        };

        // edit dates (doesn't work for some reason)
        // for(int i = 0; i < _visitRecords.size(); i++) {
        //     int randomSeed = 145678;
        //     tm newInTime = inTime;
        //     tm newOutTime = outTime;
            
        //     newInTime.tm_mon = newOutTime.tm_mon = (inTime.tm_mon - (i / 4)) % 12;
        //     newInTime.tm_mday = newOutTime.tm_mday = randomSeed / i % 28;
            
        //     _visitRecords[i].inDate = newInTime;
        //     _visitRecords[i].outDate = newOutTime;
        // }
        _logger << "Simple DB has been successfully initialized";
    }

    void SimpleDB::addRecord(const VisitRecords & v){
        _visitRecords.push_back(v);
    }

    void SimpleDB::addAppointment(const AppointmentRecords & a){
        _appRecords.push_back(a);
    }

    void SimpleDB::debugVisits(){
        for (unsigned int i = 0; i < _visitRecords.size(); i++){
            std::cout << _visitRecords[i].patientName << "\n " << asctime(&_visitRecords[i].inDate) << " " << asctime(&_visitRecords[i].outDate);
        }
    }

    void SimpleDB::debugApp(){
        for (unsigned int i = 0; i < _appRecords.size(); i++){
            std::cout << _appRecords[i].patientName << "\n " << asctime(&_appRecords[i].date);
        }
    }

    std::vector<VisitRecords> SimpleDB::getRecentVisitRecords(int size) {
        std::vector<VisitRecords> records = _visitRecords;
        records.erase(records.begin(), records.end() - size);
        return records;
    }

    std::vector<VisitRecords> SimpleDB::getAllVisitRecords() {
        return _visitRecords;
    }


}