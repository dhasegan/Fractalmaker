#ifndef _VARIABLE
#define _VARIABLE
/**
 * Implementation of the variable Class
 */ 

/**
 * The input method of the Variable types:
type:          VARIABLE_NAME(varname) typeOnFractal typeOnIteration    typeRead    ...
example:              VAR                 0 or 1        0 or 1        0 or 1 or 2   ...

 * if typeRead is VARIABLE_READ_NONE
  ...            Constant_Value 
  ...              (0.3,0.4)

 * if typeRead is VARIABLE_READ_FILE
  ...         FileName
  ...     variableName.varinput

 * if typeRead is VARIABLE_READ_EXPR
  ...       First_value         Expression            nr_of_constants_in_expression       Values_of_constants
  ...         (0.3,0.4)       add(mul(VAR,C1),C2)                 2                     (0.1,0.2)     (0.001,0.003)    

 * if typeRead is VARIABLE_READ_EXPR_FILE
  ...       filename               Expression            nr_of_constants_in_expression       Values_of_constants 
  ...   variable.varinput      add(mul(VAR,C1),C2)                 2                      (0.1,0.2)     (0.001,0.003) 
      
 * if typeRead is VARIABLE_READ_EXPR_EXPR
  ...       First_value         Expression            nr_of_constants_in_expression       Values_of_constants         ...(2)
  ...         (0.3,0.4)       add(mul(VAR,C1),C2)                 2                     (0.1,0.2)     (0.001,0.003)   ...(2)

      ...(2)            Expression            nr_of_constants_in_expression       Values_of_constants     
      ...(2)         add(mul(VAR,C1),C2)                 2                      (0.1,0.2)     (0.001,0.003) 

 */ 

// System includes
#include <complex>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

// Local includes
#include "expr.hpp"

enum VariableType
{
  VARIABLE_CONSTANT,
  VARIABLE_ITERATIVE,
};

enum VariableRead
{
  VARIABLE_READ_NONE, // FOR Constant
  VARIABLE_READ_FILE, // FOR ITERATIVE ON 1 of typeFractalIteration or typeIteration
  VARIABLE_READ_EXPR, // FOR ITERATIVE ON 1 of typeFractalIteration or typeIteration
  VARIABLE_READ_EXPR_FILE, // FOR ITERATIVE ON BOTH 
  VARIABLE_READ_EXPR_EXPR, // FOR ITERATIVE ON BOTH
};

class Variable
{
private:
  // VARIABLE Name
  std::string varname;

  // Varible Types and Values
  int typeOnFractal,typeOnIteration;
  std::complex<double> initialValue;
  std::complex<double> currentValue;

  // Usual Reading Variables
  int typeRead;
  std::fstream fin;
  std::string filename;
  Expr *expr;
  std::vector< std::pair<std::string,std::complex<double> > > exprCST;

  // Special Reading Variables
  Expr *expr2;
  std::complex<double> iterationValue;
  std::vector< std::pair<std::string,std::complex<double> > > exprCST2;
public:
  // Constructor, Destructors
  Variable();
  ~Variable();

  // Type 
  int getTypeOnFractal();
  int getTypeOnIteration();
  int getTypeRead();

  // Values
  std::pair<std::string, std::complex<double> > begin();
  std::pair<std::string, std::complex<double> > beginIteration();
  std::pair<std::string, std::complex<double> > nextIteration();
  std::pair<std::string, std::complex<double> > nextFractalIteration();  

  // I/O
  friend std::istream& operator >>(std::istream& is,Variable &v);
  friend std::ostream& operator <<(std::ostream& os,Variable &v);
  int Interface(std::istream& is,std::ostream& os);
};

std::istream& operator >>(std::istream& is,Variable &v);
std::ostream& operator <<(std::ostream& os,Variable &v);

#endif
