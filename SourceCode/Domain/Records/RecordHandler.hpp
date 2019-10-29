#pragma once

namespace Domain::Records{
    class RecordHandler{
        public:
            //Constructors
            RecordHandler() = default;
            RecordHandler(const RecordHandler & original) = default;
            RecordHandler(RecordHandler && original) = default;

            //Operations
            //Virtual function needs a default implementation otherwise would need to be defined in derived classes even if unused there
            virtual void requestNewRecord() {}
            virtual void createNewRecord() {} 
            virtual void requestNewAppointment() {}
            virtual void createNewAppointment() {}

            //Destructor
            virtual ~RecordHandler() noexcept = 0;

            protected:
                RecordHandler & operator=(const RecordHandler & rhs) = default;
                RecordHandler & operator=(RecordHandler && rhs) = default;
    };

    inline RecordHandler::~RecordHandler() noexcept
    {}
}