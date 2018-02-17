// Armand Alvarez
// Ryan Burns
// Sean Simonian
// COP 4600 Spring 2018 Programming Assignment 1

#include <stdio.h>
#include <stdlib.h>
// --- Object Definitions -- //


// --- README --- //
/*
    - Node* createEmptyNode()  :    Creates an node with null attributes
    - Node* createNode(PCB*)   :    Creates a node with the PCB* as the process attribute
    - Queue* createQueue()     :    Create an empty queue
    - Node* pop(Queue* q)      :    Pass the queue you wish to pop from and it will return the node and set the new head.
    - void push(Queue*, Node*) :    Push Node* to the end of the queue.
    - void pushByArrival(Queue* q, Node* node)          : Push Node* based on it's process's arrivalTime. Lower arrivalTime, closer to head.
    - void pushByBurstRemaining(Queue* q, Node* node)   : Push Node* based on process's burstRemaining. Lower burstRemaining, closer to head.
    ****IMPORTANT****
    To actually use a queue, you'll need to initialize a node per process before you can push/pop.
*/

typedef struct Node Node;
struct Node
{
	Node* ahead;
	Node* behind;
	PCB* process;
};

/*
	We create a Queue object so we don't need to keep track of the head and tail ourselves. The
	pop and push methods will handle that if we pass it the queue.
*/
typedef struct
{
	Node* head;
	Node* tail;
} Queue;



// --- Function List --- //
Node* createEmptyNode();
Node* createNode(PCB*);
Queue* createQueue();
Node* pop(Queue*);
void push(Queue*, Node*);
void pushByArrival(Queue* q, Node* node);
void pushByBurstRemaining(Queue* q, Node* node);



// --- Function Definitions --- //
// Empty Node Constructor
Node* createEmptyNode()
{
	Node* returnNode = malloc(sizeof(Node));

	returnNode->ahead = NULL;
	returnNode->behind = NULL;
	returnNode->process = NULL;

	return returnNode;
}

Node* createNode(PCB* process)
{
	Node* returnNode = malloc(sizeof(Node));

	returnNode->ahead = NULL;
	returnNode->behind = NULL;
	returnNode->process = process;

	return returnNode;
}

// Empty Queue Constructor
Queue* createQueue()
{
	Queue* q = malloc(sizeof(Queue));

	q->head = NULL;
	q->tail = NULL;

	return q;
}

// Pop the head of the queue.
Node* pop(Queue* q)
{
	Node* nodeToPop;

	if (q == NULL)
		return NULL;
	if (q->head == NULL)
		return NULL;

	nodeToPop = q->head;
	q->head = nodeToPop->ahead;
	nodeToPop->ahead = NULL;

	if (q->head != NULL)
        	q->head->behind = NULL;

	return nodeToPop;
}

// Push Node to the end of the Queue
void push(Queue* q, Node* node)
{
	// Seg Fault prevention
	if (q == NULL || node == NULL)
		return;

	// Empty Queue
	if (q->head == NULL)
	{
		q->head = node;
		node->ahead = NULL;
		node->behind = NULL;
	}

	// Only one node in Queue (head)
	else if (q->tail == NULL)
	{
	    	q->head->ahead = node;
		q->tail = node;
		node->ahead = NULL;
		node->behind = q->head;
	}

	// Queue has two or more nodes.
	else
	{
	    	q->tail->ahead = node;
        	node->behind = q->tail;
        	q->tail = node;
        	node->ahead = NULL;
	}
}

void pushByArrival(Queue* q, Node* node)
{
	Node* currentNode;

	if (q == NULL || node == NULL)
		return;

	currentNode = q->head;

	while(currentNode != NULL)
	{
		if (node->process->arrivalTime < currentNode->process->arrivalTime)
				break;
        currentNode = currentNode->ahead;
	}

	// Head Insert
	if (q->head == NULL)
	{
		q->head = node;
	}
	// Tail Insert
	else if (currentNode == NULL)
	{
		// Null Tail
		if (q->tail == NULL)
		{
			q->tail = node;
			q->head->ahead = node;
			q->tail->behind = q->head;
		}

		// There is a Tail
		else
		{
			q->tail->ahead = node;
			node->behind = q->tail;
			q->tail = node;
		}
	}
	else
	{
	    if (currentNode == q->head)
            	q->head = node;
		node->behind = currentNode->behind;
		node->ahead = currentNode;
		currentNode->behind = node;
	}

}

void pushByBurstRemaining(Queue* q, Node* node)
{
	Node* currentNode;

	if (q == NULL || node == NULL)
		return;

	currentNode = q->head;

	while(currentNode != NULL)
	{
		if (node->process->burstRemaining < currentNode->process->burstRemaining)
				break;
        currentNode = currentNode->ahead;
	}

	// Head Insert
	if (q->head == NULL)
	{
		q->head = node;
	}
	// Tail Insert
	else if (currentNode == NULL)
	{
		// Null Tail
		if (q->tail == NULL)
		{
			q->tail = node;
			q->head->ahead = node;
			q->tail->behind = q->head;
		}

		// There is a Tail
		else
		{
			q->tail->ahead = node;
			node->behind = q->tail;
			q->tail = node;
		}
	}
	else
	{
	    if (currentNode == q->head)
            	q->head = node;
		node->behind = currentNode->behind;
		node->ahead = currentNode;
		currentNode->behind = node;
	}

}
