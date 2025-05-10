#include "Doctor.hh"
#include <fstream>
#include <iostream>
#include <algorithm>

Doctor::Doctor(const std::string& id, const std::string& name, int age,
    const std::string& gender, const std::string& phone,
    const std::string& address, const std::string& specialization,
    const std::string& department, const std::string& licenseNumber)
    : Person(id, name, age, gender, phone, address),
    specialization(specialization), department(department),
    licenseNumber(licenseNumber) {
}

// Getters
std::string Doctor::getSpecialization() const { return specialization; }
std::string Doctor::getDepartment() const { return department; }
std::string Doctor::getLicenseNumber() const { return licenseNumber; }

// Setters
void Doctor::setSpecialization(const std::string& specialization) {
    this->specialization = specialization;
}

void Doctor::setDepartment(const std::string& department) {
    this->department = department;
}

void Doctor::setLicenseNumber(const std::string& license) {
    licenseNumber = license;
}

// Schedule management
void Doctor::addScheduleSlot(int day, int hour) {
    schedule.emplace_back(day, hour);
    std::cout << "Added schedule slot: Day " << day << " at " << hour << ":00\n";
}

void Doctor::removeScheduleSlot(int day, int hour) {
    auto it = std::remove_if(schedule.begin(), schedule.end(),
        [day, hour](const std::pair<int, int>& slot) {
            return slot.first == day && slot.second == hour;
        });

    if (it != schedule.end()) {
        schedule.erase(it, schedule.end());
        std::cout << "Removed schedule slot: Day " << day << " at " << hour << ":00\n";
    }
    else {
        std::cout << "Schedule slot not found.\n";
    }
}

void Doctor::clearSchedule() {
    schedule.clear();
    std::cout << "Schedule cleared.\n";
}

void Doctor::displaySchedule() const {
    std::cout << "\nDoctor's Schedule:\n";
    if (schedule.empty()) {
        std::cout << "No scheduled appointments.\n";
        return;
    }

    for (const auto& slot : schedule) {
        std::cout << "Day " << slot.first << " at " << slot.second << ":00\n";
    }
}

void Doctor::displayInfo() const {
    Person::displayInfo();
    std::cout << "Specialization: " << specialization << "\n";
    std::cout << "Department: " << department << "\n";
    std::cout << "License Number: " << licenseNumber << "\n";
}

void Doctor::saveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << "Doctor Information:\n";
        Person::saveToFile(filename);
        file << "Specialization: " << specialization << "\n";
        file << "Department: " << department << "\n";
        file << "License Number: " << licenseNumber << "\n";

        file << "\nSchedule:\n";
        if (schedule.empty()) {
            file << "No scheduled appointments.\n";
        }
        else {
            for (const auto& slot : schedule) {
                file << "Day " << slot.first << " at " << slot.second << ":00\n";
            }
        }

        file << "\n----------------------------------------\n\n";
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}   