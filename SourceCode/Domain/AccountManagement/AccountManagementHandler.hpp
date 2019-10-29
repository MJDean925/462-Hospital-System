#pragma once

#include <string>

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

namespace Domain::AccountManagement{
    using TechnicalServices::Persistence::UserCredentials;

    class AccountManagementHandler{
        public:
            //Constructors
            AccountManagementHandler() = default;
            AccountManagementHandler(const AccountManagementHandler & original) = default;
            AccountManagementHandler(AccountManagementHandler && original) = default;

            //Operations
            virtual bool isAuthenticated( const UserCredentials & credentials) = 0;
            virtual std::string getRole(const std::string & name) = 0;

            //Destructor
            virtual ~AccountManagementHandler() noexcept = 0;

        protected:
            AccountManagementHandler & operator=(const AccountManagementHandler & rhs) = default;
            AccountManagementHandler & operator=(AccountManagementHandler && rhs) = default;
    };

    inline AccountManagementHandler::~AccountManagementHandler() noexcept
    {}
}