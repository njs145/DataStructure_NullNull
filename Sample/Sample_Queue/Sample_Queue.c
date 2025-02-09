#include "Sample_Queue.h"

void queue_test(void)
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

    util_check_success(queue_init(&q, 11));

    util_check_success(queue_enqueue(q, enqueue_ascending_data, 10));

    util_check_success(queue_dequeue(q, dequeue_data, 3));
    util_print_data(dequeue_data, 3);

    util_check_success(queue_dequeue(q, dequeue_data, 3));
    util_print_data(dequeue_data, 3);

    util_check_success(queue_enqueue(q, enqueue_ascending_data, 3));
    util_check_success(queue_enqueue(q, enqueue_ascending_data, 3));

    util_check_success(queue_dequeue(q, dequeue_data, 6));
    util_print_data(dequeue_data, 6);

    queue_release(q);
}