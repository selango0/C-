
//
// This program produces an amortization schedule for loans. Running the program
// should result in prompts for loan size, interest rate, and loan term. The 
// result is a new file written out containing the loan payment schedule.
//

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>

using namespace std; 

void createSchedule(double loanAmount, double annualInterestRate, int termLength);

int main()
{
   double loanAmount = 0.0;
   double annualInterestRate = 0.0;
   int termLength = 0.0;

   cout << left;

   cout << setw(36) << "Enter the principal loan amount:" << endl;
   cin >> loanAmount;

   cout << setw(36) << "Enter the annual interest rate:" << endl;
   cin >> annualInterestRate;

   cout << setw(36) <<  "Enter the loan term in years:" << endl;
   cin >> termLength;

   createSchedule(loanAmount, annualInterestRate, termLength);
}

void createSchedule(double loanAmount, double annualInterestRate, int termLength)
{
   double interestRate = annualInterestRate / 1200.0;
   int numberOfPayments = termLength * 12; 
  
   ofstream schedule("schedule.dat");
   schedule.imbue(locale("en_US.UTF-8"));
   schedule << left << showbase;
   schedule << setw(16) << "Payment";
   schedule << setw(16) << "Amount";
   schedule << setw(16) << "Interest";
   schedule << setw(16) << "Principal";
   schedule << setw(16) << "Balance" << endl;

   double paymentAmount = loanAmount * (interestRate + interestRate
      / (pow(1.0 + interestRate, numberOfPayments) - 1.0));

   for (int n = 1; n <= numberOfPayments; ++n)
   {
      double interest = loanAmount * interestRate;
      double principal = paymentAmount - interest;
      loanAmount -= principal;
   
      schedule << setw(16) << n;
      schedule << setw(16) << put_money(paymentAmount * 100.0);
      schedule << setw(16) << put_money(interest * 100.0);
      schedule << setw(16) << put_money(principal * 100.0);
      schedule << setw(16) << put_money(loanAmount * 100.0);
      schedule << endl;
   }
}

