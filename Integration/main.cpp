// main.cpp
//

#include <cmath>
#include <iostream>
#include <vector>

#include "foobar.h"

using namespace std;

double riemann(const double h, const vector<double> &xs, double(*f)(double));

int main()
{
   // get the number of rectangles to use for integration
   cout << "Enter a number of rectangles to use for integration:" << endl;
   int rect;
   cin >> rect;

   // get the low bound
   cout << "Enter a lower bound for the integral:" << endl;
   double low;
   cin >> low;

   // get the high bound
   cout << "Enter a upper bound for the integral:" << endl;
   double high;
   cin >> high;

   // compute the step size
   double step = (high - low)/rect; 
   

   // create a vector to house all of the inputs to our functions
   vector<double> input;
   for (int i = 0; i < rect; i++)
   {
   		input.push_back(low + i*step + low + step*0.5);
	}

   // populate our inputs
   // TODO

   double sqrtSum = riemann(step, input, std::sqrt);
   double sinSum = riemann(step, input, std::sin);
   double fooSum = riemann(step, input, foo);
   double barSum = riemann(step, input, bar);

   cout << "sqrt sum = " << sqrtSum << endl;
   cout << "sin sum =  " << sinSum << endl;
   cout << "foo sum =  " << fooSum << endl;
   cout << "bar sum =  " << barSum << endl;
 }

double riemann(const double h, const vector<double> &xs, double(*f)(double))
{
   double sum = 0.0;
   for (auto x : xs)
   {
      sum += h * f(x);
   }
   return sum;
}
