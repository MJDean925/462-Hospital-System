#include <memory>

#include "Domain/AccountManagement/UserAccounts.hpp"

#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"

namespace Domain::AccountManagement{
    UserAccounts::UserAccounts():
    _persistentData(std::make_unique<TechnicalServices::Persistence::SimpleDB>()),
    _loggerPtr(std::make_unique<TechnicalServices::Logging::SimpleLogger>())
    {
        _logger << "UserAccounts has been successfully initialized";
    }

    UserAccounts::~UserAccounts() noexcept{
        _logger << "UserAccounts shutdown successfully";
    }

    bool UserAccounts::isAuthenticated(const UserCredentials & credentials){
        try{
            UserCredentials credentialsFromDB = _persistentData->findCredentialsByName(credentials.userName);
            if (credentials.userName == credentialsFromDB.userName &&
                credentials.passPhrase == credentialsFromDB.passPhrase){
                    return true;
                }
        }
        catch (const TechnicalServices::Persistence::PersistenceHandler::NoSuchUser &) {}
        return false;
    }
}