// Circle.h
//
// Provides a definition for a Circle

#pragma once

#include <cmath>
#include <random>
#include <utility>
#include "Shape.h"

using namespace std;

const double PI = 4.0 * atan(1.0);

class Circle : public Shape
{
public:
   Circle( pair<double,double> c, double r ) :
      rng(),
      dis_theta(0.0, 2.0 * PI),
      dis_radius(0.0, 1.0),
      center(c),
      radius(r)
   {
      rng.seed(static_cast<unsigned long>(center.first + center.second + radius));
   }

   double get_perimeter()
   {
      return 2.0 * PI * radius;
   }

   double get_area()
   {
      return PI * radius * radius;
   }

   pair<double,double> sample_random_point()
   {
      double theta = dis_theta(rng);
      double r = sqrt(dis_radius(rng)) * radius;
      
      double x = r * cos(theta) + center.first;
      double y = r * sin(theta) + center.second;

      return {x, y};
   }

private:
   mt19937 rng;
   uniform_real_distribution<double> dis_theta;
   uniform_real_distribution<double> dis_radius;
   pair<double, double> center;
   double radius;
};
