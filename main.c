#include <stdio.h>
#include <assert.h>
#include "Sample_LinkedList.h"
#include "Sample_Queue.h"
#include "UI.h"

static __uint32_t g_age_index[MAX_OF_NODE];

typedef struct user_info_data user_info_data_t; 
struct user_info_data
{
    char *name;
    char *phone_number;
    __uint32_t age;
};

exec_test_t data_structure_exec_func[MAX_OF_TEST + 1] = {
    [TITLE]  = {"Data Structure TEST (By JinSong)", NULL},
    [TEST_1] = {"[1]New", NULL},
    [TEST_2] = {"[2]Search", NULL},
    [TEST_3] = {"[3]Search age", NULL},
    [TEST_4] = {"[4]Print", NULL},
    [TEST_5] = {"[5]Remove", NULL},
};

void LinkedList_add_list(linkedlist_t *list)
{
    printf("Enter user information [ex: jinsong 01012341234 99]\n\n");

    user_info_data_t user[10] = {
        [0] = {"aaa", "010-1111-1111", 23},
        [1] = {"bbb", "010-2222-2222", 24},
        [2] = {"cas", "010-3333-3333", 25},
        [3] = {"cbs", "010-4444-4444", 20},
        [4] = {"das", "010-5555-5555", 21},
        [5] = {"eas", "010-6666-6666", 22},
        [6] = {"edd", "010-6666-6666", 22},
        [7] = {"fas", "010-6666-6666", 22},
        [8] = {"fff", "010-6666-6666", 22},
        [9] = {"gas", "010-6666-6666", 22}
    };
    
    add_linked_list(list, (void *)&(user[0]));
    add_linked_list(list, (void *)&(user[1]));
    add_linked_list(list, (void *)&(user[2]));
    add_linked_list(list, (void *)&(user[3]));
    add_linked_list(list, (void *)&(user[4]));
    add_linked_list(list, (void *)&(user[5]));
    add_linked_list(list, (void *)&(user[6]));
    add_linked_list(list, (void *)&(user[7]));
    add_linked_list(list, (void *)&(user[8]));
    add_linked_list(list, (void *)&(user[9]));
}

void print_user_information(void *user_info)
{
    user_info_data_t* user = (user_info_data_t *)user_info;
    printf("name: %s, phone number: %s, age: %d\n",user->name, user->phone_number, user->age);
}

__uint32_t *LinkedList_get_age_index(void)
{
    return g_age_index;
}

void LinkedList_update_index_age(linkedlist_t *list)
{
    node_t *cur_node;
    node_t **node_index = NULL;
    __uint32_t *index = g_age_index;
    __uint32_t *age_data = NULL;
    __uint32_t count_node;
    __uint32_t i, j, temp_index, temp_age;

    count_node = get_list_count(list);
    // printf("node count: %d\n",count_node);

    node_index = malloc(count_node * sizeof(node_t *));
    age_data = malloc(count_node * sizeof(__uint32_t *));

    /* node init index */
    cur_node = get_first_list(list);
    for(i = 0; i < count_node; i ++)
    {
        // printf("current name: %s\n",cur_node->name);
        node_index[i] = cur_node;
        cur_node = cur_node->next;

        index[i] = i;
        age_data[i] = ((user_info_data_t *)(node_index[i]->data))->age;
    }

    // printf("%d %d %d %d %d %d \n",index[0], index[1], index[2], index[3], index[4], index[5]);
    for(i = 0; i < count_node; i ++)
    { 
        for(j = i; j < count_node; j ++)
        {
            if(age_data[i] >= age_data[j])
            {
                temp_age = age_data[i];
                temp_index = index[i];

                age_data[i] = age_data[j];
                index[i] = index[j];

                age_data[j] = temp_age;
                index[j] = temp_index;
            }

        }    
    }

    // printf("%d %d %d %d %d %d \n",index[0], index[1], index[2], index[3], index[4], index[5]);
    free(node_index);
    free(age_data);
}

node_t* search_linked_list_to_remove(linkedlist_t *list, char *search_str)
{
    node_t *prev_node = NULL;

    prev_node = list->head;

    while(strcmp(search_str, ((user_info_data_t *)(prev_node->next->data))->name) != 0)
    {
        if(((user_info_data_t *)(prev_node->next->data))->name == NULL)
        {
            printf("%s not found\n",search_str);
            return NULL;
        }
        else
        {
            prev_node = prev_node->next;
        }
    }

    return prev_node;
}

void Sample_LinkedList_search_list_by_age(linkedlist_t *list)
{
    __uint32_t *age_index = NULL;
    __uint32_t node_count;
    __uint32_t count = 0;
    __uint32_t min_age, max_age;
    node_t **user_data = NULL;
    node_t *last_user_data = NULL;

    printf("나이를 입력하세요[최대 최소]: ");
    scanf("%d", &min_age);
    scanf("%d", &max_age);

    node_count = get_list_count(list);
    user_data = malloc(node_count * sizeof(node_t *));
    last_user_data = get_last_list(list);
    age_index = LinkedList_get_age_index();

    user_data[0] = get_first_list(list);

    for(count = 0; count < (node_count - 1); count ++)
    {
        user_data[count +1] = user_data[count]->next;
    }

    // printf("%d %d %d %d %d %d ",user_data[0]->age, user_data[1]->age, user_data[2]->age, user_data[3]->age, user_data[4]->age, user_data[5]->age);

    count = 0;
    while((((user_info_data_t *)(user_data[count]->data))->age <= max_age) && (count < node_count))
    {
        if((((user_info_data_t *)(user_data[count]->data))->age >= min_age) || ((user_info_data_t *)(user_data[count]->data))->age >= max_age)
        {
            printf("name: %s phone: %s, age: %d\n", ((user_info_data_t *)(user_data[count]->data))->name, ((user_info_data_t *)(user_data[count]->data))->phone_number, ((user_info_data_t *)(user_data[count]->data))->age);
        }

        count ++;
    }

    free(user_data);
}

int main(void)
{   
    Sample_LinkedList_init_linked(print_user_information, LinkedList_update_index_age, search_linked_list_to_remove, sizeof(user_info_data_t));
    UI_event_loop_exec_database(data_structure_exec_func, sizeof(data_structure_exec_func)/sizeof(exec_test_t));
    return 0;
}