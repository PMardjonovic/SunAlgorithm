#include "sun.h"
#include <unistd.h>
#include <cmath>

sun::sun()

{

	PI = 4 * atan2(1, 1);

	DEG_IN_RADS = PI / 360;

	J2000 = 2451545.0;

}

long double sun::calculateJulianTime()

{

	//Grab the current Unix time from the system

	long double currentTime = time(0);



	//convert the current time into julian days

	// Conversion comes from http://stackoverflow.com/questions/466321/convert-unix-timestamp-to-julian

	return (currentTime / 86400.0) + 2440587.5;

}



long double sun::getJulianTimeIn(string scale, long double currentTime)

{

	double conversion = 1;



	if (scale == "seconds")

	{

		conversion = 24 * 60 * 60;

	}

	else if (scale == "minuets")

	{

		conversion = 24 * 60;

	}

	else if (scale == "hours")

	{

		conversion = 24;

	}

	else if (scale == "years")

	{

		conversion = 1 / 365.25;

	}

	else if (scale == "centuries")

	{

		conversion = 1 / (365.25 * 100);

	}

	else if (scale == "millennia")

	{

		conversion = 1 / (365.25 * 1000);

	}

	else if (scale == "tenmillennia")

	{

		conversion = 1 / (365.25 * 10000);

	}

	else

	{ }

	return currentTime * conversion;

}



long double sun::getHeliocentricLongitude(long double currentTime)

{

	long double L, l[5];



	l[0] = calcPositionTerm(175347046, 0, 0, currentTime);						//1

	l[0] = l[0] + calcPositionTerm(3341656, 4.6692568, 6283.07585, currentTime);//2

	l[0] = l[0] + calcPositionTerm(34894, 4.6261, 12566.1517, currentTime);		//3

	l[0] = l[0] + calcPositionTerm(3497, 2.7441, 5753.3849, currentTime);		//4

	l[0] = l[0] + calcPositionTerm(3418, 2.8289, 3.5231, currentTime);			//5

	l[0] = l[0] + calcPositionTerm(3136, 3.6277, 77713.7715, currentTime);		//6

	l[0] = l[0] + calcPositionTerm(2676, 4.4181, 7860.4194, currentTime);		//7

	l[0] = l[0] + calcPositionTerm(2343, 6.1352, 3930.2097, currentTime);		//8

	l[0] = l[0] + calcPositionTerm(1324, 0.7425, 11506.7698, currentTime);		//9

	l[0] = l[0] + calcPositionTerm(1273, 2.0371, 529.691, currentTime);			//10



	l[1] = calcPositionTerm(628331966747, 0, 0, currentTime);					//1

	l[1] = l[1] + calcPositionTerm(206059, 2.678235, 6283.075850, currentTime);	//2

	l[1] = l[1] + calcPositionTerm(4303, 2.6351, 12566.1517, currentTime);		//3

	l[1] = l[1] + calcPositionTerm(425, 1.59, 3.523, currentTime);				//4

	l[1] = l[1] + calcPositionTerm(119, 5.796, 26.298, currentTime);			//5

	l[1] = l[1] + calcPositionTerm(109, 2.966, 1577.344, currentTime);			//6

	l[1] = l[1] + calcPositionTerm(93, 2.59, 18849.23, currentTime);			//7

	l[1] = l[1] + calcPositionTerm(72, 1.14, 529.96, currentTime);				//8

	l[1] = l[1] + calcPositionTerm(68, 1.87, 398.15, currentTime);				//9

	l[1] = l[1] + calcPositionTerm(67, 4.41, 5507.55, currentTime);				//10



	l[2] = calcPositionTerm(52919, 0, 0, currentTime);							//1

	l[2] = l[2] + calcPositionTerm(8720, 1.0721, 6283.0758, currentTime);		//2

	l[2] = l[2] + calcPositionTerm(309, 0.867, 12566.152, currentTime);			//3

	l[2] = l[2] + calcPositionTerm(27, 0.05, 3.52, currentTime);				//4

	l[2] = l[2] + calcPositionTerm(16, 5.19, 26.3, currentTime);				//5

	l[2] = l[2] + calcPositionTerm(16, 3.68, 155.42, currentTime);				//6

	l[2] = l[2] + calcPositionTerm(10, 0.76, 18849.23, currentTime);			//7

	l[2] = l[2] + calcPositionTerm(9, 2.06, 77713.77, currentTime);				//8

	l[2] = l[2] + calcPositionTerm(7, 0.83, 775.52, currentTime);				//9

	l[2] = l[2] + calcPositionTerm(5, 4.66, 1577.34, currentTime);				//10



	l[3] = calcPositionTerm(289, 5.844, 6283.076, currentTime);					//1

	l[3] = l[3] + calcPositionTerm(35, 0, 0, currentTime);						//2

	l[3] = l[3] + calcPositionTerm(17, 5.49, 12566.15, currentTime);			//3

	l[3] = l[3] + calcPositionTerm(3, 5.2, 155.42, currentTime);				//4

	l[3] = l[3] + calcPositionTerm(1, 4.72, 3.52, currentTime);					//5

	l[3] = l[3] + calcPositionTerm(1, 5.30, 18849.23, currentTime);				//6

	l[3] = l[3] + calcPositionTerm(1, 5.97, 242.73, currentTime);				//7



	l[4] = calcPositionTerm(114, 3.142, 0, currentTime);						//1

	l[4] = l[4] + calcPositionTerm(8, 4.13, 6283.08, currentTime);				//2

	l[4] = l[4] + calcPositionTerm(1, 3.84, 12566.15, currentTime);				//3



	L = calcPositionTerm(1, 3.14, 0, currentTime);								//1



	for (int i = 4; i >= 0; i--)

	{

		L = l[i] + currentTime * L;

	}



	L = L / 100000000;



	return L;

}



long double sun::getHeliocentricLatitude(long double currentTime)

{

	long double B, b[2];



	b[0] = calcPositionTerm(280, 3.199, 84334.662, currentTime);			//1

	b[0] = b[0] + calcPositionTerm(102, 5.422, 5507.553, currentTime);		//2

	b[0] = b[0] + calcPositionTerm(80, 3.88, 5223.69, currentTime);			//3

	b[0] = b[0] + calcPositionTerm(44, 3.7, 2352.87, currentTime);			//4

	b[0] = b[0] + calcPositionTerm(32, 4, 1577.34, currentTime);			//5

	

	b[1] = calcPositionTerm(9, 3.9, 5507.55, currentTime);					//1

	b[1] = b[1] + calcPositionTerm(6, 1.73, 5223.69, currentTime);			//2



	B = b[1];



	for (int i = 1; i >= 0; i--)

	{

		B = b[i] + currentTime * B;

	}



	B = B / 100000000;



	return B;



}



long double sun::getHeliocentricRadiusVector(long double currentTime)

{

	long double R, r[4];



	r[0] = calcPositionTerm(100013989, 0, 0, currentTime);

	r[0] = r[0] + calcPositionTerm(1670700, 3.0984635, 6283.07585, currentTime);

	r[0] = r[0] + calcPositionTerm(13956, 3.05525, 12566.15170, currentTime);

	r[0] = r[0] + calcPositionTerm(3084, 5.1985, 77713.7715, currentTime);

	r[0] = r[0] + calcPositionTerm(1628, 1.1739, 5753.3849, currentTime);

	r[0] = r[0] + calcPositionTerm(1576, 2.8469, 7860.4194, currentTime);

	r[0] = r[0] + calcPositionTerm(925, 5.453, 11506.770, currentTime);

	r[0] = r[0] + calcPositionTerm(542, 4.564, 3930.21, currentTime);

	r[0] = r[0] + calcPositionTerm(472, 3.661, 5884.927, currentTime);

	r[0] = r[0] + calcPositionTerm(346, 0.964, 5507.553, currentTime);



	r[1] = calcPositionTerm(103019, 1.10749, 6283.07585, currentTime);

	r[1] = r[1] + calcPositionTerm(1721, 1.0644, 12566.1517, currentTime);

	r[1] = r[1] + calcPositionTerm(702, 3.142, 0, currentTime);

	r[1] = r[1] + calcPositionTerm(32, 1.02, 18849.23, currentTime);

	r[1] = r[1] + calcPositionTerm(31, 2.84, 5507.55, currentTime);

	r[1] = r[1] + calcPositionTerm(25, 1.32, 5223.69, currentTime);

	r[1] = r[1] + calcPositionTerm(18, 1.42, 1577.34, currentTime);

	r[1] = r[1] + calcPositionTerm(10, 5.91, 10977.08, currentTime);

	r[1] = r[1] + calcPositionTerm(9, 1.42, 6275.96, currentTime);

	r[1] = r[1] + calcPositionTerm(9, 0.27, 5486.78, currentTime);



	r[2] = calcPositionTerm(4359, 5.7846, 6283.07585, currentTime);

	r[2] = r[2] + calcPositionTerm(124, 5.579, 12566.152, currentTime);

	r[2] = r[2] + calcPositionTerm(12, 3.14, 0, currentTime);

	r[2] = r[2] + calcPositionTerm(9, 3.63, 77713.77, currentTime);

	r[2] = r[2] + calcPositionTerm(6, 1.87, 5573.14, currentTime);

	r[2] = r[2] + calcPositionTerm(3, 5.47, 18849.23, currentTime);



	r[3] = calcPositionTerm(145, 4.273, 6238.076, currentTime);

	r[3] = r[3] + calcPositionTerm(7, 3.92, 12566.15, currentTime);



	R = calcPositionTerm(4, 2.56, 6283.08, currentTime);



	for (int i = 3; i >= 0; i--)

	{

		R = r[i] + currentTime * R;

	}



	R = R / 100000000;



	return R;



}



long double sun::calcPositionTerm(long double a, long double b, long double c, long double currentTime)

{

	long double innerValue;

	innerValue = b + (c * currentTime);

	return a* cos(innerValue);

}



long double sun::getObliquity(long double currentTime)

{

	long double U = getJulianTimeIn("tenmillennia", currentTime);





	long double epsilon = U * 0.0006805556;		//U10

	epsilon =  U * (epsilon + 0.001608333);		//U9

	epsilon =  U * (epsilon + 0.007741667);		//U8

	epsilon = -U * (epsilon + 0.001977778);		//U7

	epsilon =  U * (epsilon + 0.01084722);		//U6

	epsilon =  U * (epsilon + 0.06935278);		//U5

	epsilon = -U * (epsilon + 0.01427222);		//U4

	epsilon = -U * (epsilon + 0.5553472);		//U3

	epsilon =  U * (epsilon + 0.0004305556);	//U2

	epsilon = -U * (epsilon + 1.300258);		//U1

	epsilon = epsilon + 23.43929;				//U0



	return epsilon*DEG_IN_RADS;



}



void sun::getSunCoordinates(long double position[4])

{

	long double currentTime = calculateJulianTime();



	long double L = getHeliocentricLongitude(currentTime); // Earth's Heliocentric Longitude (Radians)

	long double B = getHeliocentricLatitude(currentTime); // Earth's Heliocentric Latitude (Radians)

	long double R = getHeliocentricRadiusVector(currentTime); // Earth's Heliocentric Radius Vector (AU)





	long double theta = L + PI; // Sun's Geocentric Longitude (Radians)

	long double beta = -B; // Sun's Geocentric Latitude (Radians)



	//return the spherical coordinates of the sun

	position[0] = theta;

	position[1] = beta;

	position[2] = R;

	position[3] = currentTime;

}



void sun::getSunRectangularCoordinates(long double position[4])

{

	// Load the spherical coordinates of the sun

	long double theta = position[0];

	long double beta = position[1];

	long double R = position[2];

	long double currentTime = position[3];



	// Get the current obliquity of the earth's orbit

	long double epsilon = getObliquity(currentTime);



	// Calculate the Rectangular coordinates of the sun

	long double X = R * cos(beta) *cos(theta);

	long double Y = R * (cos(beta)*sin(theta)*cos(epsilon) - sin(beta)*sin(epsilon));

	long double Z = R * (cos(beta)*sin(theta)*sin(epsilon) + sin(beta)*cos(epsilon));



	// Return the rectangular coordinates of the sun

	position[0] = X;

	position[1] = Y;

	position[2] = Z;

}



void sun::getSunPosition(long double position[4])

{

	// Handle the tracking where the sun is geocentrically

	getSunCoordinates(position);

//	getSunRectangularCoordinates(position);

}



int main()

{
    long double value = 0;
    int currentTimeH = ((time(0)/3600)-4) % 24;
    int currentTimeM = (time(0) / 60) % 60;

    sun test;
    
    long double position[4] = {0,0,0,0};


    for(int i = 0; i < 100; i++)
    {
        test.getSunPosition(position);
        value = sqrt((position[0]*position[0])+(position[1]*position[1])+(position[2]*position[2]));
        cout << value << "\n";
        position[0] = (position[0] / value);
        position[1] = (position[1] / value);
        position[2] = (position[2] / value);
	cout << "x: " << position[0] << "\n"  << "y: " << position[1] << "\n"  << "z: " << position[2] << "\n" << "time: " << currentTimeH << ":" << currentTimeM << "\n";
        
        usleep(1000000);
    }

    

    return 0;

}
