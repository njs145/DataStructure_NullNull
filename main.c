#include <stdio.h>
#include <assert.h>
#include "Sample_LinkedList.h"
#include "Sample_Queue.h"
#include "UI.h"

exec_test_t data_structure_exec_func[MAX_OF_TEST + 1] = {
    [TITLE]  = {"Data Structure TEST (By JinSong)", NULL},
    [TEST_1] = {"1. Linked List Test", delete_linkedlist_test},
    [TEST_2] = {"2. Queue Test", queue_test}
};

int main(void)
{   
    UI_event_loop_exec_test(data_structure_exec_func, sizeof(data_structure_exec_func)/sizeof(exec_test_t));
    return 0;
}