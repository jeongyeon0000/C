#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} QueueType;

// 오류 메시지를 출력하고 프로그램 종료
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 큐 초기화
void init_queue(QueueType* q) {
    q->rear = -1;
    q->front = -1;
}

// 큐 상태 출력
void queue_print(QueueType* q) {
    for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
        if (i <= q->front || i > q->rear)
            printf("|   ");
        else
            printf("| %d ", q->data[i]);
    }
    printf("|\n");
}

// 큐가 가득 찼는지 확인
int is_full(QueueType* q) {
    return q->rear == MAX_QUEUE_SIZE - 1;
}

// 큐가 비어 있는지 확인
int is_empty(QueueType* q) {
    return q->front == q->rear;
}

// 큐에 데이터 삽입
void enqueue(QueueType* q, int item) {
    if (is_full(q)) {
        error("큐가 포화상태입니다.");
    }
    q->data[++(q->rear)] = item;
}

// 큐에서 데이터 제거
int dequeue(QueueType* q) {
    if (is_empty(q)) {
        error("큐가 공백상태입니다.");
    }
    return q->data[++(q->front)];
}

int main() {
    QueueType q;
    init_queue(&q);

    printf("초기 큐 상태:\n");
    queue_print(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    queue_print(&q);

    int item = dequeue(&q);
    queue_print(&q);

    enqueue(&q, 40);
    enqueue(&q, 50);
    queue_print(&q);

    item = dequeue(&q);
    queue_print(&q);

    // enqueue(&q, 60) 오류 발생

    return 0;
}