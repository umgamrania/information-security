#pragma once
#include <stdio.h>
#include <stdlib.h>

// Structure for storing data of one node of linked list
typedef struct _node_t{
    char a;
    char b;
    struct _node_t *next;
} node_t;

// Structure for storing head and tail ptrs of a linked list
typedef struct _ll{
    node_t *head;
    node_t *tail;
} linked_list_t;

node_t *get_node(char a, char b) {
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->a = a;
    node->b = b;
    node->next = NULL;
    return node;
}

linked_list_t *new_list() {
    linked_list_t *list = (linked_list_t*)malloc(sizeof(linked_list_t));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void insert_front(linked_list_t *list, char a, char b) {
    node_t *node = get_node(a, b);
    if(list->head == NULL) {
        list->tail = node;
    }
    else{
        node->next = list->head;
    }
    list->head = node;
}

void insert_end(linked_list_t *list, char a, char b) {
    node_t *node = get_node(a, b);
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
        printf("%c %c", ptr->a, ptr->b);
        ptr = ptr->next;
    }
    printf("\n");
}

void free_list(linked_list_t *list) {
    node_t *ptr = list->head;
    node_t *tmp;

    while(ptr != NULL){
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}