#include "User.h"
int User::count = 0; // initialize the count with primary value
User::User()
{
    name = "";
    age = 0;
    password = "";
    email = "";
    count++;
    id = count;
}

User::User(string &name, int age, string &password, string &email)
{
    this->name = name;
    this->age = age;
    this->password = password;
    this->email = email;
    count++;
    id = count;
}

User::User(const User &user)
{
    name = user.name;
    age = user.age;
    password = user.password;
    email = user.email;
    id = user.id;
    /*
     we have 2 ways to call it
      u2 = u1;
      u2(u1);

      User u2 = u1; here, it will call the copy constructor
      User u2;
      u2 = u1; here, it will call the default copy constructor
     */
}
void User::setname(string n)
{
    name =n;
}
string User::getname()const
{
    return name;
}
void User::setpassword(string& p)
{
    password=p;
}
string User::getpassword()const
{
    return password;
}
void User::setemail(string e)
{
    email=e;
}
string User::getemail() const
{
    return email;
}
void User::setage(int a)
{
    age =a;
}
int User::getage()const
{
    return age;
}
void User::setid(int i)
{
    id = i;
}
int User::getid()const
{
    return id;
}
bool User::operator == (const User & user)
{
    if(name != user.name || id != user.id || password != user.password || age != user.age || email != user.email)
    {
        return false;
    }
    return true;
    // return !(name != user.name || id != user.id || password != user.password || age != user.age || email != user.email);
}
void User::Display()
{
    cout << "=======================\n";
    cout << "Name : " << name <<endl;
    cout << "ID : " << id <<endl;
    cout << "Email : " << email <<endl;
    cout << "Age : " << age <<endl;
    cout << "=======================\n";
}
/*void User::operator=(const User & user)// u2 = u1 --> u2 will be = u1 except the id
{
    name = user.name;
    age = user.age;
    password = user.password;
    email = user.email;
}*/
ostream &operator<<(ostream & output, const User & user)
{
    cout << "========================\n";
    output << "User " << user.id << " Info.\n";
    output << "Name : " << user.name;
    output << "\nID : " << user.id;
    output << "\nEmail : " << user.email;
    output << "\nAge : " << user.age << endl;
    cout << "========================\n";
    return output; // عشان كدا استخدمنا ال& عشان اعرف اطبع اكتر من اوبجكت في سطر واحد
}
istream &operator>>(istream & input, User &user)
{
    cin.ignore();
    cout << "<Enter User Info>\n";
    cout << "Enter Your Name : ";
    getline(input, user.name);
    cout << "Enter Your Email : ";
    input >> user.email;
    cout << "Enter Your Age : ";
    input >> user.age;
    cout << "Enter Your Password : ";
    input >> user.password;
    cin.ignore();
    return input; // عشان كدا استخدمنا ال& عشان اعرف اخد اكتر من اوبجكت في سطر واحد
}