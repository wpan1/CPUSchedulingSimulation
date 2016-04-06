typedef struct node {
    void *data;
    struct node *next;
} node_t;

node_t* ll_create();
void ll_add_last(node_t *head, void *data);
void ll_add_front(node_t *head, void *data);
int ll_remove(node_t *head, void *data);
int ll_find(node_t *head, void *data);
void *ll_removelargest_process(node_t *head);
void ll_push(node_t *head, void *data);
void *ll_get(node_t *head);
void *ll_pop(node_t *head);
void ll_print_process(node_t *head);
void ll_print_memory(node_t *head);