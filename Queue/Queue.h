#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "common.h"

typedef struct queue
{
    __int32_t front;
    __int32_t rear;
    __uint32_t max_size;
    __uint8_t *data;
}queue;

typedef enum err_queue
{
    err_queue_success = 0,
    err_queue_alloc_fail,
    err_queue_data_alloc_fail,
    err_queue_invalid_queue,
    err_queue_empty,
    err_queue_full,
    err_queue_overrun,
    err_queue_underrun,
    err_queue_free_fail,
    err_queue_data_free_fail
}err_queue;

extern err_queue queue_init(queue **pt_queue, __uint32_t size);
extern err_queue queue_enqueue(queue *pt_queue, __uint8_t *data, __uint32_t size);
extern err_queue queue_dequeue(queue *pt_queue, __uint8_t *data, __uint32_t size);
extern err_queue queue_release(queue *pt_queue);
extern err_queue queue_peek(queue *pt_queue, __uint8_t *data, __uint32_t size);
extern void queue_err_handler(err_queue err);