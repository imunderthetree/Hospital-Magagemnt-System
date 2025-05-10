#ifndef ADMIN_HH
#define ADMIN_HH

#include <string>
#include <vector>

class Admin {
private:
    std::string username;
    std::string password;

    // Menu file constants
    static const std::string PATIENT_MENU_FILE;
    static const std::string DOCTOR_MENU_FILE;
    static const std::string NURSE_MENU_FILE;

    // Data file constants (added from new.cpp)
    static const std::string DOCTORS_FILE;
    static const std::string NURSES_FILE;
    static const std::string PATIENTS_FILE;

    void createDefaultMenuFiles();
    bool writeMenuFile(const std::string& filename, const std::vector<std::string>& content);
    void editMenuItem(std::vector<std::string>& menu);
    void addMenuItem(std::vector<std::string>& menu);
    void removeMenuItem(std::vector<std::string>& menu);

public:
    Admin(const std::string& uname, const std::string& pwd);

    bool authenticate(const std::string& uname, const std::string& pwd);
    std::vector<std::string> readMenuFile(const std::string& filename);
    void displayMenu(const std::vector<std::string>& menu);

    bool readPatientMenu();
    bool editPatientMenu();
    bool readDoctorMenu();
    bool editDoctorMenu();
    bool readNurseMenu();
    bool editNurseMenu();

    // Methods integrated from new.cpp
    void read_file(const std::string& filename);
    void add_file(const std::string& filename, const std::string& content);
    int set_admin_choice();
};

#endif // ADMIN_HH