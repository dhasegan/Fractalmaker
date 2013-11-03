#ifndef _FractalIMAGE
#define _FractalIMAGE
/**
 * Fractal Image Class
 */ 

// System includes
#include <string>
#include <complex>
#include <iostream>
#include <fstream>

// Local includes
#include "expr.hpp"
#include "region.hpp"
#include "image.hpp"
#include "../utils/transformpixeltocomplex.hpp"

class Fractal
{
private:
  Expr expr; // Expression of the Fractal
  Region reg; // On what region
  int It; // How many iterations

  void setIterations();
  int generateForPoint(std::complex<double>);
public:
  // Constructors & Destructors
  Fractal();
  Fractal(std::string,Region &);
  Fractal(Expr &,Region &);
  ~Fractal();

  // Setters and getters
  void setFractalFunction(Expr e);
  void setFractalRegion(Region r);
  Expr getFractalFunction();
  Region getFractalRegion();
  std::string getFractalStringFunction();

  // add variable
  void addVariable(std::string,std::complex<double>);

  // generates the fractal
  void generate(int **mat,ImageDimension& imgD);
  //TODO: work with interactive variables
    // int **generate(ImageDimension& imgD, vector< Variable* > );
};

#endif
