// main.cpp
//
// driver for a simple particle system
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Body.h"
#include "PythonVisualizer.h"

using namespace std;

int main(int argc, char **argv)
{
   ifstream config_file(argv[1]);

   PythonVisualizer *vis = nullptr;
   if (argc == 3)
   {
      vis = new PythonVisualizer;
      vis->setupVisualization();
   }

   vector<Body> bodies;

   string buffer;
   while (getline(config_file, buffer))
   {
      stringstream ss(buffer);
      double mass = 0.0;
      double x = 0.0;
      double y = 0.0;

      ss >> mass >> x >> y;      
      bodies.emplace_back(mass, x, y);
   }

   ofstream data("particle_data.dat");

   for (int i = 0; i < 750; ++i)
   {
      for (auto &particle_a : bodies)
      {
         for (auto &particle_b : bodies)
         {
            if (&particle_a == &particle_b)
            {
               continue;
            }

            particle_a.receive_force_from(particle_b);
         }
      }
      vector<double> visdata;
      for (auto &particle : bodies)
      {
         particle.update(1.0);

         auto p = particle.get_position();
         data << p.first << " " << p.second << " ";

         visdata.push_back(p.first);
         visdata.push_back(p.second);
      }

      if (vis != nullptr)
      {
         vis->visualize(visdata);
      }

      data << endl;
   }
}

