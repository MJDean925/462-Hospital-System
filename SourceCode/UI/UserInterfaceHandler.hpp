#pragma once

namespace UI
{
    class UserInterfaceHandler
    {
        public:
            //Constructors
            UserInterfaceHandler() = default;
            UserInterfaceHandler(const UserInterfaceHandler & original) = default;
            UserInterfaceHandler( UserInterfaceHandler && original) = default;

            //Operations
            virtual void launch() = 0;

            //Destructor
            virtual ~UserInterfaceHandler() noexcept = 0;

        protected:
            UserInterfaceHandler & operator=(const UserInterfaceHandler & rhs) = default;
            UserInterfaceHandler & operator=(UserInterfaceHandler && rhs) = default;

    };

    inline UserInterfaceHandler::~UserInterfaceHandler() noexcept
    {}
}