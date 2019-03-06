// main.cpp
// Shalmika Sougandini

#include <iostream>
using namespace std;

// implement your function here!
double computeInterest(double principal, double rate, int months)
{
	double totalInterest = 0.0;
	for (int i = 0; i < months; i++)
	{
  		double interest = principal*rate;
		principal += interest;
		totalInterest += interest;

	}
	return totalInterest;
}

int main()
{
   cout <<  "enter a loan amount: " << endl;
   double loan = 0.0;
   cin >> loan;

   cout << "enter a loan term: " << endl;;
   int term = 0;
   cin >> term;

   double interest = computeInterest(loan, 0.025, term);

   cout << "total interest = " << interest << endl;
}

