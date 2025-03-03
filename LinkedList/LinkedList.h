#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdalign.h>
#include <sys/stat.h>
#include "/usr/include/assert.h"
#include "common.h"

#define ADD_TYPE_TAIL       0
#define ADD_TYPE_HEAD       1
#define ADD_TYPE            ADD_TYPE_TAIL

typedef struct node node_t;
struct node
{
    void *data;
    node_t *next;
    node_t *prev;
};

typedef struct list_handler list_handler_t;
struct list_handler
{
    void* (*add_data)(void *);
    void (*print_node)(void *);
    void (*update_node_index)(void *);
    node_t* (*search_method)(void *, char *);
};

typedef struct linkedlist linkedlist_t;
struct linkedlist
{
    list_handler_t *hadler;
    node_t *head;
    node_t *tail;
    size_t data_size;
};

extern node_t* get_first_list(linkedlist_t *linkedlist);
extern node_t* get_last_list(linkedlist_t *linkedlist);
extern void print_linked_list(void);
extern void add_linked_list(linkedlist_t *list, void *data);
extern void release_linked_list(linkedlist_t *list);
extern node_t* search_linked_list(linkedlist_t *list, char *search_str);
extern void remove_linked_list(linkedlist_t *list, char* search_str);
extern linkedlist_t* init_linked_list(list_handler_t *list, size_t data_size);
extern __uint32_t get_list_count(linkedlist_t *list);

#endif