#include "Book.h"
int Book::count = 0;
Book::Book()
{
    title = "";
    isbn = "";
    count++;
    id = count;
    category = "";
    averagerating=0.0;
    ratenums = 0;
    ratesum = 0.0;
    //User author; // call the empty constructor from Class User
    // if we use a pointer ( *author ) we should make this line
    // author = new User;
    //hasAuthor = false;
}

Book::Book(string title,string isbn,string category)
{
    this->title = title;
    this->isbn = isbn;
    this->category = category;
    count++;
    id = count;
    averagerating=0.0;
    ratenums = 0;
    ratesum = 0.0;
    //User author;
    //hasAuthor = false;
}
Book::Book(const Book& book)
{
    category = book.category;
    title = book.title;
    isbn = book.isbn;
    id = book.id;
    averagerating = book.averagerating;
    //author = book.author;
    /*if(book.hasAuthor)
    {
        /*author = new User;
        hasAuthor = true;
        author = book.author;
        setAuthor(book.author); // to avoid making more objects from class User
    */
    author = book.author;
    ratesum = book.ratesum;
    ratenums = book.ratenums;
}
void Book::setTitle(string title)
{
    this->title = title;
}
string Book::getTitle() const
{
    return title;
}
void Book::setId(int id)
{
    this->id = id;
}
int Book::getId() const
{
    return id;
}
void Book::setAverage(double average)
{
    this->averagerating = average;
}
double Book::getAverage() const
{
    return averagerating;
}
void Book::setCategory(string category)
{
    this->category = category;
}
string Book::getCategory() const
{
    return category;
}
void Book::setIsbn(string isbn)
{
    this->isbn = isbn;
}
string Book::getIsbn() const
{
    return isbn;
}
void Book::setAuthor(const User & user)
{
    //hasAuthor = true;
    author = user; //if we have an author ,then call the constructor from class User
}
User Book::getAuthor() const
{
    return author;
}
void Book::ratebook(double rate)
{
    ratenums++;
    ratesum += rate;
    averagerating = ratesum / ratenums;
}
bool Book::operator==(const Book &book)
{
    return(isbn == book.isbn && category == book.category && title == book.title && averagerating == book.averagerating &&
           id == book.id && averagerating == book.averagerating && author == book.author);
    // author will call the == in the user class
}
ostream &operator<<(ostream &output,const Book &book)
{
    output << "======================\n";
    output << "Title : " << book.title;
    output << "\nIsbn : " << book.isbn;
    output << "\nID : " << book.id;
    output << "\nCategory : " << book.category;
    output << "\nAverage : " << book.averagerating << endl;
    if(book.getAuthor().getname() != "")
        cout << book.author;
    output << "======================\n";
    return output; // عشان كدا استخدمنا ال& عشان اعرف اطبع اكتر من اوبجكت في سطر واحد
}
istream &operator>>(istream &input, Book &book)
{
    cout << "<Enter The Book Info>\n";
    cout << "Enter Your Title : " ;
    input >> book.title;
    cout << "\nEnter Your Isbn : " ;
    input >> book.isbn;
    cout << "\nEnter Your Category : " ;
    input >> book.category;
    return input;
}