#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <gmp.h>
#include <fstream>
#include "rsa.h" 

using namespace std;

RSA::RSA()
{
	initializeGMP();
        
    if(!checkKeys())
        generateKeys();
}

RSA::~RSA()
{
    clearGMP();
}

void RSA::initializeGMP()
{
    //Initialize all the GMP integers
    mpz_init(d);
    mpz_init(e);
    mpz_init(n);

    mpz_init(M);
    mpz_init(c);
}


void RSA::clearGMP()
{
    //Clear the GMP integers
    mpz_clear(d);
    mpz_clear(e);
    mpz_clear(n);

    mpz_clear(M);
    mpz_clear(c);
}

void RSA::generateKeys()
{
    /* Create keys:
    *
    *  1. Choose two large distinct primes p and q
    *  2. Calculate n = pq and x = (p-1)(q-1)
    *  3. Select a random integer e (1<e<x) such that gcd(e,x) = 1
    *  4. Calculate the unique d such that ed = 1(mod x)
    *  5. Public key pair:  (e,n)
	*     Private key pair: (d,n)
    */

	mpz_t p,q;
	
    //set p = 509
    mpz_init(p);
    mpz_set_ui(p, 509);

    //set q = 521
    mpz_init(q);
    mpz_set_ui(q, 521);

    /*
    *  Step 2 : Calculate n (=pq) and x =(p-1)(q-1))
    */

    char n_str[1000];

    mpz_t x;

    mpz_init(x);


    //Calculate n

    mpz_mul(n, p, q);

    mpz_get_str(n_str, 10, n);
	cout << "\nn = " << n_str; 
    
	//Calculate x

    mpz_t p_minus_1, q_minus_1;

    mpz_init(p_minus_1);
    mpz_init(q_minus_1);

    mpz_sub_ui(p_minus_1, p, (unsigned long int)1);
    mpz_sub_ui(q_minus_1, q, (unsigned long int)1);

    mpz_mul(x,p_minus_1,q_minus_1);
	
	
    /*
    *  Step 3 : Get small odd integer e such that gcd(e,x) = 1.
    */

    mpz_t gcd;
    mpz_init(gcd);

    unsigned long int e_int = 65537;

    while(true)
    {
        mpz_gcd_ui(gcd, x, e_int);

        if(mpz_cmp_ui(gcd, (unsigned long int)1) == 0)
            break;

        //try the next odd integer
        e_int += 2;
    }

    mpz_set_ui(e, e_int);


    /*
    *  Step 4 : Calculate unique d such that e*d = 1(mod x)
    */
    
	char d_str[1000];

    if(mpz_invert(d,e,x)==0)
    {
        cout <<"\nError: No multiplicative inverse!\n";
        generateKeys();
    }
	
	mpz_get_str(d_str, 10, d);
	cout << endl; 
	
	/*
    *  Step 5: Print the public and private key pairs
    */
	
    cout << "\nPublic Keys (e,n) : " << "\n\n";
    cout << "\nValue of 'e': " << e_int << endl;
    cout << "\nValue of 'n': " << n_str << endl;

    cout << endl; 
	
    cout << "\nPrivate Key: \n\n";
    cout << "\nValue of 'd': " << d_str;

    string publicFile;
    string privateFile;

    publicFile = privateFile = getenv("HOME");   //assign home directory to publicFile, privateFile

    publicFile.append("/.rsapublic");
    privateFile.append("/.rsaprivate");

	ofstream fpublic(publicFile); 
	ofstream fprivate(privateFile);
	
	if((!fpublic) || (!fprivate))
    {
        exit(1);
    }
	
	//Write ~/.rsapublic
	fpublic << e_int << endl << endl; 
	fpublic << n_str << endl << endl; 

    // Write ~/.rsaprivate
	fprivate << d_str << endl << endl;  
    
    fpublic.close();
	fprivate.close();
   
    cout<< "\n\nWrote RSA Key Files ...\n";
    cout << "\nPublic Key File: " << publicFile << endl;
    cout << "\nPrivate Key File: "  << privateFile << endl;
    
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(x);
    mpz_clear(p_minus_1);
    mpz_clear(q_minus_1);
    mpz_clear(gcd);
}


int RSA::checkKeys()
{
    /* This function checks whether the keys exist 
    *  in the file ~/.rsaprivate and ~/.rsapublic
    */

    string publicFile;
    string privateFile;

    publicFile = privateFile = getenv("HOME");

    publicFile.append("/.rsapublic");
    privateFile.append("/.rsaprivate");
	
	ifstream fpublic(publicFile);
    ifstream fprivate(privateFile);
    
    if((!fpublic) || (!fprivate))
    {
       //Key files don't exist
        return 0;
    }

	cout << "\nUsing RSA Key Files: \n\n";
	cout << "\nPublic Key File: " << publicFile;
    cout << "\nPrivate Key File: " << privateFile << endl;

    string d_str;
	string e_str;
	string n_str;
	
    /* Get keys! */
  
	fpublic >> e_str;         //get first string and store in e_str
	
	getline(fpublic, n_str);  //get first line and ignore it
	while(!fpublic.eof())
	{
		getline(fpublic, n_str);
		fpublic >> n_str;    //get second string and store in n_str
	}
	
    fprivate >> d_str;       //get first string from fprivate and store in d_str

    mpz_set_str(d,d_str.c_str(),10);
    mpz_set_str(e,e_str.c_str(),10);
    mpz_set_str(n,n_str.c_str(),10);

    fpublic.close();
    fprivate.close();

    return 1;
}

bool RSA::encrypt(istream& fin, ostream& fout)
{
	cout<<"Encrypting...\n\n";

   
    char chread;        					// character read 
    
    string e_str;
	string n_str;
	
	
    string publicFile = getenv("HOME"); 	// file containing public key
    publicFile.append("/.rsapublic");

	ifstream fpublic_key(publicFile);       // file pointer to public keyfile

    if(!fpublic_key)
    {
        std::cerr << "Error: Could not read.." << publicFile;
        return false;
    }

    getline(fpublic_key, e_str);
    //second line is blank that's why
    getline(fpublic_key, n_str);
    getline(fpublic_key, n_str);
    fpublic_key.close();

    mpz_set_str(e, e_str.c_str(),10);
    mpz_set_str(n, n_str.c_str(),10);

    if(!fin)
    {
        std::cerr << "Error: Could not open file for reading..";
        return false;
    }

    
    if(!fout)
    {
        std::cerr << "Error: Could not open file for writing..";
        return false;
    }

    chread = 'a';

    while (fin >> noskipws >> chread) {				///Don't skip whitespaces
        encrypt(chread, fout);
    }
	return true;
}

void RSA::encrypt(char msg, ostream& fout)
{
  
    int tmp;
    char tmps[4];
    string intmsg = "";

    /* (mpz_t) M is the messsage in gmp integer 
    *  (mpz_t) c is the cipher in gmp integer */

    char ciphertext[1000];

    tmp = (int)msg;

    
    sprintf(tmps,"%03d",tmp);      			//print it in a 3 character wide format
    intmsg.append(tmps);           			//store the formatted tmp in tmps 

    mpz_set_str(M,intmsg.c_str(),10);

    
    mpz_powm(c,M,e,n);						//c = M^e(mod n)

    
    mpz_get_str(ciphertext,10,c);			//get the string representation of the cipher

    
    fout << ciphertext << endl;				//write the ciphertext to the output file
   
}


bool RSA::decrypt(istream& fin, ostream& fout)
{
      
	cout << "Decrypting...\n\n";

    string ciphertext;      // ciphertext 

    /* Here, (mpz_t) c is the cipher in gmp integer  
    *  and (mpz_t) M is the message in gmp integer */

    char decrypted[1000];   //decrypted text
         
 
    if(!fin)
    {
        std::cerr << "Error: Could not open file for reading..";
        return false;
    }

    
    if(!fout)
    {
        std::cerr << "Error: Could not open file for writing..";
        return false;
    }

	while(getline(fin, ciphertext))
    {
 
        mpz_set_str(c,ciphertext.c_str(),10);
        
        mpz_powm(M,c,d,n);				// M = c^d(mod n) 

        mpz_get_str(decrypted,10,M);

        decrypt(decrypted, fout);
    }	
	return true;
}

void RSA::decrypt(string str, ostream& fout)
{
    /* This function shows the decrypted integer 
    *  message as a text string 
    */

    unsigned int i=0;
    int tmpnum;
    string strmod = "";

    /* make the message length an integral multiple
    *  of 3 by adding zeroes to the left if needed
    */

    if(str.size()%3 == 1)
    {
        strmod = "00";
    }
    else if(str.size()%3 == 2)
    {
        strmod = "0";
    }
    
    strmod.append(str);

    while(i<=strmod.size()-3)
    {
        tmpnum = strmod[i] - 48;
        tmpnum = 10*tmpnum + (strmod[i+1] - 48);
        tmpnum = 10*tmpnum + (strmod[i+2] - 48);

        i += 3;

        fout << (char)tmpnum;
    }
}
