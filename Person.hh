#ifndef PERSON_HH
#define PERSON_HH

#include <string>
#include <vector>

class Person {
protected:
    std::string id;
    std::string name;
    int age;
    std::string gender;
    std::string phoneNumber;
    std::string address;

public:
    Person(const std::string& id, const std::string& name, int age,
        const std::string& gender, const std::string& phone,
        const std::string& address);
    virtual ~Person() {}

    // Getters
    std::string getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getGender() const;
    std::string getPhoneNumber() const;
    std::string getAddress() const;

    // Setters
    void setName(const std::string& name);
    void setAge(int age);
    void setGender(const std::string& gender);
    void setPhoneNumber(const std::string& phone);
    void setAddress(const std::string& address);

    // Display and save methods
    virtual void displayInfo() const;
    virtual void saveToFile(const std::string& filename) const;
};

#endif // PERSON_HH