
#include <sstream>
#include <iomanip>
#include <set>
#include "util.h"
#include "clothing.h"

using namespace std;


// std::set<std::string> keywords() const;
// std::string displayString() const;
// void dump(std::ostream& os) const;

//string size
//string brand 


// clothing
// Men's Fitted Shirt
// 39.99
// 25
// Medium
// J. Crew

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand)
    : Product(category, name, price, qty), size_(size), brand_(brand){

}

Clothing::~Clothing() {}

set<string> Clothing::keywords() const{
    set<string> nameWord = parseStringToWords(name_);
    set<string> brandWord = parseStringToWords(brand_);

    set<string> keyWords = setUnion(nameWord, brandWord);

    return keyWords;
}

string Clothing::displayString() const{
    stringstream ss;
    ss << name_ << endl;
    ss << "Size: " << size_ << " Brand: " << brand_ << endl;
    ss <<  price_ << " " << qty_ << " left." << endl;

    return ss.str();
}

void Clothing::dump(ostream& os) const{
    
    os << "clothing" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << size_ << endl;
    os << brand_ << endl;

}

