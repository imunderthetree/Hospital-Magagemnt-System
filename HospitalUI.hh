#ifndef HOSPITAL_UI_HH
#define HOSPITAL_UI_HH

#include <iostream>
#include <string>
#include <vector>
#include "Admin.hh"
#include "Receptionist.hh"
#include "Patient.hh"
#include "Doctor.hh"
#include "Nurse.hh"
#include "Ambulance.hh"

class HospitalUI {
public:
    HospitalUI() = default;
    ~HospitalUI() = default;

    // Main menu display
    int displayMainMenu();

    // Handle different menu sections
    void handleAdminMenu(Admin& admin);
    void handleReceptionMenu(Receptionist& reception);
    void handlePatientServices(std::vector<Patient>& patients);
    void handleMedicalStaffMenu(std::vector<Doctor>& doctors, std::vector<Nurse>& nurses);
    void handleAmbulanceServices(Ambulance& ambulance);

private:
    // Admin sub-menus
    int displayAdminMenu();
    void authenticateAdmin(Admin& admin);

    // Reception sub-menus
    int displayReceptionMenu();
    int getSelectedDay();

    // Patient sub-menus
    int displayPatientMenu();
    void registerNewPatient(std::vector<Patient>& patients);
    void viewPatientInfo(const std::vector<Patient>& patients);
    void updatePatientInfo(std::vector<Patient>& patients);
    void admitPatient(std::vector<Patient>& patients);
    void dischargePatient(std::vector<Patient>& patients);

    // Medical staff sub-menus
    int displayMedicalStaffMenu();
    void registerDoctor(std::vector<Doctor>& doctors);
    void registerNurse(std::vector<Nurse>& nurses);
    void viewDoctorInfo(const std::vector<Doctor>& doctors);
    void viewNurseInfo(const std::vector<Nurse>& nurses);
    void updateDoctorSchedule(std::vector<Doctor>& doctors);
    void updateNurseShifts(std::vector<Nurse>& nurses);

    // Ambulance sub-menus
    int displayAmbulanceMenu();
};

#endif // HOSPITAL_UI_HH