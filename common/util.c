#ifndef __UTIL_C
#define __UTIL_C

#include "util.h"

void print_data(__uint8_t *data, __uint32_t size)
{
    __uint32_t i, j;
    __uint32_t col_per_num, left_size;

    left_size = size;
    for(i = 0; i <= (size / 16); i ++)
    {
        if((size / 16) > 0)
        {
            col_per_num = 16;
        }
        else
        {
            col_per_num = size % 16;
        }

        for(j = 0; j < col_per_num; j ++)
        {
            printf("0x%02x ",data[(i * 16) + j]);
        }

        left_size -= 16;
        printf("\n");
    }
}

#endif