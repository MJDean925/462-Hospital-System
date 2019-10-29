#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "Domain/Sessions/Session.hpp"
#include "Domain/AccountManagement/UserAccounts.hpp"
#include "Domain/Records/VisitRecords.hpp"
#include "Domain/Records/AppointmentRecords.hpp"

#include "TechnicalServices/Logging/LoggerHandler.hpp"
#include "TechnicalServices/Logging/SimpleLogger.hpp"
#include "TechnicalServices/Persistence/SimpleDB.hpp"

#include "UI/SimpleUI.hpp"

namespace UI
{
    SimpleUI::SimpleUI()
    : _loggerPtr (std::make_unique<TechnicalServices::Logging::SimpleLogger>()),
    _accounts(std::make_unique<Domain::AccountManagement::UserAccounts>()),
    _visitRecords(std::make_unique<Domain::Records::VisitRecords>()),
    _appointmentRecords(std::make_unique<Domain::Records::AppointmentRecords>())
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
        /*
        //Test code to ensure sessions are created properly, for now they create own pData, delete that later
        std::cout << "Creating Doctor Session\n";
        std::unique_ptr<Domain::Sessions::SessionHandler> sessionControl = Domain::Sessions::SessionHandler::createSession("Doctor");
        std::cout << "Getting roles...\n";
        std::vector<std::string> roles = sessionControl->getCommands();
        std::cout << roles[0] << " " << roles[1] << " " << roles[2] << "\n";
        std::cout << "Finished\n";
        */
        bool running = true;
        bool loggedIn = false;
        std::string uName;
        std::string pWord;
        std::string role;
        std::vector<std::string> commands;
        unsigned int selection;
        std::string selectedCommand;
        do{
            std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
 
            std::cout << "   Username:   ";
            std::getline(std::cin, uName);
            std::cout << "   Password:   ";
            std::getline(std::cin, pWord);

            if (_accounts->isAuthenticated({uName, pWord, ""})){
                _logger << "Login successful for \"" + uName + "\"";
                loggedIn = true;
                role = _accounts->getRole(uName);
                std::unique_ptr<Domain::Sessions::SessionHandler> currentSession = Domain::Sessions::SessionHandler::createSession(role);
                commands = currentSession->getCommands();
                if (role == "Doctor"){
                    do{
                        for (unsigned int i = 0; i < commands.size(); i++){
                        std::cout << std::setw(2) << i << " - " << commands[i] << "\n";
                        }
                        std::cin >> selection;
                        if(selection == 0){

                        }
                        else if(selection == 1){

                        }
                        else if(selection == 2){

                        }
                        else{
                            std::cout << "Invalid option\n";
                        }
                    }while(loggedIn);
                }
                else if (role == "Receptionist"){

                }
                else if (role == "Analyst"){

                }
            }
            else{
                _logger << "Login failed for \"" + uName + "\"";
            }
           

       }while(running);

    }
}