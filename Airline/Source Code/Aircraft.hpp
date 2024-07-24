#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <string>
#include <fstream>
#include <vector>


class Aircraft {

private:
    int capacity;
    std::string model;
    std::string fileName;

public:

    // Constructors
    Aircraft(); // Default constructor
    Aircraft(int capacity, const std::string& model, const std::string& fileName); // Parameterized constructor

    // Getter and Setter methods
    int getCapacity() const {
        return capacity;
    }
    void setCapacity(int capacity);

    std::string getModel() const {
        return model;
    }
    void setModel(const std::string& model);

    std::string getFileName() const {
        return fileName;
    }
    void setFileName(const std::string& fileName);

    void writePlaneCapacity(const std::vector<int>& planeArray) const;

    std::vector<int> readPlaneCapacity() const;

    virtual void reset();

    virtual void checkAndCreateFiles() const;

    virtual ~Aircraft() = default;
};

#endif //AIRCRAFT_HPP
