#include <stdio.h>
#include <stdlib.h>
#include "memoryfree.h"

/*
Create a sorted linked list to store free memory
addresses and their corresponding size
*/
node_sorted_t *memfree_create(int memsize){
	// Create list
	node_sorted_t* memfree = sll_create();
	// Set memory address as 0 and size and memsize
	memory_t *nodeadd = memnode_create(memsize,0);
	memnode_add(memfree, nodeadd);
	return memfree;
}

/*
Create a memory structure
*/
memory_t *memnode_create(int memsize, int memaddr){
	// Allocate memory, and check
	memory_t *memnode = (memory_t*)malloc(sizeof(memory_t));
	if (memnode == NULL){
		fprintf(stderr, "Could not allocate memory for list\n");
		exit(1);
	}
	// Populate corresponding values
	memnode->memsize = memsize;
	memnode->memaddr = memaddr;
	return memnode;
}

/*
Add a memory node to list
*/
void memnode_add(node_sorted_t *head, void *data){
	// Add to list
	memory_t *memdata = (memory_t*)data;
	// Edge cases where memory size is 0
	if (memdata->memsize == 0){
		// Do nothing
		return;
	}
	sll_add(head, memdata->memaddr, data);
	// Merge nodes that are adjacent
	mergeholes(head);
}

/*
Merge adjacent memory address nodes, and remove empty
memory nodes
*/
void mergeholes(node_sorted_t *head){
	// If singular memory node, do nothing
	if (head->next == NULL){
		return;
	}
	// Find adjacent nodes
	node_sorted_t *curr = head->next, *prev = head;
	while(curr != NULL){
		// If memory overlaps, add memory size to the node with
		// higher memory address
		memory_t *prevdata = (memory_t*)prev->data;
		memory_t *currdata = (memory_t*)curr->data;
		if (prevdata->memaddr == currdata->memsize + currdata->memaddr){
			node_sorted_t *temp = curr;
			prevdata->memsize += currdata->memsize;
			prevdata->memaddr = currdata->memaddr;
			prev->sortval = curr->sortval;
			prev->next = curr->next;
			free(temp);
			curr = prev->next;
		}
		else{
			prev = curr;
			curr = curr->next;
		}
	}
}

/*
Remove node from free memory
*/
void memnode_remove(node_sorted_t *head, void *data){
	// Convert data to usable type
	node_sorted_t *curr = head, *prev = head;
	memory_t *memdata = (memory_t*)data;
	// Edge cases where memory size is 0
	if (memdata->memsize == 0){
		// Do nothing
		return;
	}
	int memaddr = memdata->memaddr;
	// Find where in memory the node is to be removed
	while(curr != NULL){
		if (curr->sortval == memaddr){
			break;
		}
		curr = curr->next;
		prev = curr;
	}
	// Add nodes corresponding to after and before the memory hole
	memory_t *currdata = (memory_t*)curr->data;
	// After memory hole
	memory_t *node1 = memnode_create(currdata->memsize+currdata->memaddr-memdata->memaddr-memdata->memsize,memdata->memaddr+memdata->memsize);
	// Before memory hole (size,address)  -- Not needed as multi and fcfs only allocate at the start of free memory
	//memory_t *node2 = memnode_create(memdata->memaddr-currdata->memaddr, currdata->memaddr);
	// Add both holes to data
	if (curr->next == NULL){
		curr->data = node1;
		curr->sortval = node1->memaddr;
		//sll_add(head, node2->memaddr, node2); 
		mergeholes(head);
		return;
	}
	if (prev == curr){
		curr->sortval = node1->memaddr;
		curr->data = node1;
		mergeholes(head);
		return;
	}
	prev->next = curr->next;	
	free(curr);
	sll_add(head, node1->memaddr, node1); 
	//sll_add(head, node2->memaddr, node2); 
	mergeholes(head);
}