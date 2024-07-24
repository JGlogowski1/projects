#include "Accessible.hpp"

Accessible::Accessible() : flyer(), accessRequired(false) {}

bool Accessible::getAccessRequired() const {
    return accessRequired;
}

void Accessible::setAccess(bool tempAccessRequired) {
    accessRequired = tempAccessRequired;
}

Flyer& Accessible::getFlyer() {
    return flyer;
}

const Flyer& Accessible::getFlyer() const {
    return flyer;
}

void Accessible::reset() {
    flyer.reset(); // Call the reset method of the Flyer object
}
