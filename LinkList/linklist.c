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
typedef struct LNode
{
     elem data;
     struct LNode *next;
}LNode,*linklist;
void Initlist(linklist l)
{
     l=(LNode*)malloc(sizeof(LNode));
     l->next=NULL;
};
LNode* craetnode(elem x)
{
     LNode* newnode=(LNode*)malloc(sizeof(LNode));
     if(newnode==NULL)
     {
          printf("失败");
          exit(-1);
     }
     newnode->data=x;
     newnode->next=NULL;
     return newnode;
}
int ListEmpty(linklist L)
{
     if(L->next==NULL)
       return 1;
     else 
       return 0;
}
int Getdata(linklist L,int i,elem *e)
{
     linklist p=L->next;
     int j=1;
     while (p&&j<i)
     {
          p=p->next;
          ++j;
     }
     if(!p||j>i)
     {
         return 0;
     }
     *e=p->data;
     return 1;
}
int Listinsert(linklist L,int i,elem e)
{
     linklist p;
     p=L;
     int j=0;
     while(p&&j<i-1)
     {
          p=p->next;
          ++j;
     }
     if(!p||j>i-1)
     {
          printf("失败");
          return 0;
     }
     LNode *s=(LNode*)malloc (sizeof(LNode));
     s->data=e;
     s->next=p->next;
     p->next=s;
     return 1;
}
int Listdelete(linklist L,int i,elem *e)
{
     linklist p,q;
     p=L;
     int j=0;
     while(p->next&&j<i-1)
     {
          p=p->next;
          ++j;
     }
     if(!p||j>i-1)
     {
          printf("失败");
          return 0;
     }
     q=p->next;
     p->next=q->next;
     *e=q->data;
     free(q);
     return 1;
}
void clearlist(linklist L)
{
     linklist p;
     while (L->next)
     {
          p=L->next;
          L->next=p->next;
          free(p);
     }
}
void creatnewhead(linklist L,elem e)
{
     linklist p;
     p=(LNode*)malloc (sizeof(LNode));
     p->data=e;
     p->next=L->next;
     L->next=p;
}
void creatnewtail(linklist L,elem e)
{
     linklist p,r;
     r=L;
     p=(LNode*)malloc (sizeof(LNode));
     p->data=e;
     r->next=p;
     r=p;
     r->next=NULL;
}
void playlist(linklist L)
{
     linklist p=L;
     while(1)
     {
          if(p->next==NULL)
          {
          printf("%d\n",p->data);
          break;
          }
          else 
          {
          printf("%d\n",p->data);
          p=p->next;   
          }
     }
}
int main()
{
     // LNode *l=craetnode(3);
     // creatnewhead(l,4);
     // Listinsert(l,1,6);
     // playlist(l);
}