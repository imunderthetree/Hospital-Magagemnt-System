#ifndef PATIENT_HH
#define PATIENT_HH

#include "Person.hh"
#include <vector>

class Patient : public Person {
private:
    std::string patientId;
    std::string bloodType;
    std::string emergencyContact;
    std::vector<std::string> medicalHistory;
    std::vector<std::pair<std::string, std::string>> medications; // medication and dosage
    std::vector<std::string> allergies;
    bool isAdmitted;
    std::string roomNumber;

public:
    Patient(const std::string& id, const std::string& name, int age, 
            const std::string& gender, const std::string& phone, 
            const std::string& address, const std::string& patientId, 
            const std::string& bloodType, const std::string& emergencyContact);
    
    // Getters
    std::string getPatientId() const;
    std::string getBloodType() const;
    std::string getEmergencyContact() const;
    bool getAdmissionStatus() const;
    std::string getRoomNumber() const;

    // Setters
    void setBloodType(const std::string& bloodType);
    void setEmergencyContact(const std::string& contact);

    // Medical records management
    void addMedicalHistory(const std::string& record);
    void addMedication(const std::string& medication, const std::string& dosage);
    void addAllergy(const std::string& allergy);

    // Admission control
    void admit(const std::string& roomNumber);
    void discharge();

    // Display methods
    void displayInfo() const override;
    void displayMedicalHistory() const;
    void displayMedications() const;
    void displayAllergies() const;

    // Save to file
    void saveToFile(const std::string& filename) const override;
};

#endif // PATIENT_HH