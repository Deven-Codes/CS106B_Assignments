/*
 * Project: StockCutting
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include "Vector.h"

int Sum(Vector<int> &set);
int CutStock(Vector<int> &requests, int stockLength);
Vector<int> SubtractSets(Vector<int> set, Vector<int> sub);
void AddToData(int num);
void MakeSubsets(Vector<int> &requests);
void PossibleSubsets(int stockLength);
int FindMaxSubset();


Vector<Vector<int> > subsets;

int main ()
{
	int numStocks;
	int stockLength = 10;
	Vector<int> requests;
	
	requests.add(4);
	requests.add(3);
	requests.add(4);
	requests.add(5);
	requests.add(1);
	requests.add(1);
	requests.add(2);
	requests.add(7);
	requests.add(8);

	cout << "Raw Set: { ";
	for(int i = 0; i < requests.size(); i++) {
		cout << requests[i] << " ";
	}
	cout << "}" << endl;

	MakeSubsets(requests);
	PossibleSubsets(stockLength);
	
	numStocks = CutStock(requests, stockLength);
	cout << "Number: " << numStocks << endl;
	
	return 0;
}

int CutStock(Vector<int> &requests, int stockLength)
{
	 if(!requests.isEmpty()) {
		if(Sum(requests) < stockLength) {
			return 1;
		} else {
			int index = FindMaxSubset();
			Vector<int> newSet = SubtractSets(requests, subsets[index]);
			MakeSubsets(newSet);
			PossibleSubsets(stockLength);
			return (1 + CutStock(newSet, stockLength));
		}
	}
	return 0;
}

void MakeSubsets(Vector<int> &requests)
{
	if(subsets.isEmpty()) {
		for(int i = 0; i < requests.size(); i++) {
			AddToData(requests[i]);
		}
	} else {
		subsets.clear();
		MakeSubsets(requests);
	}
}

void AddToData(int num)
{
	if(!subsets.isEmpty()) {
		int size = subsets.size();
		for(int i = 0; i < size; i++) {
			Vector<int> a;
			a = subsets[i];
			a.add(num);
			subsets.add(a);
		}
	}
	Vector<int> a;
	a.add(num);
	subsets.add(a);
}

void PossibleSubsets(int stockLength)
{
	Vector<Vector<int> > possible;
	for(int i = 0; i < subsets.size(); i++) {
		if(Sum(subsets[i]) <= stockLength) possible.add(subsets[i]);
	}
	subsets.clear();
	subsets = possible;
}



int FindMaxSubset() 
{
	int subsetMaxSum = 0;
	int subsetMaxIndex = -1;

	for(int i = 0; i < subsets.size(); i++) {
		int sum = Sum(subsets[i]);
		if(subsetMaxSum < sum) {	
			subsetMaxSum = sum;
			subsetMaxIndex = i;
		}
	}
	return subsetMaxIndex;
}

int Sum(Vector<int> &set)
{
	int sum = 0; 
	for(int i = 0; i < set.size(); i++) {
		sum += set[i];
	}
	return sum;
}

Vector<int> SubtractSets(Vector<int> set, Vector<int> sub)
{
	for(int i = 0; i < sub.size(); i++) {
		for(int j = 0; j < set.size(); j++) {
			if(sub[i] == set[j]) {
				set.removeAt(j);
				break;
			}
		}
	}
	return set;
}