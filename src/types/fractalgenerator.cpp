/**
 * @brief implementation of the Fractal Generator class
 */

// Header include
#include "fractalgenerator.hpp"

// System includes
#include <string>
#include <iostream>
#include <fstream>

// Local includes
#include "expr.hpp"
#include "variable.hpp"
#include "image.hpp"
#include "color.hpp"
#include "colorimage.hpp"
#include "region.hpp"
#include "regionvariable.hpp"
#include "fractal.hpp"

// Namespaces
using namespace std;


FractalGenerator::FractalGenerator()
{
  gotResults = 0;
  iterations = 0;
  expr = NULL; 
  nrVariables = 0;
  variables = NULL;
  regionvariable = NULL;
  colorimage = NULL;
  nrColorVariables = 0;
  colorvariables = NULL;
}

FractalGenerator::FractalGenerator(string fn)
{
  gotResults = 0;
  iterations = 0;
  expr = NULL; 
  nrVariables = 0;
  variables = NULL;
  regionvariable = NULL;
  colorimage = NULL;
  nrColorVariables = 0;
  colorvariables = NULL;

  readFromFilename(fn);
}

FractalGenerator::~FractalGenerator()
{
  if (expr != NULL)
    delete expr;
  if (nrVariables > 0 && variables != NULL)
    delete[] variables;
  if (regionvariable != NULL)
    delete regionvariable;
  if (colorimage != NULL)
    delete colorimage;
  if (nrColorVariables > 0 && colorvariables != NULL)
    delete[] colorvariables;
}

void FractalGenerator::readFromFilename(string fn)
{
  // get filename
  filename = fn;
 
  // open file 
  fstream fin;
  fin.open(fn.c_str(),ios::in);

  if (!fin.is_open())
  {
      fprintf(stderr,"FractalGenerator Error: Cannot open file!\n");
      gotResults = 0;
      return ;
  }

  // read nr of iterations
  fin >> iterations;
  if (iterations <= 0)
  {
    fprintf(stderr,"FractalGenerator Error: bad iteration number\n");
    gotResults = 0;
    return ;
  }

  // read fractal filename
  fin >> fractalfilename;
  if (fractalfilename != "" && fractalfilename.compare( fractalfilename.size() - 4, 4 , ".tga" ) != 0)
  {
    // if the fractal file name does not end in ".tga"
    fprintf(stderr,"FractalGenerator Error: bad fractal file name\n");
    gotResults = 0;
    return ;
  }

  // read Image Dimension
  int height,width;
  fin >> height;
  fin >> width;
  imagedimension.setHeight(height);
  imagedimension.setWidth(width);
  
  // read expression
  expr = new Expr;
  fin >> (*expr);

  // read nr of variables
  fin >> nrVariables;
  if (nrVariables < 0)
  {
    fprintf(stderr,"FractalGenerator Error: bad number of variables\n");
    gotResults = 0;
    return ;
  }
  // read variables if we have some
  if (nrVariables > 0)
  {
    variables = new Variable[ nrVariables ];  
    for(int i=0;i<nrVariables;++i)
    {
      fin >> variables[i];
    }
  }

  // read regionvariables
  regionvariable = new RegionVariable;
  fin >> (*regionvariable);

  // read colorimage
  colorimage = new ColorImage;
  fin >> (*colorimage);

  // read nr of color variables
  fin >> nrColorVariables;
  if (nrColorVariables < 0)
  {
    fprintf(stderr,"FractalGenerator Error: bad number of color variables\n");
    gotResults = 0;
    return ;
  }
  // read colorvariables if we have some
  if (nrColorVariables > 0)
  {
    colorvariables = new Variable[ nrColorVariables ];  
    for(int i=0;i<nrColorVariables;++i)
    {
      fin >> colorvariables[i];
    }
  }

  // close file
  fin.close();

  // everything went fine!
  gotResults = 1;
}

// creates all the fractals
void FractalGenerator::generate()
{
  Region currReg;
  pair<string, complex<double> > varValue;
  int h = imagedimension.getHeight();
  int w = imagedimension.getWidth();
  int **imageIt;
  Color **imageColor;

  // check if everything was read good:
  if (gotResults == 0)
  {
    fprintf(stderr,"FractalGenerator Error: Cannot generate!\n");
    return ;
  }
  
  // set fractal
  fractal.setFractalFunction( (*expr) );
  currReg = (*regionvariable).beginRegion();
  fractal.setFractalRegion(currReg);
  
  // set variables on fractal
  for(int i=0 ; i < nrVariables ; ++i)
  {
    varValue = variables[i].begin();
    fractal.addVariable( varValue.first, varValue.second );
    cout << "first X = " << varValue.second << endl;
  }
  // set variables on color image
  for(int i=0; i < nrColorVariables ; ++i)
  {
    varValue = colorvariables[i].begin();
    (*colorimage).addVariable( varValue.first, varValue.second ); 
  }

  // create tables for Iteration and color
  imageIt = new int*[ h ];
  imageColor = new Color*[ h ];
  for(int i=0; i < h ;++i)
  {
    imageIt[i] = new int[ w ];
    imageColor[i] = new Color[ w ];
  }

  // RUN
  cout << "Printing fractals: " << endl;
  for(int i=0; i < iterations ;++i)
  {
    cout << "Fractal " << i+1 << " out of " << iterations << " ... ";
    cout.flush();
    // make fractal
    fractal.generate(imageIt,imagedimension);
    (*colorimage).make_image(imageColor,imageIt,imagedimension);
    Image image(fractalfilename.c_str(),imagedimension);
    // write in file
    image.addColorMatrix(imageColor);


    // increment region
    currReg = (*regionvariable).nextRegion();
    fractal.setFractalRegion(currReg);

    // increment variables on fractal
    for(int j=0 ; j < nrVariables ; ++j)
    {
      varValue = variables[j].nextIteration();
      cout << "next X = " << varValue.second << endl;
      fractal.addVariable( varValue.first, varValue.second );
    }
    // increment variables on color image
    for(int j=0; j < nrColorVariables ; ++j)
    {
      varValue = colorvariables[j].nextIteration();
      (*colorimage).addVariable( varValue.first, varValue.second ); 
    }
    
    // increment filename
    if ( !incrementFilename(fractalfilename) )
    {
      fprintf(stderr,"FractalGenerator Error: Bad fractal filename: could not increment!\n");
      return ;
    }

    cout << "done!" << endl;
  }

  // delete tables for Iteration and color
  for(int i=0;i < h ;++i)
  {
    delete[] imageIt[i];
    delete[] imageColor[i];
  }
  delete[] imageIt;
  delete[] imageColor;
}

void FractalGenerator::generate(int progsnr,int progs)
{
  Region currReg;
  pair<string, complex<double> > varValue;
  int h = imagedimension.getHeight();
  int w = imagedimension.getWidth();
  int **imageIt;
  Color **imageColor;

  // check if everything was read good:
  if (gotResults == 0)
  {
    fprintf(stderr,"FractalGenerator Error: Cannot generate!\n");
    return ;
  }
  
  // set fractal
  fractal.setFractalFunction( (*expr) );
  currReg = (*regionvariable).beginRegion();
  fractal.setFractalRegion(currReg);
  
  // set variables on fractal
  for(int i=0 ; i < nrVariables ; ++i)
  {
    varValue = variables[i].begin();
    fractal.addVariable( varValue.first, varValue.second );
  }
  // set variables on color image
  for(int i=0; i < nrColorVariables ; ++i)
  {
    varValue = colorvariables[i].begin();
    (*colorimage).addVariable( varValue.first, varValue.second ); 
  }

  // create tables for Iteration and color
  imageIt = new int*[ h ];
  imageColor = new Color*[ h ];
  for(int i=0; i < h ;++i)
  {
    imageIt[i] = new int[ w ];
    imageColor[i] = new Color[ w ];
  }

  // RUN
  cout << "Printing fractals: " << endl;
  for(int i=0; i < iterations ;++i)
  {
    if (i % progs == progsnr)
    {
      cout << "Fractal " << i/progs << " out of " << (iterations-1)/progs+(iterations%progs >= progsnr) << " ... "; 
      cout.flush();
      // make fractal
      fractal.generate(imageIt,imagedimension);
      (*colorimage).make_image(imageColor,imageIt,imagedimension);
      Image image(fractalfilename.c_str(),imagedimension);
      // write in file
      image.addColorMatrix(imageColor);
    }


    // increment region
    currReg = (*regionvariable).nextRegion();
    fractal.setFractalRegion(currReg);

    // increment variables on fractal
    for(int j=0 ; j < nrVariables ; ++j)
    {
      varValue = variables[j].nextIteration();
      fractal.addVariable( varValue.first, varValue.second );
    }
    // increment variables on color image
    for(int j=0; j < nrColorVariables ; ++j)
    {
      varValue = colorvariables[j].nextIteration();
      (*colorimage).addVariable( varValue.first, varValue.second ); 
    }
    
    // increment filename
    if ( !incrementFilename(fractalfilename) )
    {
      fprintf(stderr,"FractalGenerator Error: Bad fractal filename: could not increment!\n");
      return ;
    }

    if (i % progs == progsnr)
      cout << "done!" << endl;
  }

  // delete tables for Iteration and color
  for(int i=0;i < h ;++i)
  {
    delete[] imageIt[i];
    delete[] imageColor[i];
  }
  delete[] imageIt;
  delete[] imageColor;
}
  
// creates all the fractals from the filename fn
void FractalGenerator::generate(string fn)
{
  readFromFilename(fn);
  generate();
}

int FractalGenerator::incrementFilename(string &fn)
{
  int it = fn.size() - 5;
  int ok = 1;
  while (ok)
    if (fn[it] < '0' || fn[it] > '9' || it < 0)
    {
      return 0;  
    }
    else
    {
      fn[it] ++;
      if (fn[it] > '9')
      {
        fn[it] = '0';
        it --;
        ok = 1;
      }
      else 
        ok = 0;    
    }
  return 1;
}
