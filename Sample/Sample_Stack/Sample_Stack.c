#ifndef __SAMPLE_STACK_C__
#define __SAMPLE_STACK_C__

#include "Sample_Stack.h"

void stack_test(void)
{
    stack *q;
    err_stack ret;
    __uint8_t *push_ascending_data;
    __uint8_t *push_descending_data;
    __uint8_t *pop_data;

    __uint32_t j;

    push_ascending_data = malloc(TEST_PUSH_DATA_MAX_SIZE);
    push_descending_data = malloc(TEST_PUSH_DATA_MAX_SIZE);
    pop_data = malloc(TEST_PUSH_DATA_MAX_SIZE);

    if((push_ascending_data != NULL) && (push_descending_data != NULL) && (pop_data != NULL))
    {
        for(__uint32_t i = 0; i < TEST_PUSH_DATA_MAX_SIZE; i ++)
        {
            push_ascending_data[i] = i%255;
        }

        j = 0;
        for(__uint32_t i = (TEST_PUSH_DATA_MAX_SIZE -1); i > 0; i --)
        {
            
            push_descending_data[j] = i%256;
            j ++;
        }
    }
    else
    {
        printf("error: test push_ascending_data alloc fail!\n");
        assert(0);
    }

    util_check_success(stack_init(&q, 11));

    util_check_success(stack_push(q, push_ascending_data, 10));

    util_check_success(stack_pop(q, pop_data, 3));
    util_print_data(pop_data, 3);

    util_check_success(stack_pop(q, pop_data, 3));
    util_print_data(pop_data, 3);

    util_check_success(stack_push(q, push_ascending_data, 3));
    util_check_success(stack_push(q, push_ascending_data, 3));

    util_check_success(stack_pop(q, pop_data, 6));
    util_print_data(pop_data, 6);

    stack_release(q);
}

#endif