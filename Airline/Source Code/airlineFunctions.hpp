#ifndef AIRLINEFUNCTIONS
#define AIRLINEFUNCTIONS

#include "Aircraft.hpp"
#include "Flyer.hpp"
#include "Accessible.hpp"
#include "PrivateJet.hpp"
#include <vector>

// Function declarations
int displayMenu(const Flyer& myFlyer, const Aircraft& aircraft, const Accessible& myAccessibleFlyer);
Aircraft chooseAircraft(Flyer& myFlyer);
int getUserClass(const Aircraft& aircraft);
int checkPlane(const std::vector<int>& planeArray, int start, int end);
int getSeat(const Aircraft& aircraft, const Flyer& myFlyer, const PrivateJet& myPrivateJet);
std::string inputData(int checkInput);
void requestUserInformation(Flyer& myFlyer, Accessible& myAccessibleFlyer);
bool inputDataAccess();
void assignSeat(int seatNum, const Aircraft& aircraft);
void aircraftChange(Aircraft& aircraft, Flyer& myFlyer);
void newAircraft(Aircraft& aircraft, PrivateJet& myPrivateJet);
int confirmSeat();
int confirmWait();
bool verifyInfo(const Flyer& myFlyer);
void printPass(const Flyer& myFlyer, const Accessible& myAccessibleFlyer);
void writePass(const Flyer& myFlyer, const Accessible& myAccessibleFlyer);
void writeWaitingList(const Flyer& myFlyer, const Accessible& myAccessibleFlyer);
void waitListAssignment(Aircraft& aircraft, Flyer& myFlyer, PrivateJet& myPrivateJet);



#endif
