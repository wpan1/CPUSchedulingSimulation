#define EOL -1

typedef struct node_sorted {
    int sortval;
    void* data;
    struct node_sorted * next;
}node_sorted_t;

node_sorted_t* sll_create();
void sll_add(node_sorted_t *head, int sortval, void* data);
int sll_remove(node_sorted_t *head, void* data);
void sll_print_process(node_sorted_t *head);
void sll_print_memory(node_sorted_t *head);