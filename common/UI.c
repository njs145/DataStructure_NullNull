#ifndef __UI_C
#define __UI_C

#include "UI.h"

static __uint32_t line_len = 0;

static void UI_print_side_padding(__uint32_t padding_size)
{
    __uint32_t count;
    for(count = 0; count < padding_size; count ++)
    {
        printf(" ");
    }
}

static void UI_print_line(__uint32_t line_len, char design_line)
{
    __uint32_t count;
    for(count = 0; count < line_len; count ++)
    {
        printf("%c",design_line);
    }
}

void UI_print_manu_title(char *title)
{
    size_t title_size;
    __uint32_t count;
    
    /* measure title size */
    title_size = strlen(title);
    line_len = (title_size + (TITLE_SIDE_PADDING_COUNT + 1) * 2);

    /* print top line by '=' */
    UI_print_line((__uint32_t)line_len, '=');
    printf("\n");

    /* print middle line by title */
    printf("#");
    UI_print_side_padding(TITLE_SIDE_PADDING_COUNT);
    printf("%s",title);
    UI_print_side_padding(TITLE_SIDE_PADDING_COUNT);
    printf("#");
    printf("\n");

    /* print bottom line by '=' */
    UI_print_line((__uint32_t)line_len, '=');
    printf("\n");
}

void UI_print_manu(exec_test_t *exec_test, __uint32_t test_num)
{
    __uint32_t count;
    size_t left_len;
    size_t test_name_len;
    char *exit_massage = "0.return to previous manu";

    UI_print_line(line_len, '=');
    for(count = 1; count < test_num; count ++)
    {
        left_len = line_len;
        printf("\n");
        printf("#");
        left_len --;

        UI_print_side_padding(1);
        left_len --;

        test_name_len = strlen(exec_test[count].test_name);
        printf("%s",exec_test[count].test_name);         
        left_len = left_len - test_name_len;

        UI_print_side_padding((left_len - 1));     
        printf("#");
        printf("\n");

        if(count != (test_num -1))
        {
            printf("#");
            UI_print_side_padding((line_len - 2));
            printf("#");     
        }
    }
    
    printf("#");
    UI_print_side_padding((line_len - 2));
    printf("#"); 

    left_len = line_len;
    printf("\n");
    printf("#");
    left_len --;

    UI_print_side_padding(1);
    left_len --;

    test_name_len = strlen(exit_massage);
    printf("%s",exit_massage);         
    left_len = left_len - test_name_len;

    UI_print_side_padding((left_len - 1));     
    printf("#");
    printf("\n");

    UI_print_line(line_len, '=');
    printf("\n");
}

void UI_event_loop_exec_test(void *cookies, exec_test_t *exec_test, __uint32_t test_num)
{
    __uint32_t select;

    do
    {
        printf("\n");
        UI_print_manu_title(exec_test[0].test_name);
        printf("\n");

        UI_print_manu(exec_test, test_num);
        printf("select: ");
        scanf("%d", &select);

        if(select != 0)
        {
            exec_test[select].exec_func(cookies);
        }

    }while(select != 0);
}

void UI_event_loop_exec_database(void *cookies, exec_test_t *exec_test, __uint32_t test_num)
{
    __uint32_t select = 0;
    __uint32_t count;

    do
    {
        /* cursor go to top & screen clear */
        printf("\033[H\033[J");

        printf("\n");
        UI_print_manu_title(exec_test[0].test_name);
        printf("\n");

        /* print menu */
        for(count = 1; count < test_num; count ++)
        {
            printf("%s   ",exec_test[count].test_name);
        }
        printf("[0]Exit   ");
        printf("\n\n");

        if(select != 0)
        {
            if(exec_test[select].exec_func != NULL)
            {
                exec_test[select].exec_func(cookies);
            }
            else
            {
                printf("Can't execute\n");
            }
        }

        printf("\n");
        UI_print_line(line_len,'=');
        printf("\n");
        printf("select: ");
        scanf(" %d",&select);

    } while (select != 0);
    
}

#endif