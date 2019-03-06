// Body.h
//

#pragma once

#include <cmath>

using namespace std;

static const double G = 6.673e-11;

class Body
{
public:
   Body(double m, double x, double y) : mass(m), xpos(x), ypos(y),xvel(0.0), yvel(0.0)
   {
   		
		mass = m;
		xpos = x;
		ypos = y;
		
		
	}
	
	void receive_force_from(const Body &other)
	{	double xpos2 = other.xpos;
		double ypos2 = other.ypos;
		double xdiff = xpos - xpos2;
		double ydiff = ypos - ypos2;
		
		double r = sqrt(pow(xdiff,2) + pow(ydiff,2));
		double F = G*(mass/pow(r,2));
		
		double theta = atan2(ydiff, xdiff);
		
		fx += F*cos(theta);
		fy += F*sin(theta);
	}
	
	void update(double dt)
	{
		double xacc = dt/fx;
		double yacc = dt/fy; 
		
		xvel += xacc*dt;
		yvel += yacc*dt; 
		
		xpos += xvel*dt;
		ypos += yvel*dt;
		
		fx = 0.0;
		fy = 0.0; 
	}
	
	pair<double,double> get_position() 
	{
		return pair<double,double> {xpos,ypos};
	}
		
		 

private:
   double mass;
   double xpos;
   double ypos;
   double xvel;
   double yvel;
   double fx = 0.0;
   double fy = 0.0;
};
