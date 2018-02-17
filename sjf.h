// Armand Alvarez
// Ryan Burns
// Sean Simonian
// COP 4600 Spring 2018 Programming Assignment 1
// Preemptive Shortest Job First

#include <stdio.h>
#include <stdlib.h>

void shortestJobFirst(Data* data, FILE* out)
{
	int i, processCount, timer = 0;
	Node* currentNode = NULL;
	Node* activeNode = NULL;
	Queue* arrivalq;
	Queue* scheduleq;

	if (data == NULL || out == NULL)
		return;

	processCount = data->processcount;

	// Initialize Arrival Queue
	arrivalq = createQueue();
	for (i = 0; i < processCount; i++)
	{
		pushByArrival(arrivalq, createNode(data->pcbArray[i]));
	}

	// Output Header
	fprintf(out, "%d processes\n", processCount);
	fprintf(out, "Using Shortest Job First (Pre)\n\n");

	// Initialize Schedule Queue
	scheduleq = createQueue();

	while (timer < data->runfor)
	{
		// Manage Arrivals
		while (arrivalq->head != NULL && arrivalq->head->process->arrivalTime == timer)
		{
			currentNode = pop(arrivalq);
			fprintf(out, "Time %d: %s arrived\n", timer,currentNode->process->name);
			currentNode->process->lastUse = timer;
			pushByBurstRemaining(scheduleq, currentNode);
			currentNode = NULL;
		}

		// Process Finished
		if (activeNode != NULL && activeNode->process->burstRemaining == 0)
		{
			fprintf(out, "Time %d: %s finished\n", timer, activeNode->process->name);
			free(activeNode);
			activeNode = NULL;
		}

		// We aren't working on anything and there's something to queue.
		if (activeNode == NULL && scheduleq->head != NULL)
		{
			activeNode = pop(scheduleq);
			activeNode->process->waitTime += timer - activeNode->process->lastUse;
			fprintf(out, "Time %d: %s selected (burst %d)\n", timer, activeNode->process->name, activeNode->process->burstRemaining);
		}
		// Check if something new in the queue should pre-empt activeNode
		else if (scheduleq->head != NULL && activeNode->process->burstRemaining > scheduleq->head->process->burstRemaining)
		{
			activeNode->process->lastUse = timer;
			currentNode = activeNode;
			activeNode = pop(scheduleq);
			activeNode->process->waitTime += timer - activeNode->process->lastUse;
			pushByBurstRemaining(scheduleq, currentNode);
			currentNode = NULL;
			fprintf(out, "Time %d: %s selected (burst %d)\n", timer, activeNode->process->name, activeNode->process->burstRemaining);
		}

		// IDLE
		if (activeNode == NULL)
			fprintf(out, "Time %d: IDLE\n", timer);
		// Decrement Burst Remaining of active process.
		else
			activeNode->process->burstRemaining--;

        timer++;

	}

	// Check if a process finished on the last tick
	if (activeNode != NULL && activeNode->process->burstRemaining == 0)
    	{
        	fprintf(out, "Time %d: %s finished\n", timer, activeNode->process->name);
        	free(activeNode);
        	activeNode = NULL;
    	}

	free(scheduleq);
	free(arrivalq);

	fprintf(out, "Finished at time %d\n\n", timer);

	for (i = 0; i < processCount; i++)
	{
		fprintf(out, "%s wait %d turnaround %d\n", data->pcbArray[i]->name, data->pcbArray[i]->waitTime,
           	data->pcbArray[i]->waitTime + data->pcbArray[i]->burst);
	}

}
