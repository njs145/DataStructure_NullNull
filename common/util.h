#ifndef __UTIL_H
#define __UTIL_H

#include <stdio.h>

extern void util_print_data(__uint8_t *data, __uint32_t size);
extern void util_check_success(int err);
#endif