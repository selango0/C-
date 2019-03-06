//ShapeFactory.cpp

#include "Circle.h"
#include "Quad.h"
#include "ShapeFactory.h"

using namespace std;

ShapeFactory::~ShapeFactory()
{
	for(auto& x : shapes)
	{
		delete[] x;
	}
}

Shape* ShapeFactory::make_shape(const string &shape_name, const vector<double>&data)
{
	Shape* shape = nullptr;
	
	if(shape_name == "circle")
	{
		shape = new Circle({data[0], data[1]}, data[2]);
		shapes.push_back(shape);
	}
	else if(shape_name == "quad")
	{
		shape = new Quad({data[0], data[1]}, data[2], data[3]);
		shapes.push_back(shape);
	}
	return shape;
}


