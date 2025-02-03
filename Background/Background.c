#include "Background.h"
#include "common.h"

void Simple_LinkedList_App(void)
{
    USERDATA user_DB[MAX_ADDRESS_NUM];
    __uint8_t user_count = 0;
    __uint8_t remaind_retry;
    char select;
    while(1)
    {
        if(user_count >= MAX_ADDRESS_NUM)
        {
            printf("더이상 저장 할 수 없습니다. 프로그램을 종료 합니다.\n");
            break;
        }

        printf("<회원 가입>\n");
        printf("회원 정보를 입력하세요 [이름, 휴대폰 번호, 나이]\n");

        printf("이름: ");
        scanf("%s", user_DB[user_count].name);

        printf("휴대폰번호: ");
        scanf("%s",user_DB[user_count].phone_number);

        printf("나이: ");
        scanf("%d",&user_DB[user_count].age);

        printf("입력하신 정보가 맞으십니까? [맞으면 y를 누르시고 아니면 x를 눌러 다시 기입하세요.]\n");
        printf("이름: %s, 번호: %s, 나이:%d\n", user_DB[user_count].name, user_DB[user_count].phone_number, user_DB[user_count].age);

        for(remaind_retry = MAX_ERROR_RETRY; remaind_retry > 0;)
        {
            printf("select: ");
            scanf(" %c",&select);
            if(select == 'x')
            {
                break;
            }
            else if(select == 'y')
            {
                user_count ++;
                break;
            }
            else
            {
                remaind_retry --;
                printf("재 입력 하세요 y와 x만 입력할 수 있습니다. [재 입력 가능 횟수: %d]",remaind_retry);
            }
        }
        printf("\n");
    }

    for(user_count = 0; user_count < (MAX_ADDRESS_NUM - 1); user_count ++)
    {
        user_DB[user_count].next_user = &user_DB[user_count + 1];
    }

    printf("회원1 이름: %s\n",user_DB[0].name);
    printf("회원2 이름: %s\n",user_DB[0].next_user->name);
    printf("회원3 이름: %s\n",user_DB[0].next_user->next_user->name);
    printf("회원4 이름: %s\n",user_DB[0].next_user->next_user->next_user->name);
}