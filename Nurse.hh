#ifndef NURSE_HH
#define NURSE_HH

#include "Person.hh"
#include <vector>
#include <utility> // for std::pair

class Nurse : public Person {
private:
    std::string department;
    std::string nurseId;
    std::vector<std::pair<int, int>> shifts; // day and hour

public:
    Nurse(const std::string& id, const std::string& name, int age,
        const std::string& gender, const std::string& phone,
        const std::string& address, const std::string& department,
        const std::string& nurseId);

    // Getters
    std::string getDepartment() const;
    std::string getNurseId() const;

    // Setters
    void setDepartment(const std::string& department);
    void setNurseId(const std::string& nurseId);

    // Shift management
    void addShift(int day, int hour);
    void removeShift(int day, int hour);
    void clearShifts();
    void displayShifts() const;

    // Display and save methods
    void displayInfo() const override;
    void saveToFile(const std::string& filename) const override;
};

#endif // NURSE_HH