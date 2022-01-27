#pragma once
#include "Jobs.h"

class ProcessorClass
{
private:
jobClass jobLive;
int jobTracker = 0;
public:
ProcessorClass();
jobClass topStack();
jobClass jobRet() {
return jobLive;
}
void jobProcess();
void shift(jobClass inputJob);
bool isEmpty();
bool isFull();
bool isComplete();
~ProcessorClass();
};