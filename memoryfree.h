#include <stdio.h>
#include "sortedlinkedlist.h"

typedef struct memorynode{
    int memsize;
    int memaddr;
} memory_t;

node_sorted_t *memfree_create(int memsize);
memory_t *memnode_create(int memsize, int memaddr);
void memnode_add(node_sorted_t *head, void *data);
void mergeholes(node_sorted_t *head);
void memnode_remove(node_sorted_t *head, void *data);