#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include "product.h"

//string name
//double price
//int quantity in stock

//category 


class Clothing : public Product{

//string size
//string brand 

public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
    ~Clothing();

    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private: 
    std:: string size_;
    std:: string brand_;

};


#endif