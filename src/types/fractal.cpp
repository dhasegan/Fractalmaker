/** 
 * Implementation of the Fractal class
 */ 

// System includes
#include <string>

// Local includes
#include "expr.hpp"
#include "region.hpp"
#include "image.hpp"
#include "fractal.hpp"

using namespace std;

Fractal::Fractal()
{
  expr = Expr("add(mul(Z,Z),C)");
  reg = Region( complex<double>(-2,1) , complex<double>(1,-1) );
  setIterations();
}
  
Fractal::Fractal(string stre,Region &r)
{
  expr = Expr(stre);
  reg = r;
  setIterations();
}
  
Fractal::Fractal(Expr &e,Region &r)
{
  expr = e;
  reg = r;
  setIterations();
}

Fractal::~Fractal()
{
}

void Fractal::setFractalFunction(Expr e)
{
  expr = e;
}
  
void Fractal::setFractalRegion(Region r)
{
  reg = r;
}

Expr Fractal::getFractalFunction()
{
  return expr;
}

Region Fractal::getFractalRegion()
{
  return reg;
}
  
string Fractal::getFractalStringFunction()
{
  return expr.getString();
}
  
void Fractal::addVariable(string name,complex<double> value)
{
  expr.addVariable(name,value);
}

void Fractal::generate(int **ret, ImageDimension& imgD)
{
  int height = imgD.getHeight();
  int width = imgD.getWidth();

  for(int i=0;i<height;++i)
    for(int j=0;j<width;++j)
    {
      complex<double> Z = transformPixelToComplex(i,j,imgD,reg);
      ret[i][j] = generateForPoint(Z);
    }
}

void Fractal::setIterations()
{
	double L = reg.getLength();
  It = (double)100/pow(L,((double)1/4));
}

int Fractal::generateForPoint(complex<double> Z)
{
  expr.addVariable("C",Z);
  for(int i=0;i<It;++i)
  {
    expr.addVariable("Z",Z);
    Z = expr.calculate();
    if (abs(Z) > 2)
      return i;
  }
  return -1;
}

