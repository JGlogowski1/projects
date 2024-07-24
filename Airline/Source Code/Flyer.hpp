// Flyer.hpp

#ifndef FLYER_HPP
#define FLYER_HPP

#include <string>
#include <fstream>

class Flyer {
private:
    std::string name;
    std::string lastName;
    std::string birthday;
    int flightClass;
    std::string aircraft;
    int seatNum;

public:
    Flyer();
    Flyer(const std::string& name, const std::string& lastName, const std::string& birthday,
          int userClass, const std::string& aircraft, int seatNum);

    std::string getName() const;
    void setName(const std::string& newName);

    std::string getLastName() const;
    void setLastName(const std::string& newLastName);

    std::string getBirthday() const;
    void setBirthday(const std::string& newBirthday);

    int getFlightClass() const;
    void setFlightClass(int newFlightClass);

    std::string getAircraft() const;
    void setAircraft(const std::string& newAircraft);

    int getSeatNum() const;
    void setSeatNum(int newSeatNum);


    virtual void reset();

    virtual ~Flyer() = default;

};

#endif
