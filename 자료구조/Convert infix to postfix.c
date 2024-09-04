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
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어있습니다.\n");
		exit(1);
	}
	return s->data[s->top];
}
int prec(char op) {
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}
void infix_to_postfix(char exp[]) {
	size_t i = 0;
	char ch, top_op;
	size_t len = strlen(exp);
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		switch (ch) {
		case '+': case'-': case'*': case'/':
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				printf("%c", pop(&s));
			push(&s, ch);
			break;
		case '(':
			push(&s, ch);
			break;
		case ')':
			top_op = pop(&s);
			while (top_op != '(') {
				printf("%c", top_op);
				top_op = pop(&s);
			}
			break;
		default:
			printf("%c", ch);
			break;
		}
	}
	while (!is_empty(&s))
		printf("%c", pop(&s));
}
int main(void) {
	char *s = "(2+3)*4+9";
	printf("중위표기수식 %s \n", s);
	printf("후위표기식");
	infix_to_postfix(s);
	printf("\n");
	return 0;
}