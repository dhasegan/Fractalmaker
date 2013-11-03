#ifndef _REGION_H
#define _REGION_H
/**
 * @brief: Implementation of the basic Region class
 * @comment: this does the basic operations
 */ 

// System includes
#include <complex>
#include <string>

class Region //every region has a center and the length on the Ox axis
{
private:
	std::complex <double> center; // center of the region
	double length; // length on the Ox axis
  double dimension; // dimension (usualy 3:2)
public:
	Region();
	Region(std::complex <double>,std::complex <double>); // upper left corner and lower right corner
	Region(double,double,double,double);  // upper left corner and lower right corner in coordinates
	Region(std::complex <double>,double,double); // center, length and dimension
	Region(const Region&); // copy constructor

	// setters, getters
	void setCenter(std::complex <double> c);
	void setLength(double l);
  void setDimension(double d);
	std::complex <double> getCenter();
	double getLength();
  double getDimension();
	double Ylength(); // length on Oy axis 
	std::complex <double> getLeftUpCorner();
	std::complex <double> getRightUpCorner();
	std::complex <double> getLeftLowerCorner();
	std::complex <double> getRightLowerCorner();

	// Distance between two regions
	double distanceBetween(const Region&);

	// Transformations
	Region zoomOn(const double factor); // return the square zoomed on with factor
	Region translationBy(std::complex <double> v); // translation by a vector
	Region translationBy(double vx,double vy); // translation by vector in coordinates

	// Operators
	Region operator=(const Region& rhs);
};

#endif
