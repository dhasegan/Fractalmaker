
// System includes
#include <complex>
#include <string>
#include <iostream>
#include <fstream>

// Local includes
#include "region.hpp"
#include "regionvariable.hpp" 

// Namespaces
using namespace std;

RegionVariable::RegionVariable()
{
  filename = "";
  nrOfRegions = 0;
  currentNrRegion = 0;
}

RegionVariable::RegionVariable(string fn)
{
  filename = fn;
  fin.open(filename.c_str(),ios::in);
  nrOfRegions = 0;
  currentNrRegion = 0;
}

RegionVariable::~RegionVariable()
{
  if (fin.is_open())
  {
    fin.close();
  }
}

Region RegionVariable::beginRegion()
{
  if (!fin.is_open())
  {
    fprintf(stderr,"RegionVariable: Please open file first\n"); 
    return Region();
  }
  
  fin >> nrOfRegions;
  currentNrRegion = 1;
  complex<double> upleft,downright;
  fin >> upleft;
  fin >> downright;
  Region ret(upleft,downright);
  currentValue = ret;
  return currentValue;
}

Region RegionVariable::nextRegion()
{
  if (!fin.is_open())
  {
    fprintf(stderr,"RegionVariable: Please open file first\n");
    return Region();
  }
  if ( currentNrRegion < nrOfRegions )
  {
    currentNrRegion ++;
    complex<double> upleft,downright;
    fin >> upleft;
    fin >> downright;
    Region ret(upleft,downright);
    currentValue = ret;    
  } 
    
  return currentValue;
}

istream& operator >>(istream& is,RegionVariable &v)
{
  string nm;
  is >> nm;
  if (nm != "Region")
  {
    fprintf(stderr,"RegionValue: Problem while reading\n");
    return is;
  }

  is >> v.filename;
  v.fin.open(v.filename.c_str(),ios::in);
  return is;
}
ostream& operator <<(ostream& os,RegionVariable &v)
{
  os << "Region ";
  os << v.filename;
  return os;
}
