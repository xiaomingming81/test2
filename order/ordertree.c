#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define EQ(a,b) ((a==b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

// #define EQ(a,b) (!strcmp((a),(b)))
// #define LT(a,b)  (strcmp((a),b)<0)
// #define LQ(a,b)  (strcmp((a),b)<=0)

typedef struct BitNode
{
    int data;
    struct BitNode *lchild,*rchild;
}BitNode,*Bitree;

Bitree Search(Bitree t,int k)
{
    Bitree p=t;
    while (p!=NULL)
    {
        if(k==p->data)
        return p;
        if(k<p->data)
        p=p->lchild;
        if(k>p->data)
        p=p->rchild;
    }
    return NULL;
}
int SearchBST(Bitree t,int key,Bitree f,Bitree *p)
{
    if(!t)
    {
        p=f;
        return 0;
    }
    else if(key==t->data)
    {
        p=t;
        return 1;
    }
    else if(key<t->data)
        return SearchBST(t->lchild,key,t,p);
    else 
        return SearchBST(t->rchild,key,t,p);
}
int insertBST(Bitree *t,int e)
{
    Bitree p,s;
    if(SearchBST(t,e,NULL,p)==0)
    {
        s=(Bitree)malloc(sizeof(BitNode));
        s->data=e;
        s->lchild=s->rchild=NULL;
        if(!p)
        t=s;
        else if(e<p->data)
        p->lchild=s;
        else 
        p->rchild=s;
        return 1;
    }
    else return 0;
}
int deleteBST(Bitree t,int key)
{
    if(!t)
    return 0;
    else
    {
        if(key==t->data)
        return delete(t);
        else if(key<t->data)
        return deleteBST(t->lchild,key);
        else
        return deleteBST(t->rchild,key);
    }
}
int delete(Bitree p)
{
    Bitree q,s;
    if(!p->rchild)
    {
        q=p;
        p=p->lchild;
        free(q);
    }
    else if (!p->lchild)
    {
        q=p;
        p=p->rchild;
        free(q);
    }
    else
    {
        q=p;
        s=p->lchild;
        while (s->rchild)
        {
            q=s;
            s=s->rchild;
        }
        p->data=s->data;
        if(q!=p)
        q->rchild=s->lchild;
        else
        q->lchild=s->lchild;
        free(s);
    }
    return 1;
}

void R_Rotate(Bitree p)
{
    Bitree le;
    le=p->lchild;
    p->rchild=le->rchild;
    le->lchild=p;
    p=le;
}

void L_Rotate(Bitree p)
{
    Bitree re;
    re=p->rchild;
    p->rchild=re->lchild;
    re->lchild=p;
    p=re;
}

