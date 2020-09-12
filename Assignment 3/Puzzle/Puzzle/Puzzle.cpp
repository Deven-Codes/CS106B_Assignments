/*
 * Project: Puzzle
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include "Vector.h"
#include "random.h"

bool Solvable(int start, Vector<int> &squares);
bool RecSolvable(int start, Vector<int> &squares, int index, Vector<int> indicies);
bool CheckIndex(int index, Vector<int> &indicies);

Vector<int> index;
int count = 0;

int main ()
{
	Randomize();
	Vector<int> squares;
	//for(int i = 0; i < 9; i++) {
	//	squares.add(RandomInteger(1,8));
	//}
	squares.add(3);
	//squares.add(6);
	//squares.add(4);
	squares.add(1);
	//squares.add(3);
	//squares.add(4);
	squares.add(2);
	//squares.add(5);
	squares.add(3);
	squares.add(0);
	
	cout << "Puzzle: { ";
	for(int i = 0; i < squares.size(); i++) {
		cout << squares[i] << " ";
	}
	cout << "}" << endl;

	cout << endl << "Puzzle is solvable: ";
	if(Solvable(squares[0], squares)) {
		cout << "True" << endl;
	} else {
		cout << "False" << endl;
	}
	
	return 0;
}

bool Solvable(int start, Vector<int> &squares)
{
	Vector<int> indicies;
	return RecSolvable(start, squares, 0, indicies);
}	

bool RecSolvable(int start, Vector<int> &squares, int index, Vector<int> indicies) 
{
	//if(count > (squares.size() * squares.size())) return false;
	//if(start == 0) {
	//	return true;
	//}

	if(CheckIndex(index, indicies)) {
		return start == 0;
	} else if(index < squares.size() && index >= 0) {
		indicies.add(index);
		count++;
		return (RecSolvable(squares[index], squares, index + squares[index], indicies)
			|| RecSolvable(squares[index], squares, index - squares[index], indicies));
	} else {
		return false;
	}
}

bool CheckIndex(int index, Vector<int> &indicies)
{
	if(!indicies.isEmpty()) {
		for(int i = 0; i < indicies.size(); i++) {
			if(indicies[i] == index) return true;
		}
	}
	return false;
}