
#include <sstream>
#include <iomanip>
#include "util.h"
#include "movie.h"

using namespace std;


// std::set<std::string> keywords() const;
// std::string displayString() const;
// void dump(std::ostream& os) const;


// movie
// Hidden Figures DVD
// 17.99
// 1
// Drama
// PG

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating)
    : Product(category, name, price, qty), genre_(genre), rating_(rating){

}

set<string> Movie::keywords() const{
    set<string> keyWords = parseStringToWords(name_);
    string g = convToLower(genre_);
    keyWords.insert(g);

    return keyWords;
}

string Movie::displayString() const{
    stringstream ss;
    ss << name_ << endl;
    ss << "Genre: " << genre_ << "Rating: " << rating_ << endl;
    ss << price_ << qty_ << " left." << endl;
    
    return ss.str();
}

void Movie::dump(ostream& os) const{

    os << "movie" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << genre_ << endl;
    os << rating_ << endl;

}

