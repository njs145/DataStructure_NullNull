#include <stdio.h>
#include <assert.h>
#include "Background.h"
#include "LinkedList.h"
#include "common.h"
#include "UI.h"
#include "Queue.h"
#include "Stack.h"
#include "util.h"

#define TEST_ENQUEUE_DATA_MAX_SIZE  10

static void delete_linkedlist_test(void);
static void queue_test(void);
static void stack_test(void);

exec_test_t data_structure_exec_func[MAX_OF_TEST + 1] = {
    [TITLE]  = {"Data Structure TEST (By JinSong)", NULL},
    [TEST_1] = {"1. Linked List Test", delete_linkedlist_test},
    [TEST_2] = {"2. Queue Test", queue_test},
    [TEST_3] = {"3. Stack Test", stack_test}
};

static void add_dummy_list(void)
{
    add_linked_list("가나다", "010-1111-1111", 20);
    add_linked_list("나다라", "010-2222-2222", 21);
    add_linked_list("다라마", "010-3333-3333", 22);
    add_linked_list("라마바", "010-4444-4444", 23);
    add_linked_list("마바사", "010-5555-5555", 24);
    add_linked_list("바사아", "010-6666-6666", 25);
}

static void delete_linkedlist_test(void)
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

static void queue_test(void)
{
    queue *q;
    err_queue ret;
    __uint8_t *enqueue_ascending_data;
    __uint8_t *enqueue_descending_data;
    __uint8_t *dequeue_data;

    __uint32_t j;

    enqueue_ascending_data = malloc(TEST_ENQUEUE_DATA_MAX_SIZE);
    enqueue_descending_data = malloc(TEST_ENQUEUE_DATA_MAX_SIZE);
    dequeue_data = malloc(TEST_ENQUEUE_DATA_MAX_SIZE);

    if((enqueue_ascending_data != NULL) && (enqueue_descending_data != NULL) && (dequeue_data != NULL))
    {
        for(__uint32_t i = 0; i < TEST_ENQUEUE_DATA_MAX_SIZE; i ++)
        {
            enqueue_ascending_data[i] = i%255;
        }

        j = 0;
        for(__uint32_t i = (TEST_ENQUEUE_DATA_MAX_SIZE -1); i > 0; i --)
        {
            
            enqueue_descending_data[j] = i%256;
            j ++;
        }
    }
    else
    {
        printf("error: test enqueue_ascending_data alloc fail!\n");
        assert(0);
    }

    util_check_success(queue_init(&q, 10));

    util_check_success(queue_enqueue(q, enqueue_ascending_data, 10));

    util_check_success(queue_peek(q, dequeue_data, 3));
    util_print_data(dequeue_data, 3);

    util_check_success(queue_peek(q, dequeue_data, 3));
    util_print_data(dequeue_data, 3);

    util_check_success(queue_peek(q, dequeue_data, 3));
    util_print_data(dequeue_data, 3);

    queue_release(q);
}

static void stack_test(void)
{

}

int main(void)
{   
    UI_event_loop_exec_test(data_structure_exec_func, sizeof(data_structure_exec_func)/sizeof(exec_test_t));
    return 0;
}