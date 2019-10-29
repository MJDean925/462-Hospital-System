#pragma once

#include <vector>
#include <string>

namespace Domain::Records{
    class RecordHandler{
        public:
            //Constructors
            RecordHandler() = default;
            RecordHandler(const RecordHandler & original) = default;
            RecordHandler(RecordHandler && original) = default;

            //Operations
            //Virtual function needs a default implementation otherwise would need to be defined in derived classes even if unused there
            virtual std::vector<std::string> requestNewRecord() {}
            virtual void createNewRecord(std::string pName, std::string dName, std::string pTestimony, std::string diag, std::string treatment, std::string ref, std::string presc, tm inDate, tm outDate, std::string output) {} 
            virtual std::vector<std::string> requestNewAppointment() {}
            virtual void createNewAppointment(std::string pName, std::string dName, tm appTime, std::string pTestimony, std::string output) {}

            //Destructor
            virtual ~RecordHandler() noexcept = 0;

            protected:
                RecordHandler & operator=(const RecordHandler & rhs) = default;
                RecordHandler & operator=(RecordHandler && rhs) = default;
    };

    inline RecordHandler::~RecordHandler() noexcept
    {}
}