#ifndef _IMAGE_H
#define _IMAGE_H
/**
 * Image Class and ImageDimension Class
 * which actually makes the .tga files
 */ 

// System includes
#include <iostream>
#include <fstream>

// Local includes
#include "color.hpp"

enum ImageBrightness
{
  BRIGHT,
  NOT_BRIGHT,
};

class ImageDimension
{
private:
  int height;
  int width;
public:
  ImageDimension();
  ImageDimension(int h,int w); // height, width
  ~ImageDimension();

  void setHeight(int h);
  void setWidth(int w);
  int getHeight();
  int getWidth();
  double getRatio();
  ImageDimension& operator=(const ImageDimension& rhs);
};

class Image // Image puts pixels in a weird order 
{			// but from the last line every pixel from left to right to the first line every pixel from left to right
			// in system xOy starts from (0,0) goes to right to (0,w)
				// then takes every line (i,0) to (i,w)
				// until reaches last line (h,0) to (h,w)
private: 
  ImageDimension imageDim;
  enum ImageBrightness type;
	std::ofstream imageFile;
	
public:
	Image(const char* fileName,ImageDimension& imgD);
	~Image();

  void setBrightness(enum ImageBrightness t);
  enum ImageBrightness getBrightness();
	
	void addColor(Color color); 
  void addColorMatrix(Color **color);
};

#endif
