//
// Created by Mahmoud Elshafei on 10/14/2024.
//

#ifndef ADDRESS_H
#define ADDRESS_H

#include <iostream>
#include <iomanip>

class Address {
    std::string StreetNumber;
    std::string StreetName;
    std::string City;
    std::string Country;
public:
    Address() : StreetName(""), StreetNumber(""), Country(""), City("") { };
    Address(std::string &num, std::string& streetname, std::string& city, std::string& country) :
            StreetNumber(num), StreetName(streetname), City(city), Country(country) { }  // o(1) time - o(1) memory

    // Copy constructor
    Address(const Address& other) : StreetNumber(other.StreetNumber), StreetName(other.StreetName), City(other.City), Country(other.Country) {} // o(1) time - o(1) memory

    // Copy assignment operator
    Address& operator=(const Address& other) { // o(1) time - o(1) memory
        if (this != &other) {
            StreetNumber = other.StreetNumber;
            StreetName = other.StreetName;
            City = other.City;
            Country = other.Country;
        }
        return *this;
    }

    void setStreetNum(int street) { // o(1) time - o(1) memory
        this->StreetNumber = street;
    }
    std::string getStreetnum() const { // o(1) time - o(1) memory
        return StreetNumber;
    }
    void setStreetName(const std::string& street) { // o(1) time - o(1) memory
        this->StreetName = street;
    }
    std::string getStreetName() const { // o(1) time - o(1) memory
        return StreetName;
    }
    void setCity(const std::string& city) { // o(1) time - o(1) memory
        this->City = city;
    }
    std::string getCity() const { // o(1) time - o(1) memory
        return City;
    }
    void setCountry(const std::string& country) { // o(1) time - o(1) memory
        this->Country = country;
    }
    std::string getCountry() const { // o(1) time - o(1) memory
        return Country;
    }

    bool operator==(const Address& other) const { // o(1) time - o(1) memory
        return StreetNumber == other.StreetNumber && StreetName == other.StreetName && City == other.City && Country == other.Country;
    }

    // Convert address to a formatted string
    std::string toString() const {
        return StreetNumber + " " + StreetName + ", " + City + ", " + Country;
    }

    void get_full_address() const { // O(1) time - O(1) memory
        std::cout << "\n\tFull Address:\n";
        std::cout << std::setw(20) << std::left << "Street Number:" << " " << StreetNumber << '\n';
        std::cout << std::setw(20) << std::left << "Street Name:" << " " << StreetName << '\n';
        std::cout << std::setw(20) << std::left << "City:" << " " << City << '\n';
        std::cout << std::setw(20) << std::left << "Country:" << " " << Country << '\n';
    }

    friend std::ostream& operator<<(std::ostream& os, const Address& address);
};

std::ostream& operator<<(std::ostream& os, const Address& address) {
    os << address.StreetNumber << ", "
       << address.StreetName << ", "
       << address.City << ", "
       << address.Country;
    return os;
}

#endif //CONTACTS_BOOK_APP_ADDRESS_H

