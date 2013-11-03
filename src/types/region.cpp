/**
 * Implementation of Region class
 *
 */ 

// System includes
#include <complex>

// Local includes
#include"region.hpp"

// Namespaces

using namespace std;

Region::Region()
{
	center = complex<double>(0,0);
	length = 0;
  dimension = 1;
}
	
Region::Region(complex<double> ul,complex<double> lr) // upper left corner and lower right corner
{
	complex<double> c(ul.real() + (lr.real()-ul.real())/2,lr.imag() + (ul.imag()-lr.imag())/2);
	center = c;
	length = lr.real() - ul.real();
  dimension = (lr.real() - ul.real()) / (ul.imag() - lr.imag());
}

Region::Region(double ulr,double uli,double lrr,double lri)  // upper left corner and lower right corner in coorginates
{
	complex<double> c(ulr+ (lrr-ulr)/2,lri+ (uli-lri)/2);
	center = c;
	length = lrr - ulr;
  dimension = (lrr - ulr) / (uli - lri);
}

Region::Region(complex<double> c,double l,double d) // center and length
{
	center = c;
	length = l;
  dimension = d;
}

Region::Region(const Region& ref) // copy constructor
{
	center = ref.center;
	length = ref.length;
  dimension = ref.dimension;
}

void Region::setCenter(complex<double> c)
{
	center = c;
}
void Region::setLength(double l)
{
	length = l;
}
void Region::setDimension(double d)
{
  dimension = d;
}
complex<double> Region::getCenter()
{
	return center;
}
double Region::getLength()
{
	return length;
}
double Region::getDimension()
{
	return dimension;
}
double Region::Ylength()
{
  return length / dimension;
}
complex<double> Region::getRightUpCorner()
{
	complex<double> c(center.real()+length/2,center.imag()+Ylength()/2);
	return c;
}
complex<double> Region::getLeftUpCorner()
{
	complex<double> c(center.real()-length/2,center.imag()+Ylength()/2);
	return c;
}
complex<double> Region::getLeftLowerCorner()
{
	complex<double> c(center.real()-length/2,center.imag()-Ylength()/2);
	return c;
}
complex<double> Region::getRightLowerCorner()
{
	complex<double> c(center.real()+length/2,center.imag()-Ylength()/2);
	return c;
}

double Region::distanceBetween(const Region &reg)
{
	return abs( center - reg.center );
}

	// Transformations
Region Region::zoomOn(const double factor) // return the square zoomed on with factor
{
	return Region(center,length*factor,dimension);
}
Region Region::translationBy(complex<double> v) // translation by a vector
{
	return Region(center + v,length,dimension);
}
Region Region::translationBy(double vx,double vy) // translation by vector in coordinates
{
	return Region(complex<double>(vx,vy) + center,length,dimension);
}

	// Operators
Region Region::operator=(const Region& rhs)
{
	center = rhs.center;
	length = rhs.length;
  dimension = rhs.dimension;
  return (*this);
}

