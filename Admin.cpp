
#include "Admin.hh" 
#include <iostream>
#include <fstream>


#include <iostream>
#include <fstream>

using namespace std;
const string Admin::PATIENT_MENU_FILE = "patient_menu.txt";
const string Admin::DOCTOR_MENU_FILE = "doctor_menu.txt";
const string Admin::NURSE_MENU_FILE = "nurse_menu.txt";

Admin::Admin(const string& uname, const string& pwd)
    : username(uname), password(pwd) {
    createDefaultMenuFiles();
}

bool Admin::authenticate(const string& uname, const string& pwd) {
    return (username == uname && password == pwd);
}

void Admin::createDefaultMenuFiles() {
    ifstream patientFile(PATIENT_MENU_FILE);
    if (!patientFile.good()) {
        vector<string> defaultPatientMenu = {
            "1. View Personal Information",
            "2. Update Contact Information",
            "3. View Medical History",
            "4. View Current Medications",
            "5. Schedule Appointment",
            "6. View Upcoming Appointments",
            "7. Request Prescription Refill",
            "8. Exit"
        };
        writeMenuFile(PATIENT_MENU_FILE, defaultPatientMenu);
    }
    patientFile.close();

    ifstream doctorFile(DOCTOR_MENU_FILE);
    if (!doctorFile.good()) {
        vector<string> defaultDoctorMenu = {
            "1. View Patient List",
            "2. View Patient Details",
            "3. Update Patient Record",
            "4. Add New Patient",
            "5. Prescribe Medication",
            "6. Schedule Appointment",
            "7. View Appointment Calendar",
            "8. Exit"
        };
        writeMenuFile(DOCTOR_MENU_FILE, defaultDoctorMenu);
    }
    doctorFile.close();

    ifstream nurseFile(NURSE_MENU_FILE);
    if (!nurseFile.good()) {
        vector<string> defaultNurseMenu = {
            "1. View Assigned Patients",
            "2. Record Vital Signs",
            "3. View Patient Details",
            "4. Add Task",
            "5. View Tasks",
            "6. Mark Task as Completed",
            "7. View Schedule",
            "8. Exit"
        };
        writeMenuFile(NURSE_MENU_FILE, defaultNurseMenu);
    }
    nurseFile.close();
}

vector<string> Admin::readMenuFile(const string& filename) {
    vector<string> menuContent;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return menuContent;
    }

    string line;
    while (getline(file, line)) {
        menuContent.push_back(line);
    }

    file.close();
    return menuContent;
}

bool Admin::writeMenuFile(const string& filename, const vector<string>& content) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return false;
    }

    for (const auto& line : content) {
        file << line << "\n";
    }

    file.close();
    return true;
}

void Admin::displayMenu(const vector<string>& menu) {
    for (const auto& line : menu) {
        cout << line << endl;
    }
}

void Admin::editMenuItem(vector<string>& menu) {
    if (menu.empty()) {
        cout << "Menu is empty. Nothing to edit." << endl;
        return;
    }

    cout << "Current menu items:" << endl;
    for (size_t i = 0; i < menu.size(); i++) {
        cout << i + 1 << ": " << menu[i] << endl;
    }

    int choice;
    cout << "Enter the number of the item to edit (1-" << menu.size() << "): ";
    cin >> choice;

    if (choice < 1 || choice > static_cast<int>(menu.size())) {
        cout << "Invalid choice." << endl;
        return;
    }

    cin.ignore();
    string newText;
    cout << "Enter new text for this menu item: ";
    getline(cin, newText);

    menu[choice - 1] = newText;
    cout << "Menu item updated successfully." << endl;
}

void Admin::addMenuItem(vector<string>& menu) {
    cin.ignore();
    string newItem;
    cout << "Enter new menu item text: ";
    getline(cin, newItem);

    menu.push_back(newItem);
    cout << "Menu item added successfully." << endl;
}

void Admin::removeMenuItem(vector<string>& menu) {
    if (menu.empty()) {
        cout << "Menu is empty. Nothing to remove." << endl;
        return;
    }

    cout << "Current menu items:" << endl;
    for (size_t i = 0; i < menu.size(); i++) {
        cout << i + 1 << ": " << menu[i] << endl;
    }

    int choice;
    cout << "Enter the number of the item to remove (1-" << menu.size() << "): ";
    cin >> choice;

    if (choice < 1 || choice > static_cast<int>(menu.size())) {
        cout << "Invalid choice." << endl;
        return;
    }

    menu.erase(menu.begin() + choice - 1);
    cout << "Menu item removed successfully." << endl;
}

bool Admin::readPatientMenu() {
    vector<string> menu = readMenuFile(PATIENT_MENU_FILE);

    if (menu.empty()) {
        cout << "Patient menu is empty or could not be read." << endl;
        return false;
    }

    cout << "\n===== Patient Menu =====\n";
    displayMenu(menu);
    return true;
}

bool Admin::editPatientMenu() {
    vector<string> menu = readMenuFile(PATIENT_MENU_FILE);

    if (menu.empty()) {
        cout << "Creating new patient menu file." << endl;
    }

    bool editing = true;
    while (editing) {
        cout << "\n===== Edit Patient Menu =====\n";
        cout << "1. View current menu\n";
        cout << "2. Edit a menu item\n";
        cout << "3. Add a menu item\n";
        cout << "4. Remove a menu item\n";
        cout << "5. Save and exit\n";
        cout << "0. Exit without saving\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            if (menu.empty()) {
                cout << "Menu is currently empty." << endl;
            }
            else {
                displayMenu(menu);
            }
            break;
        case 2:
            editMenuItem(menu);
            break;
        case 3:
            addMenuItem(menu);
            break;
        case 4:
            removeMenuItem(menu);
            break;
        case 5:
            if (writeMenuFile(PATIENT_MENU_FILE, menu)) {
                cout << "Patient menu saved successfully." << endl;
            }
            else {
                cout << "Failed to save patient menu." << endl;
            }
            editing = false;
            break;
        case 0:
            cout << "Exiting without saving changes." << endl;
            editing = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return true;
}

bool Admin::readDoctorMenu() {
    vector<string> menu = readMenuFile(DOCTOR_MENU_FILE);

    if (menu.empty()) {
        cout << "Doctor menu is empty or could not be read." << endl;
        return false;
    }

    cout << "\n===== Doctor Menu =====\n";
    displayMenu(menu);
    return true;
}

bool Admin::editDoctorMenu() {
    vector<string> menu = readMenuFile(DOCTOR_MENU_FILE);

    if (menu.empty()) {
        cout << "Creating new doctor menu file." << endl;
    }

    bool editing = true;
    while (editing) {
        cout << "\n===== Edit Doctor Menu =====\n";
        cout << "1. View current menu\n";
        cout << "2. Edit a menu item\n";
        cout << "3. Add a menu item\n";
        cout << "4. Remove a menu item\n";
        cout << "5. Save and exit\n";
        cout << "0. Exit without saving\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            if (menu.empty()) {
                cout << "Menu is currently empty." << endl;
            }
            else {
                displayMenu(menu);
            }
            break;
        case 2:
            editMenuItem(menu);
            break;
        case 3:
            addMenuItem(menu);
            break;
        case 4:
            removeMenuItem(menu);
            break;
        case 5:
            if (writeMenuFile(DOCTOR_MENU_FILE, menu)) {
                cout << "Doctor menu saved successfully." << endl;
            }
            else {
                cout << "Failed to save doctor menu." << endl;
            }
            editing = false;
            break;
        case 0:
            cout << "Exiting without saving changes." << endl;
            editing = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return true;
}

bool Admin::readNurseMenu() {
    vector<string> menu = readMenuFile(NURSE_MENU_FILE);

    if (menu.empty()) {
        cout << "Nurse menu is empty or could not be read." << endl;
        return false;
    }

    cout << "\n===== Nurse Menu =====\n";
    displayMenu(menu);
    return true;
}

bool Admin::editNurseMenu() {
    vector<string> menu = readMenuFile(NURSE_MENU_FILE);

    if (menu.empty()) {
        cout << "Creating new nurse menu file." << endl;
    }

    bool editing = true;
    while (editing) {
        cout << "\n===== Edit Nurse Menu =====\n";
        cout << "1. View current menu\n";
        cout << "2. Edit a menu item\n";
        cout << "3. Add a menu item\n";
        cout << "4. Remove a menu item\n";
        cout << "5. Save and exit\n";
        cout << "0. Exit without saving\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            if (menu.empty()) {
                cout << "Menu is currently empty." << endl;
            }
            else {
                displayMenu(menu);
            }
            break;
        case 2:
            editMenuItem(menu);
            break;
        case 3:
            addMenuItem(menu);
            break;
        case 4:
            removeMenuItem(menu);
            break;
        case 5:
            if (writeMenuFile(NURSE_MENU_FILE, menu)) {
                cout << "Nurse menu saved successfully." << endl;
            }
            else {
                cout << "Failed to save nurse menu." << endl;
            }
            editing = false;
            break;
        case 0:
            cout << "Exiting without saving changes." << endl;
            editing = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return true;
}