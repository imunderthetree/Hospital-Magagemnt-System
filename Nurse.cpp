#include "Nurse.hh"
#include <fstream>
#include <iostream>
#include <algorithm>

Nurse::Nurse(const std::string& id, const std::string& name, int age,
    const std::string& gender, const std::string& phone,
    const std::string& address, const std::string& department,
    const std::string& nurseId)
    : Person(id, name, age, gender, phone, address),
    department(department), nurseId(nurseId) {
}

// Getters
std::string Nurse::getDepartment() const { return department; }
std::string Nurse::getNurseId() const { return nurseId; }

// Setters
void Nurse::setDepartment(const std::string& department) {
    this->department = department;
}

void Nurse::setNurseId(const std::string& nurseId) {
    this->nurseId = nurseId;
}

// Shift management
void Nurse::addShift(int day, int hour) {
    shifts.emplace_back(day, hour);
    std::cout << "Added shift: Day " << day << " at hour " << hour << "\n";
}

void Nurse::removeShift(int day, int hour) {
    auto it = std::remove_if(shifts.begin(), shifts.end(),
        [day, hour](const std::pair<int, int>& shift) {
            return shift.first == day && shift.second == hour;
        });

    if (it != shifts.end()) {
        shifts.erase(it, shifts.end());
        std::cout << "Removed shift: Day " << day << " at hour " << hour << "\n";
    }
    else {
        std::cout << "Shift not found.\n";
    }
}

void Nurse::clearShifts() {
    shifts.clear();
    std::cout << "All shifts cleared.\n";
}

void Nurse::displayShifts() const {
    std::cout << "\nNurse's Shifts:\n";
    if (shifts.empty()) {
        std::cout << "No shifts scheduled.\n";
        return;
    }

    for (const auto& shift : shifts) {
        std::cout << "Day " << shift.first << " at hour " << shift.second << "\n";
    }
}

void Nurse::displayInfo() const {
    Person::displayInfo();
    std::cout << "Department: " << department << "\n";
    std::cout << "Nurse ID: " << nurseId << "\n";
}

void Nurse::saveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << "Nurse Information:\n";
        Person::saveToFile(filename);
        file << "Department: " << department << "\n";
        file << "Nurse ID: " << nurseId << "\n";

        file << "\nShifts:\n";
        if (shifts.empty()) {
            file << "No shifts scheduled.\n";
        }
        else {
            for (const auto& shift : shifts) {
                file << "Day " << shift.first << " at hour " << shift.second << "\n";
            }
        }

        file << "\n----------------------------------------\n\n";
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}