// Written by Sharan Krishnan, 994103

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <limits.h>
#include "data_generation.h"
#include "treap.h"
#include "dynamic_array.h"

#define MAX_LENGTH 1000000

void experiment_one(searchkey_t *, operation_t **);
void experiment_two(searchkey_t *, operation_t **);
void experiment_three(searchkey_t *, operation_t **);
void experiment_four(searchkey_t *, operation_t **);
void single_run(operation_t **, int);
void count_down(int );

int main(int argc, char **argv){
    searchkey_t *keys_dict = (searchkey_t *)malloc(MAX_LENGTH*sizeof(searchkey_t));
    operation_t **ops = (operation_t **)malloc(MAX_LENGTH*sizeof(operation_t *));
    printf("Experiment 1\n");
    experiment_one(keys_dict, ops);
    printf("Experiment 2\n");
    experiment_two(keys_dict, ops);
    printf("Experiment 3\n");
    experiment_three(keys_dict, ops);
    printf("Experiment 4\n");
    experiment_four(keys_dict, ops);
    free(keys_dict);
    free(ops);
    return 0;
}

void experiment_one(searchkey_t *keys_dict, operation_t **ops){
    int id_next = 1;
    int L[5] = {100000, 200000, 500000, 800000, 1000000};
    for (int i=0; i<5; i++){
        for (int j=0; j<L[i]; j++){
            ops[j] = gen_insertion(&id_next, keys_dict);
        }
        printf("L=%d\n", L[i]);
        single_run(ops, L[i]);
        id_next = 1;
    }
    printf("\n");
}

void experiment_two(searchkey_t *keys_dict, operation_t **ops){
    int denom, outcome, id_next=1;
    double p[5] = {0.1, 0.5, 1, 5, 10};
    for (int i=0; i<5; i++){
        denom = (int) 100/(p[i]);
        for (int j=0; j<MAX_LENGTH; j++){
            outcome = rand()%denom;
            if (outcome || j == 0){
                ops[j] = gen_insertion(&id_next, keys_dict);
            }
            else{
                ops[j] = gen_deletion(&id_next, keys_dict);
            }
        }
        printf("p=%lf\n", p[i]);
        single_run(ops, MAX_LENGTH);
        id_next = 1;
    }
    printf("\n");
}

void experiment_three(searchkey_t *keys_dict, operation_t **ops){
    int denom, outcome, id_next=1;
    double p[5] = {0.1, 0.5, 1, 5, 10};
    for (int i=0; i<5; i++){
        denom = (int) 100/(p[i]);
        for (int j=0; j<MAX_LENGTH; j++){
            outcome = rand()%denom;
            if (outcome || j==0){
                ops[j] = gen_insertion(&id_next, keys_dict);
            }
            else{
                ops[j] = gen_search();
            }
        }
        printf("p=%lf\n", p[i]);
        single_run(ops, MAX_LENGTH);
        id_next = 1;
    }
    printf("\n");
}

void experiment_four(searchkey_t *keys_dict, operation_t **ops){
    int denom=20, outcome, id_next=1;
    int L[5] = {100000, 200000, 500000, 800000, 1000000};
    for (int i=0; i<5; i++){
        for (int j=0; j<L[i]; j++){
            outcome = rand()%denom;
            if (outcome>1 || j ==0){
                ops[j] = gen_insertion(&id_next, keys_dict);
            }
            else if (outcome == 1){
                ops[j] = gen_deletion(&id_next, keys_dict);
            }
            else{
                ops[j] = gen_search();
            }
        }
        printf("L=%d\n", L[i]);
        single_run(ops, L[i]);
        id_next = 1;
    }
    printf("\n");
}

void single_run(operation_t *ops[], int L){
    struct timeval start, end;
    treap_t *treap = new_treap();
    gettimeofday(&start, NULL);
    for (int i=0; i < L; i++){
        if (ops[i]->optype == INSERT){
            insert_treap(treap, ops[i]->element);
        }
        else if(ops[i]->optype == DELETE){
            delete_treap(treap, ops[i]->key);
        }
        else{
            search_treap(treap, ops[i]->key);
        }
    }
    gettimeofday(&end, NULL);
    printf("Treap: %lf\n", end.tv_sec + end.tv_usec/1e6 - start.tv_sec - start.tv_usec/1e6);

    array_t *DA = new_array();
    gettimeofday(&start, NULL);
    for (int i=0; i < L; i++){
        if (ops[i]->optype == INSERT){
            insert_array(DA, ops[i]->element);
        }
        else if(ops[i]->optype == DELETE){
            delete_array(DA, ops[i]->key);
        }
        else{
            search_array(DA, ops[i]->key);
        }  
    }
    gettimeofday(&end, NULL);
    printf("Array: %lf\n", end.tv_sec + end.tv_usec/1e6 - start.tv_sec - start.tv_usec/1e6);
    
    free_treap(treap);
    free_array(DA);
    for (int i=0; i < L; i++){
        free(ops[i]->element);
        free(ops[i]);
    }
    
}
