#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "header.h"

extern int debugMode;

//----------------------------------------------------------------------
//Initializing the strct 
void init(order_Queue **q){
	(*q)->head = NULL;
	(*q)->tail = NULL;
	(*q)->size = 0;
	
	if(debugMode == 1){
		printf("Initializing the struct Queue\n");
	}
}
//----------------------------------------------------------------------
//Deleting the memory allocated to the struct while quitting to avoid memory leaks
void deleteQueue(order_Queue **q){
	order_Node *node;
	node = (*q)->head;

	for(int i = 0;i<(*q)->size;i++){
		(*q)->head = (*q)->head->next;
		free(node->name);
		free(node);
		node = (*q)->head;
	}
}
//----------------------------------------------------------------------
//adding a new item to the Queue
void addToList(order_Queue *s,char *name, int numBurgers,int numSalads,boolean status){
	
		order_Node *temp = malloc (sizeof(order_Node));
		temp->name = name;	
		temp->burgers = numBurgers;
		temp->salads = numSalads;
		temp->status = status;
	
	if(s->tail == NULL && s->head == NULL){
		
		s->head = temp;
		s->tail = temp;
	}
	else{
		s->tail->next = temp;
		s->tail = s->tail->next;
	}
	
	s->size++;
	
}

//----------------------------------------------------------------------
//Checks if an order with specific name exists int the Queue
bool doesNameExist( order_Queue *q, char *name){
	order_Node *ptr;
	ptr = q->head;
	for(int i = 0; i< q->size; i++){
		if(strcmp((ptr->name),(name)) == 0){
			return true;
		}
		ptr = ptr->next;		
	}
	free(ptr);
	return false;
}
//----------------------------------------------------------------------
//Updates the status of call orders to in-restaurant
void updateStatus(order_Queue *q,char *name){
	order_Node *ptr;
	ptr = q->head;
	for(int i = 0; i<q->size; i++){
		if(strcmp((ptr->name),(name)) == 0){	
			if(ptr->status == true){
				printf("The order status has already been set to in-restaurant.\n");

			}
			else{
				ptr->status = true;
				printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);
			}
		}
		if(debugMode == 1){
			printf("Order number %d by \"%s\" with %d burgers and %d salads ", i+1,ptr->name, ptr->burgers,ptr->salads);
			if(ptr->status == true){
				printf("is a in-restaurant order.\n");
			}
			else{
				printf("is an on-call order.\n");
			}
		}
		ptr = ptr->next;
	}
}
//----------------------------------------------------------------------
//retrieves and removes order that are less that the number of burgers and salads prepared
void retrieveAndRemove(order_Queue *q,int numBurgers,int numSalads){

		order_Node *ptr;
		order_Node *prevPtr;
		ptr = q->head;
		prevPtr = NULL;
	
	if(ptr == NULL){
		printf("There are no orders on the list.\n");
		free(ptr);
		return;
	}
	else{
	for(int i =0;i<q->size;i++){
		if(ptr->burgers <= numBurgers && ptr->salads <= numSalads && ptr->status == true){
			q->size --;
			// checks to update head and tail
			if(ptr == q->head){
				q->head = q->head->next;
				printf("Order Number %d by \"%s\" with %d burgers and %d salads is being served and deleted from orders list. \n", 
					   i+1 ,ptr->name, ptr->burgers, ptr->salads);
				free(ptr->name);
				free(ptr);
				break;
			}
			else if(ptr == q->tail){
				q->tail = prevPtr;
				q->tail->next = NULL;
				printf("Order Number %d by \"%s\" with %d burgers and %d salads is being served and deleted from orders list. \n",
					   i+1 ,ptr->name, ptr->burgers, ptr->salads);
				free(ptr->name);
				free(prevPtr->name);
				free(ptr);
				free(prevPtr);
				break;
			}
			else{
				prevPtr->next = ptr->next;
				printf("Order Number %d by \"%s\" with %d burgers and %d salads is being served and deleted from orders list. \n", 
					   i+1 ,ptr->name, ptr->burgers, ptr->salads);
				
				free(prevPtr->name);
				free(ptr->name);
				free(prevPtr);
				free(ptr);
				
				break;	
			}
		}
		else{
		prevPtr = ptr;
		ptr = ptr->next;
		}
		if(debugMode == 1){
			printf("Order number %d by \"%s\" with %d burgers and %d salads ", i+1,ptr->name, ptr->burgers,ptr->salads);
			if(ptr->status == true){
				printf("is a in-restaurant order.\n");
			}
			else{
				printf("is an on-call order.\n");
			}
		}
			if(ptr == NULL){
			printf("There are no in-restaurant orders on the list.\n");
			break;
			}
	}
			
}
	
}
//----------------------------------------------------------------------
// Counts the number of order before a specific order
void countOrdersAhead(order_Queue *q, char *name){
	
	order_Node *node;
	node = q->head;
	int count = 0;
	if(strcmp(q->head->name , name) == 0){
		printf("There are no orders before this order.\n");
	}
	else{
	for(int i = 0;i < q->size-1 ; i++){
		if(strcmp((node->name),(name)) == 0){
			break;
		}
		else{
			count = count + 1;
			node = node->next;
		}
	}
		printf("The number of orders before your order is : %d \n" , count);
	}
}
//----------------------------------------------------------------------
// displays the time of orders preparation before a specific order 
void displayWaitingTime(order_Queue *q,char *name){
	order_Node *node;
	node = q->head;
	int burger_Count = 0;
	int salad_Count = 0;
	int burgerTime = 0;
	int saladTime = 0;
	int totalTime = 0;
	

	for(int j=0; j< q->size; j++){
		if(strcmp((node->name),(name)) == 0){
			break;
		}
		else{

			burger_Count = burger_Count + node->burgers;
			salad_Count = salad_Count + node->salads;
			
		}
		//...........................
		//debugMode
		if(debugMode == 1){
			
			printf("Order number %d by \"%s\" with %d burgers and %d salads ", j+1,node->name, node->burgers,node->salads);
			if(node->status == true){
				printf("is a in-restaurant order.\n");
			}
			else{
				printf("is an on-call order.\n");
			}
		}
		//...........................
		
			node = node->next;
	}

	//...........................
	//debugMode
	if(debugMode ==1){
		printf("There are total number of %d burgers and %d salads\n", burger_Count, salad_Count);
	}
	//...........................
	
	burgerTime = burger_Count * 10;
	saladTime = salad_Count * 5;
	
	//...........................
	//debugMode
	if(debugMode ==1){
		printf("The total time to make %d burgers is %d minutes and %d salads is %d minutes\n",
			   burger_Count, burgerTime, salad_Count,saladTime);
	}
	//...........................
	
	totalTime = burgerTime + saladTime;
	printf( "The total waiting time is: %d minutes\n", totalTime);

}
//----------------------------------------------------------------------
//displays the list of orders before a specific order
void displayOrdersAhead(order_Queue *q,char *name){
	order_Node *node;
	node = q->head;
	
	if(strcmp(q->head->name , name) != 0){

	printf ("Order for \"%s\" is behind the following orders\n\n", name);

		
	for(int j=0;j<q->size;j++){
		if(strcmp((node->name),(name)) == 0){
			break;
		}
			printf("Order Number %d by \"%s\" with %d burgers and %d salads ", j+1 ,node->name, node->burgers, node->salads);
			if(node->status == true){
				printf("is a in restaurant.\n");
			}
			else{
				printf("is an on-call order.\n");
			}
		//...........................
		//debugMode
		if(debugMode == 1){
			
			printf("Order number %d by \"%s\" with %d burgers and %d salads ", j+1,node->name, node->burgers,node->salads);
			if(node->status == true){
				printf("is a in-restaurant order.\n");
			}
			else{
				printf("is an on-call order.\n");
			}
		}
		//...........................
			node = node->next;
	}
	}
	return;
}
//----------------------------------------------------------------------
//displays the orders list
void displayListInformation(order_Queue *q){
	
	order_Node *node;
	node = q->head;
	
	if(q->head == NULL){
		printf("The list is empty.\n");
	}
	else{
	for(int j=0;j<q->size;j++){
		printf("Order Number %d by \"%s\" with %d burgers and %d salads ", j+1 ,node->name, node->burgers, node->salads);
		if(node->status == true){
				printf("in restaurant.\n");
			}
			else{
				printf("on call order.\n");
			}
		node = node->next;
	}
	}
}