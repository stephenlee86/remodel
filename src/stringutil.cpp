#include <string>
#include <vector>
#include <iostream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace std;

#include "stringutil.h"

//http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
string& stringutil::ltrim(string &s) 
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
string& stringutil::rtrim(string &s) 
{
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

// trim from both ends
string& stringutil::trim(string &s) 
{
  return ltrim(rtrim(s));
}

// split: receives a string delimiter; returns a vector of strings
//http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
const vector<string> stringutil::split(string &str, string delimiter, int rep) {
  //if (!_flds.empty()) _flds.clear();  // empty vector if necessary
  vector<string> _flds;
  size_t pos = 0;
  string token;
  while ((pos = str.find(delimiter)) != string::npos) {
    token = str.substr(0, pos);
    trim(token);
    _flds.push_back(token);
    str.erase(0, pos + delimiter.length());
  }

  //the last token
  _flds.push_back(trim(str));

  return _flds;
}


