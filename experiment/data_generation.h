// Written by Sharan Krishnan, 994103

#define INSERT 1
#define DELETE 2
#define SEARCH 3
#define MAX_KEY ((int)1e7+1)

typedef int searchkey_t;

typedef struct{
    int id;
    searchkey_t key;
}element_t;

typedef struct {
    int optype;
    searchkey_t key;
    element_t *element;
}operation_t;

element_t *gen_element(int *, searchkey_t *);
operation_t *gen_insertion(int *, searchkey_t *);
operation_t *gen_deletion(int *, searchkey_t *);
operation_t *gen_search();
int gen_random();
void print_elem(element_t *);
void print_op(operation_t *op);
void print_key_dict(int n, searchkey_t *key_dict);