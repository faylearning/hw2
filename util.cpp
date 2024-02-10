#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
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

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
