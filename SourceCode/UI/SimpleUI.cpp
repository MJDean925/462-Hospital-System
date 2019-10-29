#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>
#include <ctime>

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
        std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );

        do{
            std::cout << "   Username:   ";
            std::getline(std::cin, uName);
            std::cout << "   Password:   ";
            std::getline(std::cin, pWord);
            //Ensures the user has an account
            if (_accounts->isAuthenticated({uName, pWord, ""})){
                _logger << "Login successful for \"" + uName + "\"";
                loggedIn = true;
                role = _accounts->getRole(uName);
                //Creates the session to find commands
                std::unique_ptr<Domain::Sessions::SessionHandler> currentSession = Domain::Sessions::SessionHandler::createSession(role);
                commands = currentSession->getCommands();
                //Checks if user is a doctor
                if (role == "Doctor"){
                    do{//Loops the same user's options and decisions until logout or shutdown called
                        do{ //Loops to print commands and to make sure commands are in range
                            for (unsigned int i = 0; i < commands.size(); i++){
                                std::cout << std::setw(2) << i << " - " << commands[i] << "\n";
                            }
                            std::cin >> selection;
                        }while(selection >= commands.size());
                        selectedCommand = commands[selection];
                        //Set of if/else if for checking commands
                        if(selectedCommand == "Create Record"){
                            std::cout << "Create Record selected\n"; 
                            //Figure out what goes in visit records
                            std::vector<std::string> visitFields = _visitRecords->requestNewRecord();
                            //Create and initialize all fields to empty
                            /*std::string pName = "";
                            std::string dName = "";
                            std::string pTestimony = "";
                            std::string diag = "";
                            std::string treatment = "";
                            std::string ref = "";
                            std::string presc = "";*/
                            std::vector<std::string> entries;
                            std::string output;
                            tm inDate;
                            tm outDate;
                            //Get inDate and set it
                            time_t in;
                            //t = current time
                            time(&in);
                            //inDate = t as struct tm, * and & needed due to pointer arguments and returns
                            inDate = * localtime(&in);
                            /*
                            This was used to test time to string stuff
                            std::string time_as_string = asctime(&inDate);
                            std::cout << time_as_string << '\n';
                            */

                            //Initialize entries to empty, not including final 3 entries which don't require user input until end
                            for (unsigned int i = 0; i < visitFields.size() - 3; i++){
                                entries.push_back("");
                            }
                            //Loop to display and data filling until the file until command finished
                            bool finished = false;
                            do{
                                do{
                                    for (unsigned int i = 0; i < entries.size(); i++){
                                        std::cout << i << " - " << visitFields[i] << ": " << entries[i] << '\n';
                                    }
                                    std::cout << entries.size() << " - Finished\n";
                                    std::cin >> selection;
                                }while(selection > entries.size());
                                if (selection == entries.size()){
                                    finished = true;
                                }
                                else{
                                    std::cout << "Enter information: ";
                                    std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
                                    std::getline(std::cin, entries[selection]);
                                }
                            }while(!finished);
                            //Finished populating entries information
                            //Get out time and create the record
                            time_t out;
                            time(&out);
                            outDate = * localtime(&out);

                            std::cout << "Export record to file? (Y/N)\n";
                            std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
                            std::getline(std::cin,output);
                            //Call method using data gathered
                            _visitRecords->createNewRecord(entries[0], entries[1], entries[2], entries[3], entries[4], entries[5], entries[6], inDate, outDate, output);
                        }
                        else if(selectedCommand == "Logout"){
                            std::cout << "Logout selected\n";
                            std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
                            loggedIn = false;
                        }
                        else if(selectedCommand == "Shutdown"){
                            std::cout << "Shutdown selected\n";
                            loggedIn = false;
                            running = false;
                        }
                        else{
                            std::cout << "Invalid option\n";
                        }
                    }while(loggedIn);
                }
                else if (role == "Receptionist"){//Checks if user is a receptionist
                    do{//Loop the same user's options and decisions until logout or shutdown is called
                        do{//Lists commands and ensures in range
                            for (unsigned int i = 0; i < commands.size(); i++){
                                std::cout << std::setw(2) << i << " - " << commands[i] << "\n";
                            }
                            std::cin >> selection;
                        }while(selection >= commands.size());
                        selectedCommand = commands[selection];
                        //If/Else if block for executing commands
                        if(selectedCommand == "Create Appointment"){
                            std::cout << "Create Appointment selected\n"; 
                            //Add functionality
                        }
                        else if(selectedCommand == "Logout"){
                            std::cout << "Logout selected\n";
                            std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
                            loggedIn = false;
                        }
                        else if(selectedCommand == "Shutdown"){
                            std::cout << "Shutdown selected\n";
                            loggedIn = false;
                            running = false;
                        }
                        else{
                            std::cout << "Invalid option\n";
                        }
                    }while(loggedIn);
                }
                else if (role == "Analyst"){//Checks if the user is an analyst
                    do{//Loop the same user's options and decisions until logout or shutdown is called
                        do{//Lists commands and makes sure in range
                            for (unsigned int i = 0; i < commands.size(); i++){
                                std::cout << std::setw(2) << i << " - " << commands[i] << "\n";
                            }
                            std::cin >> selection;
                        }while(selection >= commands.size());
                        selectedCommand = commands[selection];
                        //If/Else if block for executing commands
                        if(selectedCommand == "View Trends"){
                            std::cout << "View Trends selected\n"; 
                            //Add functionality
                        }
                        else if(selectedCommand == "Logout"){
                            std::cout << "Logout selected\n";
                            std::cin.ignore(  std::numeric_limits<std::streamsize>::max(), '\n' );
                            loggedIn = false;
                        }
                        else if(selectedCommand == "Shutdown"){
                            std::cout << "Shutdown selected\n";
                            loggedIn = false;
                            running = false;
                        }
                        else{
                            std::cout << "Invalid option\n";
                        }
                    }while(loggedIn);
                }
            }
            else{
                _logger << "Login failed for \"" + uName + "\"";
            }
           

       }while(running);

    }
}