//Chemical.h
//Header for homework 06

#include <string>
#include <iostream>

#pragma once

using namespace std; 

class Chemical {

private:
	string name;
	double mass;
	double specificHeatCapacity;
	double temperature;
	

public: 
	Chemical(string n, double m, double c);
	
	double applyEnergyDifference(double q);
	


	
};

