#include "Sample_LinkedList.h"
#include "LinkedList.h"

linkedlist_t* Sample_LinkedList_init_linked(void (*print_func)(void *), void* (*add_data)(void *), void (*update_index)(void *),
                                   node_t* (*search_method)(void *, char *), size_t data_size)
{
    linkedlist_t * target_list = NULL;
    
    target_list = init_linked_list(print_func, add_data, update_index, search_method, data_size);
    return target_list;
}