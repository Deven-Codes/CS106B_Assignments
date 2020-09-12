#ifndef _pqueue_h
#define _pqueue_h

#include "genlib.h"
#include "vector.h"
#include "disallowcopy.h"
//#include "cmpfn.h"


template <typename Type>
class PQueue
{
public:
	PQueue();
	PQueue(int (*func1)(Type &, Type &));
	~PQueue();

	int size();
	bool isEmpty();
	void enqueue(Type val);
	Type dequeueMin();

private:
	DISALLOW_COPYING(PQueue);
	Vector<Type> heap;
	void Swap(int i, int j);
	void FindPos();
	void FindMin();
	int Comparison (Type &a, Type &b);
	int (*func)(Type &, Type &);
};

#include "pqueue.cpp"

#endif