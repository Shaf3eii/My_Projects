#include "UserList.h"

UserList::UserList()
{
    capacity = 0;
    usersCount=0;
}
UserList::UserList(int capacity)
{
    this->capacity=capacity;
    users = new User[capacity]; // will call the constructor from class User (capacity times)
    usersCount = 0;
}
void UserList::addUser(const User &user)
{
    if(usersCount < capacity)
    {
        users[usersCount] = user;
        users[usersCount].setid(usersCount + 1); // to make correct id
        usersCount++;
    }
    else
    {
        cout << "Not Enough Space.\n" << endl;
    }
}
User* UserList::searchUser(string name)
{
    for(int i = 0 ; i < usersCount ; ++i)
    {
        if(users[i].getname() == name)
            return &users[i];//(&) because we using return pointer
    }
    return nullptr;// so, we used return pointer
    // if we not have this name in the array of users
}
User* UserList::searchUser(int id)
{
    for(int i = 0 ; i < usersCount ; ++i)// why we use usersCount instead of capacity ??
    {
        if(users[i].getid() == id)
            return &users[i];
    }
    return nullptr;// return 0;
}
void UserList::deleteUser(int id)
{
    for(int i = 0 ; i < usersCount ; ++i)
    {
        if(users[i].getid() == id)
        {
            while(i < usersCount - 1)
            {
                users[i] = users[i + 1];
                users[i].setid(i + 1); // to make id
                ++i;
            }
            usersCount--;
            capacity--;
            break;
        }
    }
}
ostream &operator<<( ostream& output,const UserList&userlist)
{
    for(int i = 0 ; i < userlist.usersCount ; ++i)
    {
        output << userlist.users[i] << " ";
    }
    return output;
}
UserList::~UserList()
{
    delete[]users;
}