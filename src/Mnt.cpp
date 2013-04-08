#include "Mnt.hpp"

Mnt::Mnt() 
{
  zMatrix = NULL;
}

Mnt::Mnt(string fic) 
{
  ifstream mnt(fic.c_str());
  if (!mnt) throw BadFileLocation(fic);
  string line;
  int NODATA_value;
  for (int i=0;i<NB_INFOS;i++) 
    {
      mnt>>line;
      if (line=="ncols")  mnt>>nbCols; 
      else if (line=="nrows")  mnt>>nbRows; 
      else if (line=="xllcorner")  mnt>>p.x; 
      else if (line== "yllcorner")  mnt>>p.y; 
      else if (line== "cellsize")  mnt>>cellSize; 
      else if (line== "NODATA_value")  mnt>>NODATA_value; 
      else throw BadFileDescription(fic);
    } 
  cout<<"Hello"<<endl;
  remplirMatrix(mnt, nbCols,nbRows,cellSize);
}

void Mnt::remplirMatrix(ifstream& fic, unsigned int nbCols, unsigned int nbRows, unsigned int cellSize) 
{
  zMatrix = new float* [nbCols];
  cout<<nbRows<<endl;
  for (unsigned int i=0;i<nbCols;i++) 
      zMatrix[i] = new float [nbRows];
  for (unsigned int i=0;i<nbCols;i++) 
    
      for (unsigned int j = 0; j<nbRows;j++)
	{
	  cout<<i<<" "<<j<<endl;
	  fic>>zMatrix[j][i];
	}
}

float* Mnt::toSommetsTab() const 
{
  float* sommets = new float [nbCols*nbRows*3];
  int cpt = 0;
  for (unsigned int i=0;i<nbCols*nbRows;i++)
    {
      sommets[cpt] = i%nbCols;
      cpt++;
      sommets[cpt] = i/nbRows;
      cpt++;
      sommets[cpt] = zMatrix[i/nbRows][i%nbCols];
      cpt++;
    }
  return sommets;
}

GLuint *  Mnt::toIndexTab() const 
{
  GLuint * index = new GLuint[(nbRows-1)*(nbCols-1)*3*2];
  unsigned int cpt = 0;
  for (unsigned int i=0;i<(nbCols)*(nbRows-1);i++)
    {
      if (i%nbCols!=(nbCols-1)) {
	index[cpt]=i;
	cpt++;
	index[cpt]=i+1;
	cpt++;
	index[cpt]=i+1+nbCols;
	cpt++;
	index[cpt]=i;
	cpt++;
	index[cpt]=i+nbCols;
	cpt++;
	index[cpt]=i+1+nbCols;
	cpt++;
      }
    }
  return index;
}

Mnt::~Mnt() 
{
  for (unsigned int i=0;i<nbRows;i++)
    delete zMatrix[i];
  delete zMatrix;
}
