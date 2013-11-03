#include "colorimage.hpp"
#include "color.hpp"
#include "expr.hpp"

#include <iostream>
#include <string>

using namespace std;

char* fn = "pic2.tga";

int main()
{
  int h = 10,w = 10;
  ImageDimension imgD(w,h);
  Image testimage(fn,imgD);

/*  Expr er("IT");
  er.addVariable("IT",complex<double>(2,3));
  cout << er.calculate() << endl;*/
  

  Expr eg("sin(IT)");
  Expr eb("sin(IT)");
  //ColorImage ci2;//(er,eg,eb);
  ColorImage ci2("cos(mul(C,IT))","sin(mul(C,IT))","mul(cos(mul(C,IT)),sin(mul(C,IT)))");
  ci2.addVariable("C",complex<double>(0.3,0));
 // cin >> ci2;
  int **A = new int* [h];
  for(int i=0;i<h;++i)
    A[i] = new int [w];
  for(int i=0;i<h;++i)
    for(int j=0;j<w;++j)
      A[i][j] = j+i;

  Color **genedcolors = ci2.make_image(A,imgD);
  for(int i=0;i<h;++i)
    for(int j=0;j<w;++j)
    {
      cout << "(" << i << "," << j << ") " << A[i][j] << " : " << genedcolors[i][j].getR() << "," << genedcolors[i][j].getG() << "," << genedcolors[i][j].getB() << endl;
    }

  testimage.setBrightness(BRIGHT);
  testimage.addColorMatrix(genedcolors);

  cout << "Color image expr: " << ci2 << endl;

  for(int i=0;i<h;++i)
  {
    delete genedcolors[i];
    delete A[i];
  }
  delete genedcolors;
  delete A;
  
  return 0;
}
