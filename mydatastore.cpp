#include "datastore.h"
#include "mydatastore.h"
#include "util.h"
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

// searching, adding products and users, saving the database, etc

MyDataStore::~MyDataStore()
{
    // products & users
    for (size_t i = 0; i < products_.size(); i++)
    {
        delete products_[i];
    }

    for (size_t i = 0; i < users_.size(); i++)
    {
        delete users_[i];
    }
}

void MyDataStore::addProduct(Product *p)
{
    // add to products_
    // add keyword to keywords
    products_.push_back(p);
    set<string> words = p->keywords();

    for (set<string>::iterator pIt = words.begin(); pIt != words.end(); ++pIt)
    {
        keywordsMap_[*pIt].insert(p);
    }
}

void MyDataStore::addUser(User *u)
{
    // string getName()
    pair<string, User *> use(u->getName(), u);
    userMap_.insert(use);
    users_.push_back(u);
}

vector<Product *> MyDataStore::search(std::vector<std::string> &terms, int type){

    // Performs a search of products whose keywords match the given "terms"
    // type 0 = AND search (intersection of results for each term) while
    // type 1 = OR search (union of results for each term)

    // std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
    // std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2){

    // if empty search --> return empty vector
    // if 1 item in search --> return matching item
    // if type 0 --> look through the terms and return INTERSECTION of products with keywordsmap
    // if type 1 --> look through terms and return UNION of products with keywordmap

    vector<string>::iterator tIt;

    vector<Product *> products;

    if (terms.size() == 0){
        return vector<Product *>(0);
    }else if (terms.size() == 1){ //if there's only one term
        map<string,set<Product*>>::iterator p = keywordsMap_.find(terms[0]);
        if(p == keywordsMap_.end()){
            return products;
        }
        set<Product*> p_val = p->second;

        products = vector<Product*>(p_val.begin(), p_val.end()); // find the matching product and return it
    }

    set<Product*> curr = keywordsMap_[terms[0]];
    for (tIt = terms.begin()+1; tIt != terms.end(); ++tIt){
        if (type == 0){ //AND
            curr = setIntersection(curr, keywordsMap_[*tIt]);
        }
        else if (type == 1){ //OR
            // curr.insert(keywordsMap_[*tIt]);
            curr = setUnion(curr, keywordsMap_[*tIt]);
        }
    }

    return vector<Product*>(curr.begin(), curr.end());
}


void MyDataStore::dump(std::ostream& ofile){
    // Reproduce the database file from the current Products and User values

    // std::vector<Product*> products_;
    // std::vector<User*> users_;

    //products
    ofile << "Products:" << endl;
    vector<Product*>::iterator pIt;
    for (pIt = products_.begin(); pIt != products_.end(); ++pIt){
        (*pIt)->dump(ofile);
    }

    //users
    ofile << "Users:" << endl;
    vector<User*>::iterator uIt;
    for (uIt = users_.begin(); uIt != users_.end(); ++uIt){
        (*uIt)->dump(ofile);
    }

}

void MyDataStore:: add(std:: string username, Product* hit_result_index){
    if (userMap_.find(username) != userMap_.end()) {
        carts_[username].push_back(hit_result_index);
    }else{
        cout << "No user with this username" << endl;
        return;
    }
    
}

void MyDataStore:: viewcart(std::string username){
    //map<std::string, std::deque<Product*>> carts_
    //Users should be able to view their entire cart while maintaining its order
    
    deque <Product*>& cart = carts_[username];
    deque<Product*>::iterator cIt;

    int num = 1;
    for(cIt = cart.begin(); cIt != cart.end(); ++cIt){
        cout << "Item number " << num << ": " << (*cIt)->displayString() << endl;
    }

}
void MyDataStore:: buycart (std::string username){
    deque<Product*>& cart = carts_[username];
    User* user = userMap_[username];

    deque<Product*>::iterator cIt;

    while(cIt != cart.end()){
        int price = (*cIt)->getPrice();
        int quant = (*cIt)->getQty();
        int bal = user->getBalance();
        if ((price <= bal) && (quant > 0)){
            (*cIt)->subtractQty(1);
            user->deductAmount(price);
            cIt = cart.erase(cIt);
        }else{
            cIt++;
        }
    }
    
}

