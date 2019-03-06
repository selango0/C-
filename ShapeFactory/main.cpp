// main.cpp
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "Circle.h"
#include "Quad.h"
#include "Shape.h"
#include "ShapeFactory.h"

using namespace std;

void read_configuration(const string &file_name, ShapeFactory &factory, vector<Shape*> &shapes);

int main(int argc, char **argv)
{
   if (argc != 2)
   {
      cerr << "You must pass in some configuration file!" << endl;
      return 1;
   }

   ShapeFactory factory;
   vector<Shape*> shapes;
   read_configuration(argv[1], factory, shapes);

   int counter = 1;
   for (auto &s : shapes)
   {
      cout << s->get_perimeter() << " " << s->get_area() << endl;

      string filename = "points_" + to_string(counter) + ".dat";
      ofstream fdata(filename);
      for (int i = 0; i < 100; ++i)
      {
         auto rpoint = s->sample_random_point();
         fdata << rpoint.first << " " << rpoint.second << "\n";
      }
      counter++;
   }
}

void read_configuration(const string &file_name, ShapeFactory &factory, vector<Shape*> &shapes)
{
	using double_buffer = istream_iterator<double>;
	ifstream shape_file(file_name);
	string buffer; 
	
	while(getline(shape_file, buffer))
	{
		istringstream iss(buffer);
		string shape_name; 
		
		iss >> shape_name;
		vector<double> data;
		copy(double_buffer(iss), double_buffer(), back_inserter(data));
		Shape *shape = factory.make_shape(shape_name, data);
		shapes.push_back(shape);
	}
}

