//rsa header file
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <gmp.h>
#include <fstream>

#pragma once

using namespace std;

class RSA
{
public: 
	RSA();
	~RSA();
	bool encrypt(istream&, ostream&);
	bool decrypt(istream&, ostream&);
	
private: 
	void initializeGMP();
	void clearGMP();
	int  checkKeys();
	void generateKeys();
	void encrypt(char msg, ostream& fout);
	void decrypt(string str, ostream& fout);
private:
	mpz_t d,e,n;
	mpz_t M,c;
	
}; 

