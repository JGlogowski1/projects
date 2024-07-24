#ifndef PRIVATEJET_HPP
#define PRIVATEJET_HPP

#include <string>
#include "Aircraft.hpp"

class PrivateJet : public Aircraft {
private:
    std::string takeoff;

public:
    // Constructors
    PrivateJet(); // Default constructor
    PrivateJet(int capacity, const std::string& model, const std::string& fileName,
               const std::string& takeoff); // Parameterized constructor

    // Getter and setter for takeoff
    std::string getTakeoff() const;
    void setTakeoff(const std::string& newTakeoff);

    // Overridden method from Aircraft class
    int getCapacity() const; // Override the getCapacity method

    // Additional methods if needed

    // Overridden reset method if needed
    void reset() override;

    // Overridden checkAndCreateFiles method if needed
    void checkAndCreateFiles();
};

#endif //PRIVATEJET_HPP
