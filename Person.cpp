#include "Person.hh"
#include <fstream>
#include <iostream>

Person::Person(const std::string& id, const std::string& name, int age,
    const std::string& gender, const std::string& phone,
    const std::string& address)
    : id(id), name(name), age(age), gender(gender), phoneNumber(phone), address(address) {
}

// Getters implementation
std::string Person::getId() const { return id; }
std::string Person::getName() const { return name; }
int Person::getAge() const { return age; }
std::string Person::getGender() const { return gender; }
std::string Person::getPhoneNumber() const { return phoneNumber; }
std::string Person::getAddress() const { return address; }

// Setters implementation
void Person::setName(const std::string& name) { this->name = name; }
void Person::setAge(int age) { this->age = age; }
void Person::setGender(const std::string& gender) { this->gender = gender; }
void Person::setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
void Person::setAddress(const std::string& address) { this->address = address; }

void Person::displayInfo() const {
    std::cout << "ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Age: " << age << "\n";
    std::cout << "Gender: " << gender << "\n";
    std::cout << "Phone: " << phoneNumber << "\n";
    std::cout << "Address: " << address << "\n";
}

void Person::saveToFile(const std::string& filename) const {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << "Person Information:\n";
        file << "ID: " << id << "\n";
        file << "Name: " << name << "\n";
        file << "Age: " << age << "\n";
        file << "Gender: " << gender << "\n";
        file << "Phone: " << phoneNumber << "\n";
        file << "Address: " << address << "\n\n";
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}