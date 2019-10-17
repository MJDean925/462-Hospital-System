#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"

#include "UI/SimpleUI.hpp"

namespace UI
{
    SimpleUI::SimpleUI()
    : _loggerPtr (std::make_unique<TechnicalServices::Logging::SimpleLogger>()),
    _persistentData (std::make_unique<TechnicalServices::Persistence::SimpleDB>())
    {
        _logger << "Simple UI has been successfully initialized";
    }

    SimpleUI::~SimpleUI() noexcept
    {
        _logger << "Simple UI shutdown successfully";
    }

    //Operations
    void SimpleUI::launch()
    {
        std::vector<std::string> roles = _persistentData->findRoles();
        std::cout << roles[0];
    }
}