//main.cpp
//Shalmika Sougandini

#include <iostream>
using namespace std;

int main() {

double temperature = 0.0;
char u; 

cout << "Enter a temperature:" << endl;
cin >> temperature; 

cout << "What unit is the temperature in? (c or f)" << endl;
cin >> u;

//if (u == 'c' || u == 'C')
if (u == 'c')
   {
     double F = 0.0;
     F = ((temperature*9.0/5.0)+32);
     cout << temperature << "C = " << F << "F" << endl; 
     }
 
//else if (u == 'f' || u == 'F') 
else if (u == 'f')
    {
      double C = 0.0; 
      C = (temperature - 32.0)*5.0/9.0;
      cout << temperature << "F = " << C << "C" << endl;
      }
else 
    {
       cout << "ERROR" << endl;
       }
       
       
 }
       
