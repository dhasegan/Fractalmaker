// System includes
#include <complex>

// Local includes
#include "types/region.hpp"
#include "types/image.hpp"

using namespace std;

complex <double> transformPixelToComplex(int i,int j,ImageDimension imgD,Region reg)
{ //TODO: make this function better
	int w = imgD.getWidth();
  int h = imgD.getHeight();
	complex<double> luc = reg.getLeftUpCorner(); // left upper corner
	double deltaX = reg.getLength();
	double deltaY = reg.Ylength();

	complex<double> C((double)j * deltaX / w,(double)-i * deltaY / h);
	// invert by Ox axis
	// make it proportional to Region
	// add vector luc
	return (C + luc);
}

