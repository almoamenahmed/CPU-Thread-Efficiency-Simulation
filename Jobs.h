#pragma once
#include <iostream>

class jobClass {
public:
	char jobCategory;
	int timeProcessed;
	int categoryNumber;
	int jobNumber;
	int timeArrived;
	int waitTime = 0;
};
class jobData
{
private:
	jobClass jobsGenerated[5920];
	int jobTracker = 0;
public:
	jobData();
	jobClass topStack();
	int returnTopArrival();
	int seperateJobs(int low, int high);
	int jobCount() {
		return jobTracker;
	}
	void shift(jobClass inputJob);
	void jobSort(int low, int high);
	void swap(jobClass* a, jobClass* b);
	void display();
	bool isEmpty();
	bool isFull();
	~jobData();
};
