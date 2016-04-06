#include <stdio.h>
#include <stdlib.h>
#include "process.h"

/**
Create a process_t data structure
*/
process_t *createprocess(int PID, int timecreated, int jobtime, int memsize, int memaddr){
	// Allocate memory, and check
	process_t *process = (process_t*)malloc(sizeof(process_t));
	if (process == NULL){
		fprintf(stderr, "Could not allocate memory for list\n");
		exit(1);
	}
	// Populate values and return
	process->PID = PID;
	process->timecreated = timecreated;
	process->jobtime = jobtime;
	process->memsize = memsize;
	process->memaddr = memaddr;
	return process;
}