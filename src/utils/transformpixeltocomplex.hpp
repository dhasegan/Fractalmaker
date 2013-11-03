/** 
 * Implementation of the transformPixelToComplex function
 */ 
#ifndef _TRANSFORMPIXELTOCOMPLEX
#define _TRANSFORMPIXELTOCOMPLEX

// System includes
#include <complex>

// Local includes
#include "types/region.hpp"
#include "types/image.hpp"

using namespace std;

complex <double> transformPixelToComplex(int i,int j,ImageDimension imgD,Region reg);

#endif
