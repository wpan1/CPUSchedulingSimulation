typedef struct memorynode{
    int memsize;
    int memaddr;
} memory_node_t;

typedef struct node_sorted {
    int sortval;
    void* data;
    struct node_sorted * next;
} node_sorted_t;

typedef struct Process {
   int PID;
   int memsize;
   int memaddr;
   int time;
} process_t;  

typedef struct node {
    void *data;
    struct node * next;
} node_t;
