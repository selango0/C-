//ShapeFactory.h

#pragma once 
#include <vector>
#include "Shape.h"

using namespace std;

class ShapeFactory
{
public:
	~ShapeFactory();
	Shape* make_shape(const string &shape_name, const vector<double>&data);
	
private:
	vector<Shape*>shapes;
	
};
