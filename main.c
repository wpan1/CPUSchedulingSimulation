#include <stdio.h>
#include <string.h>
#include "fcfs.h"

int main(int argc, char *argv[]){
	// Get environment parameters
	char *filename;
	char *schedalg;
	int memsize;
	getinputargs(argc, argv, &filename, &schedalg, &memsize);
	// Get process list
	node_t *processlist = getinputfile(filename);
	
	// Call scheduling algorithm
	if (strcmp(schedalg,"fcfs") == 0){
		fcfs(processlist, memsize);
	} 
	else if (strcmp(schedalg,"multi") == 0){
		multi(processlist, memsize);
	}

	return 0;
}