#include "colorimage.hpp"
#include "color.hpp"
#include "expr.hpp"
#include "image.hpp"
#include "fractal.hpp"

#include <iostream>
#include <string>

using namespace std;

char fn[] = "pic2.tga";

int main()
{
  int h = 500,w = 750;
  ImageDimension imgD(h,w);
  Image testimage(fn,imgD);

  Region rg(complex<double>(-1.5,1),complex<double>(1.5,-1));
  Expr exp;
  cin >> exp;

  Fractal fr(exp,rg);
  int **A;

  cout << "Generating fractal ... " << endl;
  A = fr.generate(imgD);
  cout << "done\n";

  int max=0;
  for(int i=0;i<h;++i)
    {
    for(int j=0;j<w;++j)
      if (max < A[i][j])
        max = A[i][j];
    }
  cout << max << endl;

 /** Normal Coloring
  ColorImage ci2("div(IT,C)","add(X,X)","add(X,X)");
  ci2.addVariable("C",complex<double>((double)max,0));
  ci2.addVariable("X",complex<double>(0,0));
  */
  ColorImage ci2("sin(mul(IT,X))","sin(add(Y,mul(IT,X)))","sin(add(Z,mul(IT,X)))");
  ci2.addVariable("C",complex<double>((double)max,0));
  ci2.addVariable("X",complex<double>(0.2,0.2));
  ci2.addVariable("Y",complex<double>(1,0));
  ci2.addVariable("Z",complex<double>(0,1));

  cout << "Generating colors ... " << endl;
  Color **genedcolors = ci2.make_image(A,imgD);
  cout << "done\n";
  /*for(int i=0;i<h;++i)
    for(int j=0;j<w;++j)
    {
      cout << "(" << i << "," << j << ") " << A[i][j] << " : " << genedcolors[i][j].getR() << "," << genedcolors[i][j].getG() << "," << genedcolors[i][j].getB() << endl;
    }*/

  testimage.setBrightness(BRIGHT);
  
  cout << "Writing in file ... " << endl;
  testimage.addColorMatrix(genedcolors);
  cout << "done\n";
  
 // cout << "Color image expr: " << ci2 << endl;

  for(int i=0;i<h;++i)
  {
    delete genedcolors[i];
    delete A[i];
  }
  delete genedcolors;
  delete A;
  
  return 0;
}
