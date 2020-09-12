/*
 * Project: CellPhoneMindReading
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include "lexicon.h"
#include "Vector.h"
#include "simpio.h"

using namespace std;

void ListMnemonic(string str);
void RecursiveMnemonic(string prefix, string rest);
void ShowMnemonic();
void printWords(string prefix);
string DigitLetters(char ch);


Vector<string> words;
Vector<string> prefixes;
Lexicon lex("lexicon.dat");

int main ()
{	
	string str;
	cout << "Enter Numbers: ";
	str = GetLine();
	ListMnemonic(str);
	ShowMnemonic();
	return 0;
}


void ListMnemonic(string str)
{
	RecursiveMnemonic("", str);
}

void RecursiveMnemonic(string prefix, string rest)
{
	if(rest.length() == 0) {
		if(lex.containsPrefix(prefix)) prefixes.add(prefix);
	} else {
		string option = DigitLetters(rest[0]);
		for(int i = 0; i < option.length(); i++) {
			RecursiveMnemonic(prefix + option[i], rest.substr(1));
		}
	}

}

void ShowMnemonic()
{
	for(int i = 0; i < prefixes.size(); i++) {
		printWords(prefixes[i]);		
	}
}

void printWords(string prefix)
{	
	string alphabets = "abcdefghijklmnopqrstuvwxyz";
	if(lex.containsWord(prefix)) cout << prefix << endl;
	
	if(lex.containsPrefix(prefix)) {
		for(int i = 0; i < alphabets.length(); i++) {
			printWords(prefix + alphabets[i]);
		}
	}

}

string DigitLetters(char ch)
{
	switch(ch) {
		case '0': return ("0");
		case '1': return ("1");
		case '2': return ("abc");
		case '3': return ("def");
		case '4': return ("ghi");
		case '5': return ("jkl");
		case '6': return ("mno");
		case '7': return ("pqrs");
		case '8': return ("tuv");
		case '9': return ("wxyz");
		default	: Error("Illegal Digit");	
	}
}