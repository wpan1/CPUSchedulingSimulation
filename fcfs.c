#include <stdio.h>
#include <stdlib.h>
#include "fcfs.h"

void fcfs(node_t *processlist, int memsize){
	int step=0;
	node_sorted_t *memfree = memfree_create(memsize);
	node_t *phmem = ll_create();
	node_t *waitingprocc = ll_create();
	process_t *process = (process_t*)ll_get(processlist);
	process_t *runningprocess = (process_t*)ll_pop(processlist);
	// Start when first process enters memory
	step = process->timecreated;
	runningprocess->memaddr = 0;
	memnode_remove(memfree,memnode_create(runningprocess->memsize,runningprocess->memaddr));
	ll_add_last(phmem,process);
	// Print debug info
	printf("time %d, %d running, numprocesses=%d, numholes=%d, memuseage=%d%%\n",
	step,
	runningprocess->PID,
	mem_processes(phmem),
	countholes(memfree, memsize),
	memusage(memfree, memsize));

	while (runningprocess != NULL || waitingprocc->data != NULL){
		if (processlist->data != NULL){
			process = (process_t*)ll_get(processlist);
		}
		// Add process to running
		while(process->timecreated == step){
			ll_add_last(waitingprocc,process);
			ll_pop(processlist);
			if (processlist->data != NULL){
				process = (process_t*)ll_get(processlist);
			}
			else{
				break;
			}
		}
		// Step counter
		step += 1;
		if (runningprocess != NULL){
			// If not currently in physical memory, find space
			if (!ll_find(phmem,runningprocess)){
				// No space available, free up some memory
				while(!find_firstfit(memfree, runningprocess)){
					process_t *largest = ll_removelargest_process(phmem);
					memnode_add(memfree, memnode_create(largest->memsize, largest->memaddr));
				}
				ll_add_last(phmem, runningprocess);
			}
			// Decrement running process
			runningprocess->jobtime -= 1;
		}
		if (runningprocess->jobtime == 0){
			// Free up memory
			memnode_add(memfree,memnode_create(runningprocess->memsize,runningprocess->memaddr));
			ll_remove(phmem, runningprocess);
			if (waitingprocc->data != NULL){
				runningprocess = ll_pop(waitingprocc);
				// Find free address
				int memaddr = find_firstfit(memfree,process);
				// If space available
				if (memaddr != -1){
					runningprocess->memaddr = memaddr;
					// Add to physcial memory
					ll_add_last(phmem,runningprocess);
					// Remove from free memory
					memnode_remove(memfree,memnode_create(runningprocess->memsize,memaddr));
				}
				// If space not availabe
				else{
					// No space available, free up some memory
					while(find_firstfit(memfree, runningprocess) == -1){
						process_t *largest = ll_removelargest_process(phmem);
						memnode_add(memfree, memnode_create(largest->memsize, largest->memaddr));
					}
					runningprocess->memaddr = find_firstfit(memfree, runningprocess);
					ll_add_last(phmem, runningprocess);
				}
				// Print debug info
				printf("time %d, %d running, numprocesses=%d, numholes=%d, memuseage=%d%%\n",
				step,
				runningprocess->PID,
				mem_processes(phmem),
				countholes(memfree, memsize),
				memusage(memfree, memsize));
			}
			// No process waiting
			else{
				runningprocess = NULL;
			}
		}
	}
	printf("time %d, simulation finished",step);
}

/*
Find the first space where a process can fit into memory
*/
int find_firstfit(node_sorted_t *memfree, process_t *process){
	while(memfree != NULL){
		memory_t *memnode = memfree->data;
		if (memnode->memsize >= process->memsize){
			return memnode->memaddr;
		}
		memfree = memfree->next;
	}
	return -1;
}

/*
Returns the number of processes in memory
*/
int mem_processes(node_t *phmem){
	int count = 0;
	while(phmem != NULL){
		if(phmem->data != NULL){
			count += 1;
		}
		phmem = phmem->next;
	}
	return count;
}

/*
Returns the number of holes in memory
*/
int countholes(node_sorted_t *memfree, int memsize){
	int count = 0;
	memory_t *tempmem = memfree->data;
	if (tempmem->memsize == 0){
		return 0;
	}
	while(memfree != NULL && tempmem->memsize != 0){
		count += 1;
		memfree = memfree->next;
		if (memfree != NULL){
			tempmem = memfree->data;
		}
	}
	return count;
}

/*
Returns current memory usage
*/
int memusage(node_sorted_t *memfree, int memsize){
	int count = 0;
	while(memfree != NULL){
		if(memfree->data != NULL){
			memory_t *memnode = (memory_t*)memfree->data;
			count += memnode->memsize;
		}
		memfree = memfree->next;
	}
	return 100-count*100/memsize;
}