//
// Created by Mahmoud Elshafei on 10/15/2024.
//

#ifndef CONTACTS_BOOK_APP_CONTACTSBOOK_H
#define CONTACTS_BOOK_APP_CONTACTSBOOK_H

#include "Person.h"
#include "Vector.h"
#include <fstream>

class Contacts {
    Vector<Person> contacts;

    bool is_exist(Person &p) const { // o(n) time - o(1) memory
        return contacts.find(p) != -1; // if -1 -> does not exist
    }

    bool ThePhoneNumberDoesNotExist(Vector<std::string> phone) const {
        for (int i = 0; i < contacts.getSize(); ++i) {
            if (contacts[i].getPhone_Number() == phone)
                return true; // exist
        }
        return false;
    }

public:
    Contacts() = default; // o(1) time - o(1) memory

    void AddNewContact(Person newContact) { // best case (if the contact does not exist) o(1) time - worst case o(n)
        if (is_exist(newContact))
            return std::cerr << "This Contact is already exist..\n\n", void();
        if (ThePhoneNumberDoesNotExist(newContact.getPhone_Number()))
            return std::cerr << "This Phone Number is already exist..\n\n", void();

        contacts.PushBack(newContact);
        std::cout << "This contact added successfully..\n\n";
    }

    void removeContact(Person &p) { // o(n) time - o(1) memory
        if (!is_exist(p))
            return std::cerr << "This Contact is not exist..\n\n", void();

        size_t pos = contacts.find(p); // o(n) time
        contacts.remove(pos);          // o(n) time
        std::cout << "This contact removed successfully..\n\n";
    }

    void searchContactbyfirstName(const std::string &name) const { // o(n) time - o(1) memory
        bool flag = false;
        for (int i = 0; i < contacts.getSize(); ++i) {
            if (contacts[i].getFirst_Name() == name) {
                contacts[i].printPerson();
                flag = true;
            }
        }
        if (!flag)
            std::cerr << "This name is undefined..\n\n";
    }

    void searchContactbylastName(const std::string &name) const { // o(n) time - o(1) memory
        bool flag = false;
        for (int i = 0; i < contacts.getSize(); ++i) {
            if (contacts[i].getLast_Name() == name) {
                contacts[i].printPerson();
                flag = true;
            }
        }
        if (!flag)
            std::cerr << "This name is undefined..\n\n";
    }

    void searchContactbyFullName(const std::string &fname, const std::string &lname) const { // o(n) time - o(1) memory
        bool flag = false;
        for (int i = 0; i < contacts.getSize(); ++i) {
            if (contacts[i].getFirst_Name() == fname && contacts[i].getLast_Name() == lname) {
                contacts[i].printPerson();
                flag = true;
            }
        }
        if (!flag)
            std::cout << "This name is undefined..\n\n";
    }

    void searchContactbyPhoneNumber(const Vector<std::string> &phone) const { // o(n) time - o(1) memory
        for (int i = 0; i < contacts.getSize(); ++i) {
            if (contacts[i].getPhone_Number() == phone)
                return contacts[i].printPerson(), void();
        }
    }

    void searchContactbyclass(const std::string &classif) const { // o(n) time - o(1) memory
        for (int i = 0; i < contacts.getSize(); ++i) {
            if (contacts[i].getClassification() == classif)
                return contacts[i].printPerson(), void();
        }
    }

    Person findContact(Vector<std::string> &phone) { // o(n) time - o(1) memory
        for (int i = 0; i < contacts.getSize(); ++i) {
            if (contacts[i].getPhone_Number() == phone)
                return contacts[i];
        }
        std::cerr << "This Contact not found..\n\n";
    }

    void updateContact(Person &oldContact, Person &newContact) { // o(n) time - o(1) memory
        if (!is_exist(oldContact))
            return std::cerr << "This Contact is not exist..\n\n", void();

        size_t pos = contacts.find(oldContact);
        if (ThePhoneNumberDoesNotExist(newContact.getPhone_Number()) &&
            oldContact.getPhone_Number() != newContact.getPhone_Number())
            return std::cerr << "This new phone number already exists in another contact.\n\n", void();

        contacts[pos] = newContact;
        std::cout << "This contact updated Successfully..\n\n";
    }

    void removeAllContacts() { // o(n) time - o(1) memory
        contacts.clear();
        std::cout << "All contacts have been removed..\n\n";
    }

    size_t countContacts() const { // o(1) time - o(1) memory
        return contacts.getSize();
    }

    void sortContacts() { // o(n^2) time - o(1) memory
        contacts.sort();
    }

    void reverseContacts() { // o(n) time - o(1) memory
        contacts.reverse();
    }

    void printFav() {
        for(int i = 0 ; i < contacts.getSize() ; ++i) {
            if(contacts[i].getFav()) {
                std::cout << contacts[i] << '\n';
            }
        }
    }

    void saveToFile() {
        std::ofstream outfile("contacts.txt");
        if (!outfile) {
            return std::cerr << "Error opening file for writing..\n", void();
        }

        for (int i = 0; i < contacts.getSize(); ++i) {
            const auto &contact = contacts[i];
            const Address &address = contact.getAddress();

            // Save each attribute separated by commas, with classification and isFav flag at the end
            outfile << contact.getFirst_Name() << ","
                    << contact.getLast_Name() << ","
                    << contact.getClassification() << ","
                    << contact.getPhone_Number().getSize() << ",";  // write phone count first

            for (int j = 0; j < contact.getPhone_Number().getSize(); ++j) {
                if (j > 0) outfile << ","; // separate multiple phones
                outfile << contact.getPhone_Number().getElement(j);
            }
            outfile << "," << contact.getEmail_Address().getSize() << ",";  // write email count

            for (int j = 0; j < contact.getEmail_Address().getSize(); ++j) {
                if (j > 0) outfile << ",";
                outfile << contact.getEmail_Address().getElement(j);
            }

            outfile << "," << address.getStreetnum() << ","
                    << address.getStreetName() << ","
                    << address.getCity() << ","
                    << address.getCountry() << ","
                    << (contact.getFav() ? "1" : "0") << "\n";
        }
        outfile.close();
        std::cout << "Contacts saved to file..\n";
    }

    void loadFromFile() {
        std::ifstream infile("contacts.txt");
        if (!infile) {
            return std::cerr << "Error opening file for reading..\n", void();
        }

        std::string line;
        while (getline(infile, line)) {
            std::stringstream ss(line);

            std::string firstName, lastName, classification, phoneStr, emailStr;
            std::string num, street, city, country, isFavStr;

            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, classification, ',');

            int numPhones;
            ss >> numPhones;
            ss.ignore(1, ',');  // skip comma
            Vector<std::string> phones;
            for (int i = 0; i < numPhones; ++i) {
                std::string phone;
                getline(ss, phone, ',');
                phones.PushBack(phone);
            }

            int numEmails;
            ss >> numEmails;
            ss.ignore(1, ',');  // skip comma
            Vector<std::string> emails;
            for (int i = 0; i < numEmails; ++i) {
                std::string email;
                getline(ss, email, ',');
                emails.PushBack(email);
            }

            getline(ss, num, ',');
            getline(ss, street, ',');
            getline(ss, city, ',');
            getline(ss, country, ',');

            getline(ss, isFavStr, ',');
            bool isFav = (isFavStr == "1");
            Address address(num, street, city, country);
            contacts.PushBack(Person(firstName, lastName, classification, phones, emails, address, isFav));
        }

        infile.close();
        std::cout << contacts.getSize() << " Contacts loaded successfully!\n";
    }


    ~Contacts() {
        contacts.clear();
    }

    void listContacts() const {
        const int firstNameWidth = 18;
        const int lastNameWidth = 18;
        const int cityWidth = 18;
        const int countryWidth = 18;
        const int streetWidth = 18;
        const int homeNumberWidth = 18;
        const int phoneWidth = 18;
        const int classificationWidth = 18;

        const int totalWidth = firstNameWidth + lastNameWidth + cityWidth + countryWidth +
                               streetWidth + homeNumberWidth + phoneWidth + classificationWidth + 13;

        // Print header
        std::cout << "♖" << std::string(totalWidth, '-') << "♖\n";
        std::cout << "|" << std::left << std::setw(firstNameWidth) << "First Name" << "| "
                  << std::setw(lastNameWidth) << "Last Name" << "| "
                  << std::setw(cityWidth) << "City" << "| "
                  << std::setw(countryWidth) << "Country" << "| "
                  << std::setw(streetWidth) << "Street Number" << "| "
                  << std::setw(homeNumberWidth) << "Street Name" << "| "
                  << std::setw(phoneWidth) << "Phone Number" << "| "
                  << std::setw(classificationWidth) << "Classification" << "|\n";
        std::cout << "↕" << std::string(totalWidth, '-') << "↕\n";


        int n = contacts.getSize();
        for (int i = 0; i < n; i++) {
            Person p = contacts.getElement(i);
            Address a = p.getAddress();

            std::string phoneOutput;
            if (p.getPhone_Number().getSize() > 0) {
                phoneOutput = p.getPhone_Number().getElement(0);  // First phone number
            }

//            std::cout << "get ==> " << p << std::endl;

            std::cout << "|" << std::left << std::setw(firstNameWidth) << p.getFirst_Name() << "| "
                      << std::setw(lastNameWidth) << p.getLast_Name() << "| "
                      << std::setw(cityWidth) << a.getCity() << "| "
                      << std::setw(countryWidth) << a.getCountry() << "| "
                      << std::setw(streetWidth) << a.getStreetnum() << "| "
                      << std::setw(homeNumberWidth) << a.getStreetName() << "| "
                      << std::setw(phoneWidth) << phoneOutput << "| "
                      << std::setw(classificationWidth) << p.getClassification() << "|\n";


            // Table row divider
            if (i == n - 1) {
                std::cout << "♖" << std::string(totalWidth, '-') << "♖\n";
            } else {
                std::cout << "↕" << std::string(totalWidth, '-') << "↕\n";
            }

        }
    }


};


#endif //CONTACTS_BOOK_APP_CONTACTSBOOK_H
