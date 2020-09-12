/*
 * Project: Soundex
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: Devender Singh]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */
#include <iostream>
#include "simpio.h"
#include "strutils.h"

int charCode(char ch);
string soundexCode(string name, int skip);

int main ()
{

	while(true) {
		string name = "";
		string result = "";
		cout << "Enter name: ";
		name = GetLine();
		if(name.length() == 0) break;
		name = ConvertToUpperCase(name);
		if(name.length() <= 4) {
			int skip = 0;
			result = soundexCode(name, skip);
		} else {
			int skip = 1;
			result = soundexCode(name, skip);
		}
		if(result.length() < 4) {
			int num = 4 - result.length();
			for(int i = 0; i < num; i++) 
				result += '0';
		}
		
		cout << "Soundex Code: " << result << endl;
	}
	return 0;
}

int charCode(char ch) 
{
	if(ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O'	||
		ch == 'U' || ch == 'H' || ch == 'W' ||ch == 'Y') return 0;

	if(ch == 'B' || ch == 'F' || ch == 'P' || ch == 'V') return 1;

	if(ch == 'C' || ch == 'G' || ch == 'J' || ch == 'K' || 
		ch == 'Q' || ch == 'S' || ch == 'X' || ch == 'Z') return 2;

	if(ch == 'D' || ch == 'T') return 3;

	if(ch == 'M' || ch == 'N') return 4;

	if(ch == 'L') return 5;

	if(ch == 'R') return 6;

	return -1;
}

string soundexCode(string name, int skip)
{
	string result = "";
	int prevNum = -1;
	if(skip == 0) {
		for(int i = 0; i < name.length(); i++) {
			if(i == 0) {
				result += name[i];
			} else {
				int num = charCode(name[i]);
				if(num != -1) result += IntegerToString(num);
			}	
		}
	} else {
		for(int i = 0; i < name.length(); i++) {
			if(i == 0) {
				result += name[i];
			} else {
				int num = charCode(name[i]);
				if(num != -1 && num != 0) {
					if(prevNum != num) result += IntegerToString(num);
					prevNum = num;					 
				}
			}	
			if(result.length() == 4) break;
		}
	}

	return result;
}
