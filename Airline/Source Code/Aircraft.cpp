#include <iostream>
#include "Aircraft.hpp"

// Default constructor for the Aircraft class
Aircraft::Aircraft() : capacity(0), model(""), fileName("") {
}

// Parameterized constructor for the Aircraft class
Aircraft::Aircraft(int capacity, const std::string& model, const std::string& fileName)
        : capacity(capacity), model(model), fileName(fileName) {
}

// Method to write array to the file
void Aircraft::writePlaneCapacity(const std::vector<int>& planeArray) const {
    std::ofstream file(fileName);
    if (file.is_open()) {
        for (int i = 0; i < capacity; ++i) {
            file << planeArray[i] << std::endl;
        }
        file.close();
    }
}

// Method to read array from the file
std::vector<int> Aircraft::readPlaneCapacity() const {
    std::vector<int> planeArray;

    std::ifstream file(fileName);
    if (file.is_open()) {
        int value;
        while (file >> value) {
            planeArray.push_back(value);
        }
        file.close();
    }

    return planeArray;
}

// Method to check if files exist and create them if needed
void Aircraft::checkAndCreateFiles() const {
    // Check if the files exist. If not, create them
    std::ifstream file(fileName);
    if (!file) {
        // File doesn't exist, create it
        std::ofstream createFile(fileName);
        if (createFile.is_open()) {
            // Initialize the file with zeros (assuming 0 indicates an available seat)
            for (int i = 0; i < capacity; ++i) {
                createFile << "0\n";
            }
            createFile.close();
            std::cout << "Files created successfully: " << fileName << std::endl;
        } else {
            std::cerr << "Error: Could not create file " << fileName << std::endl;
        }
    } else {
        std::cout << "Files already exist: " << fileName << std::endl;
    }
}

void Aircraft::reset() {
    model = "Not Entered";
    capacity = 0;
}
