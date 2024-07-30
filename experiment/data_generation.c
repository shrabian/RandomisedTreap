// Written by Sharan Krishnan, 994103

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "data_generation.h"

element_t *gen_element(int *id_next, searchkey_t *key_dict){
    searchkey_t key = gen_random()%MAX_KEY;
    element_t *elem = (element_t *)malloc(sizeof(element_t));
    assert(elem);
    elem->id = *id_next;
    elem->key = key;

    key_dict[*id_next-1] = key; 
    *id_next += 1;
    return elem;
}

operation_t *gen_insertion(int *id_next, searchkey_t *key_dict){
    element_t *elem = gen_element(id_next, key_dict);
    operation_t *op = (operation_t *)malloc(sizeof(operation_t));
    assert(op);
    op->optype = INSERT;
    op->key = elem->key;
    op->element = elem;
    return op;
}

operation_t *gen_deletion(int *id_next, searchkey_t *key_dict){    
    int id = gen_random()%(*id_next-1);
    searchkey_t key = key_dict[id];
    operation_t *op = (operation_t *)malloc(sizeof(operation_t));
    assert(op);
    op->optype = DELETE;
    op->key = key;
    op->element = NULL;
    return op;
}

operation_t *gen_search(){
    searchkey_t key = gen_random()%MAX_KEY;
    operation_t *op = (operation_t *)malloc(sizeof(operation_t));
    assert(op);
    op->optype = SEARCH;
    op->key = key;
    op->element = NULL;
    return op;
}

void print_elem(element_t *elem){
    if (elem != NULL){
        printf("ID: %d, SearchKey: %d\n", elem->id, elem->key);
    }
    else {
        printf("NULL\n");
    }
}

int gen_random(){
    return rand() * (RAND_MAX+1) + rand();
}

void print_op(operation_t *op){
    printf("optype: %d, searchKey: %d ", op->optype, op->key);
    print_elem(op->element);
}

void print_key_dict(int n, searchkey_t *key_dict){
    for (int i = 0; i < n; i++){
        printf("%d ", key_dict[i]);
    }
    printf("\n");
}
