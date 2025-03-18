//Glthreads (glued linked list)

//Single glthread node struct
typedef struct glthread_node_ {
    struct glthread_node_ *left;
    struct glthread_node_ *right;
} glthread_node_t;

//List of gltread nodes
typedef struct glll_ {
    glthread_node_t *head;
    unsigned int offset;
} glll_t;

void glll_add(glll_t*, glthread_node_t*);
void glll_init(glll_t*);
void glll_remove(glthread_node_t*);
void glll_insert(glll_t*, glthread_node_t*);
void glll_init_b(glll_t* __list, unsigned int __offset);