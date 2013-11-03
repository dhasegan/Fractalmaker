/*
 * Implementation of expression class
 */ 

// System includes
#include <vector>
#include <string> 
#include <iostream>
#include <fstream> 
#include <stack>
#include <complex>
#include <cstdio>
#include <map>
#include <cstring>

// Local includes
#include "expr.hpp"

using namespace std;

Expr::Expr()
{
  root = NULL;
  goodExpression = 0;
}

Expr::Expr(string Content)
{
  // TODO: WORK WITH SPACES
  int ok;
  string name;
  char c;
  stack<ENode *> St;
  int paranth = 0;
  root = new ENode;
  ENode* currentENode = root;
  goodExpression = 0;
  int hasParantheses = 0;

  ok = 1;
  for(int i=0;(unsigned int)i<Content.size();++i)
  {
    c = Content[i];
    if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') )
      name.push_back(c);
    else if (c == '(')
    {
      hasParantheses = 1;
      paranth ++;
      int code = functionCode( name );
      if (code < 0)
      {
        fprintf(stderr,"Expression: Input function is not valid!\n");
        return ;
      }
      currentENode->type = EFunction;
      currentENode->code = code;
      int pnr = functionParams( name );
      if (pnr == 1)
      {
        currentENode->params = 1;
        currentENode->Param1 = new ENode;
        currentENode->Param2 = NULL;
      }
      if (pnr == 2)
      {
        currentENode->params = 2;
        currentENode->Param1 = new ENode;
        currentENode->Param2 = new ENode;
      }

      name.clear();
      St.push( currentENode );
      currentENode = currentENode->Param1;
    }
    else if ( c == ',' )
    {
      ENode* prevNode = St.top();
      string nm = functionString(prevNode->code);
      if (name != "")
      {
        currentENode->type = EVariable;
        currentENode->var = new char[ name.size() ];
        for(int i=0;(unsigned int)i<=name.size();++i)
          currentENode->var[i]= name[i];
        currentENode->code = 0;
        currentENode->params = 0;
        currentENode->Param1 = NULL;
        currentENode->Param2 = NULL;
        name.clear();
      }
      if (functionParams(nm) <= 1)
      {
        fprintf(stderr,"Expression: Too many parameters!\n");
        return ;
      }
      currentENode = prevNode->Param2;
    }
    else if ( c == ')' )
    {
      if (paranth <= 0)
      {
        fprintf(stderr,"Expression: Bad input! Check Parantheses!\n");
        return ;
      }
      else
        paranth --;
      ENode* prevNode = St.top();
      St.pop();
      if (name != "")
      {
        currentENode->type = EVariable;
        currentENode->var = new char[ name.size()+1 ];
        for(int i=0;(unsigned int)i<=name.size();++i)
          currentENode->var[i]= name[i];
        currentENode->code = 0;
        currentENode->params = 0;
        currentENode->Param1 = NULL;
        currentENode->Param2 = NULL;
        name.clear();
      }
      currentENode = prevNode;
      if (St.empty()) 
        ok = 0;
    }
    else if ( c != ' ' && c != ';' )
    {
      fprintf(stderr,"Expression: Bad character input: %c!\n",c);
    }
  }
  if (ok)
  {
    if (hasParantheses == 0 && name != "")
    {
        currentENode->type = EVariable;
        currentENode->var = new char[ name.size() ];
        for(int i=0;(unsigned int)i<=name.size();++i)
          currentENode->var[i]= name[i];
        currentENode->code = 0;
        currentENode->params = 0;
        currentENode->Param1 = NULL;
        currentENode->Param2 = NULL;
        name.clear(); 
        goodExpression = 1;
        return ;
    }
    fprintf(stderr,"Expression: Bad input!\n");
    return ;
  }
  if (paranth)
  {
    fprintf(stderr,"Expression: Bad input! Check Parantheses!\n");
    return ;
  }

  goodExpression = 1;
}

void copyENode(ENode *destN, ENode* sourceN)
{
  if (sourceN == NULL)
  {
    destN = NULL;
    return ;
  }
  if (sourceN->type == EVariable)
  {    
    destN->type = EVariable;
    destN->var = new char[ strlen( sourceN->var )+1 ];
    destN->params = 0;
    destN->Param1 = NULL;
    destN->Param2 = NULL;
    strcpy(destN->var,sourceN->var);
    return ;
  }
  if (sourceN->type == EFunction)
  {
    destN->type = EFunction;
    destN->code = sourceN->code;
    destN->params = sourceN->params;
    if (sourceN->Param1 != NULL)
    {
      destN->Param1 = new ENode;
      copyENode(destN->Param1,sourceN->Param1);
    }
    else
      destN->Param1 = NULL;
    if (sourceN->Param2 != NULL)
    {
      destN->Param2 = new ENode;
      copyENode(destN->Param2,sourceN->Param2);
    }
    else 
      destN->Param2 = NULL;
  }
}

Expr::Expr(const Expr& exp)
{
  goodExpression = exp.goodExpression;
  if (!exp.goodExpression)
  {
    fprintf(stderr,"Expression: Cannot copy expression");
  }
  else
  {
    root = new ENode;
    copyENode(root,exp.root); 
  }
}

void deleteENode(ENode *n)
{
  if (n->params == 0)
    delete n->var;
  if (n->Param1 != NULL && n->params >= 1)
    deleteENode( n->Param1 ); 
  if (n->Param2 != NULL && n->params == 2)
    deleteENode( n->Param2 ); 

  delete n;
}

Expr::~Expr()
{
  if (root != NULL)
    deleteENode(root);
}

complex<double> calcNode(ENode* nod,map<string,complex<double> > &vmp)
{
  if (nod->type == EVariable)
  {
    map<string,complex<double> >::iterator it;
    it = vmp.find((string)nod->var);
    if (it == vmp.end())
    {
      fprintf(stderr,"Expression: Please input all necessary variables!\n");
      return complex<double>(1,0);
    }

    return it->second;
  }

  if (nod->params == 1) // 1 parameter
  {
  string str = functionString(nod->code);
  complex<double> P1 = calcNode(nod->Param1,vmp);
  if (str == "sin")
    return sin(P1);
  if (str == "sinh")
    return sinh(P1);
  if (str == "cos")
    return cos(P1);
  if (str == "cosh")
    return cosh(P1);
  if (str == "tan")
    return tan(P1);
  if (str == "tanh")
    return tanh(P1);
  if (str == "exp")
    return exp(P1);
  if (str == "log")
    return log(P1);
  if (str == "sqrt")
    return sqrt(P1);
  if (str == "real")
    return complex<double>(real(P1),0);
  if (str == "imag")
    return complex<double>(imag(P1),0);
  if (str == "abs")
    return complex<double>(abs(P1),0);
  if (str == "arg")
    return complex<double>(arg(P1),0);
  if (str == "norm")
    return complex<double>(norm(P1),0);
  if (str == "conj")
    return conj(P1);
  if (str == "polar")
    return polar(real(P1),imag(P1));
  }


  if (nod->params == 2) // 2 parameters
  {
  string str = functionString(nod->code);
  complex<double> P1 = calcNode(nod->Param1,vmp);
  complex<double> P2 = calcNode(nod->Param2,vmp);  
  if (str == "add")
    return P1+P2;
  if (str == "sub")
    return P1-P2;
  if (str == "mul")
    return P1*P2;
  if (str == "div")
  {
    if (P2 != complex<double>(0,0))
      return P1/P2;
    else
    {
      fprintf(stderr,"Expression: Division by 0!\n");
      return complex<double>(1,0);
    }
  }
  if (str == "pow")
    return pow(P1,P2);
  }
  return complex<double>(1,0);
}

void Expr::addVariable(string name,complex<double> value)
{
    map< string , complex<double> >::iterator it;
    it = variables.find(name);
    if (it == variables.end())
    {
      variables.insert( make_pair(name,value) );
      return ;
    }
    variables[name] = value;
}

complex<double> Expr::calculate()
{
  return calcNode(root,variables);
}

Expr Expr::operator=(const Expr &rhs)
{
  goodExpression = rhs.goodExpression;
  if (!rhs.goodExpression)
  {
    fprintf(stderr,"Expression: Cannot copy expression\n");
  }
  else
  {
    root = new ENode;
    copyENode(root,rhs.root); 
  }
  return (*this);
}

istream& operator >>(istream &is,Expr &exp)
{
  string Content;
  is >> Content;
  Expr newExp(Content);
  exp = newExp;

  return is;
}

string getStringENode(ENode* nod)
{
  string ret = "";
  if (nod == NULL)
    return "";
  if (nod->type == EVariable)
  {    
    return (string)nod->var;
  }
  if (nod->type == EFunction)
  {
    ret = functionString(nod->code);
    int pnr = functionParams(ret);
    ret.push_back('(');
    ret.append( getStringENode(nod->Param1) );
    if (pnr > 1)
    {
      ret.push_back(',');
      ret.append( getStringENode(nod->Param2) );
    }
    ret.push_back(')');
    return ret;
  }
  return "";
}

string Expr::getString()
{
  return getStringENode(root);
}

ostream& printENode(ostream& os, ENode* nod)
{
  if (nod == NULL)
    return os;
  if (nod->type == EVariable)
  {    
    os << nod->var;
    return os;
  }
  if (nod->type == EFunction)
  {
    string nm = functionString(nod->code);
    int pnr = functionParams(nm);
    os << nm << "(";
    printENode(os,nod->Param1);
    if (pnr > 1)
    {
      os << ",";
      printENode(os,nod->Param2);
    }
    os << ")";
    return os;
  }
  return os;
}

ostream& operator <<(ostream& os,Expr &exp)
{
  if (exp.goodExpression)
    return printENode(os, exp.root);
  fprintf(stderr, "Expression: Cannot PRINT! Bad expression!");
  return os;
}

int functionCode(std::string str)
{
  if (str == "add")
    return 1;
  if (str == "sub")
    return 2;
  if (str == "mul")
    return 3;
  if (str == "div")
    return 4;
  if (str == "pow")
    return 5;
  if (str == "sin")
    return 6;
  if (str == "sinh")
    return 7;
  if (str == "cos")
    return 8;
  if (str == "cosh")
    return 9;
  if (str == "tan")
    return 10;
  if (str == "tanh")
    return 11;
  if (str == "exp")
    return 12;
  if (str == "log")
    return 13;
  if (str == "sqrt")
    return 14;
  if (str == "real")
    return 15;
  if (str == "imag")
    return 16;
  if (str == "abs")
    return 17;
  if (str == "arg")
    return 18;
  if (str == "norm")
    return 19;
  if (str == "conj")
    return 20;
  if (str == "polar")
    return 21;
  return -1;
}
int functionParams(string str)
{
  if (str == "add")
    return 2;
  if (str == "sub")
    return 2;
  if (str == "mul")
    return 2;
  if (str == "div")
    return 2;
  if (str == "pow")
    return 2;
  if (str == "sin")
    return 1;
  if (str == "sinh")
    return 1;
  if (str == "cos")
    return 1;
  if (str == "cosh")
    return 1;
  if (str == "tan")
    return 1;
  if (str == "tanh")
    return 1;
  if (str == "exp")
    return 1;
  if (str == "log")
    return 1;
  if (str == "sqrt")
    return 1;
  if (str == "real")
    return 1;
  if (str == "imag")
    return 1;
  if (str == "abs")
    return 1;
  if (str == "arg")
    return 1;
  if (str == "norm")
    return 1;
  if (str == "conj")
    return 1;
  if (str == "polar")
    return 1;
  return 0;
}

string functionString(int cd)
{
  int i = cd;
  if (i < 1 || i > 21)
    return "";
  if (i == 1)
    return "add";
  if (i == 2)
    return "sub";
  if (i == 3)
    return "mul";
  if (i == 4)
    return "div";
  if (i == 5)
    return "pow";
  if (i == 6)
    return "sin";
  if (i == 7)
    return "sinh";
  if (i == 8)
    return "cos";
  if (i == 9)
    return "cosh";
  if (i == 10)
    return "tan";
  if (i == 11)
    return "tanh";
  if (i == 12)
    return "exp";
  if (i == 13)
    return "log";
  if (i == 14)
    return "sqrt";
  if (i == 15)
    return "real";
  if (i == 16)
    return "imag";
  if (i == 17)
    return "abs";
  if (i == 18)
    return "arg";
  if (i == 19)
    return "norm";
  if (i == 20)
    return "conj";
  if (i == 21)
    return "polar";
  return "";
}

