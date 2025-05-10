#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include <iostream>
#include <string>

using namespace std;

class Receptionist {
private:
    struct TimeSession {
        int hour;
        int minute;
        bool isAvailable;
    };

    TimeSession** sessions;
    int numDays;
    int numSessionsPerDay;

public:
    Receptionist(int days = 7);
    ~Receptionist();

    bool bookSession(int day, int hour, int minute);
    void showAvailableSessions(int day);
    void resetDay(int day);
    void advanceDay(int currentDay);
};

#endif // RECEPTIONIST_H