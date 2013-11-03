#ifndef _FRACTALRUNNER
#define _FRACTALRUNNER


/**
 * NOT finished - may be dropped
 */ 


/**
 * Runs a set of fractals with changing variables and/or changing region
 */ 

// System includes
#include <iostream>
#include <string>

// Local includes
#include "fractal.hpp"
#include "variable.hpp"

class FractalRunner
{
private:
  vector< Variable > variableSet;
  Fractal fractal;
public:
  FractalRunner();
  FractalRunner(std::string projectfilename,std::string fractalfilename);
  ~FractalRunner();

  // make the runner
  int **generate();

  friend std::istream& operator >>(std::istream& is,FractalRunner &fr);
  friend std::ostream& operator <<(std::ostream& os,FractalRunner &fr);
};

std::istream& operator >>(std::istream& is,FractalRunner &fr);
std::ostream& operator <<(std::ostream& os,FractalRunner &fr);

#endif
