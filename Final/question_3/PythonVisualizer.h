// PythonVisualizer.h
//
// This header contains a class implementation for interfacing with Python
// through the C API. In order to use the class, you must first instantiate a
// PythonVisualizer object. Once you create the object, before it can be used,
// you must call the setupVisualization function on that instance. That function
// will do some initial image setup. After the setup, you can then call the
// visualize function, passing in a vector of vectors of ints (your matrix
// representing the Abelian Sandpile). This will in realtime update the plot.
//
// Do note that when running this code, there may be a delay in startup time as
// your program loads the Python virtual machine and runtime environment.
//

#include <Python.h>

#include <cstdlib>
#include <stdexcept>
#include <vector>

class PythonVisualizer
{
public:
   PythonVisualizer(const PythonVisualizer&) = delete;
   void operator=(const PythonVisualizer&) = delete;

   PythonVisualizer() :
      pyModule(nullptr),
      setupHandle(nullptr),
      plotHandle(nullptr)
   {
      setenv("PYTHONHOME", "/usr/lib/x86_64-linux-gnu", 1);
      setenv("PYTHONPATH", "/usr/lib/python2.7/:/usr/lib/python2.7/plat-x86_64-linux-gnu:/usr/lib/python2.7/site-packages/:/usr/lib/python2.7/dist-packages:/usr/lib/python2.7/lib-dynload/:/usr/lib/python2.7/lib-tk/:.", 1);

      Py_Initialize();

      pyModule = PyImport_ImportModule("ParticleVisualizer");
      if (pyModule == nullptr)
      {
         throw std::runtime_error("There were problems loading the ParticleVisualizer module.");
      }

      setupHandle = PyObject_GetAttrString(pyModule, "setup");
      if (setupHandle == nullptr)
      {
         throw std::runtime_error("There were problems loading the ParticleVisualizer.setup method.");
      }

      plotHandle = PyObject_GetAttrString(pyModule, "plot");
      if (pyModule == nullptr)
      {
         throw std::runtime_error("There were problems loading the ParticleVisualizer.plot method.");
      }
   }

   ~PythonVisualizer()
   {
      Py_Finalize();
   }

   void setupVisualization()
   {
      PyObject *pyRetval = PyObject_CallObject(setupHandle, nullptr);
      if (pyRetval == nullptr)
      {
         throw std::runtime_error("Failed to invoke the setupHandle!");
      }

      Py_DECREF(pyRetval);
   }

   void visualize(const std::vector<double> &data)
   {
      PyObject *plotArgs = PyTuple_New(1);
      if (plotArgs == nullptr)
      {
         throw std::runtime_error("Could not create a Python tuple!");
      }

      PyObject *pyData = PyList_New(data.size());
      if (pyData == nullptr)
      {
         throw std::runtime_error("Could not create a Python list!");
      }

      if (PyTuple_SetItem(plotArgs, 0, pyData) != 0)
      {
         throw std::runtime_error("Could not populate the argument tuple with the list!");
      }

      for (size_t idx = 0; idx < data.size(); ++idx)
      {
         PyObject *pyDatum = PyFloat_FromDouble(data[idx]);
         if (pyDatum == nullptr)
         {
            throw std::runtime_error("Could not convert " + std::to_string(data[idx]) + " to a Python float!");
         }

         if (PyList_SetItem(pyData, idx, pyDatum) != 0)
         {
            throw std::runtime_error("Could not set the value for index " + std::to_string(idx) + "!");
         }
      }

      PyObject *pyRetval = PyObject_CallObject(plotHandle, plotArgs);
      if (pyRetval == nullptr)
      {
         throw std::runtime_error("Failed to invoke the plotHandle!");
      }

      Py_DECREF(pyRetval);
      Py_DECREF(pyData);
      Py_DECREF(plotArgs);
   }

private:
   PyObject *pyModule;
   PyObject *setupHandle;
   PyObject *plotHandle;
};

