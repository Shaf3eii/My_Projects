#ifndef OOP_PR1_LIBRARY__USER_H
#define OOP_PR1_LIBRARY__USER_H

#include "iostream"
#include "string"
using namespace std;
using namespace string_literals;
/// @brief
class User{
    // to call these attributes we need to create an object
    string name;
    int age;
    int id;
    string password;
    string email;
public:
    static int count; // we can call it without create an object
    User();
    User(string &,int,string &, string &);
    User(const User&);
    bool operator == (const User&);
    void setname(string);
    string getname()const;
    void setpassword(string&);
    string getpassword()const;
    void setemail(string);
    string getemail() const;
    void setage(int);
    int getage()const;
    void setid(int);
    int getid() const;
    void Display();
    //void operator=(const User &);
    friend ostream &operator<<(ostream & , const User &); // we used the (friend) because
    //we will implement the function outside the class
    friend istream &operator>>(istream & , User &);
};
#endif