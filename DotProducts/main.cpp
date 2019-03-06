// main.cpp
//

#include <array>
#include <fstream>
#include <iostream>

using namespace std;

static const long N = 100000;

// TODO: your dot product function goes here!
 int dotProduct(array<long, N> a1, array<long, N> a2)
	{
      long ans = 0;
	  for(int i = 0; i < N; i++)
	  {
	  	ans += a1[i]*a2[i];
		}
		return ans;
  }

int main()
{
   // read in data set 1
   ifstream data1("sample_vector_1.dat");
   array<long, N> v1;
   for (long i = 0; i < N; ++i)
   {
      data1 >> v1[i];
   }
   data1.close();

   // read in data set 2
   ifstream data2("sample_vector_2.dat");
   array<long, N> v2;
   for (long i = 0; i < N; ++i)
   {
      data2 >> v2[i];
   }
   data2.close();

   // TODO: call your dot product function below and store the result in the variable dot
   long int dot = dotProduct(v1, v2);

   cout << dot << endl;
}

