// Written by Sharan Krishnan, 994103

typedef struct node node_t;
struct node {
    int priority;
    element_t *element;
    node_t *parent;
    node_t *left;
    node_t *right;
};

typedef struct {
    node_t *root;
}treap_t;

element_t *search_treap(treap_t *, searchkey_t);
node_t *search_from_node(node_t *, searchkey_t);
void delete_treap(treap_t *, searchkey_t);
void insert_treap(treap_t *, element_t *);
node_t *insert_leaf(node_t *, element_t *);
int greater_than(element_t *, element_t *);
int is_empty(treap_t *);
void resolve_down(treap_t *, node_t *);
void resolve_up(treap_t*, node_t *);
void rotate_left(node_t *);
void rotate_right(node_t *);
treap_t *new_treap();
node_t *new_node(element_t *);
int min(int, int);
int is_left_child(node_t *, node_t *);
void free_nodes(node_t *);
void free_treap(treap_t *);
void print_depth_first(node_t *);
void print_node(node_t *);
