/*Author: Ahmed Almoamenand Emily Buzle
Created: 11/21/21
Modified: 12/6/21
Purpose: To create a priority queue that works with both regular priority and high priority jobs
The processor's goal is to complete each job and accommodate to the highest priority jobs 
for the current time unit.
The simulation will run for a total of 1000 time units.*/

#include <iostream>
#include "Jobs.h"
#include "Data.h"                   
#include "Processors.h"
#include <random>
#include <fstream>
#include <vector>
using namespace std;

void jobStackFunc(jobData& insertJob);

int main()
{
    jobData insertJob;
    jobStackFunc(insertJob);
    insertJob.display();
    dataStructure jobStructure(5920);
    ofstream processLogs("processorLogs.txt");
    float structAvg = 0;
    int qMax = 0;
    long int timerIdle = 1;
    int finJobs = 0;
    int aJobs = 0, bJobs = 0, cJobs = 0, dJobs = 0;
    int waitingTotal = 0;
    float waitingAvg = 0;
    int myCPU;
    int jobNum = 1;
    int jobProcess = 1;
    int interruptions = 0;
    vector<int> runTime(15);
    int rTime = 0;
    int timeToProcess = 0;
    int idleT = 0;

    cout << "\t**Processor Metrics Program**" << endl;
    do {
        cout << "Enter a number of processors to use for this program: ";
        cin >> myCPU;
        if (myCPU <= 0) {
            cout << "Number of processor(s) must be greater than 0! " << endl;
        }
    } while (myCPU < 1);
    ProcessorClass* CPU = new ProcessorClass[myCPU];
    for (int varTime = 1; varTime < 10001; varTime++) {

        for (int i = 0; i < myCPU; i++) {
            if (CPU[i].isComplete() && CPU[i].isFull()) {       //if the job is done 
                jobClass jobTemporary;
                jobTemporary = CPU[i].topStack();               //locates the first job in the stack and clears it

                processLogs << "Time " << varTime << ": Complete Processing Job:" << jobTemporary.jobNumber
                    << ", Job "
                    << jobTemporary.jobCategory << ":" << jobTemporary.categoryNumber << endl;
                finJobs++;

            }
        }
        while (insertJob.returnTopArrival() == varTime) {       //Loop to add to data structure
            jobClass jobTemporary = insertJob.topStack();       //clears the first job in the stack
            jobStructure.plugVal(jobTemporary);                 //inserts the current job

            processLogs << "Time " << varTime << ": Arrival: Overall Job: " << jobNum << ", Job " <<
                jobTemporary.jobCategory
                << ":" << jobTemporary.categoryNumber << ", Processing Time " << jobTemporary.timeProcessed <<
                ";" << endl;

            jobNum++;
            switch (jobTemporary.jobCategory) {
            case 'A':
                aJobs++;
                break;
            case 'B':
                bJobs++;
                break;
            case 'C':
                cJobs++;
                break;
            case 'D':
                dJobs++;
                break;
            }

        }
        //interrupt for type D jobs
        for (int i = 0; i < myCPU; i++) {
            if (CPU[i].isEmpty() || jobStructure.size() == 0) {
                continue;
            }
            jobClass temp = jobStructure.getMin();
            if (temp.jobCategory == 'D') {
                jobClass jobChanged;
                jobClass Djob;
                jobChanged = CPU[i].topStack();
                Djob = jobStructure.takeMinimum();
                CPU[i].shift(Djob);
                jobStructure.plugVal(jobChanged);
                interruptions++;

                processLogs << "Time " << varTime << ":- Job " << jobChanged.jobCategory << ":" <<
                    jobChanged.categoryNumber
                    << " has been interrupted;" << endl;

            }
            else
                break;
        }
        for (int i = 0; i < myCPU; i++) {       //Loop that adds to processor 
            if (jobStructure.isEmpty()) {
                processLogs << "Time " << varTime << ": Queue: Empty; ";

                break;
            }
            else if (CPU[i].isEmpty()) {
                jobClass jobTemporary = jobStructure.takeMinimum();
                waitingTotal = waitingTotal + jobTemporary.waitTime;
                jobTemporary.waitTime = 0;          //Precautionary reset
                CPU[i].shift(jobTemporary);

                processLogs << "Time " << varTime << ": Begin Processing Job: " << jobProcess << ", Job "
                    << jobTemporary.jobCategory << ":" << jobTemporary.categoryNumber << " in CPU " << i + 1 <<
                    endl;
                jobProcess++;
            }
        }


        bool jobCurrent = false;


        for (int i = 0; i < myCPU; i++) {

            if (CPU[i].isEmpty()) {                     //no current jobs
                idleT++;
                processLogs << "CPU " << i + 1 << " Idle Time:" << timerIdle << "; ";

            }
            else {
                jobClass jobTemporary = CPU[i].jobRet();
                CPU[i].jobProcess();
                jobCurrent = true;

                runTime.at(i) = rTime;
                processLogs << "Time " << varTime << ": CPU " << i + 1 << " Run Time:" << runTime.at(i) << "; ";
                timeToProcess++;
                rTime++;

            }
        }

        timerIdle = varTime + 1;
        jobStructure.increaseWait();

        structAvg = structAvg + (jobStructure.size() - structAvg) / varTime;        //computing average queue size
        if (jobStructure.size() > qMax)
            qMax = jobStructure.size();                                             //computing maximum jobs in queue
        processLogs << endl;

        //initial report metrics
        if (varTime == 500) {
            int jobArrivals = aJobs + bJobs + cJobs + dJobs;
            waitingTotal = waitingTotal + jobStructure.waitTimeLeft();
            waitingAvg = waitingTotal / jobArrivals;
            cout << endl << "Initial Metrics:" << endl;
            cout << "Number of processor(s) being used: " << myCPU << endl;
            cout << "Current queue size: " << jobStructure.size() << endl;
            cout << "Average queue size: " << structAvg << endl;
            cout << "Maximum jobs in queue: " << qMax << endl;
            cout << "Total time jobs in queue: " << waitingTotal << " time units." << endl;
            cout << "Average Time in queue: " << waitingAvg << " time units" << endl;
            cout << "Total number of jobs A arrived: " << aJobs << endl;
            cout << "Total number of jobs B arrived: " << bJobs << endl;
            cout << "Total number of jobs C arrived: " << cJobs << endl;
            cout << "Total number of jobs D arrived: " << dJobs << endl;
            cout << "Total jobs completed: " << finJobs << endl;
            cout << "Total time CPU(s) were processing: " << timeToProcess << " time units" << endl;
            cout << "Total time CPU(s) were idle: " << idleT << " time units." << endl;
        }
    }
    //Final Metrics represented 
    int jobArrivals = aJobs + bJobs + cJobs + dJobs;
    waitingTotal = waitingTotal + jobStructure.waitTimeLeft();
    waitingAvg = waitingTotal / jobArrivals;
    cout << endl << "Final Metrics:" << endl;
    cout << "Number of processor(s) being used: " << myCPU << endl;
    cout << "Current queue size: " << jobStructure.size() << endl;
    cout << "Average queue size: " << structAvg << endl;
    cout << "Maximum jobs in queue: " << qMax << endl;
    cout << "Total time jobs in queue: " << waitingTotal << " time units." << endl;
    cout << "Average Time in queue: " << waitingAvg << " time units" << endl;
    cout << "Total number of jobs A arrived: " << aJobs << endl;
    cout << "Total number of jobs B arrived: " << bJobs << endl;
    cout << "Total number of jobs C arrived: " << cJobs << endl;
    cout << "Total number of jobs D arrived: " << dJobs << endl;
    cout << "Total jobs completed: " << finJobs << endl;
    cout << "Total time CPU(s) were processing: " << timeToProcess << " time units" << endl;
    cout << "Total time CPU(s) were idle: " << idleT << " time units." << endl;
    processLogs.close();
    cout << "\nFile 'processorLogs.txt' created to store metrics." << endl;
    system("pause");
    return 0;
}