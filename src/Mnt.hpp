#ifndef DEF_MNT
#define DEF_MNT

#define NB_INFOS 6

#include <iostream>
#include <fstream>
#include <exception>
#include <GL/glut.h>

using namespace std;

struct Position
{
  int x,y;
  Position(int x = 0,int y = 0) : x(x), y(y) {}
};

class Mnt 
{

private :
 
  float ** zMatrix;
  unsigned int nbCols, nbRows;
  Position p;
  unsigned int cellSize;
  void remplirMatrix(std::ifstream&, unsigned int, unsigned int, unsigned int);
  
  class BadFileLocation : public std::exception
  {
  public:
    BadFileLocation(std::string& Msg) {}
  };

  class BadFileDescription : public std::exception
  {
  public:
    BadFileDescription(std::string& Msg) {}
  };

public : 
 
  Mnt();
  Mnt(string fic);
  Mnt(const Mnt&);
  Mnt& operator = (const Mnt&);
  float * toSommetsTab() const;
  GLuint * toIndexTab() const;
  unsigned int getLength() const { return nbCols; }
  unsigned int getHeight() const { return nbRows; }
  Position getFirstPos() const { return p; }
  ~Mnt();
};

#endif
