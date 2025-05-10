#include "Ambulance.hh" // Update the include directive to match the correct header file name
#include <iostream>

using namespace std;

// Rest of the code remains unchanged
Ambulance::Ambulance(const string& n, const string& p, bool a)
    : name(n), place(p), available(a) {
}

string Ambulance::getName() const {
    return name;
}

string Ambulance::getPlace() const {
    return place;
}

bool Ambulance::isAvailable() const {
    return available;
}

void Ambulance::setName(const string& n) {
    name = n;
}

void Ambulance::setPlace(const string& p) {
    place = p;
}

void Ambulance::setAvailability(bool a) {
    available = a;
}

bool Ambulance::call() {
    if (available) {
        cout << "Ambulance " << name << " from " << place << " is on the way!" << endl;
        available = false;
        return true;
    }
    else {
        cout << "Ambulance " << name << " from " << place << " is not available at the moment." << endl;
        return false;
    }
}

void Ambulance::freeAmbulance() {
    available = true;
    cout << "Ambulance " << name << " is now available again." << endl;
}