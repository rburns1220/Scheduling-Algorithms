// Armand Alvarez
// Ryan Burns
// Sean Simonian
// COP 4600 Spring 2018 Programming Assignment 1
// Round Robin

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>




// todo: make sure implementing data correctly. If referencing something in data, is it data.ref or data->ref?
void rr (Data* data, FILE* fp)
{
	// Print header information.
	fprintf(fp, "%d processes\n", data->processcount);
	fprintf(fp, "Using Round-Robin\n");
	fprintf(fp, "Quantum %d\n\n", data->quantum);


	// Create queue
	Queue* queue = createQueue();

	// Add all the PCBs to the queue, one by one, from the data.h file
	// todo: make sure queue is ordered by arrival time, with earliest arriving processes closes
	//   to the haed.
	int i=0;
	for (i = 0; i < data->processcount; i++)
	{
		// For each process, initialize it using the createNode method in queue.h, then
		//   push it onto the queue.
		// Push by the arrival time.
		pushByArrival(queue, createNode(data->pcbArray[i]));
	}


	// We will also make a queue for processes that have already arrived.
	// This queue should start empty.
	Queue* arrivedQueue = createQueue();


	int currentTime = 0;
	int time = 0;
	int finished = 0;
	Node* tempNode = NULL;
	Node* activeNode = NULL;

	// Now lets start the time loop. We will run from time t=0 to time t=n. We will break out of the
	//   time loop once the queue is empty.

	while (time != data->runfor)
	{
		// First thing, for each timestep, check if any processes have arrived.
		// Our selected node will cycle through the nodes in the main queue until it hits a node
		//   with a timestep greater than the current timestep.
		while (queue->head != NULL && queue->head->process->arrivalTime == time)
		{
			// Add the node to the arrivedQueue.
			tempNode = pop(queue);
			push(arrivedQueue, tempNode);

			// Announce its arrival.
			fprintf(fp, "Time %d: %s arrived\n", time, tempNode->process->name);
			tempNode->process->lastUse = time;
			tempNode = NULL;
		}

		if (activeNode == NULL && arrivedQueue->head != NULL)
        	{
            		activeNode = arrivedQueue->head;
            		fprintf(fp, "Time %d: %s selected (burst %d)\n",time, arrivedQueue->head->process->name, arrivedQueue->head->process->burstRemaining);
            		activeNode->process->waitTime += time - activeNode->process->lastUse;
        	}

		// We now have updated the queue by removing all nodes that already arrived.
		// We also updated the arrivedQueue by adding all nodes that have arrived already.

		// Check if process finished
		// If finished: pop it and select the next process
		if (arrivedQueue->head != NULL && arrivedQueue->head->process->burstRemaining == 0)
		{
			fprintf(fp, "Time %d: %s finished\n", time, arrivedQueue->head->process->name);
			tempNode = pop(arrivedQueue);
			free(tempNode);
			finished = 1;
			if (arrivedQueue->head != NULL)
            		{
                		fprintf(fp, "Time %d: %s selected (burst %d)\n",time, arrivedQueue->head->process->name, arrivedQueue->head->process->burstRemaining);
                		activeNode = arrivedQueue->head;
                		activeNode->process->waitTime += time - activeNode->process->lastUse;
            		}
            		else
            		{
                		activeNode = NULL;
            		}
			currentTime = 0;
		}

		// If a process didn't finish, and we have it the quantum, then switch processes.
		// After switch, run process selected.
		if (finished == 0 && currentTime == data->quantum)
		{
			tempNode = pop(arrivedQueue);
			tempNode->process->lastUse = time;
			push(arrivedQueue, tempNode);
			if (arrivedQueue->head != NULL)
            		{
                		activeNode = arrivedQueue->head;
                		fprintf(fp, "Time %d: %s selected (burst %d)\n",time, arrivedQueue->head->process->name, arrivedQueue->head->process->burstRemaining);
                		activeNode->process->waitTime += time - activeNode->process->lastUse;
            		}
            		else
            		{
               			activeNode = NULL;
            		}

			currentTime = 0;
		}

		// Decrement Head
		// Note we can decrement head regardless of the operations above so long as a head exists.
		// Since if a head exists, we we work one unit of time on it.
		if (arrivedQueue->head != NULL)
       	 	{
            		arrivedQueue->head->process->burstRemaining--;
            		currentTime++;
        	}

        // Check if idle.
		// If idle:
		if (arrivedQueue->head == NULL)
		{
			fprintf(fp, "Time %d: IDLE\n", time);
		}

		finished = 0;
		time++;
    }

    	// Check if a process finished on the last tick
    	if (activeNode != NULL && activeNode->process->burstRemaining == 0)
    	{
        	fprintf(fp, "Time %d: %s finished\n", time, activeNode->process->name);
        	free(activeNode);
        	activeNode = NULL;
    	}

	// The runfor time has been hit
	fprintf(fp, "Finished at time %d\n\n", time);

	for (i = 0; i < data->processcount; i++)
    	{
        	fprintf(fp, "%s wait %d turnaround %d\n", data->pcbArray[i]->name, data->pcbArray[i]->waitTime,
           	data->pcbArray[i]->waitTime + data->pcbArray[i]->burst);
    	}

    free(arrivedQueue);
    free(queue);
}
