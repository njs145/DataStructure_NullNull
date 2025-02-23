#include "Sample_LinkedList.h"

void Sample_LinkedList_init_linked(void (*print_func)(void *), void (*update_index)(linkedlist_t *list),
                                   node_t* (*search_method)(linkedlist_t *, char*), size_t data_size)
{
    init_linked_list(print_func, update_index, data_size);
}

// void Sample_LinkedList_remove_list(void)
// {
//     char name[256];

//     Sample_LinkedList_print_list();
//     printf("\n");
//     printf("Name: ");
//     scanf("%s",name);

//     remove_linked_list(name);
// }

// void Sample_LinkedList_search(void)
// {
//     char name[50] = { 0 };
//     sizeof(USERDATA);
//     USERDATA *search_user = NULL;

//     printf("type name: ");
//     scanf("%s", name);
//     search_user = search_linked_list(name);

//     printf("name: %s phone: %s, age: %d\n", search_user->name, search_user->phone_number, search_user->age);
// }

// void delete_linkedlist_test(void)
// {
//     linkedlist_t *list;
//     init_linked_list(list);

//     add_linked_list("가나다", "010-1111-1111", 20);
//     add_linked_list("나다라", "010-2222-2222", 21);
//     add_linked_list("다라마", "010-3333-3333", 22);
//     print_linked_list();
//     printf("\n");

//     remove_linked_list("나다라");
//     print_linked_list();
//     printf("\n");
//     add_linked_list("나다라", "010-2222-2222", 21);
//     print_linked_list();
//     printf("\n");

//     remove_linked_list("가나다");
//     print_linked_list();
//     printf("\n");
//     add_linked_list("가나다", "010-1111-1111", 20);
//     print_linked_list();
//     printf("\n");

//     remove_linked_list("다라마");
//     print_linked_list();
//     printf("\n");
//     add_linked_list("다라마", "010-3333-3333", 22);
//     print_linked_list();
//     printf("\n");
// }