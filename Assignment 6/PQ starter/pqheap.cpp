/*
 * File: pqvector.cpp
 * ------------------
 * This file implements the priority queue class as a vector
 * of integers stored in no particular order.  This makes it easy
 * enqueue new elements, but hard to dequeue the max (have to search for it).
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
 *	Vector<int> heap;
 *  void Swap(int i, int j);
 *	void FindPos();
 *	void FindMax();
 */


PQueue::PQueue()
{
}


PQueue::~PQueue()
{
}


bool PQueue::isEmpty()
{
    return (heap.isEmpty());  
}

int PQueue::size()
{
	return (heap.size());
}

/* Implementation notes: Swap
 * -----------------------------
 * This function will swap elements at indices i and j.
 */
void PQueue::Swap(int i, int j)
{
	int temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
}

/* Implementation notes: FindPos
 * -----------------------------
 * This function will find the position of new added elements in the heap.
 */
void PQueue::FindPos()
{
	int i = heap.size() - 1;
	int j;
	while(i >= 0) {
		j = (i - 1) / 2;
		if(i == j) break;
		if(heap[i] > heap[j]) {
			Swap(i, j);
		} else {
			break;
		}			
		i = j;
	}
}

/* Implementation notes: FindMax
 * -----------------------------
 * This function will find maximum element present in the head after dequeueMax().
 */

void PQueue::FindMax()
{
	int i = 0;
	int j, k, l;
	while(i <= heap.size()) {
		k = (2*i) + 1;
		l = (2*i) + 2;
		if(k >= heap.size()) break;
		
		if(l < heap.size()) {
			j = heap[l] >= heap[k] ? l : k;
		} else {
			j = k;
		}
		
		if(heap[i] < heap[j]) {
			Swap(i, j);
			i = j;
		} else {
			break;
		}
	}
}


/* Implementation notes: enqueue
 * -----------------------------
 * Since we're keeping the vector in no particular order, we just append this
 * new element to the end.  It's the easiest/fastest thing to do.
 */
void PQueue::enqueue(int newValue)
{
	heap.add(newValue);
	if(size() > 1) FindPos();
}


/* Implementation notes: dequeueMax
 * --------------------------------
 * Since we're keeping the vector in no particular order, we have to search to
 * find the largest element.  Once found, we remove it from the vector and
 * return that value.
 */
int PQueue::dequeueMax()
{	
	if(heap.isEmpty()) Error("Error: Dequeue empty heap");

	int val = heap[0];
	heap[0] = heap[heap.size() - 1];
	heap.removeAt(heap.size() - 1);
	FindMax();
	return val;
}
		
int PQueue::bytesUsed() 
{
	return sizeof(*this) + heap.bytesUsed();
}


string PQueue::implementationName()
{
	return "Heap";
}

void PQueue::printDebuggingInfo()
{
	cout << "------------------ START DEBUG INFO ------------------" << endl;
	cout << "Pqueue contains " << heap.size() << " nodes" << endl;
	for (int i = 0; i < heap.size(); i++) 
		cout << heap[i] << " ";
	cout << endl;
	cout << "------------------ END DEBUG INFO ------------------" << endl;
}

