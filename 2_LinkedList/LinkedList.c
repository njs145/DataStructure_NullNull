#include "LinkedList.h"

USERDATA    g_USERDATA;

void print_linked_list(void)
{
    USERDATA *temp_data = NULL;
    
    temp_data = g_USERDATA.next_user;
    while(temp_data != NULL)
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
    if(add_node != NULL)
    {
        temp_node = &g_USERDATA;
        strcpy(add_node->name, name);
        strcpy(add_node->phone_number, phone_number);
        add_node->age = age;
    #if (ADD_TYPE == ADD_TYPE_HEAD)
        if(temp_node->next_user != NULL)
        {
            add_node->next_user = temp_node->next_user;    
        }
        temp_node->next_user = add_node;
    
    #else
        if(temp_node->next_user != NULL)
        {
            while(temp_node->next_user != NULL)
            {
                temp_node = temp_node->next_user;
            }
        }
        temp_node->next_user = add_node;
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

    delete_data = g_USERDATA.next_user;
    g_USERDATA.next_user = NULL;

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
    USERDATA *search_point = g_USERDATA.next_user;

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