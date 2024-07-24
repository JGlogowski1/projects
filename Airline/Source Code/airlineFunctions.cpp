#include <iostream>
#include <string>
#include <vector>
#include <limits>

//project headers
#include "airlineFunctions.hpp"
#include "Aircraft.hpp"
#include "Accessible.hpp"
#include "Flyer.hpp"
#include "PrivateJet.hpp"


int displayMenu(const Flyer& myFlyer, const Aircraft& aircraft, const Accessible& myAccessibleFlyer) {
    int choice;
    std::string classString, accessString;

    // Set accessString based on the access requirements of the flyer
    if (myAccessibleFlyer.getAccessRequired()) {
        accessString = "Yes";
    } else {
        accessString = "No";
    }

    // Set classString based on the flight class of the flyer
    if (myFlyer.getFlightClass() == 1) {
        classString = "First Class";
    } else if (myFlyer.getFlightClass() == 2) {
        classString = "Economy Class";
    } else if (myFlyer.getFlightClass() == 3) {
        classString = "Private Jet";
    } else {
        classString = "Not Assigned";
    }

    //display main menu and prompt user for seat choice
    std::cout << "=========================================\n";
    std::cout << "          Airline Reservation System     \n";
    std::cout << "=========================================\n";
    std::cout << "   1. Enter User Information\n";
    std::cout << "   2. Choose Plane\n";
    std::cout << "   3. Choose Class\n";
    std::cout << "   4. Assign Flyer\n";
    std::cout << "   5. New Planes!!\n";
    std::cout << "   6. Exit Program\n";
    std::cout << "=========================================\n";
    //displays information about the current user and the current aircraft choice
    std::cout << "  Current User: " << myFlyer.getName() << " " << myFlyer.getLastName() << std::endl;
    std::cout << "  User Require Access: " << accessString << std::endl;
    std::cout << "  Current Aircraft: " << aircraft.getModel() << " with capacity " << aircraft.getCapacity() << std::endl;
    std::cout << "  Current User Class: " << classString << std::endl;
    std::cout << "  Current User Seat: " << myFlyer.getSeatNum() << std::endl;
    std::cout << "=========================================\n";

    while(!(std::cin >> choice) || choice < 1 || choice > 6)  {
        // clear the input stream
        std::cin.clear();
        // Repair the input stream
        std::cin.ignore(255, '\n');
        std::cout << "Error, input is not a integer. Try again" << std::endl;
    }
    return choice;
}




// Function to get user input for name, last name, birthday, or accessability  based on 'checkInput'
std::string inputData(int checkInput){
    // Variable to store the user input
    std::string output;
    // Check the value of checkInput to determine the type of input to request
    switch (checkInput) {
        case 1:
            std::cout << "Enter your First name: ";
            break;
        case 2:
            std::cout << "Enter your Last name: ";
            break;
        case 3:
            std::cout << "Enter your Birthday: ";
            break;
        case 4:
            std::cout << "Do you require accessability features\n 1. Yes\n 2. No\n";

            break;
        default:
            std::cerr << "Invalid input." << std::endl;
            break;
    }
    std::getline(std::cin, output);
    std::cout << "\n";
    return output;
};

void requestUserInformation(Flyer& myFlyer, Accessible& myAccessibleFlyer) {
    std::string name, lastName, date;
    bool access;

    name = inputData(1); // Asks for user's name
    lastName = inputData(2); // Asks for user's last name
    date = inputData(3); // Asks for user's birthday
    access = inputDataAccess(); // Asks for user's access needs

    // Asks user if they require accessability features

    if (access) {
        myAccessibleFlyer.setAccess(true);
    } else {
        myAccessibleFlyer.setAccess(false);
    }

    // Assigns the user's information to the Flyer object
    myFlyer.setName(name);
    myFlyer.setLastName(lastName);
    myFlyer.setBirthday(date);
}

bool inputDataAccess() {
    int input;
    bool returnValue;
    int loopCheck;
    do {
        std::cout << "Do you require accessability features: " << std::endl;
        std::cout << "1. Yes" << std::endl;
        std::cout << "2. No" << std::endl;
        std::cout << ">> ";
        if (!(std::cin >> input)) {
            std::cin.clear();

            // Repair the input stream
            std::cin.ignore(255, '\n');
            std::cout << "Error, input is not a integer. Try again" << std::endl;
            loopCheck = 1;
        } else  {
            if (input == 1) {
                returnValue = true;
                loopCheck = 0;
            } else if (input == 2) {
                returnValue = false;
                loopCheck = 0;
            } else {
                std::cout << "Error, invalid integer. Try again" << std::endl;
                loopCheck = 1;
            }
        }
    } while(loopCheck == 1);
    return returnValue;
}



// Function for the user to choose between aircrafts
Aircraft chooseAircraft(Flyer& myFlyer) {
    std::cout << "Choose an aircraft:" << std::endl;
    std::cout << "1. Large Plane (Capacity: 30)" << std::endl;
    std::cout << "2. Medium Plane (Capacity: 20)" << std::endl;
    std::cout << "3. Small Plane (Capacity: 10)" << std::endl;
    std::cout << "4. Private Jet (Capacity: 5)" << std::endl;

    int aircraftChoice;
    std::cin >> aircraftChoice;


    switch (aircraftChoice) {
        case 1:
            return Aircraft(30, "Large Plane", "largePlaneSeats.txt");
        case 2:
            return Aircraft(20, "Medium plane", "mediumPlaneSeats.txt");
        case 3:
            return Aircraft(10, "Small plane", "smallPlaneSeats.txt");
        case 4:
            return PrivateJet(5, "Private Jet", "privateJetSeats.txt", "ZOOOOM!!");
        default:
            std::cout << "Invalid choice." << std::endl;
            return Aircraft();  // Default constructor for default aircraft
    }
}



//function to determine if a seat is available

int getUserClass(const Aircraft& aircraft) { //Returns 1 for first class, 2 for economy class, 3 for another aircraft, 4 first class waiting list, 5 for economy class waiting list
    // Runs function to get plane array
    std::vector<int> planeArray = aircraft.readPlaneCapacity();

    int choice;

    std::cout << "Checking seat availability for " << aircraft.getModel() << " with capacity " << aircraft.getCapacity() << std::endl;

    int firstClassAvailability = checkPlane(planeArray, 0, aircraft.getCapacity() / 2);
    int economyClassAvailability = checkPlane(planeArray, aircraft.getCapacity() / 2, aircraft.getCapacity());

    if (firstClassAvailability && economyClassAvailability) {
        std::cout << "Both First Class and Economy Class are available for " << aircraft.getModel() << "." << std::endl;
        std::cout << "1. First Class\n2. Economy Class\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        while (choice != 1 && choice != 2) {
            std::cout << "Invalid choice. Please enter 1 for First Class or 2 for Economy Class: ";
            std::cin >> choice;
        }
    } else if (firstClassAvailability) {
        std::cout << "Only First Class is available for " << aircraft.getModel() << "." << std::endl;
        std::cout << "1. First Class\n";
        std::cout << "2: Choose another aircraft\n";
        std::cout << "3: Put me on the Economy waiting list\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if(choice == 2) {
            return 3;
        }
        if(choice == 3) {
            return 5;
        }
    } else if (economyClassAvailability) {
        std::cout << "Economy Class is available for " << aircraft.getModel() << "." << std::endl;
        std::cout << "1. Economy Class\n";
        std::cout << "2: Choose another aircraft\n";
        std::cout << "3: Put me on the First class waiting list\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if(choice == 1) { // If the user chooses economy class
            return 2;  // Return 2 for economy class
        }
        if(choice == 2) { // If the user chooses to change the aircraft
            return 3; // Return 3 for another aircraft
        }
        if(choice == 3) { // If the user chooses to be put on the waiting list
            return 4; // Return 4 for first class waiting list
        }

    } else {
        std::cout << "No seats available for " << aircraft.getModel() << "." << std::endl;
        std::cout << "1. Put me on the First Class waiting list\n2. Put me on the Economy waiting list\n3. Choose another aircraft\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (choice == 1){
            return 4; // Return 4 for first class waiting list
        }
        if (choice == 2){
            return 5; // Return 5 for economy class waiting list
        }

        while (choice != 1 && choice != 2) {
            std::cout << "Invalid choice. Please enter 1 to be put on the waiting list or 2 to choose another aircraft: ";
            std::cin >> choice;
            if (choice == 1){
                return 4;
            }
            if (choice == 2){
                return 3;
            }
        }
    }

    return choice;
}

// Function to check if there is an open seat within a specified range in the planeArray
int checkPlane(const std::vector<int>& planeArray, int start, int end){
    // Boolean variable to track whether an open seat is found
    bool openSeat = false;

    for (int i = start; i < end; ++i) {
        // Check if the current seat is open (0 indicates an open seat)
        if (planeArray[i] == 0){
            // Set openSeat to true if an open seat is found
            openSeat = true;
        }
    }

    // If at least one open seat is found, return 1; otherwise, return 0
    return openSeat ? 1 : 0;
}


// Function to find and return the index of an available seat within a specified range in the planeArray
int getSeat(const Aircraft& aircraft, const Flyer& myFlyer, const PrivateJet& myPrivateJet) {
    // Get the capacity of the aircraft
    int capacity = aircraft.getCapacity();
    // Get the user class
    int userClass = myFlyer.getFlightClass();
    // Get the Private Jet capacity
    int privateJetCapacity = myPrivateJet.getCapacity();
    //prints the capacity of the private jet
    std::cout << "The capacity of the private jet is: " << privateJetCapacity << std::endl;

    // Get the plane array from the aircraft
    std::vector<int> planeArray = aircraft.readPlaneCapacity();

    // Define the start and end indices based on user class
    int start, end;

    if (userClass == 1) {  // First Class
        start = 0;
        end = capacity / 2;
    } else if (userClass == 2) {  // Economic Class
        start = capacity / 2;
        end = capacity;
    } else if (userClass == 3) {  // Private Jet
        std::cout << "You have chosen the private jet. lol" << std::endl;
        start = 0;
        end = privateJetCapacity;  // Set the start and end indices to the capacity of the private jet
    } else {
        // Handle invalid user class, or implement additional classes as needed
        std::cerr << "Invalid user class." << std::endl;
        return -1;  // Indicate an error
    }

    // Variable to store the index of the assigned seat
    int seatAssigned = -1; // Initialize to -1 indicating no seat is assigned

    for (int i = start; i < end; ++i) {
        // Check if the current seat is open (0 indicates an open seat)
        if (planeArray[i] == 0) {
            // Assign the index of the open seat to seatAssigned
            seatAssigned = i + 1;
            // Exit the loop since an available seat has been found
            break;
        }
    }

    // Return the index of the assigned seat or -1 if no seat is available
    return seatAssigned;
}

// Function to assign a seat to the user
void assignSeat(int seatNum, const Aircraft& aircraft) {
    // Get the plane array from the aircraft
    std::vector<int> planeArray = aircraft.readPlaneCapacity();

    // Assign the seat number to the user in the plane array
    planeArray[seatNum - 1] = 1;

    // Write the updated plane array to the plane's seating capacity file
    aircraft.writePlaneCapacity(planeArray);

}

void aircraftChange(Aircraft& aircraft, Flyer& myFlyer) {

                    std::vector<int> planeArray = aircraft.readPlaneCapacity();
                    //checks first and business class availability
                    int firstClassAvailability = checkPlane(planeArray, 0, aircraft.getCapacity() / 2);
                    int economyClassAvailability = checkPlane(planeArray, aircraft.getCapacity() / 2, aircraft.getCapacity());

                    if(myFlyer.getFlightClass() == 1 && firstClassAvailability == 0) {
                        std::cout << "First class is not available on " << aircraft.getModel() << ". Please choose a new class.\n";
                        myFlyer.setSeatNum(0);// Resets the Seat number for the flyer
                        myFlyer.setFlightClass(0); // Reset the flight class for the flyer
                    }else if (myFlyer.getFlightClass() == 2 && economyClassAvailability == 0) {
                        std::cout << "Economy class is not available on " << aircraft.getModel() << ". Please choose a new class.\n";
                        myFlyer.setSeatNum(0);// Resets the Seat number for the flyer
                        myFlyer.setFlightClass(0); // Reset the flight class for the flyer
                    }else {
                        std::cout << "The class you have chosen is available on " << aircraft.getModel() << ".\n";
                    }


}

void newAircraft(Aircraft& aircraft, PrivateJet& myPrivateJet) {
    int choice;

    std::cout << "Which Plane would you like to swap out for a new plane" << std::endl;
    std::cout << "1. Large Plane (Capacity: 30)" << std::endl;
    std::cout << "2. Medium Plane (Capacity: 20)" << std::endl;
    std::cout << "3. Small Plane (Capacity: 10)" << std::endl;
    std::cout << "4. Private Jet (Capacity: 5)" << std::endl;
    std::cout << "5. Exit" << std::endl;

    // Input validation loop
    while (!(std::cin >> choice) || choice < 1 || choice > 5) {
        // Clear input stream
        std::cin.clear();
        // Discard invalid input
        std::cin.ignore(255, '\n');
        std::cout << "Invalid choice. Please enter a number between 1 and 5." << std::endl;
    }

    switch (choice) {
        case 1:
            aircraft = Aircraft(30, "Large Plane", "largePlaneSeats.txt");
            break;
        case 2:
            aircraft = Aircraft(20, "Medium plane", "mediumPlaneSeats.txt");
            break;
        case 3:
            aircraft = Aircraft(10, "Small plane", "smallPlaneSeats.txt");
            break;
        case 4:
            aircraft = PrivateJet(5, "Private Jet", "privateJetSeats.txt", "ZOOOOM!!");
            std::cout << myPrivateJet.getTakeoff() << std::endl;

            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            return; // Exit function
    }

    std::ofstream file(aircraft.getFileName()); // Open file associated with the new aircraft

    // Check if the file is opened successfully
    if (file.is_open()) {
        // Fill the file with zeros (0 indicates an available seat)
        for (int i = 0; i < aircraft.getCapacity(); ++i) {
            file << "0\n";
        }
        file.close(); // Close the file
        std::cout << "New aircraft with empty seats found." << std::endl;
    } else {
        std::cout << "Failed to create or open the file for the new aircraft." << std::endl;
    }

}

// Function to confirm all the user's information and seat assignment has been entered
bool verifyInfo(const Flyer& myFlyer) {
    bool choice = true;
    if (myFlyer.getName() == "" || myFlyer.getLastName() == "" || myFlyer.getBirthday() == "" || myFlyer.getAircraft() == "" || myFlyer.getFlightClass() == 0 || myFlyer.getSeatNum() == 0) {
        std::cout << "Please enter all user information before assigning a seat.\n";
        choice = false;
    }
    return choice;
}


int confirmSeat() {
    int choice;
    std::cout << "Are you sure you want to assign this seat?\nThat will place the flyer in the plane and will wipe their information from the menu\n 1. Yes\n 2. No, save info and back to menu\n";
    std::cin >> choice;
    while (choice != 1 && choice != 2) { // while loop to check for valid input
        std::cout << "Invalid choice. Please enter 1 for Yes or 2 for No: ";
        std::cin >> choice;
    }
    if (choice == 2) {
        std::cout << "Seat assignment cancelled.\n";
    }
    return choice;
}

int confirmWait() {
    int choice;
    std::cout << "Are you sure you want to be placed on the waiting list?\n 1. Yes\n 2. No, back to menu\n";
    std::cin >> choice;
    while (choice != 1 && choice != 2) {
        std::cout << "Invalid choice. Please enter 1 for Yes or 2 for No: ";
        std::cin >> choice;
    }
    if (choice == 2) {
        std::cout << "Waiting list placement cancelled.\n";
    }
    return choice;

}


void printPass(const Flyer& myFlyer, const Accessible& myAccessibleFlyer) { // This function prints the boarding pass to the console
    // Changes the users class to a string
    std::string classString;
    if (myFlyer.getFlightClass() == 1) {
        classString = "First Class";
    } else if (myFlyer.getFlightClass() == 2) {
        classString = "Economy Class";
    } else {
        classString = "Not Assigned";
    }
    // Changes the users accessability to a string
    std::string accessString;
    if (myAccessibleFlyer.getAccessRequired()) {
        accessString = "Requires Accessability";
    }

    std::cout << "=========================================\n";
    std::cout << "          Boarding Pass     \n";
    std::cout << "=========================================\n";
    std::cout << "Name: " << myFlyer.getName() << " " << myFlyer.getLastName() << std::endl;
    std::cout << "Birthday: " << myFlyer.getBirthday() << std::endl;
    std::cout << "Aircraft: " << myFlyer.getAircraft() << "      Flight Class: " << classString << std::endl;
    std::cout << "Seat Number: " << myFlyer.getSeatNum() << "      " << accessString << std::endl;
    std::cout << "=========================================\n";
}

void writePass(const Flyer& myFlyer, const Accessible& myAccessibleFlyer) { // This method writes the boarding pass to a file
    std::ofstream writePass("boardingPass.txt", std::ios::app);
    if (writePass.is_open()) {
        writePass << std::endl << myFlyer.getName() << std::endl;
        writePass << myFlyer.getLastName() << std::endl;
        writePass << myFlyer.getBirthday() << std::endl;
        writePass << myFlyer.getAircraft() << std::endl;
        writePass << myFlyer.getFlightClass() << std::endl;
        writePass << myFlyer.getSeatNum() << std::endl;
        writePass << myAccessibleFlyer.getAccessRequired() << std::endl;
        writePass.close();
    }
}

//writing class to waitlist file
void writeWaitingList (const Flyer& myFlyer, const Accessible& myAccessibleFlyer) {
    std::fstream writeWait ("waitlist.txt", std::ios::app);
    if (writeWait.is_open()) {
        writeWait << myFlyer.getName() << std::endl;
        writeWait << myFlyer.getLastName() << std::endl;
        writeWait << myFlyer.getBirthday() << std::endl;
        writeWait << myFlyer.getAircraft() << std::endl;
        writeWait << myFlyer.getFlightClass() << std::endl;
        writeWait << myAccessibleFlyer.getAccessRequired() << std::endl << std::endl;
        writeWait.close();
    }
};




// Function to process the waiting list and assign seats based on availability
void waitListAssignment(Aircraft& aircraft, Flyer& myFlyer, PrivateJet& myPrivateJet) {
    std::ifstream readWait("waitlist.txt"); // Open the waiting list file for reading

    if (!readWait.is_open()) {
        std::cerr << "Failed to open the waiting list file." << std::endl;
        return;
    } else {
        std::cout << "Waiting list file opened successfully." << std::endl;
    }

    std::string firstName, lastName, birthday, aircraftModel, accessString;
    int flightClass;
    bool accessRequired;

    // Continue reading until the end of the file is reached
    while (std::getline(readWait, firstName) && std::getline(readWait, lastName) &&
           std::getline(readWait, birthday) && std::getline(readWait, aircraftModel) &&
           readWait >> flightClass && readWait >> accessRequired) {
        // Consume newline character after reading flight class and access required
        readWait.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Create a temporary flyer object to store information from the waiting list
        Flyer tempFlyer(firstName, lastName, birthday, flightClass, aircraftModel, 0);
        Accessible tempAccessible;
        tempAccessible.setAccess(accessRequired);

        // Check availability and assign seats based on flight class
        int seatNum = getSeat(aircraft, myFlyer, myPrivateJet); // Get available seat
        if (seatNum != -1) {
            tempFlyer.setSeatNum(seatNum);
            // Print the boarding pass for the assigned seat
            printPass(tempFlyer, tempAccessible);
            // Update the plane's seating capacity to mark the assigned seat as taken
            assignSeat(seatNum, aircraft);
            std::cout << "Seat assigned successfully." << std::endl;
        } else {
            std::cout << "No available seats for " << (flightClass == 1 ? "First Class" : "Economy Class") << " on " << aircraftModel << "." << std::endl;
            // If no seat is available, add the passenger back to the waiting list
            writeWaitingList(tempFlyer, tempAccessible);
        }
    }

    readWait.close(); // Close the waiting list file
}
