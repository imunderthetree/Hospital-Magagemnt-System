#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>

using namespace std;

class Admin {
private:
    string username;
    string password;

    void createDefaultMenuFiles();
    vector<string> readMenuFile(const string& filename);
    bool writeMenuFile(const string& filename, const vector<string>& content);
    void displayMenu(const vector<string>& menu);
    void editMenuItem(vector<string>& menu);
    void addMenuItem(vector<string>& menu);
    void removeMenuItem(vector<string>& menu);

public:
    static const string PATIENT_MENU_FILE;
    static const string DOCTOR_MENU_FILE;
    static const string NURSE_MENU_FILE;

    Admin(const string& uname, const string& pwd);
    bool authenticate(const string& uname, const string& pwd);
    bool readPatientMenu();
    bool editPatientMenu();
    bool readDoctorMenu();
    bool editDoctorMenu();
    bool readNurseMenu();
    bool editNurseMenu();
};

#endif // ADMIN_H