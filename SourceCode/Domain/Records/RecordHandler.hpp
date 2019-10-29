#pragma once

namespace Domain::Records{
    class RecordHandler{
        public:
            //Constructors
            RecordHandler() = default;
            RecordHandler(const RecordHandler & original) = default;
            RecordHandler(RecordHandler && original) = default;

            //Operations
            virtual void createNewRecord() = 0;

            //Destructor
            virtual ~RecordHandler() noexcept = 0;

            protected:
                RecordHandler & operator=(const RecordHandler & rhs) = default;
                RecordHandler & operator=(RecordHandler && rhs) = default;
    };

    inline RecordHandler::~RecordHandler() noexcept
    {}
}