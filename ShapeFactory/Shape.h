// Shape.h
//
// contains the Shape base class

#pragma once

#include <utility>

using namespace std;

class Shape
{
public:
   virtual ~Shape() {}

   virtual double get_perimeter() = 0;

   virtual double get_area() = 0;

   virtual pair<double,double> sample_random_point() = 0;
};

