#ifndef HOSPITAL_UI_HH
#define HOSPITAL_UI_HH

#include "Admin.hh"
#include "Receptionist.hh"
#include "Patient.hh"
#include "Doctor.hh"
#include "Nurse.hh"
#include "Ambulance.hh"
#include <vector>

class HospitalUI {
public:
    // Main Menu
    int displayMainMenu();

    // Admin Menu
    void handleAdminMenu(Admin& admin);
    void authenticateAdmin(Admin& admin);
    int displayAdminMenu();

    // Reception Menu
    void handleReceptionMenu(Receptionist& reception);
    int getSelectedDay();
    int displayReceptionMenu();

    // Patient Services
    void handlePatientServices(std::vector<Patient>& patients);
    int displayPatientMenu();
    void registerNewPatient(std::vector<Patient>& patients);
    void viewPatientInfo(const std::vector<Patient>& patients);
    void updatePatientInfo(std::vector<Patient>& patients);
    void admitPatient(std::vector<Patient>& patients);
    void dischargePatient(std::vector<Patient>& patients);

    // Medical Staff
    void handleMedicalStaffMenu(std::vector<Doctor>& doctors, std::vector<Nurse>& nurses);
    int displayMedicalStaffMenu();
    void registerDoctor(std::vector<Doctor>& doctors);
    void registerNurse(std::vector<Nurse>& nurses);
    void viewDoctorInfo(const std::vector<Doctor>& doctors);
    void viewNurseInfo(const std::vector<Nurse>& nurses);
    void updateDoctorSchedule(std::vector<Doctor>& doctors);
    void updateNurseShifts(std::vector<Nurse>& nurses);

    // Ambulance Services
    void handleAmbulanceServices(Ambulance& ambulance);
    int displayAmbulanceMenu();
};

#endif // HOSPITAL_UI_HH