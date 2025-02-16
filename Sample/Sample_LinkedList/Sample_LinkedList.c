#include "Sample_LinkedList.h"

void add_dummy_list(void)
{
    add_linked_list("가나다", "010-1111-1111", 20);
    add_linked_list("나다라", "010-2222-2222", 21);
    add_linked_list("다라마", "010-3333-3333", 22);
    add_linked_list("라마바", "010-4444-4444", 23);
    add_linked_list("마바사", "010-5555-5555", 24);
    add_linked_list("바사아", "010-6666-6666", 25);
}

void delete_linkedlist_test(void)
{
    init_linked_list();

    add_linked_list("가나다", "010-1111-1111", 20);
    add_linked_list("나다라", "010-2222-2222", 21);
    add_linked_list("다라마", "010-3333-3333", 22);
    print_linked_list();
    printf("\n");

    remove_linked_list("나다라");
    print_linked_list();
    printf("\n");
    add_linked_list("나다라", "010-2222-2222", 21);
    print_linked_list();
    printf("\n");

    remove_linked_list("가나다");
    print_linked_list();
    printf("\n");
    add_linked_list("가나다", "010-1111-1111", 20);
    print_linked_list();
    printf("\n");

    remove_linked_list("다라마");
    print_linked_list();
    printf("\n");
    add_linked_list("다라마", "010-3333-3333", 22);
    print_linked_list();
    printf("\n");
}