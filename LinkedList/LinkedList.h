#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/assert.h"
#include "common.h"

#define MAX_OF_NODE  256

#define ADD_TYPE_TAIL       0
#define ADD_TYPE_HEAD       1
#define ADD_TYPE            ADD_TYPE_TAIL

extern USERDATA* get_first_list(void);
extern USERDATA* get_last_list(void);
extern void print_linked_list(void);
extern void add_linked_list(char *name, char *phone_number, __uint32_t age);
extern void release_linked_list(void);
extern USERDATA* search_linked_list(char *search_str);
extern void remove_linked_list(char *search_str);
extern void init_linked_list(void);
extern __uint32_t get_list_count(void);
extern __uint32_t *LinkedList_get_age_index(void);

#endif