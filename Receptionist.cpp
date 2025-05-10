#include "Receptionist.hh" 
#include <iostream>

using namespace std;

Receptionist::Receptionist(int days) {
    numDays = days;
    numSessionsPerDay = 26;

    sessions = new TimeSession * [numDays];
    for (int day = 0; day < numDays; day++) {
        sessions[day] = new TimeSession[numSessionsPerDay];

        int sessionIndex = 0;
        for (int hour = 8; hour < 21; hour++) {
            sessions[day][sessionIndex].hour = hour;
            sessions[day][sessionIndex].minute = 0;
            sessions[day][sessionIndex].isAvailable = true;
            sessionIndex++;

            sessions[day][sessionIndex].hour = hour;
            sessions[day][sessionIndex].minute = 30;
            sessions[day][sessionIndex].isAvailable = true;
            sessionIndex++;
        }
    }
}

Receptionist::~Receptionist() {
    if (sessions) {
        for (int i = 0; i < numDays; i++) {
            delete[] sessions[i];
        }
        delete[] sessions;
    }
}

bool Receptionist::bookSession(int day, int hour, int minute) {
    if (day < 0 || day >= numDays) {
        cout << "Invalid day." << endl;
        return false;
    }

    if (hour < 8 || hour >= 21 || (minute != 0 && minute != 30)) {
        cout << "Invalid time. Hours must be between 8 and 20, minutes must be 0 or 30." << endl;
        return false;
    }

    for (int i = 0; i < numSessionsPerDay; i++) {
        if (sessions[day][i].hour == hour &&
            sessions[day][i].minute == minute) {
            if (sessions[day][i].isAvailable) {
                sessions[day][i].isAvailable = false;
                cout << "Session booked successfully for day " << day
                    << " at " << hour << ":" << (minute == 0 ? "00" : "30") << endl;
                return true;
            }
            else {
                cout << "Session already booked." << endl;
                return false;
            }
        }
    }

    cout << "Session not found." << endl;
    return false;
}

void Receptionist::showAvailableSessions(int day) {
    if (day < 0 || day >= numDays) {
        cout << "Invalid day." << endl;
        return;
    }

    cout << "Available sessions for day " << day << ":" << endl;
    bool hasAvailable = false;

    for (int i = 0; i < numSessionsPerDay; i++) {
        if (sessions[day][i].isAvailable) {
            cout << sessions[day][i].hour << ":"
                << (sessions[day][i].minute == 0 ? "00" : "30") << endl;
            hasAvailable = true;
        }
    }

    if (!hasAvailable) {
        cout << "No available sessions for this day." << endl;
    }
}

void Receptionist::resetDay(int day) {
    if (day < 0 || day >= numDays) {
        cout << "Invalid day." << endl;
        return;
    }

    for (int i = 0; i < numSessionsPerDay; i++) {
        sessions[day][i].isAvailable = true;
    }

    cout << "All sessions for day " << day << " have been reset to available." << endl;
}

void Receptionist::advanceDay(int currentDay) {
    if (currentDay < 0 || currentDay >= numDays) {
        cout << "Invalid current day." << endl;
        return;
    }

    int nextDay = (currentDay + 1) % numDays;
    resetDay(nextDay);

    cout << "Advanced to day " << nextDay << ". All sessions reset." << endl;
}