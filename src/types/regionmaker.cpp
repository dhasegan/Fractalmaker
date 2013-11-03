#include <string>
#include <complex>
#include <fstream>
#include <iostream>

#include "regionmaker.hpp"
#include "region.hpp"

using namespace std;


void makeRegionFile(Region a,string filename)
{
  fstream fin;
  fin.open(filename.c_str(),ios::out);

  fin << 1;
  fin << a.getLeftUpCorner() << " " << a.getRightLowerCorner() << " ";

  fin.close();
}

void makeRegionFile(Region a,Region b,int it,string filename)
{
  if (it == 0)
    return ;
  if (it == 1)
  {
    makeRegionFile(a,filename);
    return ;
  }
  if (it == 2)
  {
    fstream fin;
    fin.open(filename.c_str(),ios::out);
    
    fin << it << endl;   
    fin << a.getLeftUpCorner() << " ";
    fin << a.getRightLowerCorner() << endl;
    fin << b.getLeftUpCorner() << " ";
    fin << b.getRightLowerCorner() << endl;
    
    fin.close();
    return ;
  }

  // we find the zooming ratio
  long double zoomRatio = pow(  (long double)b.getLength() / (long double)a.getLength() , (long double) 1/(it-1)   );

  int iterRegion; // iterations needed to change the regions center from 'a' to 'b' 
  if (   (long double)b.getLength() / (long double)a.getLength() < (long double)RegionMoveMaximumConstant    )
  { // we calculate the iterRegion needed
    Region aux = a;
    iterRegion = 0;
    while (   (long double)aux.getLength() / (long double)a.getLength() > (long double)RegionMoveMaximumConstant    )
    { 
//cout << "current length: " << aux.getLength() << endl;
      iterRegion ++;
      aux = aux.zoomOn( zoomRatio );
    }
  }
  else
  { // it is close
    iterRegion = it-1;
  }

  // we find Moving Ratio
  complex <double> moveRatio = (b.getCenter() - a.getCenter()) / complex<double>(iterRegion,0);

  // open file 
  fstream fin;
  fin.open(filename.c_str(),ios::out);

  // print first iteration
  fin << it << endl;
  fin << a.getLeftUpCorner() << " ";
  fin << a.getRightLowerCorner() << endl;

  // we iterate
  Region curr = a;  
  for(int i=1 ; i < it-1 ; i++)
  {
    curr = curr.zoomOn(zoomRatio);
    if (i <= iterRegion)
      curr = curr.translationBy(moveRatio);
    else
      curr.setCenter(b.getCenter());

    fin << curr.getLeftUpCorner() << " ";
    fin << curr.getRightLowerCorner() << endl;
  }

  // print last iteration
  fin << b.getLeftUpCorner() << " ";
  fin << b.getRightLowerCorner() << endl;

  fin.close();
}

double getZoom(Region a,Region b,int it)
{
  long double zoomRatio = pow(  (long double)b.getLength() / (long double)a.getLength() , (long double) 1/(it-1)   );
  return (double)zoomRatio;
}
