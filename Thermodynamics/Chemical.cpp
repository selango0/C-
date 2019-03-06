//Chemical.cpp

#include <iostream>
#include <string>
#include "Chemical.h"

using namespace std; 

Chemical::Chemical(string n, double m, double c)

	{
		name = n;
		mass = m;
		specificHeatCapacity = c; 
		temperature = 0.0;
	}
	
double Chemical::applyEnergyDifference(double q)
	{
		temperature = temperature + (q/(specificHeatCapacity*mass)); 
		return temperature;
		
	}
	

