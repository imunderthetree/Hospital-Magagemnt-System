#ifndef AMBULANCE_H
#define AMBULANCE_H

#include <string>

using namespace std;

class Ambulance {
private:
    string name;
    string place;
    bool available;

public:
    Ambulance(const string& n, const string& p, bool a = true);

    string getName() const;
    string getPlace() const;
    bool isAvailable() const;

    void setName(const string& n);
    void setPlace(const string& p);
    void setAvailability(bool a);

    bool call();
    void freeAmbulance();
};

#endif // AMBULANCE_H