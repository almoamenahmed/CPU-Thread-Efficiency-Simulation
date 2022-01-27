#pragma once
#include <iostream>
#include "Jobs.h"

class dataStructure // Class created representing job data structure
{
	jobClass* jobArr;
	int capacity;
	int dataSize;
public:
	dataStructure(int capacity);
	void plugVal(jobClass k);
	void swap(jobClass* x, jobClass* y);
	void minSubtree(int); // Converts elements to data structure (heap)
	void increaseWait();
	int size() {
		return dataSize;
	}
	int waitTimeLeft();
	int nodeParent(int i) { // Get node parent's index at i
		return (i - 1) / 2;
	}
	int nodeLeft(int i) { // Get left node index of child at i
		return (2 * i + 1);
	}
	int nodeRight(int i) { // Get right node index of child at i
		return (2 * i + 2);
	}
	jobClass takeMinimum();
	jobClass getMin() { // Minimum value from data struc is returned
		return jobArr[0];
	}
	bool isEmpty();
};