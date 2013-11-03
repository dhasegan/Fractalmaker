#include "types/expr.hpp"
#include <iostream>

using namespace std;

int main()
{
  Expr exp;//("add(mul(A,B),C)");
  cin >> exp;
  cout << (exp.getString()) << endl;


  cout << "My version: " << exp << endl;
  exp.addVariable("A",complex<double>(2.0,0));
  exp.addVariable("B",complex<double>(0,1.0));
  exp.addVariable("C",complex<double>(1.2,3.3));
  cout << "Result: " << exp.calculate() << endl;
  exp.addVariable("B",complex<double>(1.0,0));
  cout << "Result: " << exp.calculate() << endl;
  return 0;
}
