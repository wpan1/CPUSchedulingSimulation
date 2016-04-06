#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "memoryfree.h"

/*
Create a sorted linked list by maximum
*/
node_sorted_t* sll_create(){
    // Malloc and testing
	node_sorted_t *head = malloc(sizeof(node_sorted_t));
	if (head == NULL) {
		fprintf(stderr, "Could not allocate memory for list\n");
		exit(1);
	}
    // Populate values
	head->sortval = -1;
    head->data= NULL;
	head->next = NULL;
	return head;
}

/*
Add corresponding void data using the sortval to the linked list
*/
void sll_add(node_sorted_t *head, int sortval, void *data){
    // If list is empty, add to the starting node
    if (head->data == NULL){
        head->sortval = sortval;
        head->data = data;
        return;
    }
    // Find where the node to be added can fit
    node_sorted_t *current = head, *temp;
    while (current->next != NULL) {
        if (current->sortval <= sortval){
            break;
        }
        current = current->next;
    }
    temp = current->next;
    // If at end of list
    if (temp == NULL && current->sortval > sortval){
        // Add to end of list
        current->next = malloc(sizeof(node_sorted_t));
        if (current->next == NULL) {
            fprintf(stderr, "Could not allocate memory for node\n");
            exit(1);
        }
        current->next->sortval = sortval;
        current->next->data = data;
        current->next->next = NULL;
        return;
    }
    // Create a node where node should be added
    current->next = malloc(sizeof(node_sorted_t));
    if (current->next == NULL) {
        fprintf(stderr, "Could not allocate memory for node\n");
        exit(1);
    }
    // Add node to list
    current->next->next = temp;
    current->next->sortval = current->sortval;
    current->next->data = current->data;
    current->sortval = sortval;
    current->data = data;
}

/*
Remove node corresponding to the void data
*/
int sll_remove(node_sorted_t *head, void *data){
    node_sorted_t *temp = head, *prev;
    temp = head;
    // If only single node available
    if (head->data == data){
        // Remove node
	    if (head->next == NULL){
	    	head->data = NULL;
	        return 0;
	    }
	    // Copy the data of next node to head
        head->data = head->next->data;
        head->sortval = head->next->sortval;
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
        // Remove corresponding data node
    	if(temp->data == data){
        	if(temp == head){
                // Remove node
        		head = temp->next;
                // Free memory
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
void sll_print_process(node_sorted_t *head){
    if(head==NULL){
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
void sll_print_memory(node_sorted_t *head){
    if(head->data == NULL){
        return;
    }
    while(head!=NULL){
        memory_t *printProcess = (memory_t*)head->data;
        printf("memsize: %d ",printProcess->memsize);
        printf("memaddr: %d ",printProcess->memaddr);
        printf("sortval: %d",head->sortval);
        printf("\n");
        head=head->next;
    }
}