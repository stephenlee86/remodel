//Make sure that we have both OpenSSL & libssl-dev installed in the system. 
//http://www.askyb.com/cpp/openssl-md5-hashing-example-in-cpp/
//http://stackoverflow.com/questions/10324611/how-to-calculate-the-md5-hash-of-a-large-file-in-c
//g++ md5.cpp -lcrypto
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;

#include <openssl/md5.h>
class md5diff
{
private:
  std::string compute_md5(char *file);
public:
  md5diff();
  bool diff(char* file1, char* file2);
  ~md5diff();
};

md5diff::md5diff(){
}
md5diff::~md5diff(){
}
bool md5diff::diff(char* file1, char* file2)
{
  int i;
  string c1 = compute_md5(file1);
  string c2 = compute_md5(file2);
 
  bool flag = 1;
  
  for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
    flag = flag && (c1[i] == c2[i]);
  }
  cout << flag << endl;
}

std::string md5diff::compute_md5(char* file)
{
  unsigned char c[MD5_DIGEST_LENGTH];
  int i;
  string hashcode;
  FILE *inFile = fopen (file, "rb");
  MD5_CTX mdContext;
  int bytes;
  unsigned char data[1024];

  if (inFile == NULL) {
    printf ("%s can't be opened.\n", file);
    return 0;
  }

  MD5_Init (&mdContext);
  while ((bytes = fread (data, 1, 1024, inFile)) != 0)
    MD5_Update (&mdContext, data, bytes);
  MD5_Final (c,&mdContext);

  //for(i = 0; i < MD5_DIGEST_LENGTH; i++) printf("%02x",c[i]);

  std::stringstream s;
  for (int i = 0; i < 16; ++i) 
    s << hex << std::setfill('0') << std::setw(2) << (unsigned short) c[i];
  
  hashcode = s.str();
  //cout << hashcode << file << endl;
  fclose (inFile);
  
  return hashcode;
};

int main()
{
  char* f1 = "parser.cpp";
  char* f2 = "parser1.cpp";

  md5diff md5diff1;
  md5diff1.diff(f1, f2);

  return 0;
}
