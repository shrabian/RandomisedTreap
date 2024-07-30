// Written by Sharan Krishnan, 994103

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "data_generation.h"
#include "dynamic_array.h"

element_t *search_array(array_t *DA, searchkey_t key){
    for (int i=0; i < DA->n; i++){
        if (DA->array[i]->key == key){
            return DA->array[i];
        }
    }
    return NULL;
}

void delete_array(array_t *DA, searchkey_t key){
    if (DA->n == 0){
        return;
    }
    int i = 0;
    while (DA->array[i]->key != key){
        i++;
        if (i >= DA->n){
            return;
        }
    }
    DA->n -= 1;
    DA->array[i] = DA->array[DA->n];
    if (DA->N > 1 && DA->n <= DA->N/4){
        DA->N = DA->N/2;
        DA->array = (element_t **)realloc(DA->array, DA->N * sizeof(element_t *));
        assert(DA->array != NULL);
    }
}


void insert_array(array_t *DA, element_t *elem){
    if (DA->n == DA->N){
        DA->N = 2*(DA->N);
        DA->array = (element_t **)realloc(DA->array, DA->N * sizeof(element_t *));
        assert(DA->array != NULL);
    }
    DA->array[DA->n] = elem;
    DA->n++;
}

array_t *new_array(){
    array_t *DA = (array_t*)malloc(sizeof(array_t));
    assert(DA != NULL);
    DA->array = (element_t **)malloc(sizeof(element_t *));
    assert(DA->array != NULL);
    DA->N = 1;
    DA->n = 0;
    return DA;
}

void print_array(array_t *DA){
    printf("N = %d, n = %d\n", DA->N, DA->n);
    for (int i = 0; i < DA->n; i ++){
        printf("%d ", DA->array[i]->key);
    }
    printf("\n");
}

void free_array(array_t *DA){
    free(DA->array);
    free(DA);
}