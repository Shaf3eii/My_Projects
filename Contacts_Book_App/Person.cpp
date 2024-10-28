//
// Created by Mahmoud Elshafei on 10/15/2024.
//

#include <iostream>
#include "Address.cpp"
#include "Person.h"


class Person {
    std::string first_name, last_name;
    std::string phone_number;
    std::string email_address;
    Address address;
public:
    // o(1) time - o(1) memory
    Person(std::string& fname = (std::string &) "", std::string& lname = (std::string &) "" , std::string& phone = (std::string &) "", std::string& email = (std::string &) "", Address& address1 = (Address &) "") :
            first_name(fname), last_name(lname), phone_number(phone), email_address(email), address(address1) { };
    Person(const Person& other) : // o(1) time - o(1) memory
    first_name(other.first_name), last_name(other.last_name), phone_number(other.phone_number), email_address(other.email_address), address(other.address) { };

    Person& operator=(const Person& other) {
        if (this != &other) {
            first_name = other.first_name;
            last_name = other.last_name;
            phone_number = other.phone_number;
            email_address = other.email_address;
            address = other.address;
        }
        return *this;
    }

    bool operator==(const Person& other) {
        return (first_name == other.first_name && last_name == other.last_name && phone_number == other.phone_number && email_address == other.email_address && address == other.address);
    }

    void setFirst_Name(std::string fname) { // o(1) time - o(1) memory
        this->first_name = fname;
    }
    std::string getFirst_Name() const {
        return first_name;
    }
    void setLast_Name(std::string lname) { // o(1) time - o(1) memory
        this->last_name = lname;
    }
    std::string getLast_Name() const { // o(1) time - o(1) memory
        return last_name;
    }
    void setPhone_Number(std::string num) { // o(1) time - o(1) memory
        this->phone_number = num;
    }
    std::string getPhone_Number() const { // o(1) time - o(1) memory
        return phone_number;
    }
    void setAddress(Address a) { // o(1) time - o(1) memory
        this->address = a;
    }
    Address getAddress() const { // o(1) time - o(1) memory
        return address;
    }

    void get_full_information() const { // o(1) time - o(1) memory
        std::cout << this << " Full Information: ";
        std::cout << "\nFirst Name: " << first_name;
        std::cout << "\nLast Name: " << last_name;
        std::cout << "\nPhone Number: " << phone_number;
        std::cout << "\nEmail: " << email_address;
        std::cout << "\nAddress: ";
        address.get_full_address();
        std::cout << '\n';
    }
};

std::ostream &operator<<(std::ostream &os, const Person &person) {
    return <#initializer#>;
}
