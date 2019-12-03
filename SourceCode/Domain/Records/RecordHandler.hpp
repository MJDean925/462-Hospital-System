#pragma once

#include <vector>
#include <string>

#include "../../TechnicalServices/Persistence/SimpleDB.hpp"

namespace Domain::Records{
    class RecordHandler{
        public:
            //Constructors
            RecordHandler() = default;
            RecordHandler(const RecordHandler & original) = default;
            RecordHandler(RecordHandler && original) = default;

            //Operations
            //Virtual function needs a default implementation otherwise would need to be defined in derived classes even if unused there
			virtual std::vector<std::string> requestNew() {
				std::vector<std::string> vect{};
				return vect;
			}
			virtual void createNew(std::string pName, std::string dName, std::string pTestimony, std::string diag, std::string treatment, std::string ref, std::string presc, tm inDate, tm outDate, std::string output) {}
				//virtual std::vector<std::string> requestNewAppointment() = 0
			virtual void createNew(std::string pName, std::string dName, tm appTime, std::string pTestimony, std::string output) {}
			virtual std::vector<TechnicalServices::Persistence::VisitRecord> getRecordsByRange(int beginYear, int beginMonth, int endYear, int endMonth) {
				std::vector<TechnicalServices::Persistence::VisitRecord> vect{};
				return vect;
			};
            virtual std::vector<TechnicalServices::Persistence::VisitRecord> getRecords(int size) {
				std::vector<TechnicalServices::Persistence::VisitRecord> vect{};
				return vect;
			};
			virtual std::vector<TechnicalServices::Persistence::VisitRecord> getVRecords() {
				std::vector<TechnicalServices::Persistence::VisitRecord> vect{};
				return vect;
			};
            virtual std::vector<TechnicalServices::Persistence::PatientRecord> getPRecords() {
				std::vector<TechnicalServices::Persistence::PatientRecord> vect{};
				return vect;
			};
            virtual std::vector<TechnicalServices::Persistence::AppointmentRecord> getARecords() {
				std::vector<TechnicalServices::Persistence::AppointmentRecord> vect{};
				return vect;
			};

            //Destructor
            virtual ~RecordHandler() noexcept = 0;

            protected:
                RecordHandler & operator=(const RecordHandler & rhs) = default;
                RecordHandler & operator=(RecordHandler && rhs) = default;
    };

    inline RecordHandler::~RecordHandler() noexcept
    {}
}