#include "DBMS.h"

#define MAX_OF_NODE     256U

static __uint32_t g_age_index[MAX_OF_NODE];
static char *file_path;

typedef struct user_info_data user_info_data_t; 
struct __attribute__((packed)) user_info_data
{
    char name[20];
    char phone_number[20];
    __uint32_t age;
};

void DBMS_add_user(void *list);
void DBMS_search_user_by_name(void *list);
void DBMS_search_user_by_age(void *list);
void DBMS_print_all_user_information(void *list);
void DBMS_search_remove_user_by_name(void *list);
void DBMS_save_file_node_data(void *list, int file);
void DBMS_load_file_node_data(void *list, char *path);

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
    char input;
    user_info_data_t user_data;
    linkedlist_t *target_list = (linkedlist_t *)list;
    printf("Enter user information [ex: jinsong 01012341234 99]\n\n");

    printf("name: ");
    scanf("%s", user_data.name);
    
    printf("phone number: ");
    scanf("%s", user_data.phone_number);

    printf("age: ");
    scanf("%d",  &user_data.age);

    printf("name: %s phone number: %s age: %d\n",user_data.name, user_data.phone_number, user_data.age);
    
    add_linked_list(target_list, (void *)&(user_data));

    printf("Do you want to save? (y/n)");
    scanf(" %c",&input);
    if(input == 'y')
    {
        int file = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(file != 0)
        {
            printf("save file\n");
            DBMS_save_file_node_data((void *)target_list, file);      
        }
        else
        {
            printf("파일을 열수 없습니다.\n");
            assert(file != 0);
        }
    }

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
        target_list->hadler->print_node((void *)(node->data));

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
    target_list->hadler->print_node((void *)(search_user->data));
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
    char input;
    linkedlist_t* target_list = NULL;

    /* transfer type to list type */
    target_list = (linkedlist_t *)list;

    /* print all user information */
    DBMS_print_all_user_information(list);
    printf("\n");

    /* get name data from standard input */
    printf("Name: ");
    scanf("%s",name);

    /* remove selected node */
    remove_linked_list(target_list, name);

    printf("Do you want to save? (y/n)");
    scanf(" %c",&input);
    if(input == 'y')
    {
        int file = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(file != 0)
        {
            printf("save file\n");
            DBMS_save_file_node_data((void *)target_list, file);          
        }
        else
        {
            printf("파일을 열수 없습니다.\n");
            assert(file != 0);
        }
    }
}

linkedlist_t* DBMS_LinkedList_init_linked(list_handler_t *handler, size_t data_size)
{
    linkedlist_t * target_list = NULL;
    
    /* init list */
    target_list = init_linked_list(handler, data_size);
    return target_list;
}

void DBMS_save_file_node_data(void *list, int file)
{
    linkedlist_t *target_list = NULL;
    node_t *node = NULL;
    __uint8_t *data = NULL;
    __uint32_t count = 0;

    if(file != 0)
    {
        target_list = (linkedlist_t *)list;
        node = target_list->head->next;

        /* To prevent fragmented memory allocation, the aligned_alloc function is used. */
        data = aligned_alloc(alignof(user_info_data_t),get_list_count(list) * sizeof(user_info_data_t));

        if(data != NULL)
        {
            /* copy all data to buffer */
            while(node != target_list->tail)
            {
                memcpy(&(((user_info_data_t *)(data))[count].name), &(((user_info_data_t *)(node->data))->name), sizeof((((user_info_data_t *)(node->data))->name)));
                memcpy(&(((user_info_data_t *)(data))[count].phone_number), &(((user_info_data_t *)(node->data))->phone_number), sizeof((((user_info_data_t *)(node->data))->phone_number)));
                ((user_info_data_t *)(data))[count].age = ((user_info_data_t *)(node->data))->age;

                count ++;
                node = node->next;
            }
        }
        else
        {
            printf("data alloc fail!\n");
            assert(data != NULL);
        }
        
        /* save data */
        write(file, data, (get_list_count(list) * sizeof(user_info_data_t)));

        close(file);
    }
    else
    {
        printf("invaild file!\n");
        assert(file != 0);
    }
}

void DBMS_load_file_node_data(void *list, char *path)
{
    __uint8_t *data = NULL;
    linkedlist_t *target_list = NULL;
    struct stat file_stat;
    user_info_data_t *target_data = NULL;
    node_t *node = NULL;
    size_t node_count;
    __uint32_t i;
    int error;

    target_list = (linkedlist_t *)list;
    int file = open(path, O_RDONLY, 0644);
    if(file != 0)
    {
        /* To get file's information such like file size, fstat function is used */
        error = fstat(file, &file_stat);        
        if(error != -1)
        {
            /* To prevent fragmented memory allocation, the aligned_alloc function is used. */
            data = aligned_alloc(alignof(user_info_data_t), file_stat.st_size);
            read(file, (void *)data, file_stat.st_size);
        }
        else
        {
            printf("fstat error\n");
            assert(error != -1);
        }

        /* transfer data type to user data type */
        target_data = (user_info_data_t *)data;
        node = target_list->head->next;

        node_count = (file_stat.st_size)/sizeof(user_info_data_t);

        /* add loaded data to node */
        for(i = 0; i < node_count; i ++)
        {
            add_linked_list(target_list, (void *)(&target_data[i]));
        }

        close(file);

    }
    else
    {
        printf("invaild file!\n");
        assert(file != 0);
    }
}

void DBMS_run_DBMS(void)
{
    linkedlist_t *list = NULL;

    list_handler_t list_handler = {
        DBMS_add_data,
        DBMS_print_user_information,
        DBMS_update_index_age,
        DBMS_search_by_name,
    };

    /* define path */
    file_path = "node_data.bin";
    
    /* get new list */
    list = DBMS_LinkedList_init_linked(&list_handler, sizeof(user_info_data_t));
    DBMS_load_file_node_data((void *)list, file_path);
    UI_event_loop_exec_database((void *)list, data_structure_exec_func, sizeof(data_structure_exec_func)/sizeof(exec_test_t));
}