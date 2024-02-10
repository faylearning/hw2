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

    for (std::vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it) {
    delete *it;
  }
  for (std::vector<User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
    delete *it;
  }

    // while(!products_.empty()){
    //   delete products_.front();
    // }

    // while(!users_.empty()){
    //   delete products_.front();
    // }
}

void MyDataStore::addProduct(Product *p)
{
    // add to products_
    // add keyword to keywords
    products_.push_back(p);
    set<string> words = p->keywords();

    for (set<string>::iterator pIt = words.begin(); pIt != words.end(); ++pIt)
    {
		string word = convToLower(*pIt);
        keywordsMap_[word].insert(p);
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
    }else{
        set<Product*> curr = keywordsMap_[convToLower(terms[0])];
		// cout << curr.size() << endl;
		for (tIt = terms.begin()+1; tIt != terms.end(); ++tIt){
			if (type == 0){ //AND
				// cout << keywordsMap_[convToLower(*tIt)].size() << endl;
				// for(auto it = keywordsMap_.begin(); it != keywordsMap_.end(); ++it) {
				// 	cout << it->first << "\t" << it->second.size() << "\n";
				// }
				curr = setIntersection(curr, keywordsMap_[convToLower(*tIt)]);
				// cout << curr.size() << endl;
			}
			else if (type == 1){ //OR
				// curr.insert(keywordsMap_[*tIt]);
				curr = setUnion(curr, keywordsMap_[convToLower(*tIt)]);
			}
		}
		return vector<Product*>(curr.begin(), curr.end());
	}

    
}


void MyDataStore::dump(std::ostream& ofile){
    // Reproduce the database file from the current Products and User values

    // std::vector<Product*> products_;
    // std::vector<User*> users_;

    //products
    ofile << "<products>" << endl;
    vector<Product*>::iterator pIt;
    for (pIt = products_.begin(); pIt != products_.end(); ++pIt){
        (*pIt)->dump(ofile);
    }
    ofile<<"</products>" <<endl;

    //users
    ofile << "<users>" << endl;
    vector<User*>::iterator uIt;
    for (uIt = users_.begin(); uIt != users_.end(); ++uIt){
        (*uIt)->dump(ofile);
    }
    ofile<< "</users>" << endl;

}

void MyDataStore:: add(std:: string username, Product* hit_result_index){

    if (userMap_.find(username) != userMap_.end()) {
        carts_[username].push_back(hit_result_index);
    }
	else {
        cout << "Invalid request" << endl;
        return;
    }
    
}

void MyDataStore:: viewcart(std::string username){
    //map<std::string, std::deque<Product*>> carts_
    //Users should be able to view their entire cart while maintaining its order

	if(userMap_.find(username) == userMap_.end()){
		cout << "Invalid username" << endl;
	}else{
		deque <Product*>& cart = carts_[username];
		deque<Product*>::iterator cIt;

		int num = 1;
		for(cIt = cart.begin(); cIt != cart.end(); ++cIt){
			cout << "Item " << num << endl;
			cout << (*cIt)->displayString() << endl;
			num++;
		}
	}
}

void MyDataStore:: buycart (std::string username){
	if(userMap_.find(username) == userMap_.end()){
		cout << "Invalid username" << endl;
	}else if (carts_.find(username) == carts_.end()){
		cout << "Invalid request" << endl;
	}else{

		// vector<Product*>& cart = carts_[username];
		deque<Product*>& cart = carts_[username];
		User* user = userMap_[username];

		deque<Product*>::iterator cIt;
		cIt = cart.begin();

		int bal = user->getBalance();
		if (bal < 0){
			cout << "Invalid request" << endl;
		}

		while(cIt != cart.end()){
			int price = (*cIt)->getPrice();
			int quant = (*cIt)->getQty();
			// cout << "balance: " << bal << endl;

			if ((price <= bal) && (quant > 0)){
				(*cIt)->subtractQty(1);

				// cout << "quantity: " << quant << endl;
				user->deductAmount(price);
				bal = user->getBalance();

				// cout << "balance after deduct: " << bal << endl;
				cIt = cart.erase(cIt);
			}else{
				++cIt;
			}
		}
	} 
}


