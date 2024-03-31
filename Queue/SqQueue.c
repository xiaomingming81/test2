#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct data
{
    /* data */
    char name[8];
    int age;
    char sex[2];
    float score;
};
typedef struct data elem;

typedef struct 
{
    elem *base;
    int front;
    int rear;
}SqQueue;

int InitQueue(SqQueue *q)
{
    q->base=(elem*)malloc(10*sizeof(elem));
    if(!q->base)exit(0);
    q->front=q->rear=0;
    return 1;
}
int EnQUeue(SqQueue *q,elem e)
{
    if((q->rear+1)%10==q->front)
    return 0;
    q->base[q->rear]=e;
    q->rear=(q->rear+1)%10;
    return 1;
}
int DeQueue(SqQueue *q,elem *e)
{
    if(q->front==q->rear)
    return 0;
    *e=q->base[q->front];
    q->front=(q->front+1)%10;
    return 1;
}
int QueueLength(SqQueue q)
{
    return ((q.rear-q.front+10)%10);
}
