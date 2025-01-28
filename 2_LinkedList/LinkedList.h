#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/assert.h"
#include "../common/common.h"

#define ADD_TYPE_TAIL       0
#define ADD_TYPE_HEAD       1
#define ADD_TYPE            ADD_TYPE_TAIL

extern void print_linked_list(void);
extern void add_linked_list(char *name, char *phone_number, __uint32_t age);
extern void release_linked_list(void);
extern USERDATA* search_linked_list(char *search_str);
extern void remove_linked_list(char *search_str);