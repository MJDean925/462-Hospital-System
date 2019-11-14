#pragma once

namespace Domain::Prescriptions{
    class PrescriptionHandler{
        public:
            PrescriptionHandler() = default;
            PrescriptionHandler(const PrescriptionHandler & original) = default;
            PrescriptionHandler(PrescriptionHandler && original) = default;

            //Operations
            virtual void newPrescription() = 0;

            //Destructor
            virtual ~PrescriptionHandler() noexcept = 0;

        protected:
            PrescriptionHandler & operator=(const PrescriptionHandler & rhs) = default;
            PrescriptionHandler & operator=(PrescriptionHandler && rhs) = default;
    };

    inline PrescriptionHandler::~PrescriptionHandler() noexcept 
    {}
}