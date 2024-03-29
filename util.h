#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2){

    std::set<T> inter;
    for (typename std::set<T>::iterator sIt = s1.begin(); sIt != s1.end(); ++sIt){
        if (s2.find(*sIt) != s2.end()){
            inter.insert(*sIt);
        }
    }
    return inter;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2){
    std::set<T> setU;
    setU = s1;

    for (typename std::set<T>::iterator uIt = s2.begin(); uIt != s2.end(); ++uIt){
        setU.insert(*uIt);
    }
    return setU;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
