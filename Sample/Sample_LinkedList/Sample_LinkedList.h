#ifndef __SAMPLE_LINKEDLIST__H__
#define __SAMPLE_LINKEDLIST__H__

#include <stdio.h>
#include <assert.h>
#include "LinkedList.h"
#include "UI.h"

extern void delete_linkedlist_test(void);

extern void Sample_LinkedList_init_linked(void (*print_func)(void *), void (*update_index)(linkedlist_t *list),
                                   node_t* (*search_method)(linkedlist_t *, char*), size_t data_size);
extern void Sample_LinkedList_add_list(void);
extern void Sample_LinkedList_remove_list(void);
extern void Sample_LinkedList_print_list(void);
extern void Sample_LinkedList_search(void);


#endif  //!__SAMPLE_LINKEDLIST__H__