#include "HospitalUI.hh"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Constants for file names
const string PATIENTS_FILE = "patients.txt";
const string DOCTORS_FILE = "doctors.txt";
const string NURSES_FILE = "nurses.txt";

// Helper function to clear existing content before saving
void prepareFileForSave(const string& filename) {
    ofstream file(filename, ios::trunc);
    file.close();
}

int HospitalUI::displayMainMenu() {
    int choice;
    cout << "\n===== Hospital Management System =====" << endl;
    cout << "1. Admin Menu" << endl;
    cout << "2. Receptionist Menu" << endl;
    cout << "3. Patient Services" << endl;
    cout << "4. Medical Staff" << endl;
    cout << "5. Ambulance Services" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Admin Menu
void HospitalUI::handleAdminMenu(Admin& admin) {
    authenticateAdmin(admin);
}

void HospitalUI::authenticateAdmin(Admin& admin) {
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    if (admin.authenticate(username, password)) {
        cout << "Admin authenticated successfully!" << endl;
        int adminChoice = displayAdminMenu();

        switch (adminChoice) {
        case 1:
            admin.readPatientMenu();
            break;
        case 2:
            admin.editPatientMenu();
            break;
        case 3:
            admin.readDoctorMenu();
            break;
        case 4:
            admin.editDoctorMenu();
            break;
        case 5:
            admin.readNurseMenu();
            break;
        case 6:
            admin.editNurseMenu();
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
    else {
        cout << "Authentication failed!" << endl;
    }
}

int HospitalUI::displayAdminMenu() {
    int choice;
    cout << "\n===== Admin Panel =====" << endl;
    cout << "1. View Patient Menu" << endl;
    cout << "2. Edit Patient Menu" << endl;
    cout << "3. View Doctor Menu" << endl;
    cout << "4. Edit Doctor Menu" << endl;
    cout << "5. View Nurse Menu" << endl;
    cout << "6. Edit Nurse Menu" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Reception Menu
void HospitalUI::handleReceptionMenu(Receptionist& reception) {
    int day = getSelectedDay();
    int receptionChoice = displayReceptionMenu();

    switch (receptionChoice) {
    case 1:
        reception.showAvailableSessions(day);
        break;
    case 2: {
        int hour, minute;
        cout << "Enter hour (8-20): ";
        cin >> hour;
        cout << "Enter minute (0 or 30): ";
        cin >> minute;
        reception.bookSession(day, hour, minute);
        break;
    }
    case 3:
        reception.resetDay(day);
        break;
    case 4:
        reception.advanceDay(day);
        break;
    case 0:
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
}

int HospitalUI::getSelectedDay() {
    int day;
    cout << "Enter day (0-6): ";
    cin >> day;
    return day;
}

int HospitalUI::displayReceptionMenu() {
    int choice;
    cout << "\n===== Reception Services =====" << endl;
    cout << "1. Show Available Sessions" << endl;
    cout << "2. Book a Session" << endl;
    cout << "3. Reset Day Schedule" << endl;
    cout << "4. Advance to Next Day" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

// Patient Services
void HospitalUI::handlePatientServices(vector<Patient>& patients) {
    int patientChoice = displayPatientMenu();

    switch (patientChoice) {
    case 1:
        registerNewPatient(patients);
        break;
    case 2:
        viewPatientInfo(patients);
        break;
    case 3:
        updatePatientInfo(patients);
        break;
    case 4:
        admitPatient(patients);
        break;
    case 5:
        dischargePatient(patients);
        break;
    case 0:
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
}

int HospitalUI::displayPatientMenu() {
    int choice;
    cout << "\n===== Patient Services =====" << endl;
    cout << "1. Register New Patient" << endl;
    cout << "2. View Patient Information" << endl;
    cout << "3. Update Patient Information" << endl;
    cout << "4. Admit Patient" << endl;
    cout << "5. Discharge Patient" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void HospitalUI::registerNewPatient(vector<Patient>& patients) {
    string id, name, gender, phone, address, patientId, bloodType, emergency;
    int age;

    cin.ignore();
    cout << "Enter ID: ";
    getline(cin, id);
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter Gender: ";
    getline(cin, gender);
    cout << "Enter Phone Number: ";
    getline(cin, phone);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Patient ID: ";
    getline(cin, patientId);
    cout << "Enter Blood Type: ";
    getline(cin, bloodType);
    cout << "Enter Emergency Contact: ";
    getline(cin, emergency);

    Patient newPatient(id, name, age, gender, phone, address, patientId, bloodType, emergency);
    patients.push_back(newPatient);

    // Save all patients to file
    prepareFileForSave(PATIENTS_FILE);
    for (auto& patient : patients) {
        patient.saveToFile(PATIENTS_FILE);
    }

    cout << "Patient registered successfully! Data saved to " << PATIENTS_FILE << endl;
}

void HospitalUI::viewPatientInfo(const vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients registered yet!" << endl;
        return;
    }

    string patientId;
    cout << "Enter Patient ID: ";
    cin >> patientId;

    bool found = false;
    for (const auto& patient : patients) {
        if (patient.getPatientId() == patientId) {
            patient.displayInfo();
            patient.displayMedicalHistory();
            patient.displayMedications();
            patient.displayAllergies();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Patient not found!" << endl;
    }
}

void HospitalUI::updatePatientInfo(vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients registered yet!" << endl;
        return;
    }

    string patientId;
    cout << "Enter Patient ID: ";
    cin >> patientId;

    bool found = false;
    for (auto& patient : patients) {
        if (patient.getPatientId() == patientId) {
            int updateChoice;
            cout << "\n===== Update Patient =====" << endl;
            cout << "1. Update Phone Number" << endl;
            cout << "2. Update Address" << endl;
            cout << "3. Add Allergy" << endl;
            cout << "4. Add Medication" << endl;
            cout << "5. Add Medical History" << endl;
            cout << "0. Back" << endl;
            cout << "Enter your choice: ";
            cin >> updateChoice;

            cin.ignore();
            switch (updateChoice) {
            case 1: {
                string phone;
                cout << "Enter new phone number: ";
                getline(cin, phone);
                patient.setPhoneNumber(phone);
                cout << "Phone number updated!" << endl;
                break;
            }
            case 2: {
                string address;
                cout << "Enter new address: ";
                getline(cin, address);
                patient.setAddress(address);
                cout << "Address updated!" << endl;
                break;
            }
            case 3: {
                string allergy;
                cout << "Enter allergy: ";
                getline(cin, allergy);
                patient.addAllergy(allergy);
                cout << "Allergy added!" << endl;
                break;
            }
            case 4: {
                string medication, dosage;
                cout << "Enter medication name: ";
                getline(cin, medication);
                cout << "Enter dosage: ";
                getline(cin, dosage);
                patient.addMedication(medication, dosage);
                cout << "Medication added!" << endl;
                break;
            }
            case 5: {
                string record;
                cout << "Enter medical history record: ";
                getline(cin, record);
                patient.addMedicalHistory(record);
                cout << "Medical history updated!" << endl;
                break;
            }
            case 0:
                break;
            default:
                cout << "Invalid choice!" << endl;
            }

            found = true;

            // Save all patients after update
            prepareFileForSave(PATIENTS_FILE);
            for (auto& p : patients) {
                p.saveToFile(PATIENTS_FILE);
            }
            cout << "Changes saved to " << PATIENTS_FILE << endl;

            break;
        }
    }

    if (!found) {
        cout << "Patient not found!" << endl;
    }
}

void HospitalUI::admitPatient(vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients registered yet!" << endl;
        return;
    }

    string patientId, roomNumber;
    cout << "Enter Patient ID: ";
    cin >> patientId;
    cout << "Enter Room Number: ";
    cin >> roomNumber;

    bool found = false;
    for (auto& patient : patients) {
        if (patient.getPatientId() == patientId) {
            patient.admit(roomNumber);
            found = true;

            // Save all patients after admission
            prepareFileForSave(PATIENTS_FILE);
            for (auto& p : patients) {
                p.saveToFile(PATIENTS_FILE);
            }
            cout << "Admission recorded. Data saved to " << PATIENTS_FILE << endl;

            break;
        }
    }

    if (!found) {
        cout << "Patient not found!" << endl;
    }
}

void HospitalUI::dischargePatient(vector<Patient>& patients) {
    if (patients.empty()) {
        cout << "No patients registered yet!" << endl;
        return;
    }

    string patientId;
    cout << "Enter Patient ID: ";
    cin >> patientId;

    bool found = false;
    for (auto& patient : patients) {
        if (patient.getPatientId() == patientId) {
            patient.discharge();
            found = true;

            // Save all patients after discharge
            prepareFileForSave(PATIENTS_FILE);
            for (auto& p : patients) {
                p.saveToFile(PATIENTS_FILE);
            }
            cout << "Discharge recorded. Data saved to " << PATIENTS_FILE << endl;

            break;
        }
    }

    if (!found) {
        cout << "Patient not found!" << endl;
    }
}

// Medical Staff Menu
void HospitalUI::handleMedicalStaffMenu(vector<Doctor>& doctors, vector<Nurse>& nurses) {
    int staffChoice = displayMedicalStaffMenu();

    switch (staffChoice) {
    case 1:
        registerDoctor(doctors);
        break;
    case 2:
        registerNurse(nurses);
        break;
    case 3:
        viewDoctorInfo(doctors);
        break;
    case 4:
        viewNurseInfo(nurses);
        break;
    case 5:
        updateDoctorSchedule(doctors);
        break;
    case 6:
        updateNurseShifts(nurses);
        break;
    case 0:
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
}

int HospitalUI::displayMedicalStaffMenu() {
    int choice;
    cout << "\n===== Medical Staff =====" << endl;
    cout << "1. Register Doctor" << endl;
    cout << "2. Register Nurse" << endl;
    cout << "3. View Doctor Information" << endl;
    cout << "4. View Nurse Information" << endl;
    cout << "5. Update Doctor Schedule" << endl;
    cout << "6. Update Nurse Shifts" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void HospitalUI::registerDoctor(vector<Doctor>& doctors) {
    string id, name, gender, phone, address, specialization, department, license;
    int age;

    cin.ignore();
    cout << "Enter ID: ";
    getline(cin, id);
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter Gender: ";
    getline(cin, gender);
    cout << "Enter Phone Number: ";
    getline(cin, phone);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Specialization: ";
    getline(cin, specialization);
    cout << "Enter Department: ";
    getline(cin, department);
    cout << "Enter License Number: ";
    getline(cin, license);

    Doctor newDoctor(id, name, age, gender, phone, address, specialization, department, license);
    doctors.push_back(newDoctor);

    // Save all doctors to file
    prepareFileForSave(DOCTORS_FILE);
    for (auto& doctor : doctors) {
        doctor.saveToFile(DOCTORS_FILE);
    }

    cout << "Doctor registered successfully! Data saved to " << DOCTORS_FILE << endl;
}

void HospitalUI::registerNurse(vector<Nurse>& nurses) {
    string id, name, gender, phone, address, department, nurseId;
    int age;

    cin.ignore();
    cout << "Enter ID: ";
    getline(cin, id);
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter Gender: ";
    getline(cin, gender);
    cout << "Enter Phone Number: ";
    getline(cin, phone);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Department: ";
    getline(cin, department);
    cout << "Enter Nurse ID: ";
    getline(cin, nurseId);

    Nurse newNurse(id, name, age, gender, phone, address, department, nurseId);
    nurses.push_back(newNurse);

    // Save all nurses to file
    prepareFileForSave(NURSES_FILE);
    for (auto& nurse : nurses) {
        nurse.saveToFile(NURSES_FILE);
    }

    cout << "Nurse registered successfully! Data saved to " << NURSES_FILE << endl;
}

void HospitalUI::viewDoctorInfo(const vector<Doctor>& doctors) {
    if (doctors.empty()) {
        cout << "No doctors registered yet!" << endl;
        return;
    }

    string doctorId;
    cout << "Enter Doctor ID: ";
    cin >> doctorId;

    bool found = false;
    for (const auto& doctor : doctors) {
        if (doctor.getId() == doctorId) {
            doctor.displayInfo();
            doctor.displaySchedule();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Doctor not found!" << endl;
    }
}

void HospitalUI::viewNurseInfo(const vector<Nurse>& nurses) {
    if (nurses.empty()) {
        cout << "No nurses registered yet!" << endl;
        return;
    }

    string nurseId;
    cout << "Enter Nurse ID: ";
    cin >> nurseId;

    bool found = false;
    for (const auto& nurse : nurses) {
        if (nurse.getNurseId() == nurseId) {
            nurse.displayInfo();
            nurse.displayShifts();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Nurse not found!" << endl;
    }
}

void HospitalUI::updateDoctorSchedule(vector<Doctor>& doctors) {
    if (doctors.empty()) {
        cout << "No doctors registered yet!" << endl;
        return;
    }

    string doctorId;
    cout << "Enter Doctor ID: ";
    cin >> doctorId;

    bool found = false;
    for (auto& doctor : doctors) {
        if (doctor.getId() == doctorId) {
            int scheduleChoice;
            cout << "\n===== Doctor Schedule =====" << endl;
            cout << "1. Add Schedule Slot" << endl;
            cout << "2. Remove Schedule Slot" << endl;
            cout << "3. Display Schedule" << endl;
            cout << "4. Clear Schedule" << endl;
            cout << "0. Back" << endl;
            cout << "Enter your choice: ";
            cin >> scheduleChoice;

            switch (scheduleChoice) {
            case 1: {
                int day, hour;
                cout << "Enter day (0-6, where 0 is Sunday): ";
                cin >> day;
                cout << "Enter hour (8-20): ";
                cin >> hour;
                doctor.addScheduleSlot(day, hour);
                cout << "Schedule slot added!" << endl;
                break;
            }
            case 2: {
                int day, hour;
                cout << "Enter day (0-6, where 0 is Sunday): ";
                cin >> day;
                cout << "Enter hour (8-20): ";
                cin >> hour;
                doctor.removeScheduleSlot(day, hour);
                cout << "Schedule slot removed!" << endl;
                break;
            }
            case 3:
                doctor.displaySchedule();
                break;
            case 4:
                doctor.clearSchedule();
                cout << "Schedule cleared!" << endl;
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice!" << endl;
            }

            found = true;

            // Save all doctors after schedule update
            prepareFileForSave(DOCTORS_FILE);
            for (auto& d : doctors) {
                d.saveToFile(DOCTORS_FILE);
            }
            cout << "Schedule updated. Data saved to " << DOCTORS_FILE << endl;

            break;
        }
    }

    if (!found) {
        cout << "Doctor not found!" << endl;
    }
}

void HospitalUI::updateNurseShifts(vector<Nurse>& nurses) {
    if (nurses.empty()) {
        cout << "No nurses registered yet!" << endl;
        return;
    }

    string nurseId;
    cout << "Enter Nurse ID: ";
    cin >> nurseId;

    bool found = false;
    for (auto& nurse : nurses) {
        if (nurse.getNurseId() == nurseId) {
            int shiftChoice;
            cout << "\n===== Nurse Shifts =====" << endl;
            cout << "1. Add Shift" << endl;
            cout << "2. Remove Shift" << endl;
            cout << "3. Display Shifts" << endl;
            cout << "4. Clear Shifts" << endl;
            cout << "0. Back" << endl;
            cout << "Enter your choice: ";
            cin >> shiftChoice;

            switch (shiftChoice) {
            case 1: {
                int day, hour;
                cout << "Enter day (0-6, where 0 is Sunday): ";
                cin >> day;
                cout << "Enter hour (0-23): ";
                cin >> hour;
                nurse.addShift(day, hour);
                cout << "Shift added!" << endl;
                break;
            }
            case 2: {
                int day, hour;
                cout << "Enter day (0-6, where 0 is Sunday): ";
                cin >> day;
                cout << "Enter hour (0-23): ";
                cin >> hour;
                nurse.removeShift(day, hour);
                cout << "Shift removed!" << endl;
                break;
            }
            case 3:
                nurse.displayShifts();
                break;
            case 4:
                nurse.clearShifts();
                cout << "Shifts cleared!" << endl;
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice!" << endl;
            }

            found = true;

            // Save all nurses after shift update
            prepareFileForSave(NURSES_FILE);
            for (auto& n : nurses) {
                n.saveToFile(NURSES_FILE);
            }
            cout << "Shifts updated. Data saved to " << NURSES_FILE << endl;

            break;
        }
    }

    if (!found) {
        cout << "Nurse not found!" << endl;
    }
}

// Ambulance Services
void HospitalUI::handleAmbulanceServices(Ambulance& ambulance) {
    int ambulanceChoice = displayAmbulanceMenu();

    switch (ambulanceChoice) {
    case 1:
        ambulance.call();
        break;
    case 2:
        cout << "Ambulance Status: " << (ambulance.isAvailable() ? "Available" : "Not Available") << endl;
        break;
    case 3:
        ambulance.freeAmbulance();
        break;
    case 0:
        break;
    default:
        cout << "Invalid choice!" << endl;
    }
}

int HospitalUI::displayAmbulanceMenu() {
    int choice;
    cout << "\n===== Ambulance Services =====" << endl;
    cout << "1. Call Ambulance" << endl;
    cout << "2. Check Ambulance Status" << endl;
    cout << "3. Free Ambulance" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}