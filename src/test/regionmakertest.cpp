#include <complex>
#include <fstream>
#include <iostream>

#include "regionmaker.hpp"
#include "region.hpp"
#include "regionvariable.hpp"

using namespace std;

int main()
{

  string regionFilename = "regionmakertestoutput.regionvar";

  // Print values in a file:
  complex<double> alu,arl,blu,brl;

  cout << "Print 2 complex numbers as corners of A" << endl;
  cin >> alu;
  cin >> arl;
  Region a(alu,arl);
  
  cout << "Print 2 complex numbers as corners of B" << endl;
  cin >> blu;
  cin >> brl;
  Region b(blu,brl);

  int it;
  cout << "Print nr of it: " << endl;
  cin >> it;

  makeRegionFile(a,b,it,regionFilename);

  // Handle the values from the file created:

  RegionVariable regV(regionFilename);  

  Region curr = regV.beginRegion();  
  cout << "Left up corner " << curr.getLeftUpCorner() << " ";
  cout << "Right down corner " << curr.getRightLowerCorner() << endl;
  for(int i=1;i<it;++i)
  {
    Region curr = regV.nextRegion();  
    cout << "At " << i << ": Left up corner " << curr.getLeftUpCorner() << " ";
    cout << "Right down corner " << curr.getRightLowerCorner() << endl;
  }

  return 0;
}
