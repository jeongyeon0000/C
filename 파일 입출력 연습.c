#include<stdio.h>
int main(void)
{
	char sts[100];
	char name[50];
	char k;
	int r = 1;
	FILE* foc = NULL;
	errno_t err;
	printf("파일의 이름과 확장자를 입력해주세요(ex. 한글.hwp) : ");
	gets_s(name, sizeof(name));
	while (r)
	{
		printf("원하시는 키를 입력해주세요. (파일 생성 or 내용 리셋 : w / 파일 보기 : r / 종료 : x)   ");
		k = getchar();
		getchar();
		if (k == 'w') {
			err = fopen_s(&foc, name, "w");
			if (err == 0)
			{
				printf("100자 미만의 내용 입력: ");
				gets_s(sts, sizeof(sts));
				printf("파일에 입력된 내용: %s\n", sts);
				for (int cnt = 0; sts[cnt] != NULL; cnt++)
					fputc(sts[cnt], foc);
				fclose(foc);
				printf("%s 파일 저장 완료\n", name);
			}
			else
				printf("실패\n");
		}
		else if (k == 'r')
		{
			printf("%s 파일의 내용을 보기\n", name);
			err = fopen_s(&foc, name, "r");
			if (err == 0)
			{
				char ch;
				while ((ch = fgetc(foc)) != EOF)
				{
					putchar(ch);
				}
				fclose(foc);
				printf("\n%s 파일 읽기 완료\n", name);
			}
			else
			{
				printf("파일 열기 실패\n");
			}
		}
		else if (k == 'x')
		{
			printf("프로그램을 종료합니다.");
			r = 0;
		}
		else
			printf("잘못된 키를 누르셨습니다.\n");
	}
	return 0;
}
