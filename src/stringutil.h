#ifndef STRUTIL_H
#define STRUTIL_H
//http://www.cplusplus.com/articles/1UqpX9L8/

class stringutil : public string {
    vector<string> flds;

public:
    stringutil(string s) : string(s) { };
    vector<string>& split(string delimiter, int rep=0);
};
#endif
