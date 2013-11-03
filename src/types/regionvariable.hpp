#ifndef _REGION_VARIABLE
#define _REGION_VARIABLE

/** 
 * @brief: Class describing a Region Variable which gets its input from a file
 */

/*
 * Input type:
>> Region @filename 
    -without the '>>' where @filename is a variable with the name of the file where to get the values of the region from
 */


// System includes
#include <complex>
#include <string>
#include <iostream>
#include <fstream>

// Local includes
#include "region.hpp"


class RegionVariable
{
private:
  Region currentValue;

  std::string filename;
  std::fstream fin;
  int nrOfRegions,currentNrRegion;
public:
  // Constructors destructor
  RegionVariable();
  RegionVariable(std::string fn);
  ~RegionVariable();

  // Values
  Region beginRegion();
  Region nextRegion();

  // I/O
  friend std::istream& operator >>(std::istream& is,RegionVariable &v);
  friend std::ostream& operator <<(std::ostream& os,RegionVariable &v);
};

std::istream& operator >>(std::istream& is,RegionVariable &v);
std::ostream& operator <<(std::ostream& os,RegionVariable &v);


#endif
