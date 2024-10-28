//
// Created by Mahmoud Elshafei on 10/14/2024.
//

#include <iostream>

class Address {
    std::string Street;
    std::string City;
    std::string Country;
public:
    Address(const std::string& street = "", const std::string& city = "", const std::string& country = "") :
            Street(street), City(city), Country(country) { }  // o(1) time - o(1) memory

    // Copy constructor
    Address(const Address& other) : Street(other.Street), City(other.City), Country(other.Country) {} // o(1) time - o(1) memory

    // Copy assignment operator
    Address& operator=(const Address& other) { // o(1) time - o(1) memory
        if (this != &other) {
            Street = other.Street;
            City = other.City;
            Country = other.Country;
        }
        return *this;
    }

    void setStreet(const std::string& street) { // o(1) time - o(1) memory
        this->Street = street;
    }
    std::string getStreet() const { // o(1) time - o(1) memory
        return Street;
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
        return Street == other.Street && City == other.City && Country == other.Country;
    }

    // Convert address to a formatted string
    std::string toString() const {
        return Street + ", " + City + ", " + Country;
    }

    void get_full_address() const { // o(1) time - o(1) memory
        std::cout << "\nFull Address: \nStreet: " << Street << "\nCity: " << City << "\nCountry: " << Country << '\n';
    }

};