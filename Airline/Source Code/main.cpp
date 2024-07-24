// Project: Airline Reservation System
// Author: Joe, Michele, and Jacob
// Date: 2/3/24
// Filename: main.cpp
// Purpose: Create a program to reserve seats on an airplane

#include <iostream>
#include <string>
#include "airlineFunctions.hpp"
#include "Aircraft.hpp"
#include "Accessible.hpp"
#include "Flyer.hpp"
#include "PrivateJet.hpp"


int main() {

    //users variables
    int userClass, seatNum;
    std::string name, lastName, date;

    int choice, resetConfirm;

    bool verifyUserInfo;

    Aircraft aircraft;
    Flyer myFlyer;
    Accessible myAccessibleFlyer;
    PrivateJet myPrivateJet;

    do {
        choice = displayMenu(myFlyer, aircraft, myAccessibleFlyer);

        switch (choice) {
            case 1: {
                std::cout << "Enter User Information: \n";
                std::cin.ignore();// Clears the input buffer
                // Function that asks for user's information
                requestUserInformation(myFlyer, myAccessibleFlyer);
                break;
            }
            case 2: {
                std::cout << "Choose plane: \n";
                aircraft = chooseAircraft(myFlyer);
                std::cout << "You have chosen aircraft: " << aircraft.getModel() << " with capacity "
                          << aircraft.getCapacity() << std::endl;
                // sets the aircraft for the flyer
                myFlyer.setAircraft(aircraft.getModel());

                // Creates file if it doesn't exist
                aircraft.checkAndCreateFiles();

                if (myFlyer.getFlightClass() != 0) { // If the user has already chosen a class
                    aircraftChange(aircraft, myFlyer); // Checks the class they choose, if it is not available on new plane then the users chosen class is reset

                    seatNum = getSeat(aircraft, myFlyer, myPrivateJet); // Gets the seat number for the flyer on the new aircraft
                    myFlyer.setSeatNum(seatNum); // Updates the seat number for the flyer if aircraft is changed after class is chosen
                }
                if (aircraft.getModel() == "Private Jet") {
                    std::cout << "You have chosen the private jet.\n";
                    // Sets the user's attributes to the private jet
                    myFlyer.setAircraft("Private Jet");
                    myFlyer.setFlightClass(3);
                    // Assign a seat for the private jet
                    seatNum = getSeat(aircraft, myFlyer, myPrivateJet);
                    myFlyer.setSeatNum(seatNum);
                }







                break;
            }
            case 3: {
                if (aircraft.getModel() != "Private Jet") {
                std::cout << "Assign class: \n";
                userClass = getUserClass(aircraft);
                if (userClass == 3) { // If the user chooses to change the aircraft
                    aircraft = chooseAircraft(myFlyer);
                    std::cout << "You have chosen aircraft: " << aircraft.getModel() << " with capacity "
                              << aircraft.getCapacity() << std::endl;
                    myFlyer.setAircraft(aircraft.getModel()); // sets the aircraft for the flyer

                    break;
                } else if (userClass == 4 || userClass == 5) { // If the user chooses to be on the waiting list
                    if (userClass == 4) {
                        std::cout << "You have chosen to be on the waiting list for first class.\n";
                        resetConfirm = confirmWait();
                        if (resetConfirm == 1) { // If the user chooses to be on the waiting list
                            myFlyer.setFlightClass(1); // Set the flight class for the flyer to first class
                            writeWaitingList(myFlyer, myAccessibleFlyer); // Writes the user to the waiting list
                            myFlyer.reset(); // Resets the flyer object to default values
                            aircraft.reset(); // Resets the aircraft object to default values
                            break;
                        }
                    } else {
                        std::cout << "You have chosen to be on the waiting list for economy class.\n";
                        resetConfirm = confirmWait();
                        if (resetConfirm == 1) { // If the user chooses to be on the waiting list
                            myFlyer.setFlightClass(2); // Set the flight class for the flyer to economy class
                            writeWaitingList(myFlyer, myAccessibleFlyer); // Writes the user to the waiting list
                            myFlyer.reset(); // Resets the flyer object to default values
                            aircraft.reset(); // Resets the aircraft object to default values
                            break;
                        }

                    }
                    writeWaitingList(myFlyer, myAccessibleFlyer); // Writes the user to the waiting list
                    break;
                }
                myFlyer.setFlightClass(userClass); // Set the flight class for the flyer
                seatNum = getSeat(aircraft, myFlyer, myPrivateJet); // Get the seat number for the flyer
                myFlyer.setSeatNum(seatNum); // Set the seat number for the flyer
                }else{
                    std::cout << "You have chosen the private jet.\n";
//                    // Sets the user's attributes to the private jet
//                    myFlyer.setAircraft("Private Jet");
//                    myFlyer.setFlightClass(3);
//                    // Assign a seat for the private jet
//                    seatNum = getSeat(aircraft, myFlyer, myPrivateJet);
//                    myFlyer.setSeatNum(seatNum);
                }

                break;
            }
            case 4: {

                //case to assign seat on chosen plane
                std::cout << "Assign Flyer: \n";
                // Checks to see if all the information is entered for the user
                verifyUserInfo = verifyInfo(myFlyer);
                if (!verifyUserInfo) {
                    break;
                }

                resetConfirm = confirmSeat(); // Confirms the user wants to be assigned the seat


                if (resetConfirm == 1) { // If the user chooses to confirm the seat and reset the flyer

                    assignSeat(seatNum, aircraft); // Sets the seat number in the plane seat file

                    printPass(myFlyer, myAccessibleFlyer); // Writes the boarding pass to a file
                    writePass(myFlyer, myAccessibleFlyer); // Prints the boarding pass to the console

                    myFlyer.reset(); // Resets the flyer object to default values
                    aircraft.reset(); // Resets the aircraft object to default values
                    break;
                }

                break;
            }
            case 5: {
                std::cout << "New Planes!!\n";

                newAircraft(aircraft, myPrivateJet); // Function to create a new aircraft

                waitListAssignment(aircraft, myFlyer, myPrivateJet); // Function to assign the waiting list to seats


                break;
            }
                default: {
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
                }

            }

        }while (choice != 6);

    return 0;
}
