#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <math.h> // 제곱을 사용하기 위한 헤더파일
#include<string.h> // strcmp(문자열 비교)를 사용하기위한 헤더파일
#include <windows.h> // 콘솔창의 출력문자에 색을 넣기위한 헤더파일

int main()
{
	int n;
	char name[5]; // 금융 상품의 이름을 담을 배열
	double yija = 0.0; // 이자를 담을 변수
turn:
	printf("[이자 계산기] \n");
	printf("숫자 키를 눌러주세요.(적금 : 1  예금 : 2)\n");
	scanf("%d", &n);
	if (n == 1)
		strcpy(name, "적금");
	else if (n == 2)
		strcpy(name, "예금");
	else {
		printf("1 or 2 중 하나의 키를 골라주세요.\n");
		goto turn;
	}
	int won; // 원금을 담을 변수
	float yijayul, year; // 이자율, 연 단위의 기간을 담을 변수 선언
	printf("연 단위의 기간을 입력해주세요.(1년 3개월일 경우, 1.25)\n");
	scanf("%f", &year);
	printf("이율을 입력해주세요.(%% 제외)\n");
	scanf("%f", &yijayul);
	printf("%s에 넣을 금액을 입력해주세요.(단위 제외)\n", name);
	scanf(" %d", &won);
	yijayul /= 100.0;
	if(strcmp(name, "적금") == 0)
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
				res = won * pow((1+yijayul / 12.0),i);
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
	printf("숫자 키를 눌러주세요.(과세 : 1  저과세 : 2  비과세 : 3)\n");
	scanf("%d", &n);
	if (n == 1)
		yija -= yija * 0.154;
	else if (n == 2)
		yija -= yija * 0.014;
	printf("고객님께서 받으시는 총 이자는 %.0f원 입니다.", yija);
	return 0;
}
