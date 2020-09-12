/*
 * Project: Sorting
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: Devender Singh]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include <ctime>
#include "vector.h"
#include "random.h"
#include "mysterysort.h"

void ArrayInitialize(Vector<int> &sortOrder, Vector<int> &randOrder, Vector<int> &reverseOrder, Vector<int> &partialOrder, int limit)
{
	for(int i = 1; i <= limit; i++) {
		sortOrder.add(i);
		randOrder.add(RandomInteger(1,limit));
		reverseOrder.add(limit - (i - 1));
		if(RandomChance(0.5)) {
			partialOrder.add(i);
		} else {
			partialOrder.add(RandomInteger(1,limit));
		}
	}
}

void Mystery1(Vector<int> &sortOrder, Vector<int> &randOrder, Vector<int> &reverseOrder, Vector<int> &partialOrder, int limit)
{
	cout << "\nMystery Sort 1: " << endl;
	clock_t start;
	clock_t end;	

	ArrayInitialize(sortOrder, randOrder, reverseOrder, partialOrder, limit);

	cout << "Sorted Order: " << endl;
	start = clock();
	MysterySort1(sortOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	sortOrder.clear();

	cout << "Random Order: " << endl;
	start = clock();
	MysterySort1(randOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	randOrder.clear();

	cout << "Reverse Order: " << endl;
	start = clock();
	MysterySort1(reverseOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	reverseOrder.clear();

	cout << "Partially Sorted Order: " << endl;
	start = clock();
	MysterySort1(partialOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	partialOrder.clear();
}

void Mystery2(Vector<int> &sortOrder, Vector<int> &randOrder, Vector<int> &reverseOrder, Vector<int> &partialOrder, int limit)
{
	cout << "\nMystery Sort 2: " << endl;
	clock_t start;
	clock_t end;	

	ArrayInitialize(sortOrder, randOrder, reverseOrder, partialOrder, limit);

	cout << "Sorted Order: " << endl;
	start = clock();
	MysterySort2(sortOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	sortOrder.clear();

	cout << "Random Order: " << endl;
	start = clock();
	MysterySort2(randOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	randOrder.clear();

	cout << "Reverse Order: " << endl;
	start = clock();
	MysterySort2(reverseOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	reverseOrder.clear();	
		
	cout << "Partially Sorted Order: " << endl;
	start = clock();
	MysterySort2(partialOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	partialOrder.clear();
}

void Mystery3(Vector<int> &sortOrder, Vector<int> &randOrder, Vector<int> &reverseOrder, Vector<int> &partialOrder, int limit)
{
	cout << "\nMystery Sort 3: " << endl;
	clock_t start;
	clock_t end;	

	ArrayInitialize(sortOrder, randOrder, reverseOrder, partialOrder, limit);

	cout << "Sorted Order: " << endl;
	start = clock();
	MysterySort3(sortOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	sortOrder.clear();

	cout << "Random Order: " << endl;
	start = clock();
	MysterySort3(randOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	randOrder.clear();
	
	cout << "Reverse Order: " << endl;
	start = clock();
	MysterySort3(reverseOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	reverseOrder.clear();	
	
	cout << "Partially Sorted Order: " << endl;
	start = clock();
	MysterySort3(partialOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	partialOrder.clear();
}

void Mystery4(Vector<int> &sortOrder, Vector<int> &randOrder, Vector<int> &reverseOrder, Vector<int> &partialOrder, int limit)
{
	cout << "\nMystery Sort 4: " << endl;
	clock_t start;
	clock_t end;	

	ArrayInitialize(sortOrder, randOrder, reverseOrder, partialOrder, limit);

	cout << "Sorted Order: " << endl;
	start = clock();
	MysterySort4(sortOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	sortOrder.clear();

	cout << "Random Order: " << endl;
	start = clock();
	MysterySort4(randOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	randOrder.clear();
	
	cout << "Reverse Order: " << endl;
	start = clock();
	MysterySort4(reverseOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	reverseOrder.clear();

	cout << "Partially Sorted Order: " << endl;
	start = clock();
	MysterySort4(partialOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	partialOrder.clear();
}

void Mystery5(Vector<int> &sortOrder, Vector<int> &randOrder, Vector<int> &reverseOrder, Vector<int> &partialOrder, int limit)
{
	cout << "\nMystery Sort 5: " << endl;
	clock_t start;
	clock_t end;	

	ArrayInitialize(sortOrder, randOrder, reverseOrder, partialOrder, limit);

	cout << "Sorted Order: " << endl;
	start = clock();
	MysterySort5(sortOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	sortOrder.clear();

	cout << "Random Order: " << endl;
	start = clock();
	MysterySort5(randOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	randOrder.clear();
	
	cout << "Reverse Order: " << endl;
	start = clock();
	MysterySort5(reverseOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	reverseOrder.clear();

	cout << "Partially Sorted Order: " << endl;
	start = clock();
	MysterySort5(partialOrder);
	end = clock();
	cout << difftime(end, start) / CLOCKS_PER_SEC << endl;
	partialOrder.clear();

}

void Print(Vector<int> &v)
{
	cout << "\n{ ";
	for(int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << "}" << endl;
}


int main ()
{
	Randomize();
	Vector<int> sortOrder;
	Vector<int> randOrder;
	Vector<int> reverseOrder;
	Vector<int> partialOrder;
	
	for(int i = 1; i <= 3; i++) {
		int limit = i*10000;
		cout << "\nFor Arrays of length " << limit << ": " << endl;
		Mystery1(sortOrder, randOrder, reverseOrder, partialOrder, limit); // Insertion
		Mystery2(sortOrder, randOrder, reverseOrder, partialOrder, limit); // Quick
		Mystery3(sortOrder, randOrder, reverseOrder, partialOrder, limit); // Merge
		Mystery4(sortOrder, randOrder, reverseOrder, partialOrder, limit); // Selection
		Mystery5(sortOrder, randOrder, reverseOrder, partialOrder, limit); // Bubble
	}


	return 0;
}
