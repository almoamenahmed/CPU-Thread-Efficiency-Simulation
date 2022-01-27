#include "Processors.h"

ProcessorClass::ProcessorClass() {}
void ProcessorClass::shift(jobClass inputJob) //Element gets added to stack
{
if (jobTracker == 0) {
jobLive = inputJob;
jobTracker++;
}
}
jobClass ProcessorClass::topStack() //Element gets removed from stack
{
jobClass jobTemporary = jobLive;
jobLive = {};
jobTracker--;
return jobTemporary;
}
bool ProcessorClass::isEmpty() //Bool to test if stack is empty
{
if (jobTracker == 0)
return true;
else
return false;
}
bool ProcessorClass::isFull() //Bool to test if stack is full
{
if (jobTracker == 1)
return true;
else
return false;
}
void ProcessorClass::jobProcess() { //Works to decrease processing time for active job
jobLive.timeProcessed--;
}
bool ProcessorClass::isComplete() //Bool to test if processing is finished 
{
if (jobLive.timeProcessed == 0)
return true;
else
return false;
}
ProcessorClass::~ProcessorClass() {}