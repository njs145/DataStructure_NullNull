#include <stdio.h>
#include <assert.h>
#include "Sample_LinkedList.h"
#include "Sample_Queue.h"
#include "UI.h"

exec_test_t data_structure_exec_func[MAX_OF_TEST + 1] = {
    [TITLE]  = {"Data Structure TEST (By JinSong)", NULL},
    [TEST_1] = {"[1]New", Sample_LinkedList_add_list},
    [TEST_2] = {"[2]Search", Sample_LinkedList_search},
    [TEST_3] = {"[3]Search age", Sample_LinkedList_search_list_by_age},
    [TEST_4] = {"[4]Print", Sample_LinkedList_print_list},
    [TEST_5] = {"[5]Remove", NULL}
};

int main(void)
{   
    Sample_LinkedList_init_linked();
    UI_event_loop_exec_database(data_structure_exec_func, sizeof(data_structure_exec_func)/sizeof(exec_test_t));
    return 0;
}