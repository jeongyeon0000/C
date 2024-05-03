#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int* roto;
void my_number(int n);
void result(int n);
int main(void)
{
    while (1)
    {
        roto = NULL;
        int i, j, n, save;
        char k;

        printf("뽑을 횟수를 입력하세요: ");
        scanf("%d", &n);

        if (n <= 0)
        {
            printf("(경고) 유효한 횟수를 입력해주세요.\n");
            continue;
        }
    turn:
        roto = (int*)malloc(sizeof(int) * 6 * n);
        for (i = 0; i < 6 * n; i++)
        {
            if (i % 6 == 0) {
                printf("로또 번호 6개를 입력하세요.(1~45): ");
            }
            scanf("%d", &roto[i]);
        }
        for (i = 0; i < 6 * n; i++)
        {
            if (roto[i] >= 46 || roto[i] < 1)
            {
                printf("(경고) 범위에 맞는 번호를 입력해주세요.\n");
                goto turn;
            }
            for (j = 6 * (i / 6); j < i; j++)
            {
                if (roto[i] == roto[j])
                {
                    printf("(경고) 중복된 번호는 입력할 수 없습니다.\n");
                    goto turn;
                }
            }
        }
        do
        {
            printf("\nl: 나의 로또번호 , f: 당첨결과, r: 다시 시작, x: 종료\n원하시는 키를 입력하세요: ");
            scanf(" %c", &k);
            save = 1;
            if (k == 'l' || k == 'L') {
                my_number(n);
            }

            else if (k == 'f' || k == 'F') {
                result(n);
            }
            else if (k == 'r' || k == 'R') {
                free(roto);
                roto = NULL;
                save = 0;
            }

            else if (k == 'x' || k == 'X') {
                printf("종료합니다.\n");
                if (roto != NULL)
                    free(roto);
                return 0;
            }

            else if ((k >= 65 && k <= 90) || (k >= 97 && k <= 126)) {
                printf("잘못된 키를 누르셨습니다.\n");
            }
            else {
                printf("존재하지 않습니다. \n(경고) 다시 입력해주세요.\n");
                goto turn;
            }
        } while (save);

        if (roto != NULL)
            free(roto);
    }

    return 0;
}
void my_number(int n)
{
    int i;
    for (i = 0; i < 6 * n; i++)
    {
        if (i % 6 == 0)
        {
            if (i > 0)
                printf("\n");
            printf("%d번: ", i / 6 + 1);
        }
        printf("%d ", roto[i]);
    }
    printf("\n");
}
void result(int n)
{
    int robo[6] = { 0 };
    int i, cnt = 0;
    srand((unsigned int)time(NULL));

    for (i = 0; i < 6; i++)
    {
        robo[i] = rand() % 45 + 1;
    }

    for (i = 0; i < 6 * n; i++)
    {
        if (roto[i] == robo[i % 6])
            cnt++;

        if (i % 6 == 5)
        {
            printf("%d번: ", i / 6 + 1);

            if (cnt == 6)
                printf("당첨 되었습니다!\n");
            else if (cnt == 0)
                printf("꽝 입니다.\n");
            else
                printf("6개중 %d개 맞았습니다.\n", cnt);

            cnt = 0;
        }
    }
}
