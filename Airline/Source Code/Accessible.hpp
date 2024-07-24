#ifndef ACCESSIBLE_HPP
#define ACCESSIBLE_HPP

#include "Flyer.hpp"

class Accessible {
private:
    Flyer flyer;
    bool accessRequired;

public:
    Accessible();

    bool getAccessRequired() const;
    void setAccess(bool tempAccessRequired);

    // Methods to access and modify Flyer attributes directly
    Flyer& getFlyer();
    const Flyer& getFlyer() const;

    // Override reset method from Flyer
    void reset();
};

#endif
