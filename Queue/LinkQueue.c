#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/*
struct data
{
    char name[8];
    int age1;
    char sex[2];
    float score;
};*/
typedef char elem;

typedef struct QNode
{
    elem data;
    struct QNode *next;
}QNode,*Queueptr;

typedef struct 
{
    /* data */
    Queueptr front;
    Queueptr rear;
}LinkQueue;
int InitQueue(LinkQueue *q)
{
    q->front=q->rear=(Queueptr)malloc(sizeof(QNode));
    if(!q->front)
    exit(0);
    q->front->next=NULL;
    return 1;
}
int EnQueue (LinkQueue *q,elem e)
{
    Queueptr p;
    p=(Queueptr)malloc(sizeof(QNode));
    if(!p)
    exit(0);
    p->data=e;
    p->next=NULL;
    q->rear->next=p;
    q->rear=p;
    return 1;
}
int DeQueue (LinkQueue *q,elem *e)
{
    if(q->front==q->rear)
    return 0;
    Queueptr p;
    p=q->front->next;
    *e=p->data;
    q->front->next=p->next;
    if(q->rear==p)
    q->rear=q->front;
    free(p);
    return 1;
}
int QueueNotEmpty(LinkQueue *q)
{
    if(q->front->next==NULL)
    return 0;
    else
    return 1;
}