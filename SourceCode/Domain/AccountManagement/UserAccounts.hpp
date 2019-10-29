#pragma once

#include <memory>
#include <string>

#include "Domain/AccountManagement/AccountManagementHandler.hpp"

#include "TechnicalServices/Persistence/PersistenceHandler.hpp"
#include "TechnicalServices/Logging/LoggerHandler.hpp"

namespace Domain::AccountManagement{
    class UserAccounts : public Domain::AccountManagement::AccountManagementHandler{
        public:
            using AccountManagementHandler::AccountManagementHandler;
            UserAccounts();

            //Operations
            bool isAuthenticated (const UserCredentials & credentials) override;
            std::string getRole(const std::string & name) override;

            //Destructor
            ~UserAccounts() noexcept override;

        private:
            std::unique_ptr<TechnicalServices::Persistence::PersistenceHandler> _persistentData;
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;

            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
    };
}