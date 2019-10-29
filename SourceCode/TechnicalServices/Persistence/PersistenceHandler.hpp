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

    struct VisitRecords
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
    };

    struct AppointmentRecords
    {
        std::string         patientName;
        std::string         doctorName;
        tm                  date;
        std::string         patientTestimony;
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
            virtual void addRecord(const VisitRecords & v) = 0;
            virtual void addAppointment(const AppointmentRecords & a) = 0;
            virtual void debugVisits() = 0;
            virtual void debugApp() = 0;

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