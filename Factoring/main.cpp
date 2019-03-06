// main.cpp
//

#include <algorithm> // set_intersection
#include <iostream>
#include <numeric>   // accumulate 
#include <vector>

using namespace std;

vector<int> getFactors(int n)
{
   vector<int> factors = {1};
	
   // TODO:
   // put the code that computes the factors here!
   
   int c = 2; 
   
   while (n != 1)
   {
   		while (n % c == 0)
		{
			n = n / c; 
			factors.push_back(c);
		
		}
		
		++c;
   }

   return factors;
}

int gcd(int p, int q)
{
   vector<int> pFactors = getFactors(p);
   vector<int> qFactors = getFactors(q);

   int gcd = 0;
 
  
   vector<int> intersection;
   set_intersection(begin(pFactors), end(pFactors), begin(qFactors), end(qFactors), back_inserter(intersection));
   gcd = accumulate(begin(intersection), end(intersection), 1, multiplies<int>());
   return gcd;
}

int lcm(int p, int q)
{
   int lcm = 0;

   // TODO:
   // put the code that computes the LCM here!
   lcm = (p*q)/(gcd(p,q));

   return lcm;
}

void printFactors(const vector<int> &factors)
{
   cout << "< ";
   for (auto factor : factors)
   {
      cout << factor << " ";
   }
   cout << ">" << endl;
}

int main()
{
   int p = 0;
   cout << "Enter a positive integer for p:" << endl;
   cin >> p;

   int q = 0;
   cout << "Enter a positive integer for q:" << endl;
   cin >> q;

   if (p < 1 || q < 1)
   {
      cerr << "ERROR: both p and q need to be positive integers! Received: " << p << ", " << q << endl;
      return 1;
   }

   vector<int> pFactors = getFactors(p);
   vector<int> qFactors = getFactors(q);

   printFactors(pFactors);
   printFactors(qFactors);

   cout << "GCD = " << gcd(p, q) << endl;
   cout << "LCM = " << lcm(p, q) << endl;
}

