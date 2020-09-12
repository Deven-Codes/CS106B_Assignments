#include <iostream>
#include "pqueue.h"
#include "genlib.h"
#include "cmpfn.h"

template <typename Type>
PQueue<Type>::PQueue()
{
	func = &OperatorCmp;
}

template <typename Type>
PQueue<Type>::PQueue(int (*func1)(Type &, Type &))
{
	func = func1;
}

template <typename Type>
PQueue<Type>::~PQueue()
{
}

template <typename Type>
int PQueue<Type>::Comparison(Type &a, Type &b)
{
	if(a > b) return 1;
	else if(a < b) return -1;
	else return 0;
}

template <typename Type>
bool PQueue<Type>::isEmpty()
{
	return heap.isEmpty();
}

template <typename Type>
void PQueue<Type>::Swap(int i, int j)
{
	Type temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;
}

template <typename Type>
void PQueue<Type>::FindPos()
{
	int i = heap.size() - 1;
	int j;
	while(i >= 0) {
		j = (i - 1) / 2;
		if(i == j) break;
		int result = func(heap[i], heap[j]);
		if( result < 0 ) {
			Swap(i, j);
		} else {
			break;
		}			
		i = j;
	}
}

template <typename Type>
void PQueue<Type>::FindMin()
{
	int i = 0;
	int j, k, l;
	while(i <= heap.size()) {
		k = (2*i) + 1;
		l = (2*i) + 2;
		if(k >= heap.size()) break;
		
		if(l < heap.size()) {
			j = func(heap[k], heap[l]) <= 0 ? k : l;
		} else {
			j = k;
		}
		if(func(heap[i], heap[j]) > 0) {
			Swap(i, j);
			i = j;
		} else {
			break;
		}
	}
}

template <typename Type>
int PQueue<Type>::size()
{
	return (heap.size());
}

template <typename Type>
void PQueue<Type>::enqueue(Type val)
{
	heap.add(val);
	if(size() > 1) FindPos();

}

template <typename Type>
Type PQueue<Type>::dequeueMin()
{
	if(heap.isEmpty()) Error("Error: Dequeue empty heap");

	Type val = heap[0];
	heap[0] = heap[heap.size() - 1];
	heap.removeAt(heap.size() - 1);
	FindMin();
	return val;
}

