#include "DBMS.h"

#define MAX_OF_NODE     256U

static __uint32_t g_age_index[MAX_OF_NODE];

typedef struct user_info_data user_info_data_t; 
struct user_info_data
{
    char *name;
    char *phone_number;
    __uint32_t age;
};

void DBMS_add_user(void *list);
void DBMS_search_user_by_name(void *list);
void DBMS_search_user_by_age(void *list);
void DBMS_print_all_user_information(void *list);
void DBMS_search_remove_user_by_name(void *list);

exec_test_t data_structure_exec_func[MAX_OF_TEST + 1] = {
    [TITLE]  = {"Data Structure TEST (By JinSong)", NULL},
    [TEST_1] = {"[1]New", DBMS_add_user},
    [TEST_2] = {"[2]Search", DBMS_search_user_by_name},
    [TEST_3] = {"[3]Search age", DBMS_search_user_by_age},
    [TEST_4] = {"[4]Print", DBMS_print_all_user_information},
    [TEST_5] = {"[5]Remove", DBMS_search_remove_user_by_name},
};

__uint32_t *DBMS_get_age_index(void)
{
    return g_age_index;
}

void DBMS_add_user(void *list)
{
    linkedlist_t *target_list = (linkedlist_t *)list;
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
    
    add_linked_list(target_list, (void *)&(user[0]));
    add_linked_list(target_list, (void *)&(user[1]));
    add_linked_list(target_list, (void *)&(user[2]));
    add_linked_list(target_list, (void *)&(user[3]));
    add_linked_list(target_list, (void *)&(user[4]));
    add_linked_list(target_list, (void *)&(user[5]));
    add_linked_list(target_list, (void *)&(user[6]));
    add_linked_list(target_list, (void *)&(user[7]));
    add_linked_list(target_list, (void *)&(user[8]));
    add_linked_list(target_list, (void *)&(user[9]));
}

void DBMS_print_user_information(void *user_info)
{
    user_info_data_t* user = (user_info_data_t *)user_info;
    printf("name: %s, phone number: %s, age: %d\n",user->name, user->phone_number, user->age);
}

void* DBMS_add_data(void *data)
{
    user_info_data_t *target_data = NULL;
    
    /* alloc data of memory */
    target_data = malloc(sizeof(user_info_data_t));
    /* copy data to allock memory */
    memcpy(target_data, (user_info_data_t *)data, sizeof(user_info_data_t));

    return (void *)target_data;
}

void DBMS_update_index_age(void *list)
{
    linkedlist_t *target_list = NULL;
    node_t *cur_node;
    node_t **node_index = NULL;
    __uint32_t *index = g_age_index;
    __uint32_t *age_data = NULL;
    __uint32_t count_node;
    __uint32_t i, j, temp_index, temp_age;

    /* transfer type to list type */
    target_list = (linkedlist_t *)list;

    /* get node count */
    count_node = get_list_count(target_list);

    /* allocate node index */
    node_index = malloc(count_node * sizeof(node_t *)); /* this index make to align by age  */
    age_data = malloc(count_node * sizeof(__uint32_t *)); 

    /* node init index */
    cur_node = get_first_list(target_list);
    for(i = 0; i < count_node; i ++)
    {
        node_index[i] = cur_node;
        cur_node = cur_node->next;

        index[i] = i;
        age_data[i] = ((user_info_data_t *)(node_index[i]->data))->age;
    }

    /* align age by ascending */
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

    /* free temp memory */
    free(node_index);
    free(age_data);
}

node_t* DBMS_search_by_name(void *list, char *name)
{
    linkedlist_t *target_list = NULL;
    node_t *target_node = NULL;

    /* transfer type to list type */
    target_list = (linkedlist_t *)list;
    target_node = target_list->head->next;
    
    /* search node by name */
    while(strcmp(name, ((user_info_data_t *)(target_node->data))->name) != 0)
    {
        if(((user_info_data_t *)(target_node->data))->name == NULL)
        {
            printf("%s not found\n",name);
            return NULL;
        }
        else
        {
            target_node = target_node->next;
        }
    }

    return target_node;
}

void DBMS_print_all_user_information(void *list)
{
    linkedlist_t * target_list = NULL;
    node_t *node = NULL;

    /* transfer type to list type */
    target_list = (linkedlist_t *)list;
    node = target_list->head->next;

    /* print all information */
    while(node != target_list->tail)
    {
        // DBMS_print_user_information((user_info_data_t*)(node->data));
        target_list->print_node((void *)(node->data));

        node = node->next;
    }
}

void DBMS_search_user_by_name(void *list)
{
    char name[50] = { 0 };
    node_t *search_user = NULL;
    linkedlist_t *target_list = NULL;

    /* transfer type to list type */
    target_list = (linkedlist_t *)list;
    printf("type name: ");

    /* get name data from standard input */
    scanf("%s", name);
    search_user = search_linked_list(target_list, name);


    /* print user information */
    target_list->print_node((void *)(search_user->data));
}

void DBMS_search_user_by_age(void *list)
{
    __uint32_t *age_index = NULL;
    __uint32_t node_count;
    __uint32_t count = 0;
    __uint32_t min_age, max_age;
    node_t **user_data = NULL;
    linkedlist_t *target_list = NULL;

    /* transfer type to list type */
    target_list = (linkedlist_t *)list;

    /* get age data from standard input */
    printf("나이를 입력하세요[최대 최소]: ");
    scanf("%d", &min_age);
    scanf("%d", &max_age);

    /* get node count */
    node_count = get_list_count(target_list);

    /* alloc user node index amount of node count */
    user_data = malloc(node_count * sizeof(node_t *));

    /* get age index */
    age_index = DBMS_get_age_index();

    /* get first list */
    user_data[0] = get_first_list(target_list);

    /* allign user node */
    for(count = 0; count < (node_count - 1); count ++)
    {
        user_data[count +1] = user_data[count]->next;
    }
    
    count = 0;
    /* search node by age index */
    while((((user_info_data_t *)(user_data[age_index[count]]->data))->age <= max_age) && (count < node_count))
    {
        if((((user_info_data_t *)(user_data[age_index[count]]->data))->age >= min_age) || ((user_info_data_t *)(user_data[age_index[count]]->data))->age >= max_age)
        {
            printf("name: %s phone: %s, age: %d\n", ((user_info_data_t *)(user_data[age_index[count]]->data))->name, ((user_info_data_t *)(user_data[age_index[count]]->data))->phone_number, ((user_info_data_t *)(user_data[age_index[count]]->data))->age);
        }

        count ++;
    }

    free(user_data);
}

void DBMS_search_remove_user_by_name(void *list)
{
    char name[256];
    linkedlist_t* target_list = NULL;

    /* transfer type to list type */
    target_list = (linkedlist_t *)list;

    /* print all user information */
    DBMS_print_all_user_information(list);
    printf("\n");

    /* get name data from standard input */
    printf("Name: ");
    scanf("%s",name);

    remove_linked_list(target_list, name);
}

linkedlist_t* DBMS_LinkedList_init_linked(void (*print_func)(void *), void* (*add_data)(void *), void (*update_index)(void *),
                                   node_t* (*search_method)(void *, char *), size_t data_size)
{
    linkedlist_t * target_list = NULL;
    
    /* init list */
    target_list = init_linked_list(print_func, add_data, update_index, search_method, data_size);
    return target_list;
}

void DBMS_run_DBMS(void)
{
    linkedlist_t *list = NULL;
    
    /* get new list */
    list = DBMS_LinkedList_init_linked(DBMS_print_user_information, DBMS_add_data, DBMS_update_index_age, DBMS_search_by_name, sizeof(user_info_data_t));
    UI_event_loop_exec_database((void *)list, data_structure_exec_func, sizeof(data_structure_exec_func)/sizeof(exec_test_t));
}