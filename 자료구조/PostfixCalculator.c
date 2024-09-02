#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element;

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
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택이 다 채워져있습니다.\n");
		return;
	}
	else {
		s->data[++(s->top)] = item;
	}
}
int pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있습니다.\n");
		exit(1);
	}
	else {
		return s->data[(s->top)--];
	}
}
int eval(char exp[]) {
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;
	init_stack(&s);

	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '/' && ch != '*') {
			value = ch - '0';
			push(&s, value);
		}
		else {
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) {
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '/': push(&s, op1 / op2); break;
			case '*': push(&s, op1 * op2); break;
			}
		}
	}
	return pop(&s);
}

int main(void) {
	int result;
	char expression[] = "82/3-32*+";
	printf("후위표기식 %s\n", expression);
	result = eval(expression);
	printf("Result: %d\n", result);
	return 0;
}