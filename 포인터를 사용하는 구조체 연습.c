#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
struct score {
	int kor;
	int mat;
	int eng;
	int* c;
	int* java;
	int* python;
};
int main() {
	struct score s = { 100, 90, 80 };
	struct score* p = NULL; // 구조체 포인터
	p = &s;
	printf("구조체 s의 주소값 : %p\n", s);
	printf("국어 : %d 수학 : %d 영어 : %d \n", s.kor, s.mat, s.eng); // 도트 연산자 : 구조체 변수를 이용해 구조체 원소에 접근한다.
	printf("국어 : %d 수학 : %d 영어 : %d \n", (*p).kor, (*p).mat, (*p).eng);
	printf("국어 : %d 수학 : %d 영어 : %d \n", p->kor, p->mat, p->eng); // 화살표 연산자 : 포인터를 사용해 구조체에 접근한다.
	printf("----------------------------------\n");
	int score1 = 100;
	int score2 = 90;
	int score3 = 80;

	s.c = &score1;
	s.java = &score2;
	s.python = &score3;

	printf("C언어 : %d\n", *s.c);
	printf("Java 점수 : %d\n", *s.java);
	printf("Python 점수 : %d\n", *s.python);

	score1 = 80;
	score2 = 90;
	score3 = 100;

	printf("C언어 점수 : %d\n", *s.c);
	printf("Java 점수 : %d\n", *s.java);
	printf("Python 점수 : %d\n", *s.python);
	return 0;
}
