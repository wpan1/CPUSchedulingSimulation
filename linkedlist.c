#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "process.h"

/*
Create a linked list
*/
node_t* ll_create(){
    // Malloc and testing
	node_t *head = malloc(sizeof(node_t));
	if (head == NULL) {
		fprintf(stderr, "Could not allocate memory for list\n");
		exit(1);
	}
    // Populate values
	head->data = NULL;
	head->next = NULL;
	return head;
}

/*
Checks if data is found in list
*/
int ll_find(node_t *head, void *data){
    // If found, return 1
    while (head != NULL){
        if (head->data == data){
            return 1;
        }
        head = head->next;
    }
    // Otherwise return 0
    return 0;
}

/*
Add data to the end of list
*/
void ll_add_last(node_t *head, void *data){
    node_t *current = head;
    // If list is empty, add to first node
    if (head->data == NULL){
        head->data = data;
        head->next = NULL;
        return;
    }
    // Find the last node
    while (current->next != NULL) {
        current = current->next;
    }
    // Add data the last node
    // Memory allocation and testing
    current->next = malloc(sizeof(node_t));
    if (current->next == NULL) {
		fprintf(stderr, "Could not allocate memory for node\n");
		exit(1);
	}
    current->next->data = data;
    current->next->next = NULL;
}

/*
Add data to the end of list
*/
void ll_add_front(node_t *head, void *data){
    node_t *current = head->next;
    // If list is empty, add to first node
    if (head->data == NULL){
        head->data = data;
        head->next = NULL;
        return;
    }
    // Add data the last node
    // Memory allocation and testing
    head->next = malloc(sizeof(node_t));
    if (head->next == NULL) {
        fprintf(stderr, "Could not allocate memory for node\n");
        exit(1);
    }
    head->next->next = current;
    head->next->data = head->data;
    head->data = data;
}

void ll_push(node_t *head, void *data){
    ll_add_last(head, data);
}

/*
Get the first value in linked list
*/
void *ll_get(node_t *head){
    return head->data;
}

/*
Pop the first value in linked list
*/
void *ll_pop(node_t *head){
    void *returndata = head->data;
	if (head->next == NULL){
        head->data = NULL;
        return returndata;
    }
    node_t *temp = head->next;
	// Copy the data of next node to head
    head->data = temp->data;
    // Remove the link of next node
    head->next = temp->next;
    // Free memory
    free(temp);
    return returndata;
}

/*
Finds and returns the largest process in linked list
*/
void *ll_removelargest_process(node_t *head){
    node_t *temphead = head;
    // Convert to usable type
    process_t *largestprocess = (process_t*)head->data;
    // Find largest process
    while (head != NULL){
        process_t *tempprocess = (process_t*)head->data;
        if (tempprocess->memsize > largestprocess->memsize){
            largestprocess = tempprocess;
        }
        head = head->next;
    }
    // Remove and return largest process
    ll_remove(temphead,largestprocess);
    return largestprocess;
}

/*
Finds and removes data from linked list
*/
int ll_remove(node_t *head, void *data){
    node_t *temp = head, *prev;
    temp = head;
    // If only single node available
    if (head->data == data){
        // Remove node
	    if (head->next == NULL){
	    	head->data = NULL;
	        return 1;
	    }
        // Copy the data of next node to head
        head->data = head->next->data;
        // store address of next node
        temp = head->next;
        // Remove the link of next node
        head->next = head->next->next;
        // free memory
        free(temp);
        return 1;
	}
    // If more than one node available
    while(temp != NULL){
    	if(temp->data == data){
            // Remove corresponding data node
        	if(temp == head){
                // Remove node
        		head = temp->next;
                // free memory
        		free(temp);
        		return 1;
        	}
        	else{
        		prev->next = temp->next;
        		free(temp);
        		return 1;
        	}
   		}
	    else{
	        prev = temp;
	        temp = temp->next;
	    }
    }
    return 0;
}

/*
Print sorted linked list, for process_t nodes
*/
void ll_print_process(node_t *head){
    if(head->data == NULL){
    	return;
    }
    while(head!=NULL){
    	process_t *printProcess = (process_t*)head->data;
    	printf("%d ",printProcess->PID);
    	head=head->next;
    }
    printf("\n");
}

/*
Print sorted linked list, for memory_t nodes
*/
void ll_print_memory(node_t *head){
    if(head->data == NULL){
    	return;
    }
    while(head!=NULL){
    	process_t *printProcess = (process_t*)head->data;
    	printf("%d ",printProcess->memsize);
    	head=head->next;
    }
    printf("\n");
}