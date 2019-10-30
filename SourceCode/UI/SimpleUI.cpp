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
                            //Vector for entries
                            std::vector<std::string> entries;
                            std::string output;
                            tm inDate;
                            tm outDate;
                            //Get inDate and set it
                            time_t t;
                            //t = current time
                            time(&t);
                            //inDate = t as struct tm, * and & needed due to pointer arguments and returns
                            inDate = * localtime(&t);
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
                            time(&t);
                            outDate = * localtime(&t);

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
                            std::vector<std::string> appFields = _appointmentRecords->requestNewAppointment();
                            std::vector<std::string> entries;
                            std::string output;
                            tm date;

                            //initialize entries, only need 4, 5th is export option
                            for (unsigned int i = 0; i < appFields.size() - 1; i++){
                                entries.push_back("");
                            }

                            bool finished = false;

                            do{
                                do{
                                    for (unsigned int i = 0; i < entries.size(); i++){
                                        std::cout << i << " - " << appFields[i] << ": " << entries[i] << '\n';
                                    }
                                    std::cout << entries.size() << " - Finished\n";
                                    std::cin >> selection;
                                }while(selection > entries.size());
                                if (selection == entries.size()){
                                    finished = true;
                                }
                                else{
                                    std::cout << "Enter information: ";
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    std::getline(std::cin, entries[selection]);
                                }
                            }while(!finished);

                            std::cout << "Export appointment to file? (Y/N)\n";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::getline(std::cin, output);

                            //Manipulate AppDate to put in tm struct format, given as MM/DD/YYYY HH:MM 24h format ie 14:30 or 02:20
                            std::string dateAsString = entries[2];
                            std::string tmp;
                            //Month
                            tmp = dateAsString[0];
                            tmp = tmp + dateAsString[1];
                            date.tm_mon = std::stoi(tmp) - 1;
                            //Day
                            tmp = dateAsString[3];
                            tmp = tmp + dateAsString[4];
                            date.tm_mday = std::stoi(tmp);
                            //Year
                            tmp = dateAsString[6];
                            tmp = tmp + dateAsString[7];
                            tmp = tmp + dateAsString[8];
                            tmp = tmp + dateAsString[9];
                            date.tm_year = std::stoi(tmp) - 1900;
                            //Hour
                            tmp = dateAsString[11];
                            tmp = tmp + dateAsString[12];
                            date.tm_hour = std::stoi(tmp);
                            //Minute
                            tmp = dateAsString[14];
                            tmp = tmp + dateAsString[15];
                            date.tm_min = std::stoi(tmp);
                            //Seconds at 0
                            date.tm_sec = 0;
                            //Called to fill in the blanks
                            mktime(&date);

                            _appointmentRecords->createNewAppointment(entries[0], entries[1], date, entries[3], output);
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
                        bool viewingTrends = false;
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
                            viewingTrends = true;
                            do {
                                selection = 0;
                                std::vector<std::string> trendCommands = {"View Recent Visits", "Diagnoses By Month", "Main Menu"};
                                do {
                                    for (unsigned int i = 0; i < trendCommands.size(); i++){
                                        std::cout << std::setw(2) << i << " - " << trendCommands[i] << "\n";
                                    }
                                    std::cin >> selection;
                                }while(selection >= trendCommands.size());
                                selectedCommand = trendCommands[selection];
                                if(selectedCommand == "View Recent Visits") {
                                    std::cout << "View Recent Visits selected";
                                    auto records = _visitRecords->getRecords(15); 
                                    for(auto record : records) {
                                        std::cout << asctime(&record.inDate) << ": "<< record.patientName << " (" << record.doctorName << ") " << std::endl;
                                    }
                                }

                                else if (selectedCommand == "Diagnoses By Month") {
                                    std::cout << "Diagnoses By Month selected" << std::endl << std::endl;

                                    int startMonth, startYear, endMonth, endYear;
                                    std::cout << "Start month: " << std::endl; std::cin >> startMonth;
                                    std::cout << "Start year: " << std::endl; std::cin >> startYear;
                                    std::cout << "End month: " << std::endl; std::cin >> endMonth;
                                    std::cout << "End year: " << std::endl; std::cin >> endYear;

                                    auto records = _visitRecords->getRecordsByRange(startMonth, startYear, endMonth, endYear);
                                    for(auto record : records) {
                                        std::cout << record.patientName << " (" << record.doctorName << ") " << std::endl;
                                    }
                                }

                                else if(selectedCommand == "Main Menu") {
                                    viewingTrends = false;
                                }
                            }while(viewingTrends);
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