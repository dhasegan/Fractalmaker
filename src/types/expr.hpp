/*
 * Expression class that determines a expression as a tree
 */ 
#ifndef _EXPR
#define _EXPR

// System includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream> 
#include <complex>
#include <map>

enum ENodeTypes 
{
  EFunction,
  EVariable
};

int functionCode(std::string);
int functionParams(std::string);
std::string functionString(int);

struct ENode
{
  ENodeTypes type;
  int code;
  char* var;
  int params;
  ENode *Param1,*Param2;
};

class Expr 
{
private:
  ENode *root;
  int goodExpression;
  std::map< std::string, std::complex<double> > variables;
public:
  Expr();
  Expr(std::string);
  Expr(const Expr&);
  ~Expr();

  /**
   * @brief Add a variable
   */
  void addVariable(std::string,std::complex<double>);
  /**
   * @brief Calculate using the given variables
   */
  std::complex<double> calculate();

  std::string getString();
  Expr operator=(const Expr &rhs);
  friend std::istream& operator >>(std::istream& is,Expr &exp);
  friend std::ostream& operator <<(std::ostream& os,Expr &exp);
};

std::istream& operator >>(std::istream& is,Expr &exp);
std::ostream& operator <<(std::ostream& os,Expr &exp);

 // TODO: int needsVariable(std::string); 

#endif
