#ifndef MY_DATASTORE_H
#define MY_DATASTORE_H
#include "datastore.h"
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <string>
#include <iostream>


class MyDataStore: public DataStore{
    public:
    ~MyDataStore();

    void  addProduct(Product* p);
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    
    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    void add (std:: string username, Product* hit_result_index);
    void viewcart(std::string username);
    void buycart (std::string username);

    private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std:: map<std:: string, User*> userMap_;
    std:: map<std::string, std::set<Product*>> keywordsMap_;

    std::map<std::string, std::deque<Product*>> carts_;



};

#endif