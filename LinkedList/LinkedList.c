#include "LinkedList.h"

USERDATA    g_ll_head_node = {"__dummy head node__"," ",0};
USERDATA    g_ll_tail_node = {"__dummy tail node__"," ",0};

void init_linked_list(void)
{
    g_ll_head_node.next_user = &g_ll_tail_node;
    g_ll_tail_node.prev_user = &g_ll_head_node;
}

static USERDATA* search_linked_list_to_remove(char *search_str)
{
    USERDATA *prev_node = NULL;

    prev_node = &g_ll_head_node;

    while(strcmp(search_str, prev_node->next_user->name) != 0)
    {
        if(prev_node->next_user->name == NULL)
        {
            printf("%s not found\n",search_str);
            return NULL;
        }
        else
        {
            prev_node = prev_node->next_user;
        }
    }

    return prev_node;
}

USERDATA* get_first_list(void)
{
    return g_ll_head_node.next_user;
}

USERDATA* get_last_list(void)
{
    return g_ll_tail_node.prev_user;
}

void print_linked_list(void)
{
    USERDATA *temp_data = NULL;
    
    temp_data = &g_ll_head_node;
    while(temp_data != &g_ll_tail_node)
    {
        printf("[%p] %s %s %d %p\n",temp_data, temp_data->name, temp_data->phone_number, temp_data->age, temp_data->next_user);
        temp_data = temp_data->next_user;
    }
}

void add_linked_list(char *name, char *phone_number, __uint32_t age)
{
    USERDATA *add_node = NULL;
    USERDATA *temp_node = NULL;

    add_node = malloc(sizeof(USERDATA));
    memset(add_node,0,sizeof(USERDATA));
    if(add_node != NULL)
    {
        temp_node = &g_ll_head_node;
        strcpy(add_node->name, name);
        strcpy(add_node->phone_number, phone_number);
        add_node->age = age;
        printf("Add data: [%p] %s %s %d %p\n",add_node, add_node->name, add_node->phone_number, add_node->age, add_node->next_user);
    #if (ADD_TYPE == ADD_TYPE_HEAD)
        add_node->next_user = temp_node->next_user;    
        temp_node->next_user = add_node;
        add_node->prev_user = temp_node; 
    #else
        while(temp_node->next_user != &g_ll_tail_node)
        {
            temp_node = temp_node->next_user;
        }
        temp_node->next_user = add_node;
        add_node->prev_user = temp_node;
        add_node->next_user = &g_ll_tail_node;
        
    #endif
    }
    else
    {
        printf("memory alloc fail!\n func:%s, line:%d",__func__, __LINE__);
        assert(0);
    }
}

void release_linked_list(void)
{
    USERDATA *temp_data = NULL;
    USERDATA *delete_data = NULL;

    delete_data = g_ll_head_node.next_user;
    g_ll_head_node.next_user = NULL;

    while(delete_data != NULL)
    {
        printf("Delete data: [%p] %s %s %d %p\n",delete_data, delete_data->name, delete_data->phone_number, delete_data->age, delete_data->next_user);
        temp_data = delete_data->next_user;
        free(delete_data);
        delete_data = temp_data;
    }
}

USERDATA* search_linked_list(char *search_str)
{
    USERDATA *search_point = g_ll_head_node.next_user;

    while(strcmp(search_str, search_point->name) != 0)
    {
        if(search_point->next_user == NULL)
        {
            printf("%s not found\n",search_str);
            return NULL;
        }
        else
        {
            search_point = search_point->next_user;
        }
    }
    return search_point;
}

__uint32_t get_list_count(void)
{
    USERDATA *temp_list = NULL;
    __uint32_t count;

    temp_list = &g_ll_head_node;
    count = 0;

    while (temp_list->next_user != &g_ll_tail_node)
    {  
        temp_list = temp_list->next_user;
        count ++;
    }
    
    return count;
}

void remove_linked_list(char *search_str)
{
    USERDATA *prev_node = NULL;
    USERDATA *temp_node = NULL;

    prev_node = search_linked_list_to_remove(search_str);
    
    temp_node = prev_node->next_user;
    printf("Delete data: [%p] %s %s %d %p\n",temp_node, temp_node->name, temp_node->phone_number, temp_node->age, temp_node->next_user);
    prev_node->next_user = prev_node->next_user->next_user;
    temp_node->next_user->prev_user = prev_node;
    
    free(temp_node);
}