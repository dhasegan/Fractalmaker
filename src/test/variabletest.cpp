#include <string>
#include <complex>

#include "variable.hpp"

using namespace std;

int main()
{
  Variable var;
  cin >> var;
  pair< string , complex<double> > curr = var.begin();
  for(int i=0;i<10;++i)
  {
    cout << ">>>>" << endl; 
    for(int j=0;j < 5 ; ++j)
    {
      cout << i << ": " << curr.first << " with value " << curr.second << endl;
      curr = var.nextFractalIteration();
    }
    curr = var.nextIteration();
  }
  cout << "my version: " << var << endl;

  return 0;
}
