// Written by Sharan Krishnan, 994103

typedef struct {
    element_t **array;
    int N;
    int n;
}array_t;

element_t *search_array(array_t *, searchkey_t);
void insert_array(array_t *, element_t *);
void delete_array(array_t *, searchkey_t);
void free_array(array_t *);
array_t *new_array();
void print_array(array_t *);