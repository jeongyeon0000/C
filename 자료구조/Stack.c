#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100

typedef int element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == MAX_STACK_SIZE - 1);
}

void PUSH(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택이 다 채워져있습니다.");
		return;
	}
	else {
		s->data[++(s->top)] = item;
	}
}

int POP(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있습니다.");
		exit(1);
	}
	else {
		return s->data[(s->top)--];
	}
}

int main(void) {
	StackType s;
	init_stack(&s);
	PUSH(&s, 1);
	PUSH(&s, 2);
	PUSH(&s, 3);
	printf("%d\n", POP(&s));
	printf("%d\n", POP(&s));
	printf("%d\n", POP(&s));

	return 0;
}