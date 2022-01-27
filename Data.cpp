#include "Data.h"
#include <fstream>
#include <iomanip>
using namespace std;

dataStructure::dataStructure(int cap) //Array is given and data struc is created
{
	dataSize = 0;
	capacity = cap;
	jobArr = new jobClass[cap];
}
void dataStructure::plugVal(jobClass k)
{
	if (dataSize == capacity)
	{
		cout << "\nError: Overflow\n" << endl;
		return;
	}
	dataSize++;
	int i = dataSize - 1;
	jobArr[i] = k;
	while (i != 0 && (jobArr[nodeParent(i)].timeProcessed > jobArr[i].timeProcessed || jobArr[i].jobCategory
		== 'D'))
	{
		swap(&jobArr[i], &jobArr[nodeParent(i)]);
		i = nodeParent(i);
	}
	//Statement to ensure swap
	if (i == 0) {
		if (dataSize > 1 && (jobArr[1].timeProcessed < jobArr[0].timeProcessed ||
			jobArr[1].jobCategory == 'D')) {
			swap(&jobArr[1], &jobArr[0]);
		}
		if (dataSize > 2 && (jobArr[2].timeProcessed < jobArr[0].timeProcessed ||
			jobArr[2].jobCategory == 'D')) {
			swap(&jobArr[2], &jobArr[0]);
		}
	}
}
bool dataStructure::isEmpty() //Bool to test if data struct has elements
{
	if (dataSize == 0) {
		return true;
	}
	else {
		return false;
	}
}
void dataStructure::swap(jobClass* x, jobClass* y) //Function to swap elements x/y
{
	jobClass temp = *x;
	*x = *y;
	*y = temp;
}
void dataStructure::increaseWait() //Func to increase wait time
{
	if (dataSize > 0) {
		for (int i = 0; i < dataSize; i++) {
			jobArr[i].waitTime++;
		}
	}
}
int dataStructure::waitTimeLeft() //Calculate and return the sum of all wait times for jobs
{
	int totalWait = 0;
	if (dataSize > 0) {
		for (int i = 0; i < dataSize; i++) {
			totalWait = totalWait + jobArr[i].waitTime;
		}
	}
	return totalWait;
}
jobClass dataStructure::takeMinimum() //Removes the min element from data struct
{
	if (dataSize <= 0) {
		return { ' ',0,0,0,0 };
	}
	if (dataSize == 1)
	{
		dataSize--;
		return jobArr[0];
	}
	jobClass root = jobArr[0];
	jobArr[0] = jobArr[dataSize - 1];
	dataSize--;
	minSubtree(0);
	return root;
}
void dataStructure::minSubtree(int i) //Recursive func to convert elements to heap
{
	int l = nodeLeft(i);
	int r = nodeRight(i);
	int least = i;
	if (l < dataSize && jobArr[l].timeProcessed < jobArr[i].timeProcessed)
		least = l;
	if (r < dataSize && jobArr[r].timeProcessed < jobArr[least].timeProcessed)
		least = r;
	if (least != i)
	{
		swap(&jobArr[i], &jobArr[least]);
		minSubtree(least);
	}
}