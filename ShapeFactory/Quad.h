// Quad.h
//
// Provides a definition for a rectangle

#pragma once

#include <utility>
#include "Shape.h"

using namespace std;

class Quad : public Shape
{
public:
   Quad( pair<double,double> bl, double w, double l) :
      rng(),
      dis(0.0, 1.0),
      bottom_left(bl),
      width(w),
      length(l)
   {
      rng.seed(static_cast<unsigned long>(bottom_left.first + bottom_left.second + width + length));
   }

   double get_perimeter()
   {
      return 2.0 * (width + length);
   }

   double get_area()
   {
      return width * length;
   }

   pair<double,double> sample_random_point()
   {
      double x = dis(rng) * width + bottom_left.first;
      double y = dis(rng) * length + bottom_left.second;

      return {x, y};
   }


private:
   mt19937 rng;
   uniform_real_distribution<double> dis;
   pair<double,double> bottom_left;
   double width;
   double length;
};

