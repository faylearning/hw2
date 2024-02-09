
#include <sstream>
#include <iomanip>
#include "util.h"
#include "book.h"

using namespace std;


// std::set<std::string> keywords() const;
// std::string displayString() const;
// void dump(std::ostream& os) const;

//string ISBN
//string author 


// book
// Data Abstraction & Problem Solving with C++
// 79.99
// 20
// 978-013292372-9
// Carrano and Henry

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string ISBN, const std::string author)
    : Product(category, name, price, qty), ISBN_(ISBN), author_(author){

}

set<string> Book::keywords() const{
    set<string> aWord = parseStringToWords(author_);
    set<string> name = parseStringToWords(name_);

    set<string> keyWords = setUnion(name, aWord);
    keyWords.insert(ISBN_);

    return keyWords;
}

string Book::displayString() const{
    stringstream ss;
    ss << name_ << endl;
    ss << "Author: " << author_ << "ISBN: " << ISBN_ << endl;
    ss <<  price_ << " " << qty_ << " left." << endl;

    return ss.str();
}

void Book::dump(ostream& os) const{
    
    os << "book" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << ISBN_ << endl;
    os << author_ << endl;

}

