#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>

typedef struct USERDATA
{
    char name[32];
    char phone_number[32];
    __uint32_t age;
    struct USERDATA* next_user;
    struct USERDATA* prev_user;
}USERDATA;

#endif