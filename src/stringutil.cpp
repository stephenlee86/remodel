#include <string>
#include <vector>
#include <iostream>
using namespace std;


#include "stringutil.h"


// split: receives a string delimiter; returns a vector of strings
//http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
vector<string>& stringutil::split(string delimiter, int rep) {
    if (!_flds.empty()) _flds.clear();  // empty vector if necessary
    string s = data();

    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
      token = s.substr(0, pos);
      _flds.push_back(token);
      s.erase(0, pos + delimiter.length());
    }
    //the last token
    _flds.push_back(s);
    
    return _flds;
}
