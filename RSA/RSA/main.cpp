#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <gmp.h>
#include <fstream>
#include "rsa.h"


int main(int argc, char **argv)
{
	if (argc != 4)
	{
      cerr << "You must pass in some configuration file!" << endl;
      return 1;
	}
	string sourceFileName(argv[1]);
	string encryptFileName(argv[2]);
	string decryptFileName(argv[3]);
	
	cout << "Source File: " << sourceFileName << endl;
	cout << "Encrypted File: " << encryptFileName << endl;
	cout << "Decryted File: " << decryptFileName << endl;
	
	RSA rsa; 
	
    ifstream fileToEncrypt(sourceFileName);
    ofstream encryptedFile(encryptFileName);
	rsa.encrypt(fileToEncrypt, encryptedFile); 
	
    ifstream fileToDecrypt(encryptFileName);
    ofstream decryptedFile(decryptFileName);
    
	rsa.decrypt(fileToDecrypt, decryptedFile); 
}
