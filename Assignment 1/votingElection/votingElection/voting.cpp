/*
 * Project: votingElection
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [Devender Singh]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include "genlib.h"
#include "simpio.h"  // for getLine
#include "vector.h"  // for Vector
#include "queue.h"   // for queues
#include "random.h"

using namespace std;

void electionResults();
int getInteger();
double getDouble();
double electionInvalid(int voterA, int voterB, int trial, double error);

int main ()
{
	Randomize();
	electionResults();
	return 0;
}

void electionResults() 
{
	cout << "Enter number of voters: ";
	int numVoters = getInteger();
	cout << "Enter percentage spread between candidates: ";
	double spread = getDouble();
	cout << "Enter voting error percentage: ";
	double error = getDouble();
	cout << "Enter number of trials: ";
	int trial = getInteger();
	
	cout << "Voters: " << numVoters << endl;
	cout << "Spread: " << spread << endl;
	cout << "Error: " << error << endl;
	cout << "Trials: " << trial << endl;
	
	int voterA = numVoters * (0.5 + (0.5 * spread));
	int voterB = numVoters * (0.5 - (0.5 * spread));

	double invalid = electionInvalid(voterA, voterB, trial, error);

	cout << endl << "Election invalid percentage is " << invalid << "% after " << trial << " simulations.";
}

int getInteger()
{
	
	int num = GetInteger();
	cout << endl;
	while(true)
	{
		if(num > 0) break; 
		cout << "Input Invalid!!!" << endl;
		cout << "Enter again: ";
		num = GetInteger();
		cout << endl;
	}
	return num;
}

double getDouble()
{
	
	double real = GetReal();
	real = real / 100;
	cout << endl;
	while(true)
	{
		if(real >= 0 && real <= 1) break;
		cout << "Invalid Input!!!" << endl;
		cout << "Enter again: ";
		real = GetReal();
		real = real / 100;
		cout << endl;
	}
	return real;
}

double electionInvalid(int voterA, int voterB, int trial, double error)
{
	int invalid = 0;
	for(int i = 0; i < trial; i++)
	{
		int voterForA = voterA;
		int voterForB = voterB;

		for(int j = 0; j < voterA; j++)
		{
			if(RandomChance(error))
			{
				voterForA--;
				voterForB++;
			}
		}

		for(int k = 0; k < voterB; k++)
		{
			if(RandomChance(error))
			{
				voterForB--;
				voterForA++;
			}
		}

		if(voterForB > voterForA) invalid++;
	}

	double invalidPercent = ((double)invalid * 100) / (double)trial;

	return invalidPercent;
}
