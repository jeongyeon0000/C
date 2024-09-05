#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5

typedef int element;
typedef struct {
    int front, rear;
    element queue[MAX_SIZE];
} QueueType;

void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(QueueType* q) {
    q->rear = q->front = 0;
}

void enqueue(QueueType* q, element item) {
    if ((q->rear + 1) % MAX_SIZE == q->front)
        error("큐가 포화상태입니다.");
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (q->front == q->rear)
        error("큐는 공백 상태입니다.");
    q->front = (q->front + 1) % MAX_SIZE;
    return q->queue[q->front];
}

void queue_print(QueueType* q) {
    printf("|");
    if (q->front == q->rear) {
        printf("Queue is empty.\n");
        return;
    }
    int i = (q->front + 1) % MAX_SIZE;
    while (i != (q->rear + 1) % MAX_SIZE) {
        printf(" %d |", q->queue[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}

int main(void) {
    int item = 0;
    QueueType q;

    init(&q);

    enqueue(&q, 10); queue_print(&q);
    enqueue(&q, 10); queue_print(&q);
    enqueue(&q, 10); queue_print(&q);
    enqueue(&q, 10); queue_print(&q);
    item = dequeue(&q); queue_print(&q);
    enqueue(&q, 30); queue_print(&q);

    item = dequeue(&q); queue_print(&q);
    enqueue(&q, 30); queue_print(&q);
    enqueue(&q, 30); queue_print(&q);
    return 0;
}