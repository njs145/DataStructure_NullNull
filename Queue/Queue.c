#include "Queue.h"

static err_queue queue_is_overrun(queue *pt_queue, __uint32_t size)
{
    err_queue ret;
    __uint32_t front, rear, max_size;

    if(pt_queue != NULL)
    {
        front = pt_queue->front;
        rear = pt_queue->rear;
        max_size = pt_queue->max_size;
        if((max_size - (rear % max_size) - (front % max_size)) >= size)
        {
            ret = err_queue_success;
        }
        else
        {
            ret = err_queue_overrun;
        }
    }
    else
    {
        ret = err_queue_invalid_queue;
    }

    return ret;
}

static err_queue queue_is_underrun(queue *pt_queue, __uint32_t size)
{
    err_queue ret;
    __uint32_t front, rear, max_size;

    if(pt_queue != NULL)
    {
        front = pt_queue->front;
        rear = pt_queue->rear;
        max_size = pt_queue->max_size;
        if(((rear - 1) % max_size) - (front % max_size) + 1 >= size)
        {
            ret = err_queue_success;
        }
        else
        {
            ret = err_queue_underrun;
        }
    }
    else
    {
        ret = err_queue_invalid_queue;
    }

    return ret; 
}

static err_queue queue_is_empty(queue *pt_queue)
{
    err_queue ret;
    __uint32_t front, rear;

    if(pt_queue != NULL)
    {
        front = pt_queue->front;
        rear = pt_queue->rear;

        if(front == rear)
        {
            ret = err_queue_empty;
        }
        else
        {
            ret = err_queue_success;
        }
    }
    else
    {
        ret = err_queue_invalid_queue;
    }

    return ret;
}

static err_queue queue_is_full(queue *pt_queue)
{
    err_queue ret;
    __uint32_t front, rear, max_size;

    if(pt_queue != NULL)
    {
        front = pt_queue->front;
        rear = pt_queue->rear;
        max_size = pt_queue->max_size;
        if((front % max_size) == ((rear + 1) % max_size))
        {
            ret = err_queue_full;
        }
        else
        {
            ret = err_queue_success;
        }
    }
    else
    {
        ret = err_queue_invalid_queue;
    }

    return ret;
}

err_queue queue_init(queue **pt_queue, __uint32_t size)
{
    err_queue ret;
    queue *new_queue;

    new_queue = (queue *)malloc(sizeof(queue));
    if(new_queue != NULL)
    {
        new_queue->front = 0;
        new_queue->rear = 0;
        new_queue->max_size = size;
        new_queue->data = (__uint8_t *)malloc(size);
        
        if(new_queue->data != NULL)
        {
            *pt_queue = new_queue;
            ret = err_queue_success;
        }
        else
        {
            ret = err_queue_data_alloc_fail;
        }
    }
    else
    {
        ret = err_queue_alloc_fail;
    }

    return ret;
}

err_queue queue_enqueue(queue *pt_queue, __uint8_t *data, __uint32_t size)
{
    err_queue ret;
    __uint32_t front, rear, max_size;
    __uint32_t current_rear_point;
    __int32_t carry_size;

    if(pt_queue != NULL)
    {
        ret = queue_is_full(pt_queue);
        if(ret != err_queue_full)
        {
            ret = queue_is_overrun(pt_queue, size);
            if(ret != err_queue_overrun)
            {
                front = pt_queue->front;
                rear = pt_queue->rear;
                max_size = pt_queue->max_size;

                current_rear_point = rear % max_size;
                carry_size = (current_rear_point + size) - max_size;
                if(carry_size > 0)
                {
                    memcpy(&pt_queue->data[current_rear_point], data, (size - carry_size));
                    memcpy(&pt_queue->data, &data[(size - carry_size)],  carry_size);    
                }
                else
                {
                    memcpy(&pt_queue->data[current_rear_point], data, size);
                }
                pt_queue->rear += size;
            }
        }
    }
    else
    {
        ret = err_queue_invalid_queue;
    }

    printf("[enquque] Current queue info: front: %d, rear: %d\n",(pt_queue->front % max_size), (pt_queue->rear % max_size));

    return ret;
}

err_queue queue_dequeue(queue *pt_queue, __uint8_t *data, __uint32_t size)
{
    err_queue ret;
    __uint32_t front, rear, max_size;
    __uint32_t current_front_point;
    __int32_t carry_size;

    if(pt_queue != NULL)
    {
        ret = queue_is_empty(pt_queue);
        if(ret != err_queue_empty)
        {
            ret = queue_is_underrun(pt_queue, size);
            if(ret != err_queue_underrun)
            {
                front = pt_queue->front;
                rear = pt_queue->rear;
                max_size = pt_queue->max_size;

                current_front_point = front % max_size;
                carry_size = (carry_size + size - max_size);
                if(carry_size > 0)
                {
                    memcpy(data, &pt_queue->data[current_front_point], (size - carry_size));
                    memcpy(&data[size - carry_size], pt_queue->data, carry_size);
                    memset(&pt_queue->data[current_front_point], 0, (size - carry_size));
                    memset(pt_queue->data, 0, carry_size);
                }
                else
                {
                    memcpy(data, &pt_queue->data[current_front_point], size);
                    memset(&pt_queue->data[current_front_point], 0, size);
                }
                pt_queue->front += size;
            }
        }
    }
    else
    {
        ret = err_queue_invalid_queue;
    }

    printf("[dequeue] Current queue info: front: %d, rear: %d\n",(pt_queue->front % max_size), (pt_queue->rear % max_size));

    return ret;
}

err_queue queue_peek(queue *pt_queue, __uint8_t *data, __uint32_t size)
{
    err_queue ret;
    __uint32_t front, rear, max_size;
    __uint32_t current_front_point;
    __int32_t carry_size;

    if(pt_queue != NULL)
    {
        ret = queue_is_empty(pt_queue);
        if(ret != err_queue_empty)
        {
            ret = queue_is_underrun(pt_queue, size);
            if(ret != err_queue_underrun)
            {
                front = pt_queue->front;
                rear = pt_queue->rear;
                max_size = pt_queue->max_size;

                current_front_point = front % max_size;
                carry_size = (carry_size + size - max_size);
                if(carry_size > 0)
                {
                    memcpy(data, &pt_queue->data[current_front_point], (size - carry_size));
                    memcpy(&data[size - carry_size], pt_queue->data, carry_size);
                }
                else
                {
                    memcpy(data, &pt_queue->data[current_front_point], size);
                }
            }
        }
    }
    else
    {
        ret = err_queue_invalid_queue;
    }

    printf("[dequeue] Current queue info: front: %d, rear: %d\n",(pt_queue->front % max_size), (pt_queue->rear % max_size));

    return ret;
}

err_queue queue_release(queue *pt_queue)
{
    err_queue ret;

    if(pt_queue != NULL)
    {
        free(pt_queue->data);
        if(pt_queue == NULL)
        {
            free(pt_queue);
            if(pt_queue == NULL)
            {
                ret = err_queue_success;
            }
            else
            {
                ret = err_queue_free_fail;
            }
        }
        else
        {
            ret = err_queue_data_free_fail;
        }
    }
    else
    {
        ret = err_queue_invalid_queue;
    }
    return ret;
}

void queue_err_handler(err_queue err)
{
    switch(err)
    {
        case err_queue_alloc_fail:
            printf("err_queue_alloc_fail\n");
        break;

        case err_queue_invalid_queue:
            printf("err_queue_invalid_queue\n");
        break;

        case err_queue_empty:
            printf("err_queue_empty\n");
        break;

        case err_queue_full:
            printf("err_queue_full\n");
        break;

        case err_queue_overrun:
            printf("err_queue_overrun\n");
        break;

        case err_queue_underrun:
            printf("err_queue_underrun\n");
        break;

        case err_queue_free_fail:
            printf("err_queue_free_fail\n");
        break;

        case err_queue_data_free_fail:
            printf("err_queue_data_free_fail\n");
        break;

        default:
            
        break;
    }
    if(err != err_queue_success)
    {
        assert(0);
    }
}