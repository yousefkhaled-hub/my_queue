#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node{
	char *order;
	int amount;
	struct Node *next;
}Node;

typedef struct Queue{
	Node *head;
	Node *tail;
	int size;
}Queue;

Queue *create_Queue(){
	Queue *queue = malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;
	return queue;
}

void inqueue(Queue *queue, char *Order, int Amount){
	Node *new_node = malloc(sizeof(Node));
	new_node->order = strdup(Order);
	new_node->amount = Amount;
	if(queue->head == NULL){
		queue->head = new_node;
		queue->tail = new_node;
	}
	else{
		new_node->next = queue->head;
		queue->head = new_node;
	}

	queue->size++;
}

void inqueuefront(Queue *queue, char *Order, int Amount){
	Node *new_node = malloc(sizeof(Node));
	new_node->order = strdup(Order);
	new_node->amount = Amount;

	if(queue->head == NULL){
		queue->head = new_node;
		queue->tail = new_node;
	}
	else{
		queue->tail->next = new_node;
		queue->tail = new_node;
	}

	queue->size++;
}

void print(Queue *queue){
	if(queue->size == 0){
		printf("Nothing in your menu!\n");
		return;
	}
	
	Node *temp = queue->head;
	while(temp != NULL){
		printf("Order: %s || Amount: %d\n", temp->order, temp->amount);
		temp = temp->next;
	}

	printf("All orders: %d\n", queue->size);
}

void end(Queue *queue){
	if(queue->size == 0){
		printf("Nothing to remove!\n");
		return;
	}

	Node *temp = queue->head;

	while(temp != NULL){
		queue->head = queue->head->next;
		free(temp);
		temp = queue->head;
	}
	queue->size = 0;
	queue->head = NULL;
	queue->tail = NULL;
	printf("All Orders removed!\n");
}

void popfront(Queue *queue){
	if(queue->size == 0){
		printf("Nothing in the menu!\n");
		return;
	}

	printf("FRONT::Order: %s || Amount: %d\n", queue->head->order, queue->head->amount);
}

void popbehind(Queue *queue){
	if(queue->size == 0){
		printf("Nothing in the menu!\n");
		return;
	}

	printf("BEHIND::Order: %s || Amount: %d\n", queue->tail->order, queue->tail->amount);
}

void deletefront(Queue *queue){
	if(queue->size == 0){
		printf("Nothing to delete!\n");
		return;
	}

	Node *temp = queue->head;
	queue->head = queue->head->next;
	free(temp);
	queue->size--;
}

void deletebehind(Queue *queue){
	if(queue->size == 0){
		printf("Nothing to delete!\n");
		return;
	}

	Node *temp = queue->head;
	while(temp->next != queue->tail){
		temp = temp->next;
	}

	queue->tail = temp;
	temp = temp->next;
	free(temp);
	queue->tail->next = NULL;
	queue->size--;
}

int main(){
	Queue *queue = create_Queue();
	inqueue(queue, "Pizza", 20);
	inqueue(queue, "Eqqs", 33);
	inqueue(queue, "Bottle of Water", 122);
	inqueuefront(queue, "Potion", 12);
	
	print(queue);
	
	popfront(queue);
	popbehind(queue);

	deletefront(queue);
	printf("After deleting the front one:\n");
	print(queue);

	deletebehind(queue);
	printf("After deleting from behind one:\n");
	print(queue);

	end(queue);
	free(queue);
	return 0;
}
