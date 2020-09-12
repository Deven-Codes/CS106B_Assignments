/*
 * File: pqchunklist.cpp
 * ----------------
 * This file implements the priority queue class as a doubly-linked
 * list of arrays of integers stored in descreasing order.  This makes it easy
 * dequeue the max (it's right in front), but hard to enqueue since we
 * have to search for the proper position to insert the new cell.
 *
 * Julie Zelenski, CS106
 */

#include "pqueue.h"
#include "genlib.h"
#include <iostream>

/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqvector looks like this:
 *
 *	const static int MaxElemPerBlock = 10; 
 *	struct Cell {
 *	  int value[MaxElemPerBlock];
 *	  int numUsed;
 *	  Cell *next;
 *	};
 *	Cell *head;
 *	void Shift();
 *	void Sort(Cell * cur);
 *  void NewChunk(Cell * &cur);
 */

PQueue::PQueue()
{
    head = NULL;
	//MaxElemPerBlock = 10;
}

PQueue::~PQueue()
{
       while (head != NULL) {
    	Cell *next = head->next;
		delete head;
    	head = next;
    }
}

/* Implementation notes: Sort
 * --------------------------
 *	This function will sort the arrays in each chunk.
 */
void PQueue::Sort(Cell *cur)
{
	//for(int i = 0; i < cur->numUsed - 1; i++) {
	//	int maxIndex = i;
	//	for(int j = i+1; j < cur->numUsed; j++) {
	//		if(cur->value[maxIndex] < cur->value[j]) maxIndex = j;
	//	}
	//	int temp = cur->value[i];
	//	cur->value[i] = cur->value[maxIndex];
	//	cur->value[maxIndex] = temp;
	//}
	
	for(int i = 1; i < cur->numUsed; i++) {
		int current = cur->value[i];
		int j;
		for(j = i-1; j >= 0 && cur->value[j] < current; j--) {
			cur->value[j+1] = cur->value[j];
		}
		cur->value[j+1] = current;
	}

}

/* Implementation notes: NewChunk
 * --------------------------
 *	This function will create a new chunk after the " Cell *cur ".
 */
void PQueue::NewChunk(Cell * &cur)
{
	Cell *newCell = new Cell;
	newCell->numUsed = 0;
	for(int i = cur->numUsed / 2; i < cur->numUsed; i++) {
		newCell->value[newCell->numUsed++] = cur->value[i];
	}
	newCell->next = cur->next;
	cur->next = newCell;
	cur->numUsed /= 2; 
}



bool PQueue::isEmpty()
{
    return (head == NULL);  
}

/* Implementation notes: size
 * --------------------------
 * This version doesn't cache the number of entries, so we must traverse the list to count.
 */
int PQueue::size()
{
	int count = 0;
	for(Cell *cur = head; cur != NULL; cur = cur->next) {
		count += cur->numUsed;
	}
	return count;
}


/* Implementation notes: enqueue
 * -----------------------------
 * We have to search to find the proper position, which can be a bit tricky with
 * a singly-linked list.  We walk two parallel pointers, one a step behind the other,
 * until we find the correct position to insert the new cell, which we then splice
 * into place. Note the special case of inserting at the head. Alternatively, this
 * operation could work recursively.
 */
void PQueue::enqueue(int newValue)
{	
	if(head == NULL) {
		head = new Cell;
		head->numUsed = 0;
		head->value[head->numUsed++] = newValue;
		head->next = NULL;
	} else {
		Cell *cur;
		int flag;
		Cell *prev;
		for(cur = head; cur != NULL; cur = cur->next) {
			flag = 0;
			prev = cur;
			if(cur->numUsed == MaxElemPerBlock) NewChunk(cur);
			if(newValue <= cur->value[0]) {
				if(newValue >= cur->value[cur->numUsed - 1]) {
					flag = 1;
					break;
				}
			} else {
				break;
			}
		}
		if(flag == 0) cur = prev;
		cur->value[cur->numUsed++] = newValue;
		Sort(cur);
	}
}

/* Implementation notes: Shift
 * --------------------------
 * This function will shift the elements of array in head chunk after dequeueMax(). 
 */
void PQueue::Shift()
{
	for(int i = 0; i < head->numUsed - 1; i++) {
		head->value[i] = head->value[i+1];
	}
	head->value[head->numUsed - 1] = -1;
	head->numUsed--;
	if(head->numUsed == 0) head = head->next; 
}

/* Implementation notes: dequeueMax
 * --------------------------------
 * The maximum value is kept at the head of the list, so it's easy to find and
 * remove. Note we take care to free the memory for the deleted cell.
 */
int PQueue::dequeueMax()
{
	int val;
	if(head == NULL){
		Error("Dequeue empty queue");
	} else {
		val = head->value[0];
		Shift();
		return val;
	}
}


/* Implementation notes: bytesUsed
 * -------------------------------
 * The space needed is the sum of the object + the size of all the
 * allocated list cells.
 */
int PQueue::bytesUsed()
{
	int total = sizeof(*this);
 	for (Cell *cur = head; cur != NULL; cur = cur->next)
 		total += sizeof(*cur);
 	return total;
}
	

string PQueue::implementationName()
{
	return "sorted chunklist";
}

/*
 * Implementation notes: printDebuggingInfo
 * ----------------------------------------
 * The version for the singly-linked list prints the node structure
 * in order as a debugging aid to keeping track of the cell contents
 * and the pointers between them. It prints each cell in order
 */
void PQueue::printDebuggingInfo()
{
	int count = 0;

	cout << "------------------ START DEBUG INFO ------------------" << endl;
	for (Cell *cur = head; cur != NULL; cur = cur->next) {
       cout << "Chunk #" << count << " (at address " << cur << ") val = " ;
	   for(int i = 0; i < cur->numUsed; i++) {
			cout << cur->value[i] << " ";
		}
       cout << " next = " << cur->next << endl;
       count++;
	}
	cout << "------------------ END DEBUG INFO -------------------" << endl;
}
