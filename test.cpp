#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

std::set<std::string> parseStringToWords(std::string rawWords){
    //Men's I'll The 978-000000000-1 Of J. Mice And Men AB2F
    int len = rawWords.length(); 
    std::set<std::string> list;

    std::string temp = "";

    //looping through rawWords
    for (int i = 0; i < len; i++){
        char currChar = rawWords[i];

        if(std::ispunct(currChar) && (currChar != '-')){
            //while (rawWords[i+1] != ' '){
                temp.clear();
                //i++;
            //}
        }


        if (std::isalpha(currChar) || isdigit(currChar) || (currChar == '-')){
            temp += currChar;
        }else if (temp.length() >= 2){
            list.insert(temp);
            temp.clear();
        }

        // if (ispunct(currChar) && temp.length() >= 2) {
        //     list.insert(temp);
        //     temp.clear();
        // }
    
    }

    //reached end of rawWords, if longer than 1, add to set
    if (temp.length() > 1){
        list.insert(temp);
    }
    
    return list;
}

int main() {
    std::string input = "Men's I'll The 978-000000000-1 Of J. Mice And Men AB2F ";
    std::set<std::string> keywords = parseStringToWords(input);

    // Print the result
    std::cout << "Keywords: " << std::endl;
    for (const auto& keyword : keywords) {
        std::cout << keyword << std::endl;
    }
    std::cout << std::endl;

    return 0;
}