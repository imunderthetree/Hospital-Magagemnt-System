#include <iostream>
#include <string>
#include <vector>
#include "Person.hh"
#include "Patient.hh"
#include "Doctor.hh"
#include "Nurse.hh"
#include "Admin.hh"
#include "Receptionist.hh"
#include "Ambulance.hh"
#include "HospitalUI.hh"

using namespace std;

int main() {
    cout << "Welcome to Hospital Management System" << endl;

    // Initialize system objects
    Admin admin("admin", "admin123");
    Receptionist reception(7); // Create a receptionist with 7 days schedule
    Ambulance ambulance("Emergency Unit 1", "Main Hospital", true);
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Nurse> nurses;

    // Create the UI manager
    HospitalUI ui;

    int choice;
    bool running = true;

    while (running) {
        choice = ui.displayMainMenu();

        switch (choice) {
        case 1:
            ui.handleAdminMenu(admin);
            break;
        case 2:
            ui.handleReceptionMenu(reception);
            break;
        case 3:
            ui.handlePatientServices(patients);
            break;
        case 4:
            ui.handleMedicalStaffMenu(doctors, nurses);
            break;
        case 5:
            ui.handleAmbulanceServices(ambulance);
            break;
        case 0:
            cout << "Exiting Hospital Management System. Goodbye!" << endl;
            running = false;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}