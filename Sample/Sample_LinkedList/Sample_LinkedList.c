#include "Sample_LinkedList.h"

void Sample_LinkedList_search_list_by_age(void)
{
    __uint32_t *age_index = NULL;
    __uint32_t node_count;
    __uint32_t count = 0;
    __uint32_t min_age, max_age;
    USERDATA **user_data = NULL;
    USERDATA *last_user_data = NULL;

    printf("나이를 입력하세요[최대 최소]: ");
    scanf("%d", &min_age);
    scanf("%d", &max_age);

    node_count = get_list_count();
    user_data = malloc(node_count * sizeof(USERDATA *));
    last_user_data = get_last_list();
    age_index = LinkedList_get_age_index();

    user_data[0] = get_first_list();

    for(count = 0; count < (node_count - 1); count ++)
    {
        user_data[count +1] = user_data[count]->next_user;
    }

    // printf("%d %d %d %d %d %d ",user_data[0]->age, user_data[1]->age, user_data[2]->age, user_data[3]->age, user_data[4]->age, user_data[5]->age);

    count = 0;
    while((user_data[age_index[count]]->age <= max_age) && (count < node_count))
    {
        if((user_data[age_index[count]]->age >= min_age) || (user_data[age_index[count]]->age >= max_age))
        {
            printf("name: %s phone: %s, age: %d\n", user_data[age_index[count]]->name, user_data[age_index[count]]->phone_number, user_data[age_index[count]]->age);
        }

        count ++;
    }

    free(user_data);
}

void add_dummy_list(void)
{
    add_linked_list("가나다", "010-1111-1111", 24);
    add_linked_list("나다라", "010-2222-2222", 25);
    add_linked_list("다라마", "010-3333-3333", 22);
    add_linked_list("라마바", "010-4444-4444", 23);
    add_linked_list("마바사", "010-5555-5555", 20);
    add_linked_list("바사아", "010-6666-6666", 21);
}

void Sample_LinkedList_init_linked(void)
{
    init_linked_list();
}

void Sample_LinkedList_add_list(void)
{
    printf("Enter user information [ex: jinsong 01012341234 99]\n\n");
    
    add_linked_list("가나다", "010-1111-1111", 23);
    add_linked_list("나다라", "010-2222-2222", 24);
    add_linked_list("다라마", "010-3333-3333", 25);
    add_linked_list("라마바", "010-4444-4444", 20);
    add_linked_list("마바사", "010-5555-5555", 21);
    add_linked_list("바사아", "010-6666-6666", 22);
    add_linked_list("나나나", "010-6666-6666", 22);
    add_linked_list("다다다", "010-6666-6666", 22);
    add_linked_list("라라라", "010-6666-6666", 22);
    add_linked_list("나나나", "010-6666-6666", 22);
}

void Sample_LinkedList_remove_list(void)
{
    char name[256];

    Sample_LinkedList_print_list();
    printf("\n");
    printf("Name: ");
    scanf("%s",name);

    remove_linked_list(name);
}

void Sample_LinkedList_print_list(void)
{
    print_linked_list();
}

void Sample_LinkedList_search(void)
{
    char name[50] = { 0 };
    sizeof(USERDATA);
    USERDATA *search_user = NULL;

    printf("type name: ");
    scanf("%s", name);
    search_user = search_linked_list(name);

    printf("name: %s phone: %s, age: %d\n", search_user->name, search_user->phone_number, search_user->age);
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