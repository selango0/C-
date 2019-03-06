// main.cpp
// Shalmika Sougandini
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
   // 

   // get the low bound
   // TODO

   // get the high bound
   // TODO

   // compute the step size
   // TODO

   // create a vector to house all of the inputs to our functions
   // TODO

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
