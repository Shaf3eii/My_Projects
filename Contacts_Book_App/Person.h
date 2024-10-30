//
// Created by Mahmoud Elshafei on 10/15/2024.
//

#ifndef PERSON_H
#define PERSON_H

#include "Address.h"
#include "Vector.h"

class Person {
    std::string first_name, last_name;
    Vector<std::string> phone_number;
    Vector<std::string> email_address;
    std::string classification;
    Address address;
    bool isFavorite;

    // Basic validation for email ( check if contains '@' )
    bool VaildEmail(std::string &email) {
        if (email.find('@') != std::string::npos && email.find('.') != std::string::npos)
            return true;
        return false;
    }

    // Basic validation for phone number (digits only)
    bool ValidNum(std::string &num) {
        if (num.find_first_not_of("0123456789") == std::string::npos)
            return true;
        return false;
    }

public:

// o(1) time - o(1) memory
    Person() : first_name(""), last_name(""), classification(""), phone_number(Vector<std::string>()),
               email_address(Vector<std::string>()), address(), isFavorite(false) {}

    Person(const std::string& fname, const std::string& lname, const std::string& cla, const Vector<std::string>& phoneNumber,
           const Vector<std::string> &email, const Address &address, bool isFav)
            : first_name(fname), last_name(lname), classification(cla),
              phone_number(phoneNumber), email_address(email), address(address), isFavorite(isFav) {

//        std::cout << std::endl << classification << std::endl;
    }


    Person &operator=(const Person &other) {
        if (this != &other) {
            first_name = other.first_name;
            last_name = other.last_name;
            phone_number = other.phone_number;
            email_address = other.email_address;
            address = other.address;
        }
        return *this;
    }

    bool operator==(const Person &other) const {
        return (first_name == other.first_name && last_name == other.last_name);
    }

    bool operator!=(const Person &other) const {
        return !(*this == other);
    }

    bool operator<(const Person &other) const {
        if (first_name < other.first_name)
            return true;
        if (first_name > other.first_name)
            return false;
        return last_name < other.last_name;
    }

    bool operator>(const Person &other) const {
        return other < *this;
    }

    void setFirst_Name(std::string &fname) { // o(1) time - o(1) memory
        this->first_name = fname;
    }

    std::string getFirst_Name() const {
        return first_name;
    }

    void setLast_Name(std::string &lname) { // o(1) time - o(1) memory
        this->last_name = lname;
    }

    std::string getLast_Name() const { // o(1) time - o(1) memory
        return last_name;
    }

    void setPhone_Number(Vector<std::string> &numbers) { // o(n) time - o(1) memory
        bool valid = true;
        for (int i = 0; i < numbers.getSize(); ++i) {
            if (ValidNum(numbers[i])) {
                phone_number.PushBack(numbers[i]);
            } else {
                std::cerr << "Invalid phone number. Only digits are allowed.\n";
            }
        }
    }

    Vector<std::string> getPhone_Number() const { // o(1) time - o(1) memory
        return phone_number;
    }

    void setEmail_Address(Vector<std::string> &email) { // o(n) time - o(1) memory
        for (int i = 0; i < email.getSize(); ++i) {
            if (VaildEmail(email[i])) {
                this->email_address = email;
            } else {
                std::cerr << "Invalid email address.\n";
            }
        }
    }

    Vector<std::string> getEmail_Address() const { // o(1) time - o(1) memory
        return email_address;
    }

    void setAddress(Address a) { // o(1) time - o(1) memory
        this->address = a;
    }

    Address getAddress() const { // o(1) time - o(1) memory
        return address;
    }

    void setClassification(std::string &cl) {
        classification = cl;
    }

    std::string getClassification() const {
//        std::cout << "getter ==> " << classification << std::endl;
        return classification;
    }

    void setFav(bool fav) {
        isFavorite = fav;
    }

    bool getFav() const {
        return isFavorite;
    }

    std::string get_full_name() const {
        return first_name + ' ' + last_name;
    }

    ~Person() {
        phone_number.clear();
        email_address.clear();
    }

    void printPerson() const {
        std::cout << std::left << std::setw(18) << "First Name: " << getFirst_Name() << std::endl;
        std::cout << std::left << std::setw(18) << "Last Name: " << getLast_Name() << std::endl;
        std::cout << std::left << std::setw(18) << "Class: " << getClassification() << std::endl;
        std::cout << std::left << std::setw(18) << "Numbers: " << getPhone_Number().getElements() << std::endl;
        std::cout << std::left << std::setw(18) << "Emails: " << getEmail_Address().getElements() << std::endl;
        std::cout << std::left << std::setw(18) << "Address: " << getAddress() << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &os, const Person &person);
};

std::ostream &operator<<(std::ostream &os, const Person &person) {
    os << std::left
       << "| " << std::setw(10) << person.getFirst_Name()
       << "| " << std::setw(10) << person.getLast_Name()
       << "| " << std::setw(10) << person.getClassification()
       << "| " << std::setw(10) << (person.getFav() ? "Yes" : "No")
       << "| ";
    for (int i = 0; i < person.getPhone_Number().getSize(); ++i) {
        os << person.getPhone_Number()[i];
        if (i < person.getPhone_Number().getSize() - 1)
            os << ", ";
    }
    os << std::setw(20) << "| ";
    for (int i = 0; i < person.getEmail_Address().getSize(); ++i) {
        os << person.getEmail_Address()[i];
        if (i < person.getEmail_Address().getSize() - 1)
            os << ", ";
    }

    os << std::setw(20) << "| ";
    os << std::setw(30) << person.getAddress() << "| ";

    return os;
}


#endif //PERSON_H
