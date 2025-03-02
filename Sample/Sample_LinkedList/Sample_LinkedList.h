#ifndef __SAMPLE_LINKEDLIST__H__
#define __SAMPLE_LINKEDLIST__H__

#include <stdio.h>
#include <assert.h>
#include "LinkedList.h"
#include "UI.h"

// extern void delete_linkedlist_test(void);

extern linkedlist_t* Sample_LinkedList_init_linked(void (*print_func)(void *), void* (*add_data)(void *), void (*update_index)(void *),
                                   node_t* (*search_method)(void *, char *), size_t data_size);
// extern void Sample_LinkedList_add_list(void);
// extern void Sample_LinkedList_remove_list(void);
// extern void Sample_LinkedList_print_list(void);
// extern void Sample_LinkedList_search(void);


#endif  //!__SAMPLE_LINKEDLIST__H__