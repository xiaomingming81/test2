#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct BiTNode 
{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct 
{
    BiTree a[10];
    int top;
}seqstack;
typedef struct{
    char ch[7];
    int low,high;
}sqlist;

int Printelement (char e)
{
    printf("%c",e);
    return 1;
}
void Preorder(BiTree t,int (*Printelement)(char e))
{
    if(t!=NULL)
    {
        Printelement(t->data);
        Preorder(t->lchild,Printelement);
        Preorder(t->rchild,Printelement);
    }
}
void Inorder(BiTree t,int (*Printelement)(char e))
{
    if(t!=NULL)
    {
        Inorder(t->lchild,Printelement);
        Printelement(t->data);
        Inorder(t->rchild,Printelement);
    }
}
void Nextorder(BiTree t,int (*Printelement)(char e))
{
    if(t!=NULL)
    {
        Nextorder(t->lchild,Printelement);
        Nextorder(t->rchild,Printelement);
        Printelement(t->data);
    }
}

void norder(BiTree t)
{
    BiTree l=t;
    seqstack s;
    int *a,*b;
    s.top=-1;
    while(t||s.top!=-1)
    {
        while (t)
        {
            //printf("%d",t->data);
            s.a[++s.top]=t;
            t=t->lchild;
        }
        t=s.a[s.top];
        if(t->rchild!=l)
        {
            //printf("%d",t->data);
            t=t->rchild;
            if(t==NULL)
            {
                l=t;
            }
        }
        else 
        {
            printf("%c",t->data);
            s.top--;
            l=t;
            t=NULL;
        }
    }
}

void iorder(BiTree t)
{
    seqstack s;
    s.top=-1;
    while (t||s.top!=-1)
    {
        while(t)
        {
            //printf("%d",t->data);
            s.a[++s.top]=t;
            t=t->lchild;

        }
        t=s.a[s.top--];
        printf("%c",t->data);
        t=t->rchild;
    }
    
}

void porder(BiTree t)
{
    seqstack s;
    s.top=-1;
    while (t||s.top!=-1)
    {
        while(t)
        {
            printf("%c",t->data);
            if(t->rchild!=NULL)
                s.a[++s.top]=t;
            t=t->lchild;
        }
        if(s.top>-1)
        {
            t=s.a[s.top--];
            t=t->rchild;
        }
    }
}

int depth(BiTree t)
{
    int deep,depthleft,depthright;
    if(!t)
    deep=0;
    else
    {
        depthleft=depth(t->lchild);
        depthright=depth(t->rchild);
        deep=1+(depthleft>depthright?depthleft:depthright);
    }
    return deep;
}
int leafnum(BiTree t)
{
    if(!t)
    return 0;
    if(t&&!t->lchild&&!t->rchild)
    return 1;
    return (leafnum(t->lchild)+leafnum(t->rchild));
}
BiTree CopyTree(BiTree t)
{
    BiTree newlptr,newrptr,newt;
    if(!t)
    return NULL;
    if(t->lchild)
    {
        newlptr =CopyTree(t->lchild);
    }
    else newlptr=NULL;
    if(t->rchild)
    newrptr=CopyTree(t->rchild);
    else newrptr=NULL;
    newt=(BiTNode*)malloc(sizeof(BiTNode));
    newt->data=t->data;
    newt->lchild=newlptr;
    newt->rchild=newrptr;
    return newt;
}
int KthLayernum(BiTree t,int k)
{
    int a,b;
    if(!t)
    return 0;
    if(k==1)
    return 1;
    a=KthLayernum(t->lchild,k-1);
    b=KthLayernum(t->rchild,k-1);
    return a+b;
}
BiTree Butrpm(sqlist s1,sqlist s2)
{
    int j,l1,l2,h1,h2;
    int c;
    BiTNode *p;
    l1=s1.low;
    l2=s2.low;
    h1=s1.high;
    h2=s2.high;
    if(l1>h1||l2>h2)
    return 0;
    c=s1.ch[s1.low];
    p->data=c;
    for(j=s2.low;j<=s2.high;j++)
    {
        if(c==s2.ch[j])
        break;
    }
    s1.low=l1+1;
    s1.high=l1+j-l2;
    s2.low=l2;
    s2.high=j-1;
    p->lchild=Butrpm(s1,s2);
    p->rchild=Butrpm(s1,s2);
    return p;
}
BiTree build(char* a ,int* pi)
{
    if(a[*pi] =='#')
    {
        (*pi)++;
        return NULL;
    }
    else
    {
    BiTree p=( BiTNode*)malloc(sizeof(BiTNode));
    p->data=a[*pi];
    ++(*pi);
    p->lchild=build(a,pi);
    p->rchild=build(a,pi);
    return p;
    }
}
int main()
{
    char s[100];
    scanf("%s",s);
    BiTree t;
    int i=0;
    t=build(s,&i);
    Preorder(t,Printelement);
    printf("\n");
    Inorder(t,Printelement);
    printf("\n");
    Nextorder(t,Printelement);
    printf("\n");
    printf("%d\n",leafnum(t));
    printf("%d\n",depth(t));
    iorder(t);
}
