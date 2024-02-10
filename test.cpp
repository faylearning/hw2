#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;

std::set<std::string> parseStringToWords(string rawWords){
    //Men's Shirt I'll The ISBN 978-000000000-1 Of J. Mice And AB2F
    int len = rawWords.length(); 
    std::set<std::string> list;
    std::string temp = "";

    //looping through rawWords
    for (int i = 0; i < len; i++){
        
        char currChar = rawWords[i];
        // temp.clear();
        if(std::ispunct(currChar) && (currChar != '-')){
            if (temp.length() >= 2){
                list.insert(temp);
            }
            temp.clear();
        }else if (std::isalpha(currChar) || isdigit(currChar) || (currChar == '-')){
            temp += currChar;
            // cout << "temp:  " << temp << endl;
        }else if (currChar == ' '){
            if(temp.length() >= 2){
                list.insert(temp);
                // cout << "adding " << temp << endl;
            }
            temp.clear();
        }
        
    }
    //reached end of rawWords, if longer than 1, add to set
    if (temp.length() > 1){
        list.insert(temp);
        temp.clear();
    }
    return list;
}

int main() {
    std::string input = "Men's Shirt I'll The ISBN 978-000000000-1 Of J. Mice And AB2F";
    std::set<std::string> keywords = parseStringToWords(input);

    // Print the result
    std::cout << "Keywords: " << std::endl;
    for (const auto& keyword : keywords) {
        std::cout << keyword << std::endl;
    }
    std::cout << std::endl;

    return 0;
}