#include "LinkedList.h"

static __uint32_t g_age_index[MAX_OF_NODE] = { 0 };

linkedlist_t* init_linked_list(void (*print_func)(void *), void* (*add_data)(void *), void (*update_index)(void *), node_t* (*search_method)(void *, char *), size_t data_size)
{
    linkedlist_t *new_linked_list = NULL;

    new_linked_list = malloc(sizeof(linkedlist_t));
    new_linked_list->head = malloc(sizeof(node_t));
    new_linked_list->tail = malloc(sizeof(node_t));

    new_linked_list->head->next = new_linked_list->tail;
    new_linked_list->tail->prev = new_linked_list->head;

    new_linked_list->print_node = print_func;
    new_linked_list->update_node_index = update_index;
    new_linked_list->search_method = search_method;
    new_linked_list->add_data = add_data;

    return new_linked_list;
}

node_t* get_first_list(linkedlist_t *linkedlist)
{
    return linkedlist->head->next;
}

node_t* get_last_list(linkedlist_t *linkedlist)
{
    return linkedlist->tail->prev;
}

void add_linked_list(linkedlist_t *list, void *data)
{
    node_t *add_node = NULL;
    node_t *temp_node = NULL;
    __uint32_t data_size;

    data_size = list->data_size;
    add_node = malloc(sizeof(node_t));
    temp_node = list->head;
    memset(add_node,0,sizeof(node_t));
    if(add_node != NULL)
    {
        add_node->data = list->add_data(data);
    #if (ADD_TYPE == ADD_TYPE_HEAD)
        add_node->next = temp_node->next;    
        temp_node->next = add_node;
        add_node->prev = temp_node; 
    #else
        while(temp_node->next != list->tail)
        {
            temp_node = temp_node->next;
        }
        temp_node->next = add_node;
        add_node->prev = temp_node;
        add_node->next = list->tail;
        
    #endif
    }
    else
    {
        printf("memory alloc fail!\n func:%s, line:%d",__func__, __LINE__);
        assert(0);
    }

    list->update_node_index(list);
}

void release_linked_list(linkedlist_t *list)
{
    node_t *temp_data = NULL;
    node_t *delete_data = NULL;

    delete_data = list->head->next;
    list->head->next = NULL;

    while(delete_data != NULL)
    {
        // printf("Delete data: [%p] %s %s %d %p\n",delete_data, delete_data->name, delete_data->phone_number, delete_data->age, delete_data->next_user);
        temp_data = delete_data->next;
        free(delete_data);
        delete_data = temp_data;
    }
}

node_t* search_linked_list(linkedlist_t *list, char *search_str)
{
    node_t *search_point = NULL;

    search_point = list->search_method(list, search_str);

    return search_point;
}

__uint32_t get_list_count(linkedlist_t *list)
{
    node_t *temp_list = NULL;
    __uint32_t count;

    temp_list = list->head;
    count = 0;

    while (temp_list->next != list->tail)
    {  
        temp_list = temp_list->next;
        count ++;
    }
    
    return count;
}

void remove_linked_list(linkedlist_t *list, char* search_str)
{
    node_t *remove_node = NULL;
    
    remove_node = list->search_method(list, search_str);
    
    remove_node->prev->next = remove_node->next;
    remove_node->next->prev = remove_node->prev;
    
    list->update_node_index;
    
    free(remove_node);
}