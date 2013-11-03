#ifndef COLOR_H
#define COLOR_H	
/**
 * Basic color class with R G B
 */ 

class Color
{
private:
	double R,G,B;
public:
	Color();
	Color(double r,double g,double b);
  Color(const Color& rhs);
	Color operator*(const Color& rhs);
	Color& operator+=(const Color& rhs);
	Color& operator/=(const int N);
	bool operator==(const Color& rhs);
	Color operator+(const Color& rhs);
	Color operator=(const Color& rhs);

	void setR(double r);
	void setG(double g);
	void setB(double b);
	double getR();
	double getG();
	double getB();
};

#endif
