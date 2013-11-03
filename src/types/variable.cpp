
// System includes
#include <complex>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

// Local includes
#include "variable.hpp"
#include "expr.hpp"

// Namspaces
using namespace std;

  // Constructor, Destructors
Variable::Variable()
{
  varname = "";
  typeOnFractal = VARIABLE_CONSTANT;
  typeOnIteration = VARIABLE_CONSTANT;
  typeRead = VARIABLE_READ_NONE;
  filename = "";
  initialValue = complex<double> (0,0);
  currentValue = complex<double> (0,0);
  expr = NULL;
}

Variable::~Variable()
{
  if (typeRead == VARIABLE_READ_FILE)
  {
    if (fin.is_open())
    {
      fin.close();
    }
  }
  if (typeRead == VARIABLE_READ_EXPR)
  {
    if (expr != NULL)
    {
      delete expr;
    }
  }
}
  
int Variable::getTypeOnFractal()
{
  return typeOnFractal;
}
  
int Variable::getTypeOnIteration()
{
  return typeOnIteration;
}
  
int Variable::getTypeRead()
{
  return typeRead;
}

pair< string, complex<double> > Variable::begin()
{
  if (typeRead == VARIABLE_READ_NONE)
    return make_pair(varname,initialValue);
  if (typeRead == VARIABLE_READ_FILE)
  {
    fin >> initialValue;
    currentValue = initialValue;
    return make_pair(varname,currentValue);
  }
  if (typeRead == VARIABLE_READ_EXPR)
  {
    currentValue = initialValue;
    return make_pair(varname,currentValue);
  }
  if (typeRead == VARIABLE_READ_EXPR_FILE)
  {
    fin >> currentValue;
    return make_pair(varname,currentValue);
  }
  if (typeRead == VARIABLE_READ_EXPR_EXPR)
  {
    iterationValue = initialValue;
    currentValue = iterationValue;
    return make_pair(varname,currentValue);
  }

  return make_pair("",complex<double>(1,0));
}

pair< string ,complex<double> > Variable::beginIteration()
{
  return make_pair(varname,currentValue);
}

pair< string , complex<double> > Variable::nextFractalIteration()
{
 if (typeOnFractal == VARIABLE_ITERATIVE)
 {
  if (typeRead == VARIABLE_READ_NONE)
    return make_pair(varname,initialValue);
  if (typeRead == VARIABLE_READ_FILE)
  {
    fin >> currentValue;
    return make_pair(varname,currentValue);
  }
  if (typeRead == VARIABLE_READ_EXPR)
  {
    (*expr).addVariable(varname,currentValue);
    currentValue = (*expr).calculate();
    return make_pair(varname,currentValue);
  }
  if (typeRead == VARIABLE_READ_EXPR_FILE)
  {
    (*expr).addVariable(varname,currentValue);
    currentValue = (*expr).calculate();
    return make_pair(varname,currentValue);
  }
  if (typeRead == VARIABLE_READ_EXPR_EXPR)
  {
    (*expr).addVariable(varname,currentValue);
    currentValue = (*expr).calculate();
    return make_pair(varname,currentValue);
  }
 }
 else
 {
  return make_pair(varname,currentValue);
 }

  return make_pair("",complex<double>(1,0));
}

pair< string , complex<double> > Variable::nextIteration()
{
 if (typeOnIteration == VARIABLE_ITERATIVE)
 {
  if (typeRead == VARIABLE_READ_NONE)
    return make_pair(varname,initialValue);
  if (typeRead == VARIABLE_READ_FILE)
  {
    if (typeOnFractal != VARIABLE_ITERATIVE)
    // if we havent already incremented
      fin >> currentValue;
    return make_pair(varname,currentValue);
  }
  if (typeRead == VARIABLE_READ_EXPR)
  {
    if (typeOnFractal != VARIABLE_ITERATIVE)
    { // if we havent already incremented
      (*expr).addVariable(varname,currentValue);
      currentValue = (*expr).calculate();
     }
    return make_pair(varname,currentValue);
  }
  if (typeRead == VARIABLE_READ_EXPR_FILE)
  {
    fin >> currentValue;
    return make_pair(varname,currentValue);
  }
  if (typeRead == VARIABLE_READ_EXPR_EXPR)
  {
    (*expr2).addVariable(varname,iterationValue);
    iterationValue = (*expr2).calculate();
    currentValue = iterationValue;
    return make_pair(varname,currentValue);
  }
 }
 if (typeOnIteration == VARIABLE_CONSTANT)
 {
  if (typeOnFractal == VARIABLE_ITERATIVE && typeRead == VARIABLE_READ_FILE)
  {
    fin.close();
    fin.open(filename.c_str(),ios::in);
    fin >> initialValue;
    currentValue = initialValue;
    return make_pair(varname,currentValue);
  }
  else
  {
    currentValue = initialValue;
    return make_pair(varname,currentValue);
  }
 }


  return make_pair("",complex<double>(1,0));
}

istream& operator >>(istream& is,Variable &v)
{
  // Local variables
  int nrOfVariables;
  string constantName;
  complex< double > constantValue;

  // Reading basic stuff
  is >> v.varname;
  is >> v.typeOnFractal;
  is >> v.typeOnIteration;
  is >> v.typeRead;
  
  // Errors:
  if ( v.typeRead != VARIABLE_READ_NONE && v.typeRead != VARIABLE_READ_FILE && v.typeRead != VARIABLE_READ_EXPR && 
       v.typeRead != VARIABLE_READ_EXPR_FILE && v.typeRead != VARIABLE_READ_EXPR_EXPR )
  {
    fprintf(stderr,"Variable: Bad Read Type\n");
    return is;
  }
  if ( v.typeOnFractal != VARIABLE_CONSTANT && v.typeOnFractal != VARIABLE_ITERATIVE )
  { 
    fprintf(stderr,"Variable: Bad Variable Type\n");
    return is;
  }
  if ( v.typeOnIteration != VARIABLE_CONSTANT && v.typeOnIteration != VARIABLE_ITERATIVE )
  { 
    fprintf(stderr,"Variable: Bad Variable Type\n");
    return is;
  }
  if ( (v.typeRead == VARIABLE_READ_EXPR_FILE || v.typeRead == VARIABLE_READ_EXPR_EXPR) && 
       (v.typeOnFractal != VARIABLE_ITERATIVE || v.typeOnIteration != VARIABLE_ITERATIVE ) )
  {
    fprintf(stderr,"Variable: Bad Input Read Types: doesn't work with variable types\n");
    return is;
  }

  // Actual reading
  if (v.typeRead == VARIABLE_READ_NONE) // For VARIABLE_READ_NONE
  {
    is >> v.initialValue;
    v.currentValue = v.initialValue;
    return is;
  }
  if (v.typeRead == VARIABLE_READ_FILE) // For VARIABLE_READ_FILE
  {
    is >> v.filename;  
    v.fin.open(v.filename.c_str(),ios::in);
    return is;
  }
  if (v.typeRead == VARIABLE_READ_EXPR) // For VARIABLE_READ_EXPR
  {
    is >> v.initialValue;
    v.currentValue = v.initialValue;
    v.expr = new Expr;
    is >> (*v.expr);
    is >> nrOfVariables;
    for(; nrOfVariables ; --nrOfVariables)
    {
      is >> constantName;
      is >> constantValue;  
      (*v.expr).addVariable(constantName,constantValue);
      v.exprCST.push_back( make_pair(constantName,constantValue) );
    }
    return is;
  }
  if (v.typeRead == VARIABLE_READ_EXPR_FILE) // For VARIABLE_READ_EXPR_FILE
  {
    is >> v.filename; 
    v.fin.open(v.filename.c_str(),ios::in);
    v.expr = new Expr;
    is >> (*v.expr);
    is >> nrOfVariables;
    for(; nrOfVariables ; --nrOfVariables)
    {
      is >> constantName;
      is >> constantValue;  
      (*v.expr).addVariable(constantName,constantValue);
      v.exprCST.push_back( make_pair(constantName,constantValue) );
    }
    return is;
  }
  if (v.typeRead == VARIABLE_READ_EXPR_EXPR) // For VARIABLE_READ_EXPR_EXPR
  {
    is >> v.initialValue;
    v.currentValue = v.initialValue;
    // first expression
    v.expr = new Expr;
    is >> (*v.expr);
    is >> nrOfVariables;
    for(; nrOfVariables ; --nrOfVariables)
    {
      is >> constantName;
      is >> constantValue;  
      (*v.expr).addVariable(constantName,constantValue);
      v.exprCST.push_back( make_pair(constantName,constantValue) );
    }
    // second expression
    v.expr2 = new Expr;
    is >> (*v.expr2);
    is >> nrOfVariables;
    for(; nrOfVariables ; --nrOfVariables)
    {
      is >> constantName;
      is >> constantValue;  
      (*v.expr2).addVariable(constantName,constantValue);
      v.exprCST2.push_back( make_pair(constantName,constantValue) );
    }
    
  }

  return is;
}

ostream& operator <<(ostream& os,Variable &v)
{
  os << v.varname << " ";
  os << v.typeOnFractal << " ";
  os << v.typeOnIteration << " ";
  os << v.typeRead << " ";
  if (v.typeRead == VARIABLE_READ_NONE)
  {
    os << v.initialValue << " ";
    return os;
  }
  if (v.typeRead == VARIABLE_READ_FILE)
  {
    os << v.filename << " ";
    return os;
  }
  if (v.typeRead == VARIABLE_READ_EXPR)
  {
    os << v.initialValue << " ";
    os << (*v.expr) << " ";
    os << v.exprCST.size() << " ";
    for(int i=0;(unsigned int)i < v.exprCST.size() ; ++i)
      os << v.exprCST[i].first << " " << v.exprCST[i].second << " ";
    return os;
  }
  if (v.typeRead == VARIABLE_READ_EXPR_FILE)
  {
    os << v.filename << " ";
    os << (*v.expr) << " ";
    os << v.exprCST.size() << " ";
    for(int i=0;(unsigned int)i < v.exprCST.size() ; ++i)
      os << v.exprCST[i].first << " " << v.exprCST[i].second << " ";
    return os;
  }
  if (v.typeRead == VARIABLE_READ_EXPR_EXPR)
  {
    os << v.initialValue << " ";
    // first expression
    os << (*v.expr) << " ";
    os << v.exprCST.size() << " ";
    for(int i=0;(unsigned int)i < v.exprCST.size() ; ++i)
      os << v.exprCST[i].first << " " << v.exprCST[i].second << " ";
    // second expression
    os << (*v.expr2) << " ";
    os << v.exprCST2.size() << " ";
    for(int i=0;(unsigned int)i < v.exprCST2.size() ; ++i)
      os << v.exprCST2[i].first << " " << v.exprCST2[i].second << " ";
    return os;
  }
  return os;
}

int Variable::Interface(istream& is,ostream& os)
{
  // Local variables
  int nrOfVariables;
  string constantName;
  complex< double > constantValue;
  char charc;
  string strs;

  // Reading basic stuff

  os << "Print the name of the variable (has to be the same as in function):" << endl;
  is >> varname;

  os << "Constant or Iterative on Fractal? (\'c\' or \'i\') ";
  is >> charc;
  if (charc == 'i')
    typeOnFractal = VARIABLE_ITERATIVE;
  else if (charc == 'c')
    typeOnFractal = VARIABLE_CONSTANT;
  else
    {
      os << "Variable: Error while reading!" << endl; 
      return 0;
    }

  os << "Constant or Iterative on Fractal sequence? (\'c\' or \'i\') ";
  is >> charc;
  if (charc == 'i')
    typeOnIteration = VARIABLE_ITERATIVE;
  else if (charc == 'c')
    typeOnIteration = VARIABLE_CONSTANT;
  else
    {
      os << "Variable: Error while reading!" << endl; 
      return 0;
    }

  os << "Read from: \n(c) Constant \n(f) Read values from a File \n(e) Calculate by Expression \n(fe) Read values for the sequence from the File and values for the fractal from Expression \n(ee) Calculate both sequence and fractal values from expressions\n[For the last two read manual for neclarifications]" << endl;
  is >> strs;
  if (strs == "c")
    typeRead = VARIABLE_READ_NONE;
  else if (strs == "f")
    typeRead = VARIABLE_READ_FILE;
  else if (strs == "e")
    typeRead = VARIABLE_READ_EXPR;
  else if (strs == "fe")
    typeRead = VARIABLE_READ_EXPR_FILE;
  else if (strs == "ee")
    typeRead = VARIABLE_READ_EXPR_EXPR;
  else 
    {
      os << "Variable: Error while reading!" << endl; 
      return 0;
    }
  
  // Errors:
  if ( typeRead != VARIABLE_READ_NONE && typeRead != VARIABLE_READ_FILE && typeRead != VARIABLE_READ_EXPR && 
       typeRead != VARIABLE_READ_EXPR_FILE && typeRead != VARIABLE_READ_EXPR_EXPR )
  {
    fprintf(stderr,"Variable: Bad Read Type\n");
    return 0;
  }
  if ( typeOnFractal != VARIABLE_CONSTANT && typeOnFractal != VARIABLE_ITERATIVE )
  { 
    fprintf(stderr,"Variable: Bad Variable Type\n");
    return 0;
  }
  if ( typeOnIteration != VARIABLE_CONSTANT && typeOnIteration != VARIABLE_ITERATIVE )
  { 
    fprintf(stderr,"Variable: Bad Variable Type\n");
    return 0;
  }
  if ( (typeRead == VARIABLE_READ_EXPR_FILE || typeRead == VARIABLE_READ_EXPR_EXPR) && 
       (typeOnFractal != VARIABLE_ITERATIVE || typeOnIteration != VARIABLE_ITERATIVE ) )
  {
    fprintf(stderr,"Variable: Bad Input Read Types: doesn't work with variable types\n");
    return 0;
  }

  // Actual reading
  if (typeRead == VARIABLE_READ_NONE) // For VARIABLE_READ_NONE
  {
    os << "What is the Value of the Constant? (print complex<double> number) " << endl;
    is >> initialValue;
    currentValue = initialValue;
    return 1;
  }
  if (typeRead == VARIABLE_READ_FILE) // For VARIABLE_READ_FILE
  {
    os << "Print name of the file? " << endl;
    is >> filename;  
    fin.open(filename.c_str(),ios::in);
    return 1;
  }
  if (typeRead == VARIABLE_READ_EXPR) // For VARIABLE_READ_EXPR
  {
    os << "What is the initial value? (print a complex<double>) " << endl;
    is >> initialValue;
    currentValue = initialValue;
    expr = new Expr;
    os << "Print the expression of the Variable change:" << endl;
    is >> (*expr);
    os << "How many constants in the expression above? " << endl;
    is >> nrOfVariables;
    for(; nrOfVariables ; --nrOfVariables)
    {
      os << "Print the constants name: " << endl;
      is >> constantName;
      os << "Print the constants value(complex<double>): " << endl;
      is >> constantValue;  
      (*expr).addVariable(constantName,constantValue);
      exprCST.push_back( make_pair(constantName,constantValue) );
    }
    return 1;
  }
  if (typeRead == VARIABLE_READ_EXPR_FILE) // For VARIABLE_READ_EXPR_FILE
  {
    os << "Print name of the file? " << endl;
    is >> filename; 
    fin.open(filename.c_str(),ios::in);
    expr = new Expr;
    os << "Print the expression of the Variable change:" << endl;
    is >> (*expr);
    os << "How many constants in the expression above? " << endl;
    is >> nrOfVariables;
    for(; nrOfVariables ; --nrOfVariables)
    {
      os << "Print the constants name: " << endl;
      is >> constantName;
      os << "Print the constants value(complex<double>): " << endl;
      is >> constantValue;  
      (*expr).addVariable(constantName,constantValue);
      exprCST.push_back( make_pair(constantName,constantValue) );
    }
    return 1;
  }
  if (typeRead == VARIABLE_READ_EXPR_EXPR) // For VARIABLE_READ_EXPR_EXPR
  {
    os << "What is the initial value? (print a complex<double>) " << endl;
    is >> initialValue;
    currentValue = initialValue;
    // first expression
    expr = new Expr;
    os << "Print the expression of the Variable change in the fractal iteration:" << endl;
    is >> (*expr);
    os << "How many constants in the expression above? " << endl;
    is >> nrOfVariables;
    for(; nrOfVariables ; --nrOfVariables)
    {
      os << "Print the constants name: " << endl;
      is >> constantName;
      os << "Print the constants value(complex<double>): " << endl;
      is >> constantValue;  
      (*expr).addVariable(constantName,constantValue);
      exprCST.push_back( make_pair(constantName,constantValue) );
    }
    // second expression
    expr2 = new Expr;
    os << "Print the expression of the Variable change in the fractal sequence:" << endl;
    is >> (*expr2);
    os << "How many constants in the expression above? " << endl;
    is >> nrOfVariables;
    for(; nrOfVariables ; --nrOfVariables)
    {
      os << "Print the constants name: " << endl;
      is >> constantName;
      os << "Print the constants value(complex<double>): " << endl;
      is >> constantValue;  
      (*expr2).addVariable(constantName,constantValue);
      exprCST2.push_back( make_pair(constantName,constantValue) );
    }
    return 1;
  }
  return 0;
}

