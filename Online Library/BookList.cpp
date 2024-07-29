#include "booklist.h"

BookList::BookList()
{
    capacity = 0;
    booksCount = 0;
}
BookList::BookList(int capacity)
{
    this->capacity = capacity;
    books = new Book[capacity]; // will call the empty constructor from class Book
    booksCount = 0;
}
void BookList::addBook(const Book& book)// at the end of the array.
{
    if(booksCount < capacity)
    {
        books[booksCount] = book;
        books[booksCount].setId(booksCount+1); // to avoid incorrect id
        booksCount++;
    }
    else
    {
        cout << "Not Enough Space.\n" << endl;
    }
}
Book* BookList::searchBook(string name)
{
    for(int i = 0 ; i < booksCount ; ++i)
    {
        if(books[i].getTitle() == name)
        {
            return &books[i];
        }
    }
    return nullptr;
}
Book* BookList::searchBook(int id)
{
    for(int i = 0 ; i < booksCount ; ++i)
    {
        if(books[i].getId() == id)
        {
            return &books[i];
        }
    }
    return nullptr;
}
void BookList::deleteBook(int id)//delete a book
{
    for(int i = 0 ; i < booksCount ; ++i)
    {
        if(books[i].getId() == id)
        {
            while(i < booksCount - 1)
            {
                books[i] == books[i + 1];
                books[i].setId(i + 1);
                i++;
            }
            booksCount--;
            capacity--;
            break;
        }
    }

}
Book BookList::getTheHighestRatedBook()
{
    double HighestRate = -1.0;
    int index = 0;
    for(int i = 0 ; i < booksCount ; ++i)
    {
        if(books[i].getAverage() > HighestRate)
        {
            HighestRate = books[i].getAverage();
            index = i;
        }
    }
    return books[index];
}

void BookList::getBooksForUser(const User &user)// get all books of this author
{
    bool flag = false;
    for(int i = 0 ; i < booksCount ;++i)
    {
        if(books[i].getAuthor() == user)
        {
            cout << books[i] << " ";
            flag =true;
        }
    }
    if(!flag)
        cout << "No BOOKS for this Author\n";
}
Book& BookList::operator[] (int index) // general rule we use & with []
{
    if(index < 0 || index >= booksCount)
        cout << "Index Not Found\n";
    else
        return books[index];
}
ostream&operator<<(ostream & output,const BookList & booklist)
{
    for(int i = 0 ; i < booklist.booksCount ; ++i)//////// .
    {
        output << booklist.books[i] << endl;// print from class book
    }
    return output;
}
BookList::~BookList()
{
    delete []books;
}