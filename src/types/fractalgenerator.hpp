#ifndef _FRACTALGENERATOR
#define _FRACTALGENERATOR

/**
 * @brief Class for Fractal Generator
 * @description reads the variables and runs the fractal iteration
 */ 

/* Reading pattern:

iterations                      // nr of iterations
first fractal filename          // the name of the file of the first fractal has to end in xxxx.tga
                                                // where x is a digit from 0 to 9
Image dimension                 // image dimension

expr                            // general fractal expression

Variables_number                // number of variables: Nv
Variable1                       // list of variables for fractal expression
Variable2 
...
VariableNv

Region regionvariable           // region variable

colorimage                      // color image variable (3 expr)
ColorVariablesNumber            // color image variables number: Nc
ColorVariable1                  // list of variables for color image definition
ColorVariable2
...
ColorVariableNc

 */ 

// System includes
#include <string>

// Local includes
#include "expr.hpp"
#include "variable.hpp"
#include "image.hpp"
#include "colorimage.hpp"
#include "regionvariable.hpp"
#include "fractal.hpp"

class FractalGenerator
{
private:
  int iterations; // nr of fractal iterations
  std::string fractalfilename; // fractal file name
  ImageDimension imagedimension; // image dimension
  Expr *expr; // expression of the fractal
  int nrVariables; // nr of variables
  Variable *variables; // variables
  RegionVariable *regionvariable; // region variable
  ColorImage *colorimage; // color image 
  int nrColorVariables; // nr of color variables
  Variable *colorvariables; // color variables

  Fractal fractal; // fractal

  std::string filename;
  
  void readFromFilename(std::string);
  int incrementFilename(std::string&);
  int gotResults;
public:
  FractalGenerator();
  FractalGenerator(std::string);
  ~FractalGenerator();

  /**
   * @brief:  creates all iterations of the fractal from the file read
   */
  void generate();
  void generate(std::string);

  /**
   * @brief: does one job of distributed more
   * @comment: if the job is divided into progs smaller jobs then this will make progsnr's job
   */
  void generate(int progsnr,int progs); 
};

#endif
