#include "ContactsBook.h"


void Welcome();
void MainMenu();
Person GetInformation();
void addNewContact(Contacts &contacts);
void removeContact(Contacts &contacts);
void searchContact(Contacts &contacts);
void ListContacts(Contacts &contacts);
void ListFavContacts(Contacts &contacts);
void UpdateContact(Contacts &contacts);
void NumberOfCurrentContacts(Contacts &contacts);
void SortContacts(Contacts &contacts);
void ClearContacts(Contacts &contacts);
void ReverseContacts(Contacts &contacts);
void saveFile(Contacts &contacts);
void loadFile(Contacts &contacts);
void Exit();

int main() {
    system("color 0B");
    Welcome();
    MainMenu();
    Contacts contacts;
    int op;
    bool flag = true;
    do {
        std::cin >> op;
        switch (op) {
            case 1:
                addNewContact(contacts);
                break;
            case 2:
                removeContact(contacts);
                break;
            case 3:
                searchContact(contacts);
                break;
            case 4:
                ListContacts(contacts);
                break;
            case 5:
                ListFavContacts(contacts);
                break;
            case 6:
                UpdateContact(contacts);
                break;
            case 7:
                NumberOfCurrentContacts(contacts);
                break;
            case 8:
                SortContacts(contacts);
                break;
            case 9:
                ClearContacts(contacts);
                break;
            case 10:
                ReverseContacts(contacts);
                break;
            case 11:
                saveFile(contacts);
                break;
            case 12:
                loadFile(contacts);
                break;
            case 13:
                Exit();
                flag = false;
                break;
            default:
                std::cout << "Enter a valid choice from 1 to 9 ..\n";
        }
    } while (flag);
    return 0;
}

void Welcome() {
    std::cout << "\t\tWelcome to our Contact Book App\n";
}

void MainMenu() {
    std::cout << "\t\t=============================\n";
    std::cout << "\t\t     Contacts Book Menu:      \n";
    std::cout << "\t\t-----------------------------\n";
    std::cout << "\t\t1. Add a new Contact\n";
    std::cout << "\t\t2. Delete Contact\n";
    std::cout << "\t\t3. Search Contact\n";
    std::cout << "\t\t4. Print All Contacts\n";
    std::cout << "\t\t5. Print Favourite Contacts\n";
    std::cout << "\t\t6. Update Contact Information\n";
    std::cout << "\t\t7. The number of contacts\n";
    std::cout << "\t\t8. Sort contacts book\n";
    std::cout << "\t\t9. Remove contacts book\n";
    std::cout << "\t\t10. Reverse contacts book\n";
    std::cout << "\t\t11. Save contacts book\n";
    std::cout << "\t\t12. Load contacts book\n";
    std::cout << "\t\t13. Exit\n";
    std::cout << "\t\t=============================\n";
    std::cout << "Enter your choice: ";
}

Person GetInformation() {
    std::cout << "Enter the contact information: ";
    std::cout << "\nEnter the first name: ";
    std::string fname;
    std::cin.ignore();
    std::getline(std::cin, fname);
    std::cout << "Enter the last name: ";
    std::string lname;
    std::getline(std::cin, lname);
    std::cout << "Enter Classification (Family, Friend, Work, Other): ";
    std::string classification;
    std::getline(std::cin, classification);
    std::cout << "How many phone numbers: ";
    int n;
    std::cin >> n;
    std::cin.ignore();
    Vector<std::string> phones;
    for(int i = 0; i < n; ++i) {
        std::cout << "[" << i + 1 << "] Enter phone number: ";
        std::string phone;
        std::getline(std::cin, phone);
        phones.PushBack(phone);
    }
    std::cout << "How many emails: ";
    int e;
    std::cin >> e;
    std::cin.ignore();
    Vector<std::string> emails;
    for(int i = 0; i < e; ++i) {
        std::cout << "[" << i + 1 << "] Enter email: ";
        std::string email;
        std::getline(std::cin, email);
        emails.PushBack(email);
    }
    char isFavString;
    std::cout << "Favorite contact? [1]Yes [2]No : ";
    std::cin >> isFavString;
    bool isFav = (isFavString == '1');
    std::cin.ignore();
    std::cout << "Enter the address: \n";
    std::string streetNum;
    std::cout << "Enter the streetNumber: ";
    std::getline(std::cin, streetNum);
    std::cout << "Enter the streetName: ";
    std::string street;
    std::getline(std::cin, street);
    std::cout << "Enter the country: ";
    std::string country;
    std::getline(std::cin, country);
    std::cout << "Enter the city: ";
    std::string city;
    std::getline(std::cin, city);
    system("pause");
    Address address(streetNum, street, city, country);
    Person P(fname, lname, classification, phones, emails, address, isFav);
    return P;
}


void addNewContact(Contacts &contacts) {
    Person P = GetInformation();
    std::cout << "nnnnn\n";
    contacts.AddNewContact(P);
    MainMenu();
}

void removeContact(Contacts &contacts) {
    Person P = GetInformation();
    contacts.removeContact(P);
    MainMenu();
}

void searchContact(Contacts &contacts) {
    std::cout << "How do you to search the contact ?\n";
    std::cout << "1- Search by first name\n";
    std::cout << "2- Search by last name\n";
    std::cout << "3- Search by full name\n";
    std::cout << "4- Search by phone number\n";
    std::cout << "5- Search by classification\n";
    int op;
    std::cin >> op;
    std::cin.ignore();
    std::string cont;
    if (op != 3) {
        std::cout << "Enter The contact: ";
        std::getline(std::cin, cont);
    }
    switch (op) {
        case 1:
            contacts.searchContactbyfirstName(cont);
            break;
        case 2:
            contacts.searchContactbylastName(cont);
            break;
        case 3: {
            std::string fname, lname;
            std::cout << "Enter the first name: ";
            std::getline(std::cin, fname);
            std::cout << "Enter the last name: ";
            std::getline(std::cin, lname);
            contacts.searchContactbyFullName(fname, lname);
            break;
        }
        case 4: {
            Vector<std::string> contact;
            contact.PushBack(cont);
            contacts.searchContactbyPhoneNumber(contact);
            break;
        }
        case 5: {
            contacts.searchContactbyclass(cont);
            break;
        }
        default:
            std::cerr << "Invalid choice..\n";
    }
    MainMenu();
}

void ListContacts(Contacts &contacts) {
    contacts.listContacts();
    MainMenu();
}

void ListFavContacts(Contacts &contacts) {
    contacts.printFav();
    MainMenu();
}

void UpdateContact(Contacts &contacts) {
    std::cout << "Enter the old contact information: \n";
    Person old = GetInformation();
    std::cout << "Enter the new contact information: \n";
    Person New = GetInformation();
    contacts.updateContact(old, New);
    MainMenu();
}

void NumberOfCurrentContacts(Contacts &contacts) {
    std::cout << "The contact book have " << contacts.countContacts() << " contact..\n";
    MainMenu();
}

void SortContacts(Contacts &contacts) {
    contacts.sortContacts();
    std::cout << "The contacts sorted successfully..\n";
    MainMenu();
}

void ClearContacts(Contacts &contacts) {
    contacts.removeAllContacts();
    MainMenu();
}

void ReverseContacts(Contacts &contacts) {
    contacts.reverseContacts();
    std::cout << "The contacts reversed successfully..\n";
    MainMenu();
}

void saveFile(Contacts &contacts) {
    contacts.saveToFile();
    MainMenu();
}

void loadFile(Contacts &contacts) {
    contacts.loadFromFile();
    MainMenu();
}

void Exit() {
    std::cout << "Waiting for you next time <3 ..\n";
}