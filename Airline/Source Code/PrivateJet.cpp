#include "PrivateJet.hpp"

// Default constructor for the PrivateJet class
PrivateJet::PrivateJet() : takeoff("ZOOOOM!!") {} // Default constructor

// Parameterized constructor for the PrivateJet class
PrivateJet::PrivateJet(int capacity, const std::string& model, const std::string& fileName,
                       const std::string& takeoff) : Aircraft(capacity, model, fileName), takeoff(takeoff) {} // Parameterized constructor

// Getter method for takeoff
std::string PrivateJet::getTakeoff() const {
    return takeoff;
}

// Setter method for takeoff
void PrivateJet::setTakeoff(const std::string& newTakeoff) {
    takeoff = newTakeoff;
}

// Overridden method to return the capacity of the private jet
int PrivateJet::getCapacity() const {
    // Implement custom logic to determine the capacity of the private jet
    // For now, let's assume it's a constant value
    return 5; // Example capacity for a private jet
}

// Overridden reset method if needed
void PrivateJet::reset() {
    takeoff = "ZOOOOM!!";
}

// Implementation for checkAndCreateFiles() if needed
void PrivateJet::checkAndCreateFiles() {
    // Implement if necessary
    // Example: std::cout << "Checking and creating files in PrivateJet..." << std::endl;
    // You can also call the base class method if needed
    Aircraft::checkAndCreateFiles();
}