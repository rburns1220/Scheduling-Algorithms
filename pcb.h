// --- Object Definitions

// Process Control Block --- Expand on this object as needed. Just don't forget to change the constructors. 
typedef struct 
{ 
	int arrivalTime;
	int burst;
	int burstRemaining;
	int lastUse; 			// Describes the time unit the program last got kicked off the processor
	int waitTime;
} PCB;


// --- Constructor List --- // 
PCB* createEmptyPCB();
PCB* createPCB(int, int, int, int, int);


// --- Constructor Definitions --- // 

// Empty PCB Constructor 
PCB* createEmptyPCB()
{
	PCB* pcb = malloc(sizeof(PCB));
	return pcb;
}

// Full Input PCB Constructor
PCB* createPCB(int arrivalTime, int burst, int burstRemaining, int lastUse, int waitTime)
{
	PCB* pcb = malloc(sizeof(PCB));

	pcb->arrivalTime = arrivalTime;
	pcb->burst = burst;
	pcb->burstRemaining = burstRemaining;
	pcb->lastUse = lastUse;
	pcb->waitTime = waitTime;

	return pcb;
}
