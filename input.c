#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        "input.h"
#include        "process.h"

/* Extern declarations: */

extern  int     optind;
extern  char    *optarg;

int getinputargs(int argc, char** argv, char **filename, char **schedalg, int *memsize)
{
	char input;
	/* parse command line options example
	 
	   an appropraite usage message should be included
	 
	   a sample command line is provided below:
	
					./prog_name -l Java -s 500
	 
	   where l option is used to specify the name of the schedalg used (char array)
	         s option is used to specify the size or the number of lines in the file (int)
	 
	*/
	while ((input = getopt(argc, argv, "f:l:m:")) != EOF)
	{
		switch ( input )
		{
			case 'f':
				// set the value of size (int value) based on optarg
				*filename = optarg;
				break;

			case 'l':
				if(strcmp(optarg, "fcfs") == 0) 
					*schedalg  = optarg;

				else if(strcmp(optarg, "multi") == 0) 
					*schedalg  = optarg;

				else
				{
					// exit if optarg unknown
					fprintf(stderr, "Unknown Scheduling Algorithm %s\n ", optarg);
					exit(1);
				}
 				break;
					// should not get here
          
			case 'm':
				// set the value of size (int value) based on optarg
				*memsize = atoi(optarg);
				break;

			default:
				// do something
				break;
		} 
	}	
	// ideally, a usage statement should also be included

	// once the input arguments have been processed, call other functions
	// after appropriate error checking
	return 0;
}

/*
Get input from file
*/
node_t *getinputfile(char *filename){
	node_t *processlist = ll_create();
	int threadinput[4];
	// Open file with only read permissions
	FILE *fp;
	fp = fopen (filename, "r");
	// Read and add to list
	while(fscanf(fp,"%d %d %d %d\n",&threadinput[0],&threadinput[1],&threadinput[2],&threadinput[3]) > 0){
		ll_add_last(processlist, createprocess(threadinput[1], threadinput[0], threadinput[3], threadinput[2],-1));
	}
	// Close file and return linked lsit
	fclose(fp);
	return processlist;
}