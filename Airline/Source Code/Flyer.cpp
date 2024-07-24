// Flyer.cpp

#include <iostream>
#include <fstream>
#include "Flyer.hpp"

Flyer::Flyer() : name("Not Entered"), lastName(""), birthday("Not Entered"), flightClass(0), aircraft("Not Entered"), seatNum(0) {}

Flyer::Flyer(const std::string& name, const std::string& lastName, const std::string& birthday,
             int userClass, const std::string& aircraft, int seatNum)
        : name(name), lastName(lastName), birthday(birthday), flightClass(0), aircraft(aircraft), seatNum(seatNum) {
    // Logic to set flightClass based on userClass can be added here
}

std::string Flyer::getName() const {
    return name;
}

void Flyer::setName(const std::string& newName) {
    name = newName;
}

std::string Flyer::getLastName() const {
    return lastName;
}

void Flyer::setLastName(const std::string& newLastName) {
    lastName = newLastName;
}

std::string Flyer::getBirthday() const {
    return birthday;
}

void Flyer::setBirthday(const std::string& newBirthday) {
    birthday = newBirthday;
}

int Flyer::getFlightClass() const {
    return flightClass;
}

void Flyer::setFlightClass(int newFlightClass) {
    flightClass = newFlightClass;
}

std::string Flyer::getAircraft() const {
    return aircraft;
}

void Flyer::setAircraft(const std::string& newAircraft) {
    aircraft = newAircraft;
}

int Flyer::getSeatNum() const {
    return seatNum;
}

void Flyer::setSeatNum(int newSeatNum) {
    seatNum = newSeatNum;
}



void Flyer::reset() { // This method resets the Flyer object to default values
    name = "Not Entered";
    lastName = "";
    birthday = "Not Entered";
    flightClass = 0;
    aircraft = "Not Entered";
    seatNum = 0;
}