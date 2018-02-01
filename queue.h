// --- Object Definitions -- //

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
Node* createNode(Node*, Node*, PCB*);
Queue* createQueue();
Node* pop(Queue*);
void push(Queue*, Node*);



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

// Full Input Node Constructor
Node* createNode(Node* ahead, Node* behind, PCB* process)
{
	Node* returnNode = malloc(sizeof(Node));

	returnNode->ahead = ahead;
	returnNode->behind = behind;
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

	nodeToPop = q->head;
	q->head = nodeToPop->ahead;
	nodeToPop->ahead = NULL;
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
		q->tail = node;
		node->ahead = NULL;
		node->behind = q->head;
	}

	// Queue has two or more nodes.
	else
	{
		node->behind = q->tail;
		node->ahead = NULL;
		q->tail = node;
	}
}


