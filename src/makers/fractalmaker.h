#include"fractalmaker.h"

FractalMaker::FractalMaker(Fractal &frac,Region &reg,int** colorInput,char* filename)
{
	changeIterations(frac,reg);
	Image img(filename,IMAGE_WIDTH,IMAGE_HEIGHT);

	int w = IMAGE_WIDTH,h = IMAGE_HEIGHT;
	for(int j=h;j>0;--j) // for every pixel calculate its value
		for(int i=1;i<=w;++i) 
		{
			complex <double> C = fromPixelToRegion(i,j,reg);

			int nr_it = frac.gen(C);
			Color newColor = findColor(nr_it, colorInput);
			img.addColor(newColor);
		}
}

Color FractalMaker::findColor(int nr_it,int** c)
{
	if (!nr_it) 
		return Color(0,0,0); // Black
//Color Black(0,0,0);
	
	/* Correct color formulation 
	double red = abs(cos(c[0][0]*Pi/(c[0][1]*nr_it)+Pi/c[0][2]));
	double green = abs(cos(c[1][0]*Pi/(c[1][1]*nr_it)+Pi/c[1][2]));
	double blue = abs(cos(c[2][0]*Pi/(c[2][1]*nr_it)+Pi/c[2][2]));
	*/

	double divident = ( (double)50 - nr_it );
	double red = 1-abs(cos(c[0][0]*Pi/(c[0][1]*nr_it)+Pi/c[0][2]));
	double blue = 1-abs(cos(c[1][0]*Pi/(c[1][1]*nr_it)+Pi/c[1][2]));
	double green = 1-abs(cos(c[2][0]*Pi/(c[2][1]*nr_it)+Pi/c[2][2]));

	return Color(red,green,blue);
}

void FractalMaker::changeIterations(Fractal &f,Region &r)
{
	double L = r.getLength();
	f.setIt(100/pow(L,((double)1/4)));
}

double calculateZoom(double ratio)
{ 
	return pow(ZoomConstantInSlideshow,ratio*maxIterationsPerZoom);
	// p = r^(d/v) where
	// p - zoom ratio here 
	// r - zoom rate in slideshow 0.98 or 9.95
	// d - ratio of vector to dimension of region. in (0,1)
	// v - speed of the zoom in slideshow i.e. v = 1/100
	// deduced from formulas: r^n = p and v = d/n where n is the iterations of the zoom needed
}
