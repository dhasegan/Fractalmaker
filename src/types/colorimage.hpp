#ifndef _COLORIMAGE
#define _COLORIMAGE
/**
 * Color Image Class
 */ 

// System includes
#include <string>
#include <complex>
#include <iostream>
#include <fstream>

// Local includes
#include "color.hpp"
#include "expr.hpp"
#include "image.hpp"

class ColorImage
{
private:
  // Expression of the coloring image
  Expr* exp_R;
  Expr* exp_G;
  Expr* exp_B;
public:
  // Constructors & Destructors
  ColorImage();
  ColorImage(std::string,std::string,std::string);
  ColorImage(Expr &exp_r,Expr &exp_g,Expr &exp_b);
  ~ColorImage();

  // Setters and getters
  void setColorFunctions(Expr &exp_r,Expr &exp_g,Expr &exp_b);
  void setColorFunctions(std::string,std::string,std::string);
  void setColorFunctionR(Expr &exp_r);
  void setColorFunctionR(std::string);
  void setColorFunctionG(Expr &exp_g);
  void setColorFunctionG(std::string);
  void setColorFunctionB(Expr &exp_b);
  void setColorFunctionB(std::string);
  std::string getColorFunctionR();
  std::string getColorFunctionG();
  std::string getColorFunctionB();
  std::string getColorFunctions();
  
  // add variable
  void addVariable(std::string,std::complex<double>);

  // computes the actual image
  void make_image(Color **ret,int **it,ImageDimension&);

  // I/O
  friend std::istream& operator >>(std::istream& is,ColorImage &ci);
  friend std::ostream& operator <<(std::ostream& os,ColorImage &ci);
};

std::istream& operator >>(std::istream& is,ColorImage &ci);
std::ostream& operator <<(std::ostream& os,ColorImage &ci);

#endif
