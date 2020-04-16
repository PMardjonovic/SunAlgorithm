#include <ctime>
#include <iostream>
#include <cmath>
#include <string>
using namespace std; 

#ifndef SUN_H
#define SUN_H

class sun
{
private:
	//Constants for the class
	long double PI;
	long double DEG_IN_RADS;
	double J2000;
	/////////////////////////////////////////////////

	//Conversion to Julian Time- Equations based on ch 7
	long double calculateJulianTime();
	long double getJulianTimeIn(string, long double);
	/////////////////////////////////////////////////

	//Heliocentric Positioning-Equations from ch 31
	long double getHeliocentricLongitude(long double);
	long double getHeliocentricLatitude(long double);
	long double getHeliocentricRadiusVector(long double);
	long double calcPositionTerm(long double, long double, long double, long double);
	/////////////////////////////////////////////////

	//Obliquity of the Earths orbit- Equations from ch 21
	long double getObliquity(long double);
	/////////////////////////////////////////////////

	//Convert the sun's position into geocentric rectangluar coordinates-Equations from ch 25
	void getSunRectangularCoordinates(long double[4]);
	/////////////////////////////////////////////////

	//Finds the sun's geocentric position-Equations from ch 24
	void getSunCoordinates(long double[4]);
	/////////////////////////////////////////////////

public:
	void getSunPosition(long double [4]);
	sun();
};

#endif
