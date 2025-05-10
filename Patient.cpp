#include "Patient.hh"
#include <fstream>
#include <iostream>

Patient::Patient(const std::string& id, const std::string& name, int age,
    const std::string& gender, const std::string& phone,
    const std::string& address, const std::string& patientId,
    const std::string& bloodType, const std::string& emergencyContact)
    : Person(id, name, age, gender, phone, address),
    patientId(patientId), bloodType(bloodType),
    emergencyContact(emergencyContact), isAdmitted(false), roomNumber("") {
}

// Getters
std::string Patient::getPatientId() const { return patientId; }
std::string Patient::getBloodType() const { return bloodType; }
std::string Patient::getEmergencyContact() const { return emergencyContact; }
bool Patient::getAdmissionStatus() const { return isAdmitted; }
std::string Patient::getRoomNumber() const { return roomNumber; }

// Setters
void Patient::setBloodType(const std::string& bloodType) { this->bloodType = bloodType; }
void Patient::setEmergencyContact(const std::string& contact) { emergencyContact = contact; }

// Medical records management
void Patient::addMedicalHistory(const std::string& record) {
    medicalHistory.push_back(record);
}

void Patient::addMedication(const std::string& medication, const std::string& dosage) {
    medications.emplace_back(medication, dosage);
}

void Patient::addAllergy(const std::string& allergy) {
    allergies.push_back(allergy);
}

// Admission control
void Patient::admit(const std::string& roomNumber) {
    isAdmitted = true;
    this->roomNumber = roomNumber;
    std::cout << "Patient " << name << " admitted to room " << roomNumber << std::endl;
}

void Patient::discharge() {
    isAdmitted = false;
    roomNumber = "";
    std::cout << "Patient " << name << " discharged." << std::endl;
}

// Display methods
void Patient::displayInfo() const {
    Person::displayInfo();
    std::cout << "Patient ID: " << patientId << "\n";
    std::cout << "Blood Type: " << bloodType << "\n";
    std::cout << "Emergency Contact: " << emergencyContact << "\n";
    std::cout << "Status: " << (isAdmitted ? "Admitted" : "Not Admitted") << "\n";
    if (isAdmitted) {
        std::cout << "Room Number: " << roomNumber << "\n";
    }
}

void Patient::displayMedicalHistory() const {
    std::cout << "\nMedical History:\n";
    for (const auto& record : medicalHistory) {
        std::cout << "- " << record << "\n";
    }
}

void Patient::displayMedications() const {
    std::cout << "\nCurrent Medications:\n";
    for (const auto& med : medications) {
        std::cout << "- " << med.first << " (Dosage: " << med.second << ")\n";
    }
}

void Patient::displayAllergies() const {
    std::cout << "\nAllergies:\n";
    for (const auto& allergy : allergies) {
        std::cout << "- " << allergy << "\n";
    }
}

void Patient::saveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << "Patient Information:\n";
        Person::saveToFile(filename);
        file << "Patient ID: " << patientId << "\n";
        file << "Blood Type: " << bloodType << "\n";
        file << "Emergency Contact: " << emergencyContact << "\n";
        file << "Status: " << (isAdmitted ? "Admitted" : "Not Admitted") << "\n";
        if (isAdmitted) {
            file << "Room Number: " << roomNumber << "\n";
        }

        file << "\nMedical History:\n";
        for (const auto& record : medicalHistory) {
            file << "- " << record << "\n";
        }

        file << "\nMedications:\n";
        for (const auto& med : medications) {
            file << "- " << med.first << " (Dosage: " << med.second << ")\n";
        }

        file << "\nAllergies:\n";
        for (const auto& allergy : allergies) {
            file << "- " << allergy << "\n";
        }

        file << "\n----------------------------------------\n\n";
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}