#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include "product.h"

//string name
//double price
//int quantity in stock

//category 


class Movie : public Product{

//string genre
//string rating 

public:
    Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
    ~Movie();

    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private: 
    std:: string genre_;
    std:: string rating_;

};


#endif