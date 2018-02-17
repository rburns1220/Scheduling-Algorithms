// Armand Alvarez
// Ryan Burns
// Sean Simonian
// COP 4600 Spring 2018 Programming Assignment 1


#include <string.h>
#include <stdlib.h>

// --- Object Definitions


// Process Control Block --- Expand on this object as needed. Just don't forget to change the constructors.
typedef struct
{
	char* name;
	int arrivalTime;
	int burst;
	int burstRemaining;
	int lastUse; 			// Describes the time unit the program last got kicked off the processor
	int waitTime;
} PCB;


// --- Constructor List --- //
PCB* createEmptyPCB();
PCB* createPCB(char*, int, int, int, int, int);


// --- Constructor Definitions --- //

// Empty PCB Constructor
PCB* createEmptyPCB()
{
	PCB* pcb = malloc(sizeof(PCB));
	pcb->waitTime = 0;
	return pcb;
}

// Full Input PCB Constructor
PCB* createPCB(char* name, int arrivalTime, int burst, int burstRemaining, int lastUse, int waitTime)
{
	PCB* pcb = malloc(sizeof(PCB));

	pcb->name = malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(pcb->name, name);
	pcb->arrivalTime = arrivalTime;
	pcb->burst = burst;
	pcb->burstRemaining = burstRemaining;
	pcb->lastUse = lastUse;
	pcb->waitTime = waitTime;

	return pcb;
}
