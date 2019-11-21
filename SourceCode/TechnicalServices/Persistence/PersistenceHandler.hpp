#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <ctime>

namespace TechnicalServices::Persistence
{
    struct UserCredentials
    {
        std::string         userName;
        std::string         passPhrase;
        std::string         role;
    };

    //Add structs for Analyst, Receptionist, Patients

    struct Record{

    };

    struct VisitRecord
    {
        std::string         patientName;
        std::string         doctorName;
        tm                  inDate;
        tm                  outDate;
        std::string         patientTestimony;
        std::string         diagnosis;
        std::string         treatmentPlan;
        std::string         referral;
        std::string         prescription;
        //int                 ID;
    };

    struct AppointmentRecord
    {
        std::string         patientName;
        std::string         doctorName;
        tm                  date;
        std::string         patientTestimony;
    };

    struct PatientRecord
    {
        std::string         Name;
        std::string         Address;
        std::string         Insurance;
        std::string         PreferredPharmacy;
        //std::vector<int>    VisitRecordIDs;
    };

    class PersistenceHandler{
        public:
            struct NoSuchUser : std::domain_error {using domain_error::domain_error;};
            //Constructors
            PersistenceHandler()    = default;
            PersistenceHandler(const PersistenceHandler & original) = default;
            PersistenceHandler( PersistenceHandler && original) = default;

            //Operations
            virtual std::vector<std::string> findRoles() = 0;
            virtual UserCredentials findCredentialsByName( const std::string & name) = 0;
            virtual void addRecord(const VisitRecord & v) = 0;
            virtual void addAppointment(const AppointmentRecord & a) = 0;
            virtual void debugVisits() = 0;
            virtual void debugApp() = 0;
            virtual std::vector<VisitRecord> getRecentVisitRecords(int size) = 0;
            virtual std::vector<VisitRecord> getAllVisitRecords() = 0;
            virtual std::vector<PatientRecord> getAllPatientRecords() = 0;
            virtual std::vector<AppointmentRecord> getAllAppRecords() = 0;

            //Destructor
            virtual ~PersistenceHandler() noexcept = 0;

        protected:
            //Copy assignment operators
            PersistenceHandler & operator=(const PersistenceHandler & rhs) = default;
            PersistenceHandler & operator=(PersistenceHandler && rhs) = default;
    };

    inline PersistenceHandler::~PersistenceHandler() noexcept
    {}

}