// Armand Alvarez
// Ryan Burns
// Sean Simonian
// COP 4600 Spring 2018 Programming Assignment 1
// First-Come First-Served

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void firstComeFirstServed(Data* data, FILE* out)
{
	// Can't run if files don't exist
	if (data == NULL || out == NULL)
	{
		return;
	}

	fprintf(out, "%d processes\nUsing First Come First Served\n\n", data->processcount);

	int i, timer = 0;
	Node* tempProcess = NULL;	// temp node used for popping/pushing processes
	Node* activeProcess = NULL;	// node used to control the process currently executing

	// arrivedQueue will hold a node for each process that has arrived and has not yet completed
	Queue* arrivedQueue = createQueue();


	// Initialize main process queue to hold a node for each process in the order that they'll arrive
	Queue* processQueue = createQueue();
	for (i = 0; i < data->processcount; i++)
	{
		pushByArrival(processQueue, createNode(data->pcbArray[i]));
	}


	// 1 iteration per time unit, for the amount of time it's told to run
	for (timer = 0; timer < data->runfor; timer++)
	{
		// At the start of each each timestep, cycle through all processes that arrive at the current time.
		// Pop these process from the main queue and push them to the end of the arrivedQueue
		while (processQueue->head != NULL && processQueue->head->process->arrivalTime == timer)
		{
			tempProcess = pop(processQueue);
			push(arrivedQueue, tempProcess);
			fprintf(out, "Time %d: %s arrived\n", timer, tempProcess->process->name);
			tempProcess = NULL;
		}

		// Check if the active process is complete
		if (activeProcess != NULL && activeProcess->process->burstRemaining == 0)
		{
			fprintf(out, "Time %d: %s finished\n", timer, activeProcess->process->name);
			free(activeProcess);
			activeProcess = NULL;
		}

		// Start a new process
		if (activeProcess == NULL && arrivedQueue->head != NULL)
		{
			activeProcess = pop(arrivedQueue);
			activeProcess->process->waitTime += timer - activeProcess->process->arrivalTime;
			fprintf(out, "Time %d: %s selected (burst %d)\n", timer, activeProcess->process->name, activeProcess->process->burstRemaining);
		}

		// If a process is executed during this timestep, decrement it's remaining burst time
		if (activeProcess != NULL)
		{
			activeProcess->process->burstRemaining--;
		}
		else
		{
			fprintf(out, "Time %d: IDLE\n", timer);
		}
	}


	// Check if a process finished on the last tick
	if (activeProcess != NULL && activeProcess->process->burstRemaining == 0)
	{
		fprintf(out, "Time %d: %s finished\n", timer, activeProcess->process->name);
		free(activeProcess);
		activeProcess = NULL;
	}


	fprintf(out, "Finished at time %d\n\n", timer);
	for (i = 0; i < data->processcount; i++)
	{
		// Calculate turn around time as time spent waiting + time spent executing
		int turnAroundTime = data->pcbArray[i]->waitTime + data->pcbArray[i]->burst;

		fprintf(out, "%s wait %d turnaround %d\n", data->pcbArray[i]->name, data->pcbArray[i]->waitTime, turnAroundTime);
	}

	free(processQueue);
	free(arrivedQueue);
	if (activeProcess != NULL)
        	free(activeProcess);

}
