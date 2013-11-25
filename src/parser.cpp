#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class parser
{
private:
  char *pExpr;
public:
  parser();
  double parse(char *exp);
  ~parser();
};

parser::parser()
{
  cout << "Start.. " << endl;
}

parser::~parser() 
{
  cout << "The End." << endl;
}

double parser::parse(char *exp)
{
  pExpr = exp;
  cout << pExpr << endl;
}

int main() 
{
  string s = "DEFAULT <- baz";
  parser program;
  char expstr[80];
  cin.getline(expstr, 79);

  program.parse(expstr);
  return 0;
}
#if(md5(file1Path) == md5(file2Path))
#    cout<<"Files are equal"<<endl;
#else
#    cout<<"Files are not equal"<<endl;
