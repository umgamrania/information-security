#pragma once
#include <stdio.h>
#include <stdlib.h>

// Structure for storing data of one node of linked list
typedef struct _node_t{
    char val;
    struct _node_t *next;
} node_t;

// Structure for storing head and tail ptrs of a linked list
typedef struct _ll{
    node_t *head;
    node_t *tail;
} linked_list_t;

node_t *get_node(char val) {
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->val = val;
    node->next = NULL;
    return node;
}

linked_list_t *new_list() {
    linked_list_t *list = (linked_list_t*)malloc(sizeof(linked_list_t));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void insert_front(linked_list_t *list, char val) {
    node_t *node = get_node(val);
    if(list->head == NULL) {
        list->tail = node;
    }
    else{
        node->next = list->head;
    }
    list->head = node;
}

void insert_end(linked_list_t *list, char val) {
    node_t *node = get_node(val);
    if(list->tail == NULL) {
        list->head = node;
    }
    else{
        list->tail->next = node;
    }
    list->tail = node;
}

void print_list(linked_list_t *list) {
    node_t *ptr = list->head;

    while(ptr != NULL){
        printf("%c", ptr->val);
        ptr = ptr->next;
    }
    printf("\n");
}