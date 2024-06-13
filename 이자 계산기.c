#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <math.h> // 제곱을 사용하기 위한 헤더파일
#include<string.h> // strcmp(문자열 비교)를 사용하기위한 헤더파일
#include <windows.h> // 화면 전환 및 색상을 주기 위한 헤더 파일

char input(char* name);
float gesan(char name[]);
float seyul(double* yija);
char introduce();
int main()
{
	SetConsoleTitle(TEXT("이자 계산기"));
	int n, save = 1;
	char name[5]; // 금융 상품의 이름을 담을 배열
	while (save) {
		introduce();
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("[이자 계산기] \n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		input(name);
		double yija = gesan(name);// 이자를 담을 변수
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("고객님께서 받으시는 총 이자는 %.0f원 입니다.\n", yija);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		while (1) {
			printf("숫자 키를 눌러주세요.(다시 시작 : 1  종료 : 0)\n");
			scanf("%d", &n);
			if (n == 1) {
				save = 1;
				break;
			}
			else if (n == 0) {
				save = 0;
				break;
			}
			else
			{
				printf("(다시 시작 : 1  종료 : 0)중 하나의 키를 눌러주세요.\n\n");
			}
		}
	}
	return 0;
}

char input(char* name) {
	int n;
	printf("숫자 키를 눌러주세요.(적금 : 1  예금 : 2)\n");
	scanf("%d", &n);
	if (n == 1)
		strcpy(name, "적금");
	else if (n == 2)
		strcpy(name, "예금");
	else {
		printf("1 or 2 중 하나의 키를 골라주세요.\n");
		Sleep(700);
		return input(name);
	}
	return n;
}

float gesan(char name[]) {
	double yija = 0;
	int won; // 원금을 을 변수
	float yijayul, year; // 이자율, 연 단위의 기간을 담을 변수 선언
	printf("연 단위의 기간을 입력해주세요.(1년 3개월일 경우, 1.25)\n");
	scanf("%f", &year);
	printf("이율을 입력해주세요.(%% 제외)\n");
	scanf("%f", &yijayul);
	printf("%s에 넣을 금액을 입력해주세요.(단위 제외)\n", name);
	scanf(" %d", &won);
	yijayul /= 100.0;
	int n;
	if (strcmp(name, "적금") == 0)
		printf("숫자 키를 눌러주세요.(단리 : 1  월복리 : 2)\n");
	else
		printf("숫자 키를 눌러주세요.(단리 : 1  월복리 : 2  연복리 : 3)\n");

	scanf("%d", &n);
	if (n == 1) // 단리식 계산방법
	{
		if (strcmp(name, "적금") == 0)
			yija = won * (yijayul / 12) * (year * 12 * (year * 12 + 1) / 2);
		else
			yija = won * yijayul * year;
	}
	else if (n == 2) // 월복리식 계산방법
	{
		double res = 0.0;
		if (strcmp(name, "적금") == 0)
		{
			for (int i = 1; i <= 12; i++) {
				res = won * pow((1 + yijayul / 12.0), i);
				yija += res;
			}
			yija -= won * year * 12;
		}
		else
		{
			for (int i = 0; i < 12; i++) {
				res = won * (yijayul / 12.0);
				yija += res;
				won += res;
			}
		}
	}
	else if (n == 3 && strcmp(name, "예금") == 0) // 연복리식 계산방법
	{
		yija = won * (pow(1 + yijayul, year) - 1);
	}
	else {
		if(strcmp(name, "적금") == 0)
			printf("1 or 2 중 하나의 키를 골라주세요.\n");
		else if(strcmp(name, "예금") == 0)
			printf("1 or 2 or 3 중 하나의 키를 골라주세요.\n");
		return gesan(name);
	}
	return seyul(&yija);
}

float seyul(double* yija) {
	int n;
	float se;
	printf("숫자 키를 눌러주세요.(일반 : 1  세금우대 : 2  비과세 : 3)\n");
	scanf("%d", &n);
	if (n == 1)
		*yija -= *yija * 0.154;
	else if (n == 2) {
		printf("적용할 세율을 입력해주세요.(%% 제외) : ");
		scanf("%f", &se);
		*yija -= *yija * (se/100);
	}
	else if (n == 3) {}
	else {
		printf("1 or 2 or 3 중 하나의 키를 골라주세요.\n");
		return seyul(yija);
	}
	return *yija;
}
char introduce() {
	int n;
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("[이자 계산기]\n");
	printf("숫자 키를 입력해주세요. (종료 : 0   시작 : 1   사용법 : 2   용어 설명서 : 3)\n");
	scanf("%d", &n);
	if (n == 0)
		exit(0);
	else if (n == 1)
		return 0;
	else if (n == 2) {
		printf("\033[2J\033[1;1H");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("[이자 계산기 사용법]\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("- 숫자키를 통해 조작한다.\n\n");
		printf("1. 예금과 적금 중 하나의 상품을 선택한다.\n");
		printf("2. 기간과 이율 금리를 설명에 따라서 입력한다.\n");
		printf("3. 단리와 복리(월복리/연복리) 중 이자를 계산하는 방식을 선택한다.\n");
		printf("4. 세금 계산 방법을 선택한다.\n");
		printf("5. 계산에 결과에 따른 총 이자가 나온다.\n\n");
		printf("숫자 키를 눌러주세요.(창 닫기 : 0  계산기 이용 : 1)\n");
		scanf("%d", &n);
		if (n == 0) {
			printf("0 or 1 중 하나의 키를 골라주세요.\n");
			return introduce();
		}
		else if (n == 1)
			return 0;
		else {
			return introduce();
		}
	}
	else if (n == 3)
	{
		printf("\033[2J\033[1;1H");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("[이자 계산기 용어 설명서]\n\n");
		printf("1. (정기)예금과 (정기)적금 둘이 무슨 차이인가요?\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("(정기)예금 : 한 번에 목돈을 일정 기간 동안 예치하는 것\n(정기)적금 : 정해진 기간 동안 일정한 금액을 저축해 목돈을 만드는 것\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("2. 단리와 복리가 무엇인가요?\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("단리 : 원금에 대해서만 이자를 계산하는 방식이다.\n복리 : 원금에 대한 이자뿐만 아니라 이자에 대한 이자도 함께 계산하는 방법이다.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("3. 세금우대와 비과세는 어떻게 해야 받을 수 있나요?\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("세금 우대는 특정 은행의 종합원을 경우 받으실 수 있고, 비과세는 그 종합원으로 10년간 근무해야 받으실 수 있습니다.\n\n");
		printf("숫자 키를 눌러주세요.(창 닫기 : 0  계산기 이용 : 1)\n");
		scanf("%d", &n);
		if (n == 0) {
			return introduce();
		}
		else if (n == 1) {
			return 0;
		}
	}
	else {
		printf("0 or 1 or 2 중 하나의 키를 골라주세요.\n");
		Sleep(700);
		return introduce();
	}
}      
