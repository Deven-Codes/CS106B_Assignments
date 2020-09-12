/*
 * Project: 12StepProgram
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: Devender Singh]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include "simpio.h"

int CountWays(int numStairs);
const int smallStride = 1;
const int largeStride = 2;
int count = 0;

int main ()
{
	int numStairs;
	int ways;
	cout << "Enter Number of Stairs: ";
	numStairs = GetInteger();
	ways = CountWays(numStairs);
	cout << "Ways: " << ways << endl;
	return 0;
}

int CountWays(int numStairs)
{	
	int count = 0;
	if(numStairs == 0) {
		return 1;
	} else if(numStairs < 0){
		return 0;
	}
	count = count + CountWays(numStairs - smallStride) + CountWays(numStairs - largeStride);	
	return count;
}