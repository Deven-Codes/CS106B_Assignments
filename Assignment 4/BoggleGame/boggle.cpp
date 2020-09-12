/* File: boggle.cpp
 * ----------------
 * Your name here!
 */
 
#include "genlib.h"
#include "simpio.h"
#include <iostream>
#include "extgraph.h"
#include "gboggle.h"
#include "lexicon.h"
#include "random.h"
#include "vector.h"
#include "strutils.h"
#include "sound.h"
#include "grid.h"

string StandardCubes[16]  = 
{"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
 "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};
 
string BigBoggleCubes[25]  = 
{"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM", "AEEGMU", "AEGMNN", "AFIRSY", 
"BJKQXZ", "CCNSTW", "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT", "DHHLOR", 
"DHLNOR", "EIIITT", "EMOTTT", "ENSSSU", "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"};

int boardSize;


struct point{
	int row;
	int col;
};

void GiveInstructions()
{
    cout << endl << "The boggle board is a grid onto which I will randomly distribute " 
	 << "cubes. These 6-sided cubes have letters rather than numbers on the faces, " 
	 << "creating a grid of letters on which you try to form words. You go first, " 
	 << "entering all the words you can find that are formed by tracing adjoining " 
	 << "letters. Two letters adjoin if they are next to each other horizontally, " 
	 << "vertically, or diagonally. A letter can only be used once in the word. Words "
	 << "must be at least 4 letters long and can only be counted once. You score points "
	 << "based on word length: a 4-letter word is worth 1 point, 5-letters earn 2 "
	 << "points, and so on. After your puny brain is exhausted, I, the super computer, "
	 << "will find all the remaining words and double or triple your paltry score." << endl;	
}

static void Welcome()
{
    cout << "Welcome!  You're about to play an intense game of mind-numbing Boggle. " 
	 << "The good news is that you might improve your vocabulary a bit.  The "
	 << "bad news is that you're probably going to lose miserably to this little "
	 << "dictionary-toting hunk of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

void Choice(string &choice)
{
	choice = GetLine();
	while(true) {
		if(choice != "") break;
		cout << "\nPlease enter yes or no.... ";
		choice = GetLine();
	}
}

void GameInitialize()
{
	string choice;

	cout << "\nHit return when you're ready...";
    GetLine();
	 
	cout << "\nDo you want to read Instructions?... ";
	Choice(choice);
	if(choice[0] == 'y' || choice[0] == 'Y') {
		GiveInstructions();
	}

	cout << "\nDo you want sound?... ";
	Choice(choice);
	if(choice[0] == 'y' || choice[0] == 'Y') {
		cout << "Play Sound" << endl;
		SetSoundOn(true);
		PlayNamedSound("yeah right");
	} else {
		SetSoundOn(false);
	}
}

int GameSize() 
{
	string choice; 
	cout << "\nDo you want to play Big Boggle?.... ";
	Choice(choice);
	if(choice[0] == 'y' || choice[0] == 'Y') {
		return 5; // 5x5 boggle size 
	}
	return 4; // 4x4 boggle size
}

point Point(int index) {
	point p;
	p.row = index / boardSize;
	p.col = index % boardSize;

	return p;
}

Vector<int> Subtract(Vector<int> from, Vector<int> &sub)
{	
	
	for(int i = 0; i < sub.size(); i++) {
		for(int j = 0; j < from.size(); j++) {
			if(sub[i] == from[j]) { 
				from.removeAt(j);
				break;
			}
		}
	}

	return from;
}

int Index(int row, int col) {
	return (row * boardSize) + col;
}

void ForcedConfig(string &config, Vector<char> &cubes)
{
	for(int i = 0; i < boardSize*boardSize; i++) {
		point p = Point(i);
		cubes.add(config[i]);
		LabelCube(p.row, p.col, config[i]);
	}
}

void Cubes(string line, int row, int col,  Vector<char> &cubes)
{
	int index = RandomInteger(0, line.size() - 1);
	cubes.add(line[index]);
	LabelCube(row, col, line[index]);
}

void LabelCubes(int size, string arr[], Vector<char> &cubes)
{
	int limit = size*size;
	Vector<int> indices;
	for(int i = 0; i < limit; i++) {
		indices.add(i);
	}
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			int pos = RandomInteger(0, indices.size() - 1);
			int index = indices[pos];
			indices.removeAt(pos);
			Cubes(arr[index],i,j, cubes);
		}
	}
}

Vector<int> Neighbor(int row, int col) {
	Vector<int> ind;
	int r = row - 1;

	for(int i = 0; i < 3; i++) {
		int c = col - 1;
		if(r >= 0 && r < boardSize) { 
			for(int j = 0; j < 3; j++) {
				if(c >= 0 && c < boardSize ){
					if(r != row || c != col) {
						int index = (r * boardSize) + c;
						if(index >= 0 && index < (boardSize * boardSize)) {
							ind.add(index);
						}
					}
				}
				c++;
			}
		}
		r++;
	}

	return ind;
}

void FindWord(string word, Vector<char> &cubes, Vector<int> selected, Vector<string> &allWord, Lexicon &lex)
{
	if(lex.containsPrefix(word)) {
		if(lex.containsWord(word)) {
			allWord.add(word);
		}
		Vector<int> possible;
		Vector<int> neighbors;
		point p = Point(selected[selected.size() - 1]);
		neighbors = Neighbor(p.row, p.col);
		possible = Subtract(neighbors, selected);
		for(int i = 0; i < possible.size(); i++) {
			selected.add(possible[i]);
			word += cubes[possible[i]];
			FindWord(word, cubes, selected, allWord, lex);
			selected.removeAt(selected.size() - 1);
			word = word.substr(0, word.length() - 1);
		}
	}
}

void FindAllWord(Vector<char> &cubes, Vector<string> &allWord, Lexicon &lex)
{
	for(int i = 0; i < cubes.size(); i++) {
		point p;
		p = Point(i);
		string word = "";
		word += cubes[i];
		Vector<int> selected;
		selected.add(i);
		FindWord(word, cubes, selected, allWord, lex);
	}	
}

bool ContainsWord(string &word, Vector<string> &allowedWord) {
	for(int i = 0; i < allowedWord.size(); i++) {
		if(word == allowedWord[i]) return true;
	}
	return false;
}

void Answer( Vector<string> &allWord, Vector<string> &allowedWord) {
	for(int i = 0; i < allWord.size(); i++) {
		string word = allWord[i];
		if(word.length() >= 4) {
			if(allowedWord.isEmpty()) {
				allowedWord.add(word);
			} else {
				if(!ContainsWord(word, allowedWord)) {
					allowedWord.add(word);
				}
			}
		}
	}
}

bool SelectedIndex(string word, string rest, Vector<char> &cubes, Vector<int> &selected, string &result)
{
	if(rest.length() == 0) {
		return word == result;
	} else {
		Vector<int> neighbors;
		Vector<int> possible;
		point p = Point(selected[selected.size() - 1]);
		neighbors = Neighbor(p.row, p.col);
		possible = Subtract(neighbors, selected);
		for(int i = 0; i < possible.size(); i++) {
			if(rest[0] == cubes[possible[i]]) {
				selected.add(possible[i]);
				if(SelectedIndex(word + rest[0], rest.substr(1, rest.length() -1), cubes, selected, result)) {
					return true;
				}
				selected.removeAt(selected.size() - 1);
			}
		}
		return false;
	}

}

void HighlightCubes(Vector<int> &selected)
{
	for(int i = 0; i < selected.size(); i++) {
		point p = Point(selected[i]);
		HighlightCube(p.row, p.col, true);
	}
	Pause(0.30);
	for(int i = 0; i < selected.size(); i++) {
		point p = Point(selected[i]);
		HighlightCube(p.row, p.col, false);
	}
}

void HighlightWord(string &word, Vector<char> &cubes)
{
	Vector<int> selected;
	for(int i = 0; i < cubes.size(); i++) {
		if(!selected.isEmpty()) selected.clear();
		if(word[0] == cubes[i]) {
			selected.add(i);
			string str = "";
			str += word[0];
			if(SelectedIndex(str, word.substr(1, word.length() - 1), cubes, selected, word)) {
				HighlightCubes(selected);
			}
			selected.clear();
		}
	}
}

bool CheckWord(string &word, Vector<char> &cubes, Vector<string> &playerWord, Vector<string> &allowedWord, Lexicon &lex)
{
	if(word.size() < 4) {
		cout << "\nThe word length is too short!";
		cout << "\nEnter Again..." << endl;
		return false;
	}
	if(ContainsWord(word, playerWord)) {
		cout << "\nYou Already Entered that word" << endl;
		return false;
	}
	if(!ContainsWord(word, allowedWord)) {
		cout << "\nYou can't make up a word" << endl;
		return false;
	}
	if(!lex.containsWord(word)) {
		cout << "\nThis word don't exist" << endl;
		return false;
	}
	return true;
}

void PlayerTurn(Vector<char> &cubes, Vector<string> &playerWord, Vector<string> &allowedWord, Lexicon &lex)
{
	string word;
	while(true) {
		cout << "\nEnter word: " ;
		word = GetLine();
		if(word == "") break;
		word = ConvertToUpperCase(word);
		if(CheckWord(word, cubes, playerWord, allowedWord, lex)) {
			HighlightWord( word, cubes);
			playerWord.add(word);
			RecordWordForPlayer(word, Human);
		} 
	}
}

void ComputerTurn(Vector<string> &playerWord, Vector<string> allowedWord) 
{
	for(int i = 0; i < playerWord.size(); i++) {
		for(int j = 0; j < allowedWord.size(); j++) {
			if(playerWord[i] == allowedWord[j]) {
				allowedWord.removeAt(j);
				break;
			}
		}
	}
	for(int i = 0; i < allowedWord.size(); i++) {
		RecordWordForPlayer(allowedWord[i], Computer);
	}

}


int main()
{
	Randomize();
	//SetWindowSize(9, 5);
	//InitGraphics();
	
	/*variables*/
	Lexicon lex("lexicon.dat");
	string choice;
	int size;
	Vector<char> cubes;	
	Vector<string> playerWord;
	Vector<string> allWord;
	Vector<string> allowedWord;

	
	//Welcome();
	//GameInitialize();
	while(true) {
		SetWindowSize(9, 5);
		InitGraphics();
		Welcome();
		GameInitialize();
		size = GameSize();
		boardSize = size;
		DrawBoard(size, size);
		cout << "\nDo you want to force configuration of the board?.... ";
		Choice(choice);
		if(choice[0] == 'n' || choice[0] == 'N') {
			LabelCubes(size, size == 5 ? BigBoggleCubes : StandardCubes, cubes);
		} else {
			string config;
			while(true) {
				cout << "\nPlease Enter string of " << size*size << " characters long." << endl;
				config = GetLine();
				if(config.length() >= size*size) break;
			}
			ForcedConfig(config, cubes);
		}
		
		FindAllWord(cubes, allWord, lex);
		Answer(allWord, allowedWord);
		allWord.clear();
		PlayerTurn(cubes, playerWord, allowedWord, lex);
		ComputerTurn(playerWord, allowedWord);
		cout << "\nDo you want to play again?.... ";
		Choice(choice);
		if(choice[0] == 'n' || choice[0] == 'N') {
			break;
		} else {
			cubes.clear();	
			playerWord.clear();
			allWord.clear();
			allowedWord.clear();
		}
	}

	return 0;
}

