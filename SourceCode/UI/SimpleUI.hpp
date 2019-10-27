#pragma once

#include <memory>

#include "Domain/AccountManagement/AccountManagementHandler.hpp"
#include "Domain/Records/RecordHandler.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Persistence/PersistenceHandler.hpp"

#include "UI/UserInterfaceHandler.hpp"

namespace UI
{
    class SimpleUI : public UI::UserInterfaceHandler
    {
        public:
            //Constructors
            using UserInterfaceHandler::UserInterfaceHandler;
            SimpleUI();

            //Operations
            void launch() override;

            //Destructor
            ~SimpleUI() noexcept override;

        private:
            std::unique_ptr<Domain::Records::RecordHandler> _visitRecords;
            std::unique_ptr<Domain::Records::RecordHandler> _appointmentRecords;
            std::unique_ptr<Domain::AccountManagement::AccountManagementHandler> _accounts;
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;
            std::unique_ptr<TechnicalServices::Persistence::PersistenceHandler> _persistentData;
            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
    };
}