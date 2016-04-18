#include "memoryfree.h"
#include "input.h"
#include "process.h"

void multi(node_t *processlist, int memsize);
process_t *next_process(node_t* plevel1, node_t* plevel2, node_t* plevel3);
void remove_plevel(node_t* plevel1, node_t* plevel2, node_t* plevel3, void *data);
void fcfs(node_t *processlist, int memsize);
int find_firstfit(node_sorted_t *memfree, process_t *process,int memsize);
int mem_processes(node_t *phmem);
int countholes(node_sorted_t *memfree, int memsize);
int memusage(node_sorted_t *memfree, int memsize);