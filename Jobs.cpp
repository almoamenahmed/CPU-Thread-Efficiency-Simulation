#include "Jobs.h"
#include <fstream>
#include <iomanip>
using namespace std;

void jobStackFunc(jobData& insertJob)       //Purpose is to create a stack and add/return elements
{
    jobData jobSubs;
    int jobTracker = 0;
    jobClass aTemp = { 'A', 0,0,0,0,0 };
    jobClass bTemp = { 'B', 0,0,0,0,0 };
    jobClass cTemp = { 'C', 0,0,0,0,0 };
    jobClass dTemp = { 'D', 0,0,0,0,0 };
    for (int varTime = 0; varTime < 10000; varTime++) {
        //Statement to create "A" jobs
        if (varTime % 5 == 0) {
            aTemp.timeArrived = varTime + 4 + rand() % 3;
            if (aTemp.timeArrived < 10000) {
                jobTracker++;
                aTemp.jobNumber = jobTracker;
                aTemp.timeProcessed = 1 + rand() % 5;
                aTemp.categoryNumber++;
                jobSubs.shift(aTemp);
            }
        }
        //Statement to create "B" jobs
        if (varTime % 7 == 0) {
            bTemp.timeArrived = varTime + 6 + rand() % 3;
            if (bTemp.timeArrived < 10000) {
                jobTracker++;
                bTemp.jobNumber = jobTracker;
                bTemp.timeProcessed = 5 + rand() % 5;
                bTemp.categoryNumber++;
                jobSubs.shift(bTemp);
            }
        }
        //Statement to create "C" jobs
        if (varTime % 13 == 0) {
            cTemp.timeArrived = varTime + 8 + rand() % 11;
            if (cTemp.timeArrived < 10000) {
                jobTracker++;
                cTemp.jobNumber = jobTracker;
                cTemp.timeProcessed = 11 + rand() % 5;
                cTemp.categoryNumber++;
                jobSubs.shift(cTemp);
            }
        }
        //Statement to create "D" jobs
        if (varTime % 25 == 0) {
            dTemp.timeArrived = varTime + 20 + rand() % 11;
            if (dTemp.timeArrived < 10000) {
                jobTracker++;
                dTemp.jobNumber = jobTracker;
                dTemp.timeProcessed = 23 + rand() % 5;
                dTemp.categoryNumber++;
                jobSubs.shift(dTemp);
            }
        }
    }
    while (jobSubs.isEmpty() != true) {
        insertJob.shift(jobSubs.topStack());
    }
    insertJob.jobSort(0, insertJob.jobCount() - 1);         //sets the order of the stack
}
jobData::jobData() {}
void jobData::shift(jobClass inputJob)      //Adds a job to stack
{
    jobTracker++;
    jobsGenerated[jobTracker - 1] = inputJob;
}
jobClass jobData::topStack()       //Returns element that’s at the top of the stack after clearing it
{
    jobClass jobTemporary;
    jobTemporary = jobsGenerated[jobTracker - 1];
    jobsGenerated[jobTracker - 1] = { ' ',0, 0,0,0 };
    jobTracker--;
    return jobTemporary;
}
bool jobData::isEmpty()         //Bool to see if stack is empty
{
    if (jobTracker == 0) {
        return true;
    }
    else {
        return false;
    }
}
bool jobData::isFull()          //Bool statement to see if there are 5920 jobs 
{
    if (jobTracker == 5920) {
        return true;
    }
    else {
        return false;
    }
}
void jobData::display()           //Reads the elements in the stack
{

    fstream dataFile("data.txt", ios::out | ios::trunc);
    dataFile.close();
    for (int i = jobTracker - 1; i >= 0; i--) {

        fstream dataFile("data.txt", ios::app);
        dataFile << jobsGenerated[i].jobCategory << setw(6) << jobsGenerated[i].timeArrived << setw(6) <<
            jobsGenerated[i].timeProcessed << endl;
        dataFile.close();

    }
}
int jobData::returnTopArrival()               //Time that the job at top of stack arrived is returned
{
    return jobsGenerated[jobTracker - 1].timeArrived;
}
void jobData::jobSort(int low, int high)        // Function to sort jobs
{
    if (low < high)
    {
        int part = seperateJobs(low, high);
        jobSort(low, part - 1);
        jobSort(part + 1, high);
    }
}
void jobData::swap(jobClass* a, jobClass* b)        // Function to swap a/b
{
    jobClass t = *a;
    *a = *b;
    *b = t;
}
int jobData::seperateJobs(int low, int high)
{
    jobClass pivot = jobsGenerated[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {                                                                   //setting the arrival time in order 
        if (jobsGenerated[j].timeArrived >= pivot.timeArrived)          //if the current low is greater then the current high then swap them
        {
            i++;
            swap(&jobsGenerated[i], &jobsGenerated[j]);
        }
    }
    swap(&jobsGenerated[i + 1], &jobsGenerated[high]);
    return (i + 1);
}
jobData::~jobData() {}