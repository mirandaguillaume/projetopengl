#ifndef DEF_READTEXT
#define DEF_READTEXT

#include <fstream>

class ReadText {

private :
  float ** zMatrix;
  

public : 
  
  ReadText();
  ReadText(string fic);
  ReadText(const ReadText&);
  ReadText& operator = (const ReadText&);
  GLint toTab() const;
  ~ReadText();
};

#endif
