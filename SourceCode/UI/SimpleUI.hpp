#pragma once

#include <memory>

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
            std::unique_ptr<TechnicalServices::Logging::LoggerHandler> _loggerPtr;
            std::unique_ptr<TechnicalServices::Persistence::PersistenceHandler> _persistentData;

            TechnicalServices::Logging::LoggerHandler & _logger = *_loggerPtr;
    };
}