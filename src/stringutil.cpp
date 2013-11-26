#include <string>
#include <vector>
#include <iostream>
using namespace std;


#include "stringutil.h"


// split: receives a string delimiter; returns a vector of strings
vector<string>& stringutil::split(string delimiter, int rep) {
    if (!flds.empty()) flds.clear();  // empty vector if necessary
    string s = data();

    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      flds.push_back(token);
      s.erase(0, pos + delimiter.length());
    }
    //the last token
    flds.push_back(s);
    
    return flds;
}
