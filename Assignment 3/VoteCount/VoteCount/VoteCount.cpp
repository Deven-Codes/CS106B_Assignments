/*
 * Project: VoteCount
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: Devender Singh]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include "Vector.h"
#include "random.h"

Vector<Vector<int> > subsets;

int CountCriticalVote(Vector<int> &blocks, int blockIndex);
int FindIndex(Vector<int> &blocks);
void Subsets(Vector<int> &votes);
void AddTOSubsets(int vote);
void ShowSubsets();
void CriticalCases(int num, Vector<int> &votes);
Vector<int> CounterPart(Vector<int> &subset, Vector<int> votes);


int main ()
{
	Randomize();
	Vector<int> blocks;
	cout << "Blocks: { ";
	for(int i = 0; i < 5; i++) {
		int n = RandomInteger(1,10);
		blocks.add(n);
		cout << n << " ";
	}
	cout << "}" << endl << endl;;
	
	int garbage = CountCriticalVote(blocks, 0);

	return 0;
}

int CountCriticalVote(Vector<int> &blocks, int blockIndex)
{	
	if(blockIndex < blocks.size()) {
		Vector<int> votes = blocks;
		int num = votes[blockIndex];
		cout << "Block: " << num;
		votes.removeAt(blockIndex);
		
		for(int i = 0; i < votes.size(); i++) {
			AddTOSubsets(votes[i]);
		}
		CriticalCases(num, votes);
		//ShowSubsets();
		subsets.clear();
		CountCriticalVote(blocks, blockIndex + 1);
	}
	return 1;
}


int FindIndex(Vector<int> &blocks)
{
	int index = -1;
	int max = -1;
	for(int i = 0; i < blocks.size(); i++) {
		if(blocks[i] > max) {
			max = blocks[i];
			index = i;
		}
	}
	return index;
}

int Sum(Vector<int> &blocks)
{
	int sum = 0;
	for(int i = 0; i < blocks.size(); i++) {
		sum += blocks[i];
	}
	return sum;
}

void AddTOSubsets(int vote)
{
	if(!subsets.isEmpty()) {
		int size = subsets.size();
		for (int i = 0; i < size; i++) {
			Vector<int> a = subsets[i];
			a.add(vote);
			subsets.add(a);
		}
	}
	Vector<int> a;
	a.add(vote);
	subsets.add(a);
}

void CriticalCases(int num, Vector<int> &votes)
{
	int critical = 0 ;
	for(int i = 0; i < subsets.size(); i++) {
		Vector<int> rest = CounterPart(subsets[i], votes);
		int s = Sum(subsets[i]) - Sum(rest);
		if(s < 0) s = s*(-1);

		if(s < num) critical++;
		
		
	}
	cout << endl << "Critical Cases: " << critical << endl << endl; 
}



void ShowSubsets()
{
	for(int i = 0; i < subsets.size(); i++) {
		cout << "Set " << i << ": {";
		for(int j = 0; j < subsets[i].size(); j++) {
			cout << subsets[i].getAt(j) << " ";
		}
		cout << "}" << endl;
	}
}

Vector<int> CounterPart(Vector<int> &subset, Vector<int> votes)
{
	for(int i = 0; i < subset.size(); i++) {
		for(int j = 0; j < votes.size(); j ++) {
			if(subset[i] == votes[j]) {
				votes.removeAt(j);
				break;
			}
		}
	}

	return votes;
}