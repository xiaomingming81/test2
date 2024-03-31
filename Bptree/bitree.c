#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define link 0
#define thread 1

typedef struct Node 
{
    char data;
    struct Node *lchild,*rchild;
    int ltag,rtag;
}Node,*BiTree;
BiTree pre;

BiTree build(char *a,int *pi)
{
    if(a[*pi] =='#')
    {
        (*pi)++;
        return NULL;
    }
    else
    {
    BiTree p=(Node*)malloc(sizeof(Node));
    p->data=a[*pi];
    p->ltag=p->rtag=thread;
    ++(*pi);
    p->lchild=build(a,pi);
    if(p->lchild!=NULL)
    p->ltag=link;
    p->rchild=build(a,pi);
    if(p->rchild!=NULL)
    p->rtag=link;
    return p;
    }
}
void InThreading(BiTree p)
{
    if(!p)
    return;
    InThreading(p->lchild);
    if(!p->lchild)
    {
        p->lchild=pre;
        p->ltag=thread;
    }
    if(!pre->rchild)
    {
        pre->rchild=p;
        pre->rtag=thread;
    }
    pre=p;
    InThreading(p->rchild);
}
void buildthtr(BiTree thrt ,BiTree t)
{
    thrt->ltag=thrt->rtag=link;
    thrt->rchild=thrt;
    if(t==NULL)
    thrt->lchild=thrt;
    else {
        thrt->lchild=t;
        pre=thrt;
        InThreading(t);
        pre->rchild=thrt;
    }
}
int inorder(BiTree t)
{
    BiTree p=t->lchild;
    while (p!=t)
    {
        while(p->ltag==link)
        p=p->lchild;
        printf("%c",p->data);
        while(p->rtag==thread&&p->rchild!=t)
        {
            p=p->rchild;
            printf("%c",p->data);
        }
        p=p->rchild;
    }
    return 1;
}
int inorder1(BiTree t)
{
    BiTree p=t->lchild;
    int count=0;
    while (p!=t)
    {
        while(p->ltag==link)
        p=p->lchild;
        if((p->ltag==link&&p->rtag==thread)||(p->ltag==thread&&p->rtag==link))
        count++;
        while(p->rtag==thread&&p->rchild!=t)
        {
            p=p->rchild;
            if((p->ltag==link&&p->rtag==thread)||(p->ltag==thread&&p->rtag==link))
            count++;
        }
        p=p->rchild;
    }
    return count;
}
int main()
{
    char s[200];
    scanf("%s",s);
    BiTree t,thtr;
    int i=0;
    t=build(s,&i);
    buildthtr(thtr,t);
    inorder(thtr);
    printf("\n");
    printf("%d",inorder1(thtr)+1);
}