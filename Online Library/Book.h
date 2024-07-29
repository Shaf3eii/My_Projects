#ifndef OOP_PR1_LIBRARY__BOOK_H
#define OOP_PR1_LIBRARY__BOOK_H
#include "User.h"
class Book{
    string title;
    string isbn;
    string category;
    int id;
    double averagerating;
    int ratenums;//////////////
    int ratesum;//////////////
    User author; // we using the pointer to avoid making objects from Class User
    // has a --> aggregation    is a --> inheritance
    // we can use *author to make a pointer
    // bool hasAuthor;
public:
    static int count;
    Book();
    Book(string ,string ,string);
    Book(const Book&);
    void setTitle(string);
    string getTitle()const;
    void setIsbn(string);
    string getIsbn()const;
    void setId(int);
    int getId()const;
    void setCategory(string);
    string getCategory()const;
    void setAverage(double);
    double getAverage()const;
    void setAuthor(const User &);
    User getAuthor()const;
    void ratebook(double);
    bool operator==(const Book&);
    friend ostream &operator<<(ostream &,const Book &);
    friend istream &operator>>(istream & , Book &);
};

#endif