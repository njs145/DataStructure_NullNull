#include <stdio.h>
#include <string.h>

#define TITLE_SIDE_PADDING_COUNT    20U

#define TITLE           0U
#define TEST_1          1U
#define TEST_2          2U
#define TEST_3          3U
#define TEST_4          4U
#define TEST_5          5U
#define TEST_6          5U
#define MAX_OF_TEST     TEST_5



void (*exec_func)(void);

typedef struct exec_test
{
    char *test_name;
    void (*exec_func)(void);
}exec_test_t;

extern void UI_print_manu_title(char *title);
extern void UI_event_loop_exec_test(exec_test_t *exec_test, __uint32_t test_num);