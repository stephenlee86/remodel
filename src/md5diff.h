#ifndef _MD5DIFF_
#define _MD5DIFF_
class md5diff
{
private:
  std::string compute_md5(char *file);
public:
  md5diff();
  bool diff(char* file1, char* file2);
  ~md5diff();
};

#endif
