
/**
 * @brief This function gives you an interface to chose a expr 
 *          for a fractal
 *
 */ 

// System includes
#include <iostream>
#include <fstream>
#include <complex>
#include <string>
#include <vector>

// Local includes
#include "fractalgenerator.hpp"
#include "expr.hpp"
#include "variable.hpp"

// Namespaces 
using namespace std;

// Constants
string 
string outputFile = "expr.log";

void printIntro()
{
  // Starting lines
  cout << "=======================================================================" << endl;
  cout << "|                         Expression Chooser                          |" << endl;
  cout << "=======================================================================" << endl;
  cout << "| Hello! Welcome to the Expression Chooser Interface!                 |" << endl;
  cout << "| We will try to find an expression that makes a good fractal         |" << endl;
  cout << "=======================================================================" << endl;
}

int main()
{
  Expr exp;
  int varsNr;
  vector< Variable* > vars;
  Variable* vi;

  fstream flog;

  int ok = 0;
  char c;


  flog.open(outputFile.c_str(),ios::out);

  printIntro();
  while (!ok)
  {
    // find the expression we want
    cout << "=== Print an expression that you want to visualize: " << endl;
    cin >> exp;
    // get the nr of variables
    cout << "=== Print the number of variables the expression has: " << endl;
    cin >> varsNr;
    for(int i = 0 ; (unsigned int)i < varsNr ; ++i)
    {
      // get each variable throught the Variable.Interface 
      cout << "=== Now consider variable " << i+1 << ": " << endl;
      vi = new Variable;
      if ( (*vi).Interface(cin,cout) )
        vars.push_back(vi);
    }

    // find if they want a fractal sequence
    cout << "Do you want to make a fractal sequence? (y/n) \n";
    cin >> isIter;
    if ((c == 'y') || (c == 'Y'))
    {
      file.
    }

    cout << "=== Is this expression good? (y/n) " ;
    cin >> c;
    ok = ((c == 'y') || (c == 'Y'));

    if (ok)    
    {
      // writeExpression

    }

    for(int i; (unsigned int)i < vars.size() ; ++i)
    {
      vi = vars[i]; 
      delete vi;
    }
    vars.clear();
  }
 
  flog.close();
 
  return 0;
}
