#include <stdio.h>
#include <stdlib.h>
#include "fcfs.h"

#define Q1 2
#define Q2 4
#define Q3 8

void multi(node_t *processlist, int memsize){
	int step=0;
	node_sorted_t *memfree = memfree_create(memsize);
	node_t *phmem = ll_create();
	node_t *plevel1 = ll_create();
	node_t *plevel2 = ll_create();
	node_t *plevel3 = ll_create();
	process_t *process = (process_t*)ll_get(processlist);
	process_t *runningprocess = NULL;

	while (runningprocess != NULL || processlist->data != NULL){
		// Get next process to run
		if (processlist->data != NULL){
			process = (process_t*)ll_get(processlist);
		}
		// Add process to running
		while(process->timecreated == step){
			process->qtimeleft = Q1;
			ll_add_last(plevel1,process);
			ll_pop(processlist);
			if (processlist->data != NULL){
				process = (process_t*)ll_get(processlist);
			}
			else{
				break;
			}
		}
		// Handle gaps in processes (No process to run)
		if (runningprocess == NULL){
			runningprocess = next_process(plevel1,plevel2,plevel3);
			// Premature step
			if (runningprocess == NULL){
				step += 1;
				continue;
			}
			// If not currently in physical memory, find space
			if (ll_find(phmem,runningprocess) == 0){
				// No space available, free up some memory
				while(find_firstfit(memfree, runningprocess, memsize) == -1){
					process_t *largest = ll_removelargest_process(phmem);
					memnode_add(memfree, memnode_create(largest->memsize, largest->memaddr));
				}
				runningprocess->memaddr = find_firstfit(memfree,runningprocess, memsize);
				ll_add_last(phmem, runningprocess);
				memnode_remove(memfree, memnode_create(runningprocess->memsize, runningprocess->memaddr));
			}
			// Print debug info
			printf("time %d, %d running, numprocesses=%d, numholes=%d, memusage=%d%%\n",
			step,
			runningprocess->PID,
			mem_processes(phmem),
			countholes(memfree, memsize),
			memusage(memfree, memsize));
		}
		else if (runningprocess != NULL){
			// Decrement Quantum
			runningprocess->qtimeleft -= 1;
			runningprocess->jobtime -= 1;
			if (runningprocess->jobtime == 0){
				// Free up memory
				memnode_add(memfree,memnode_create(runningprocess->memsize,runningprocess->memaddr));
				ll_remove(phmem, runningprocess);
				remove_plevel(plevel1,plevel2,plevel3,runningprocess);
				// Swap to next process
				runningprocess = next_process(plevel1,plevel2,plevel3);
				// Premature step
				if (runningprocess == NULL){
					step += 1;
					continue;
				}
				// If not currently in physical memory, find space
				if (ll_find(phmem,runningprocess) == 0){
					// No space available, free up some memory
					while(find_firstfit(memfree, runningprocess, memsize) == -1){
						process_t *largest = ll_removelargest_process(phmem);
						memnode_add(memfree, memnode_create(largest->memsize, largest->memaddr));
					}
					runningprocess->memaddr = find_firstfit(memfree,runningprocess, memsize);
					ll_add_last(phmem, runningprocess);
					memnode_remove(memfree, memnode_create(runningprocess->memsize, runningprocess->memaddr));
				}
				// Print debug info
				printf("time %d, %d running, numprocesses=%d, numholes=%d, memusage=%d%%\n",
				step,
				runningprocess->PID,
				mem_processes(phmem),
				countholes(memfree, memsize),
				memusage(memfree, memsize));
			}
			else if (runningprocess->qtimeleft == 0){
				// Move to quantum 2
				if ((ll_find(plevel1,runningprocess))){
					runningprocess->qtimeleft = Q2;
					ll_remove(plevel1,runningprocess);
					ll_add_last(plevel2,runningprocess);
				}
				// Move to end of quantum 3 queue
				else if ((ll_find(plevel2,runningprocess))){
					runningprocess->qtimeleft = Q3;
					ll_remove(plevel2,runningprocess);
					ll_add_last(plevel3,runningprocess);
				}
				else{
					runningprocess->qtimeleft = Q3;
					ll_remove(plevel3,runningprocess);
					ll_add_last(plevel3,runningprocess);
				}
				// Swap processes, if none remaining, end simulation
				runningprocess = next_process(plevel1,plevel2,plevel3);
				// Premature Step
				if (runningprocess == NULL ){
					step += 1;
					continue;
				}
				// If not currently in physical memory, find space
				if (ll_find(phmem,runningprocess) == 0){
					// No space available, free up some memory
					while(find_firstfit(memfree, runningprocess, memsize) == -1){
						process_t *largest = ll_removelargest_process(phmem);
						memnode_add(memfree, memnode_create(largest->memsize, largest->memaddr));
					}
					runningprocess->memaddr = find_firstfit(memfree,runningprocess, memsize);
					ll_add_last(phmem, runningprocess);
					memnode_remove(memfree, memnode_create(runningprocess->memsize, runningprocess->memaddr));
				}
				// Print debug info
				printf("time %d, %d running, numprocesses=%d, numholes=%d, memusage=%d%%\n",
				step,
				runningprocess->PID,
				mem_processes(phmem),
				countholes(memfree, memsize),
				memusage(memfree, memsize));
			}
		}
		// Step counter
		step += 1;
	}
	// Step - 1 since, the simulation finishes on the previous step
	printf("time %d, simulation finished.\n",step-1);
}

/*
Find the next process to run
*/
process_t *next_process(node_t* plevel1, node_t* plevel2, node_t* plevel3){
	// Searches all process levels, finding first one to run
	process_t *returnprocess = (process_t*)ll_get(plevel1);
	if(returnprocess == NULL){
		returnprocess = (process_t*)ll_get(plevel2);
	}
	if (returnprocess == NULL){
		returnprocess = (process_t*)ll_get(plevel3);
	}
	if (returnprocess == NULL){
		return NULL;
	}
	return returnprocess;
}

/*
Remove specific process from plevel
*/
void remove_plevel(node_t* plevel1, node_t* plevel2, node_t* plevel3, void *data){
	// Removes from all plevels, if not found, remove does nothing
	ll_remove(plevel1,data);
	ll_remove(plevel2,data);
	ll_remove(plevel3,data);	
}