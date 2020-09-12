/*
 * Project: perfectNumber
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * This program finds out the perfect number between 1 tp 10000.
 * using N = (2^(p-1))(2^p -1) where p is a prime for which 2p -1 is a Mersenne prime.
 *
 * Name: Deveneder Singh
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */


#include <iostream>
#include <cmath>
#include "genlib.h"
#include "simpio.h"


bool isPrime(int num)
{
	if(num <= 1)
	{
		return false;
	}

	for(int i = 2; i <= (num / 2); i++)
	{
		if((num % i) == 0)
		{
			return false;
		}
	}

	return true;
}

bool isPerfect(int num)
{	
	if((num % 2) == 0) 
	{
		int sum = 1;
		for(int i = 2; i <= (num / 2); i = i*2)
		{   
 			if((num % i) == 0)
			{
				int quotent = num / i;
				sum = sum + i + quotent;
				if(quotent < (2*i)) break;
			}
		}
		
		if(sum == num)
		{
			 return true;
		} 
	}
	return false;
}

int main()
{
	double perNum;
	int count = 0;
	int choice;
	
	while(true)
	{
		cout << "Enter \"0\" to exit. " << endl 
			 << "Enter \"1\" for List of perfect numbers within 10000." << endl
			 << "Enter \"2\" to Check weather the number is perfect number." << endl << endl 
			 << "Enter your choice : " ;
		choice = GetInteger();
		cout << endl;
		if(choice == 1)
		{
			cout << "List of perfect numbers between 1 to 10000 are : " << endl;
			for(int i = 0; i < 10000; i++) 
			{
				if(isPrime(i))
				{
					count++;
					perNum = pow(2, (double(i) - 1)) * (pow(2, double(i)) - 1);
					if(perNum > 10000)
					{
						break;
					}
					cout << "Perfect Number " << count << " is : " << perNum << endl;
				}
			}			
		}
		else if(choice == 2)
		{
			int number;
			bool status;
			cout << "Enter number to be checked : ";
			number = GetInteger();
			if(isPerfect(number))
			{
				cout << number << " is a Perfect number." << endl; 
			} 
			else 
			{
				cout << number << " is not a Perfect number." << endl;
			}
 		}

		else if(choice == 0)
		{
			cout << "Exit Successfully" <<endl;
			break;
		}
		else 
		{
			cout << "Please Select the given choices." << endl;
		}
		cout << endl;
	}
	
}

