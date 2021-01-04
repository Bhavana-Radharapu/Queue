typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

//----------------------------------------------------------------------
typedef struct node{	
	char *name;
	int burgers;
	int salads;
	boolean status;
	struct node *next;
}order_Node;
 

typedef struct queue{
	order_Node *head;
	order_Node *tail;
	int size; 
}order_Queue;

order_Queue orders;
extern int debugMode;
//----------------------------------------------------------------------
void init(order_Queue **q);

void deleteQueue(order_Queue **q);
	
void addToList(order_Queue *s,char *name, int numBurgers,int numSalads,boolean status);

bool doesNameExist( order_Queue *q, char *name);

void updateStatus(order_Queue *q,char *name);

void retrieveAndRemove(order_Queue *q,int numBurgers,int numSalads);

void countOrdersAhead(order_Queue *q, char *name);

void displayWaitingTime(order_Queue *q,char *name);

void displayOrdersAhead(order_Queue *q,char *name);

void displayListInformation(order_Queue *q);

void doAdd (order_Queue **orders);

void doCallAhead (order_Queue **orders);

void doWaiting (order_Queue **orders);

void doRetrieve (order_Queue **orders);

void doList (order_Queue **q);

void doDisplay (order_Queue **q);

void doEstimateTime (order_Queue **q);

//--------------------------------------------------------
void clearToEoln();

int getNextNWSChar ();

int getPosInt ();

char *getName();

void printCommands();