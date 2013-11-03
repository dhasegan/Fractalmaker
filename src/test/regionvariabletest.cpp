#include "region.hpp"
#include "regionvariable.hpp"

#include <string>
#include <iostream>
#include <complex>

using namespace std;

int main()
{
  RegionVariable regV;
  cin >> regV;

  Region curr = regV.beginRegion();  
  cout << "Left up corner " << curr.getLeftUpCorner() << " ";
  cout << "Right down corner " << curr.getRightLowerCorner() << endl;
  for(int i=0;i<20;++i)
  {
    Region curr = regV.nextRegion();  
    cout << "At " << i << ": Left up corner " << curr.getLeftUpCorner() << " ";
    cout << "Right down corner " << curr.getRightLowerCorner() << endl;
  }
  
  return 0;
}
