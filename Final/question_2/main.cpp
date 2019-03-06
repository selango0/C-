//
//

#include <cmath>
#include <iostream>

using namespace std;

static const double PI {4.0 * atan(1.0)};

double propogate(double p0, double v0, double a, double t); 

int main()
{
   double angle;
   double speed;
   
   
   cout << "Enter a launch angle (degrees): \n"; 
   cin >> angle;
    
   
   
   cout << "Enter an initial speed (meters/second): \n";
   cin >> speed;
   
   double vx0; 
   double vy0;
   
   vx0 = speed*cos(angle * PI/180.0);
   vy0 = speed*sin(angle * PI/180.0);
   
   double x = 0.0;
   double y = 0.0;
   double t = 0.0; 
   
   while (y >= 0.0)
   {
   		
		x = propogate(0.0, vx0, 0.0, t);
		y = propogate(0.0, vy0, -9.81, t);
		
		cout << x << " " << y << '\n';
		
		
		t += 0.5;
   }
   
}

double propogate(double p0, double v0, double a, double t)
{
	
	return (p0 + v0*t + 0.5*a*pow(t, 2));


}
