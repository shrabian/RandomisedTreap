// Written by Sharan Krishnan, 994103

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "data_generation.h"
#include "treap.h"

element_t *search_treap(treap_t *treap, searchkey_t key){
    node_t *node = search_from_node(treap->root, key);
    if (node == NULL){
        return NULL;
    }
    return node->element;
}

node_t *search_from_node(node_t *node, searchkey_t key){
    if (node == NULL || node->element->key == key){
        return node;
    }
    if (node->element->key > key){
        return search_from_node(node->left, key);
    }
    return search_from_node(node->right, key);
}

void delete_treap(treap_t *treap, searchkey_t key){
    assert(treap != NULL);
    node_t *node = search_from_node(treap->root, key);
    if (node == NULL){
        return;
    }
    node->priority = INT_MAX;
    resolve_down(treap, node);
    if (node->parent == NULL){
        treap->root = NULL;
    }
    else if(is_left_child(node->parent, node)){
        node->parent->left = NULL;
    }
    else{
        node->parent->right = NULL;
    }
    free(node);
}

void insert_treap(treap_t *treap, element_t *elem){
    assert(treap != NULL);
    if (treap->root == NULL){
        treap->root = new_node(elem);
        return;
    }
    node_t *node = insert_leaf(treap->root, elem);
    resolve_up(treap, node);
}

void resolve_down(treap_t *treap, node_t *node){
    if (node->left == NULL && node->right == NULL){
        return;
    }
    if (node->right == NULL && node->left->priority < node->priority){
        rotate_right(node);
    }
    else if(node->left == NULL && node->right->priority < node->priority){
        rotate_left(node);
    }
    else if(min(node->left->priority, node->right->priority) < node->priority){
        if (min(node->left->priority, node->right->priority) == node->left->priority){
            rotate_right(node);
        }
        else{
            rotate_left(node);
        }
    }
    else{
        return;
    }
    if (node->parent->parent == NULL){
        treap->root = node->parent;
    }
    resolve_down(treap, node);
}

void resolve_up(treap_t *treap, node_t *node){
    assert(node != NULL);
    if (node->parent == NULL){
        treap->root = node;
        return;
    }
    if (node->parent->priority <= node->priority){
        return;
    }
    if (is_left_child(node->parent, node)){
        rotate_right(node->parent);
    }
    else{
        rotate_left(node->parent);
    }
    return resolve_up(treap, node);
}

void rotate_left(node_t *node){
    assert(node != NULL && node->right != NULL);
    if (node->parent != NULL && is_left_child(node->parent, node)){
        node->parent->left = node->right;
    }
    else if(node->parent !=NULL) {
        node->parent->right = node->right;
    }
    
    node->right->parent = node->parent;
    node->parent = node->right;
    node->right = node->parent->left;
    node->parent->left = node;
    if (node->right != NULL){
        node->right->parent = node;
    }
}

void rotate_right(node_t *node){
    assert(node != NULL && node->left != NULL);
    if (node->parent != NULL && is_left_child(node->parent, node)){
        node->parent->left = node->left;
    }
    else if (node->parent != NULL){
        node->parent->right = node->left;
    }
    node->left->parent = node->parent;
    node->parent = node->left;
    node->left = node->parent->right;
    node->parent->right = node;
    if (node->left != NULL){
        node->left->parent = node;
    }
}

node_t *insert_leaf(node_t *parent, element_t *elem){
    assert(parent != NULL);
    if (greater_than(parent->element, elem) && parent->left == NULL){
        node_t *node = new_node(elem);
        node->parent = parent;
        parent->left = node;
        return node;
    }
    if(!greater_than(parent->element, elem) && parent->right ==NULL){
        node_t *node = new_node(elem);
        node->parent = parent;
        parent->right = node;
        return node;
    }
    if(greater_than(parent->element, elem)){
        return insert_leaf(parent->left, elem);
    }
    return insert_leaf(parent->right, elem);
}

treap_t *new_treap(){
    treap_t *treap = (treap_t *)malloc(sizeof(treap_t));
    assert(treap != NULL);
    treap->root = NULL;
    return treap;
}

node_t *new_node(element_t *elem){
    node_t *node = (node_t *)malloc(sizeof(node_t));
    assert(node != NULL);
    node->priority = gen_random();
    node->element = elem;
    node->parent = node->left = node->right = NULL;
    return node;
}

int greater_than(element_t *e1, element_t* e2){
    return e1->key > e2->key ||
    (e1->key == e2->key && e1->id > e2->id);
}

int is_empty(treap_t * treap){
    return treap->root == NULL;
}

int is_left_child(node_t *parent, node_t *child){
    assert(parent != NULL && child != NULL);
    return (parent->left != NULL && parent->left->element->id == child->element->id);
}

int min(int n, int m){
    if (n < m){
        return n;
    }
    return m;
}

void print_depth_first(node_t *root){
    if (root == NULL){
        return;
    }
    print_node(root);
    print_depth_first(root->left);
    print_depth_first(root->right);
}

void print_node(node_t * node){
    if (node == NULL){
        return;
    }
    printf("Prio:   %d ", node->priority);
    print_elem(node->element);
}

void free_nodes(node_t *node){
    if (node == NULL){
        return;
    }
    free_nodes(node->left);
    free_nodes(node->right);
    free(node);
}

void free_treap(treap_t *treap){
    if (treap == NULL){
        return;
    }
    free_nodes(treap->root);
    free(treap);
}


