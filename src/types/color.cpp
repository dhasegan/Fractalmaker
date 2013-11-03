/**
 * Implementation of the Color Class
 */ 

// Local includes
#include "color.hpp"

Color::Color()
{
	R = G = B = 1.0 ;
}
Color::Color(double r,double g,double b)
{
  if (r > 1)
    R = (double)1.0;
  else if (r < -1)
    R = (double)-1.0;
  else 
    R = r;
  if (g > 1)
    G = (double)1.0;
  else if (g < -1)
    G = (double)-1.0;
  else 
    G = g;
  if (b > 1)
    B = (double)1.0;
  else if (b < -1)
    B = (double)-1.0;
  else 
    B = b;
}
Color::Color(const Color& rhs)
{
  R = rhs.R;
  G = rhs.G;
  B = rhs.B;
}
Color Color::operator*(const Color& rhs)
{
	return Color(R*rhs.R,G*rhs.G,B*rhs.B);
}
Color& Color::operator+=(const Color& rhs)
{
	R += rhs.R;
	G += rhs.G;
	B += rhs.B;
	return (*this);
}
Color& Color::operator/=(const int N)
{
	R /= N;
	G /= N;
	B /= N;
	return (*this);
}
bool Color::operator==(const Color& rhs)
{
	if (R != rhs.R)
		return 0;
	if (G != rhs.G)
		return 0;
	if (B != rhs.B)
		return 0;
	return 1;
}
Color Color::operator+(const Color& rhs)
{
  Color newColor(R+rhs.R,G+rhs.G,B+rhs.B);
	return newColor;
}
Color Color::operator=(const Color& rhs)
{
  R = rhs.R;
  G = rhs.G;
  B = rhs.B;
	return (*this);
}


void Color::setR(double r)
{
	R= r;
}
void Color::setG(double g)
{
	G= g;
}
void Color::setB(double b)
{
	B= b;
}
double Color::getR()
{
	return R;
}
double Color::getG()
{
	return G;
}
double Color::getB()
{
	return B;
}
