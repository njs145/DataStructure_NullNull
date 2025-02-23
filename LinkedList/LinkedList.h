#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/assert.h"
#include "common.h"

#define ADD_TYPE_TAIL       0
#define ADD_TYPE_HEAD       1
#define ADD_TYPE            ADD_TYPE_TAIL

#define MAX_OF_NODE  256

typedef struct node node_t;
struct node
{
    void *data;
    node_t *next;
    node_t *prev;
};

typedef struct linkedlist linkedlist_t;
struct linkedlist
{
    node_t *head;
    node_t *tail;
    size_t data_size;
    void (*print_node)(void *);
    void (*update_node_index)(linkedlist_t *);
    node_t* (*search_method)(linkedlist_t *, char *);
};

extern node_t* get_first_list(linkedlist_t *linkedlist);
extern node_t* get_last_list(linkedlist_t *linkedlist);
extern void print_linked_list(void);
extern void add_linked_list(linkedlist_t *list, void *data);
extern void release_linked_list(linkedlist_t *list);
extern node_t* search_linked_list(linkedlist_t *list, char *search_str);
extern void remove_linked_list(linkedlist_t *list, char* search_str);
extern linkedlist_t* init_linked_list(void (*print_func)(void *), void (*update_index)(linkedlist_t *list), size_t data_size);
extern __uint32_t get_list_count(linkedlist_t *list);

#endif