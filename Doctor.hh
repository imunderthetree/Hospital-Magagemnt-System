#ifndef DOCTOR_HH
#define DOCTOR_HH

#include "Person.hh"
#include <vector>
#include <utility> // for std::pair

class Doctor : public Person {
private:
    std::string specialization;
    std::string department;
    std::string licenseNumber;
    std::vector<std::pair<int, int>> schedule; // day and hour

public:
    Doctor(const std::string& id, const std::string& name, int age,
        const std::string& gender, const std::string& phone,
        const std::string& address, const std::string& specialization,
        const std::string& department, const std::string& licenseNumber);

    // Getters
    std::string getSpecialization() const;
    std::string getDepartment() const;
    std::string getLicenseNumber() const;

    // Setters
    void setSpecialization(const std::string& specialization);
    void setDepartment(const std::string& department);
    void setLicenseNumber(const std::string& license);

    // Schedule management
    void addScheduleSlot(int day, int hour);
    void removeScheduleSlot(int day, int hour);
    void clearSchedule();
    void displaySchedule() const;

    // Display and save methods
    void displayInfo() const override;
    void saveToFile(const std::string& filename) const override;
};

#endif // DOCTOR_HH