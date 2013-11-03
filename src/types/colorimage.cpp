/**
 * Implementation of the Color Image class
 */ 

// System includes
#include <string>
#include <complex>
#include <iostream>
#include <fstream>

// Local includes
#include "colorimage.hpp"
#include "expr.hpp"

// Namespaces
using namespace std;

ColorImage::ColorImage()
{
  exp_R = NULL;
  exp_G = NULL;
  exp_B = NULL;
}
ColorImage::ColorImage(Expr &exp_r,Expr &exp_g,Expr &exp_b)
{
  exp_R = new Expr;
  (*exp_R) = exp_r;
  exp_G = new Expr;
  (*exp_G) = exp_g;
  exp_B = new Expr;
  (*exp_B) = exp_b;
}
ColorImage::ColorImage(string strR,string strG,string strB)
{
  exp_R = new Expr(strR);
  exp_G = new Expr(strG);
  exp_B = new Expr(strB);
}
ColorImage::~ColorImage()
{
  if (exp_R != NULL) 
    delete exp_R;
  if (exp_G != NULL) 
    delete exp_G;
  if (exp_B != NULL) 
    delete exp_B;
}

void ColorImage::setColorFunctions(Expr &exp_r,Expr &exp_g,Expr &exp_b)
{
  if (exp_R != NULL) 
    delete exp_R;
  exp_R = new Expr;
  (*exp_R) = exp_r;

  if (exp_G != NULL) 
    delete exp_G;
  exp_G = new Expr;
  (*exp_G) = exp_g;

  if (exp_B != NULL) 
    delete exp_B;
  exp_B = new Expr;
  (*exp_B) = exp_b;
}

void ColorImage::setColorFunctions(string strR,string strG,string strB)
{
  if (exp_R != NULL) 
    delete exp_R;
  exp_R = new Expr(strR);

  if (exp_G != NULL) 
    delete exp_G;
  exp_G = new Expr(strG);

  if (exp_B != NULL) 
    delete exp_B;
  exp_B = new Expr(strB);
}
  
void ColorImage::setColorFunctionR(Expr &exp_r)
{
  if (exp_R != NULL) 
    delete exp_R;
  exp_R = new Expr;
  (*exp_R) = exp_r;
}
  
void ColorImage::setColorFunctionR(string strR)
{
  if (exp_R != NULL) 
    delete exp_R;
  exp_R = new Expr(strR);

}
  
void ColorImage::setColorFunctionG(Expr &exp_g)
{
  if (exp_G != NULL) 
    delete exp_G;
  exp_G = new Expr;
  (*exp_G) = exp_g;
}

void ColorImage::setColorFunctionG(string strG)
{
  if (exp_G != NULL) 
    delete exp_G;
  exp_G = new Expr(strG);
}
  
void ColorImage::setColorFunctionB(Expr &exp_b)
{  
  if (exp_B != NULL) 
    delete exp_B;
  exp_B = new Expr;
  (*exp_B) = exp_b;
}
  
void ColorImage::setColorFunctionB(string strB)
{  
  if (exp_B != NULL) 
    delete exp_B;
  exp_B = new Expr(strB);
} 

string ColorImage::getColorFunctions()
{
  string ret = "";
  ret.append( (*exp_R).getString() );
  ret.push_back(' ');
  ret.append( (*exp_G).getString() );
  ret.push_back(' ');
  ret.append( (*exp_B).getString() );
  return ret;
}

string ColorImage::getColorFunctionR()
{
  return (*exp_R).getString();
}

string ColorImage::getColorFunctionG()
{
  return (*exp_G).getString();
}

string ColorImage::getColorFunctionB()
{
  return (*exp_B).getString();
}

void ColorImage::addVariable(std::string name,std::complex<double> value)
{
  exp_R->addVariable(name,value);
  exp_G->addVariable(name,value);
  exp_B->addVariable(name,value);
}

void ColorImage::make_image(Color **ret, int **it, ImageDimension& imgDim)
{
  int IMAGE_WIDTH = imgDim.getWidth();
  int IMAGE_HEIGHT = imgDim.getHeight();
  
  for(int i = 0; i<IMAGE_HEIGHT ; ++i)
    for(int j = 0; j<IMAGE_WIDTH ; ++j)
      if (it[i][j] >= 0)
      {
        addVariable("IT",it[i][j]);
        complex<double> er = exp_R->calculate();
        ret[i][j].setR( er.real() );
        complex<double> eg = exp_G->calculate();
        ret[i][j].setG( eg.real() );
        complex<double> eb = exp_B->calculate();
        ret[i][j].setB( eb.real() );
      }
      else
        ret[i][j] = Color(0,0,0);
}


istream& operator >>(istream &is,ColorImage &ci)
{
  if (ci.exp_R != NULL)
    delete ci.exp_R;
  ci.exp_R = new Expr;
  is >> (*ci.exp_R);

  if (ci.exp_G != NULL)
    delete ci.exp_G;
  ci.exp_G = new Expr;
  is >> (*ci.exp_G);

  if (ci.exp_B != NULL)
    delete ci.exp_B;
  ci.exp_B = new Expr;
  is >> (*ci.exp_B);

  return is;
}
ostream& operator <<(ostream& os,ColorImage &ci)
{
  if (ci.exp_R != NULL)
    os << (*ci.exp_R) << " ";
  if (ci.exp_G != NULL)
    os << (*ci.exp_G) << " ";
  if (ci.exp_B != NULL)
    os << (*ci.exp_B) << " ";
  return os;
}


