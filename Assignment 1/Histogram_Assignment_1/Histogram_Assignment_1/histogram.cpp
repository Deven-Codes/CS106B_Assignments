/*
 * Project: Histogram_Assignment_1
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: Devender Singh]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include <fstream>
#include "simpio.h"
#include "strutils.h"

const int rangeSize = 10;


void printValues(ifstream &in, int range[]);
void addArray(int num, int range[]);
void histogram(int range[]);


int main ()
{	
	int range[rangeSize] = {0};
	ifstream in;
	string fileName;
	
	while(true) {
		cout << "Enter File Name: ";
		fileName = GetLine();
		in.open(fileName.c_str());
		if(!in.fail()) break;
		in.clear();
		cout << "Operation fails!!!" << endl;
		cout << "Please enter correct file name." << endl;
	}
	
	printValues(in, range);
	in.close();
	histogram(range);
	return 0;
}

void printValues(ifstream &in, int range[])
{
	while(true) {
		string line;
		getline(in, line);
		if(in.fail()) break;
		int num = StringToInteger(line);
		addArray(num, range);
	}
}

void addArray(int num, int range[])
{
	if(0 <= num && num <= 9) range[0] += 1;
	if(10 <= num && num <= 19) range[1] += 1;
	if(20 <= num && num <= 29) range[2] += 1;
	if(30 <= num && num <= 39) range[3] += 1;
	if(40 <= num && num <= 49) range[4] += 1;
	if(50 <= num && num <= 59) range[5] += 1;
	if(60 <= num && num <= 69) range[6] += 1;
	if(70 <= num && num <= 79) range[7] += 1;
	if(80 <= num && num <= 89) range[8] += 1;
	if(90 <= num && num <= 99) range[9] += 1;
}

void histogram(int range[])
{
	cout << endl << "Histogram" << endl;
	cout << "---------";
	for(int i = 0; i < rangeSize; i++) {
		cout << endl;
		if(i == 0) cout << "0-9: ";
		if(i == 1) cout << "10-19: ";
		if(i == 2) cout << "20-29: ";
		if(i == 3) cout << "30-39: ";
		if(i == 4) cout << "40-49: ";
		if(i == 5) cout << "50-59: ";
		if(i == 6) cout << "60-69: ";
		if(i == 7) cout << "70-79: ";
		if(i == 8) cout << "80-89: ";
		if(i == 9) cout << "90-99: ";
		for(int j = 0; j < range[i]; j++) {
			cout << "x";
		}

	}
}
