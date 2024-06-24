#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <math.h> // 제곱을 사용하기 위한 헤더파일
#include<string.h> // strcmp(문자열 비교)를 사용하기위한 헤더파일
#include <windows.h> // 화면 전환 및 색상을 주기 위한 헤더 파일

char input(char* name); // 적금과 예금 중 금융상품을 선택하는 함수이다.
float calculate(char name[], int won, float yijayul, float year); // 계산 방법을 통해 이자를 구하는 함수이다.
float segeum(double* yija); // 세금을 계산하는 함수이다.
char introduce(); // 처음을 시작할 함수로, 설명서와 사용법을 볼 수 있다.
void clear(); // 유효하지 않은 입력들을 비운다.

int main()
{
    int n, save = 1; // 숫자를 입력받을 변수와, 반복문을 통제할 변수이다.
    char name[5]; // 금융 상품의 이름을 담을 배열
    while (save) {
        introduce(); // 처음 시작할 함수를 호출한다.
        system("cls");
        input(name);
        int won; // 금액을 담을 변수
        float yijayul, year; // 이자율, 연 단위의 기간을 담을 변수 선언
        printf("기간을 입력해주세요.(1년 3개월일 경우, 1.25)\n");
        while (scanf("%f", &year) != 1) {
            clear(); // 유효하지 않는 입력을 비우는 함수로, 입력이 필요한 사항이 있을 때마다 호출한다.
            printf("기간을 다시 입력해주세요.\n");
        }
        printf("이율을 입력해주세요.(%% 제외)\n");
        while (scanf("%f", &yijayul) != 1) {
            clear();
            printf("이율을 다시 입력해주세요.\n");
        }
        printf("%s에 넣을 금액을 입력해주세요.(단위 제외)\n", name);
        while (scanf("%d", &won) != 1) {
            clear();
            printf("금액을 다시 입력해주세요.\n");
        }
        yijayul /= 100.0;
        double yija = calculate(name, won, yijayul, year); // 이자를 담을 변수, 안에 이자를 계산하기 위한 함수를 호출한다.
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("고객님께서 받으시는 총 이자는 %.0f원 입니다.\n", yija);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        while (1) {
            printf("숫자 키를 눌러주세요.(다시 시작 : 1  종료 : 0)\n");
            while (scanf("%d", &n) != 1) {
                clear();
                printf("숫자 키를 눌러주세요.(다시 시작 : 1  종료 : 0)\n");
                printf("(다시 시작 : 1  종료 : 0)중 하나의 키를 눌러주세요.\n");
            }
            if (n == 1) {
                save = 1;
                break;
            }
            else if (n == 0) {
                save = 0;
                break;
            }
            else {
                printf("(다시 시작 : 1  종료 : 0)중 하나의 키를 눌러주세요.\n");
            }
        }
    }
    return 0;
}

char input(char* name) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("[이자 계산기] \n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    int n;
    printf("숫자 키를 눌러주세요.(적금 : 1  예금 : 2)\n");
    while (scanf("%d", &n) != 1) {
        clear();
        printf("1 or 2 중 하나의 키를 골라주세요.\n");
        Sleep(700);
        system("cls");
        return input(name);
    }
    if (n == 1) // 선택한 키에 따라, 문자열이 다르게 저장된다.
        strcpy(name, "적금");
    else if (n == 2)
        strcpy(name, "예금");
    else {
        printf("1 or 2 중 하나의 키를 골라주세요.\n");
        Sleep(700);
        system("cls");
        return input(name);
    }
    return n;
}

float calculate(char name[], int won, float yijayul, float year) {
    double yija = 0;
    int n;
    if (strcmp(name, "적금") == 0)
        printf("숫자 키를 눌러주세요.(단리 : 1  월복리 : 2)\n");
    else
        printf("숫자 키를 눌러주세요.(단리 : 1  월복리 : 2  연복리 : 3)\n");

    while (scanf("%d", &n) != 1) {
        clear();
        if (strcmp(name, "적금") == 0)
            printf("1 or 2 중 하나의 키를 골라주세요.\n");
        else if (strcmp(name, "예금") == 0)
            printf("1 or 2 or 3 중 하나의 키를 골라주세요.\n");
        return calculate(name, won, yijayul, year);
    }

    if (n == 1) // 단리식 계산방법
    {
        if (strcmp(name, "적금") == 0) // 적금과 예금의 계산방식이 다르기 때문에, 조건문을 사용하였다.
            yija = won * (yijayul / 12) * (year * 12 * (year * 12 + 1) / 2);
        else
            yija = won * yijayul * year;
    }
    else if (n == 2) // 월복리식 계산방법
    {
        double res = 0.0;
        if (strcmp(name, "적금") == 0) { // 적금과 예금의 계산방식이 다르기 때문에, 조건문을 사용하였다.
            for (int i = 1; i <= 12; i++) {
                res = won * pow((1 + yijayul / 12.0), i);
                yija += res;
            }
            yija -= won * year * 12;
        }
        else {
            for (int i = 0; i < 12; i++) {
                res = won * (yijayul / 12.0);
                yija += res;
                won += res;
            }
        }
    }
    else if (n == 3 && strcmp(name, "예금") == 0) { // 연복리식 계산방법(적금일 경우 연복리가 가능하지 않다.)
        yija = won * (pow(1 + yijayul, year) - 1);
    }
    else {
        if (strcmp(name, "적금") == 0)
            printf("1 or 2 중 하나의 키를 골라주세요.\n");
        else if (strcmp(name, "예금") == 0)
            printf("1 or 2 or 3 중 하나의 키를 골라주세요.\n");
        return calculate(name, won, yijayul, year);
    }
    return segeum(&yija);
}

float segeum(double* yija) {
    int n;
    float seyul; // 저과세일 경우 그 세율을 입력받아 담을 변수이다.
    printf("숫자 키를 눌러주세요.(과세 : 1  저과세 : 2  비과세 : 3)\n");
    while (scanf("%d", &n) != 1) {
        clear();
        printf("1 or 2 or 3 중 하나의 키를 골라주세요.\n");
        return segeum(yija);
    }
    if (n == 1)
        *yija -= *yija * 0.154;
    else if (n == 2) {
        printf("적용할 세율을 입력해주세요.(%% 제외) : "); // 저과세일 경우 그 세율을 입력받아 계산한다.
        while (scanf("%f", &seyul) != 1) {
            clear();
            printf("1 or 2 or 3 중 하나의 키를 골라주세요.\n");
        }
        *yija -= *yija * (seyul / 100);
    }
    else if (n == 3) {}
    else {
        printf("1 or 2 or 3 중 하나의 키를 골라주세요.\n");
        return segeum(yija);
    }
    return *yija;
}

char introduce() {
    int n;
    system("cls"); // 화면을 지운다.
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("[이자 계산기]\n");
    printf("숫자 키를 입력해주세요.\n(종료 : 0   시작 : 1   계산기 사용법 : 2   용어 설명서 : 3)\n");
    while (scanf("%d", &n) != 1) {
        clear();
        printf("0 or 1 or 2 or 3 중 하나의 키를 골라주세요.\n");
        Sleep(700);
        return introduce();
    }
    if (n == 0) // 종료한다.
        exit(0);
    else if (n == 1) // 계산기를 시작한다.
        return 0;
    else if (n == 2) { // 계산기 사용법을 보여준다.
        printf("\033[2J\033[1;1H");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("[이자 계산기 사용법]\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf("- 숫자키를 통해 조작한다.\n\n");
        printf("1. 예금과 적금 중 하나의 상품을 선택한다.\n");
        printf("2. 기간, 연이율, 금액를 설명에 따라서 입력한다.\n");
        printf("3. 단리와 복리(월복리/연복리) 중 이자를 계산하는 방식을 선택한다.\n");
        printf("4. 과세와 저과세와 비과세 중 세금을 계산하는 방식을 선택한다.\n");
        printf("5. 계산에 결과에 따른 총 이자가 나온다.\n\n");
        printf("숫자 키를 눌러주세요.(계산기 이용 : 1  창 닫기는 숫자키 중 아무거나 눌러주세요.)\n");
        while (scanf("%d", &n) != 1) { // 잘못된 자료형일 경우
            clear();
            printf("계산기 이용(1) 또는 창 닫기: 숫자키 중 하나를 다시 입력해주세요.\n");
        }
        if (n == 1) {
            return 0;
        }
        else if (n != 1) { // 1이 아닌 모든 숫자
            return introduce();
        }
    }
    else if (n == 3) { // 용어 설명서를 보여준다.
        printf("\033[2J\033[1;1H");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("[이자 계산기 용어 설명서]\n\n");
        printf("1. (정기)예금과 (정기)적금 둘이 무슨 차이인가요?\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf("(정기)예금 : 한 번에 목돈을 일정 기간 동안 예치하는 것\n(정기)적금 : 정해진 기간 동안 일정한 금액을 저축해 목돈을 만드는 것\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("2. 적금과 예금의 이자 계산 방식이 왜 다른가요?\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf("적금은 월마다 이자가 붙고, 예금은 대부분 연을 단위로 이자를 붙이기 때문입니다.\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("3. 단리와 복리가 무엇인가요?\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf("단리 : 원금에 대해서만 이자를 계산하는 방식이다.\n복리 : 원금에 대한 이자뿐만 아니라 이자에 대한 이자도 함께 계산하는 방법이다.\n\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("4. 단리/복리와 같은 계산방식이 통장에 나와있지 않은 경우에는 어떻게 하나요?\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        printf("은행에 문의해 보거나, 상품 설명서를 확인해 보시면 됩니다.\n");
        printf("계산기 사용이 급할 경우, 적금일 경우 단리식이고, 예금일 경우 연복리식이라 가정하고 사용하시면 됩니다.\n\n\n");
        printf("숫자 키를 눌러주세요.(계산기 이용 : 1  창 닫기는 숫자키 중 아무거나 눌러주세요.)\n");
        while (scanf("%d", &n) != 1) {// 잘못된 자료형일 경우
            clear();
            printf("계산기 이용(1) 또는 창 닫기: 숫자키 중 하나를 다시 입력해주세요.\n");
        }
        if (n == 1) {
            return 0;
        }
        else if (n != 1) {// 1이 아닌 모든 숫자
            return introduce();
        }
    }
    else if (n < 0 || n > 3) { // 같은 자료형의 잘못된 범위일 경우
        printf("0 or 1 or 2 or 3 중 하나의 키를 골라주세요.\n");
        Sleep(700);
        return introduce();
    }

}

void clear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} // 입력 버퍼를 비운다.
}
