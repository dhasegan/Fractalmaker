/**
 * Implementation of Image class and ImageDimension Class
 */ 

// System includes
#include <iostream>
#include <fstream>
#include <cmath>

// Local includes
#include "color.hpp"
#include "image.hpp"

using namespace std;

Image::Image(const char* fileName,ImageDimension& imgD)
{
  imageDim = imgD;
  type = BRIGHT;

	int height = imgD.getHeight();
	int width = imgD.getWidth();
	imageFile.open(fileName,ios_base::binary);

	imageFile.put(0).put(0);
	imageFile.put(2);

	imageFile.put(0).put(0);
	imageFile.put(0).put(0);
	imageFile.put(0);

	imageFile.put(0).put(0);
	imageFile.put(0).put(0);

	imageFile.put((unsigned char)(width & 0x00FF)).put((unsigned char)((width & 0xFF00) / 256));
	imageFile.put((unsigned char)(height & 0x00FF)).put((unsigned char)((height & 0xFF00) / 256));
	imageFile.put(24);
	imageFile.put(0);
}

Image::~Image()
{
	imageFile.close();
}
  
void Image::setBrightness(enum ImageBrightness t)
{
  type = t;
}
  
enum ImageBrightness Image::getBrightness()
{
  return type;
}

void Image::addColor(Color c)
{
  if (type == BRIGHT)
	  imageFile
	  	.put((unsigned char)255*(c.getB()))
	  	.put((unsigned char)255*(c.getG()))
	  	.put((unsigned char)255*(c.getR()));
  else
	  imageFile.put((unsigned char)255*(1-exp(-c.getB()))).put((unsigned char)255*(1-exp(-c.getG()))).put((unsigned char)255*(1-exp(-c.getR())));
}

void Image::addColorMatrix(Color **color)
{
  int height = imageDim.getHeight();
  int width = imageDim.getWidth();
  for(int i=0;i<height;++i)
    for(int j=0;j<width;++j)
      addColor(color[i][j]);
}

ImageDimension::ImageDimension()
{
  width = height = 0;
}
  
ImageDimension::ImageDimension(int h,int w)
{
  width = w;
  height = h;
}

ImageDimension::~ImageDimension()
{
}

void ImageDimension::setHeight(int h)
{
  height = h;
}
  
void ImageDimension::setWidth(int w)
{
  width = w;
}
  
int ImageDimension::getHeight()
{
  return height;
}

int ImageDimension::getWidth()
{
  return width;
}

double ImageDimension::getRatio()
{
  return ((double)width/height);
}
  
ImageDimension& ImageDimension::operator=(const ImageDimension& rhs)
{
  height = rhs.height;
  width = rhs.width;
  return (*this);
}

