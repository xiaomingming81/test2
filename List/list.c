#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
struct data
{
    /* data */
    char name[8];
    int age;
    char sex[2];
    float score;
};
typedef struct data elem;
typedef struct list{
    elem *el;
    int length;
    int listsize;
}list;
int InitList_Sq(list *l)
{
    l->el=(elem*)malloc (LIST_INIT_SIZE*(sizeof(elem)));
    if(!l->el) exit(0);
    l->length=0;
    l->listsize-LIST_INIT_SIZE;
    return 1;
};
int DestoryList(list *l)
{
    free(l->el);
    return 1;
};
int ListEmpty(list l)
{
    if(l.length==0)
        return 1;
    else 
        return 0;
};
int listlength(list l)
{
    return l.length;
};
int PriorElem(list l,int cur_e,elem *pre_e)
{
    if(cur_e<=0||l.length==0||cur_e>l.length)
    return 0;
    else 
    *pre_e=l.el[cur_e-1];
};
/*int ListInsert_Sq(list &l,int i,elem e)
{
    int j;
    for(j=l.length;j>=i-1;j--)
    l.el[j+1]-l.el[j];
    l.el[i-1]=e;
    l.length++;
    return 1;
}*/
int ListInsert_Sq(list *l,int i,elem e)
{
    if(i<1||i>l->length+1)
    return 0;
    if(l->length>=l->listsize)
    {
        elem *newbase;
        newbase=(elem*)realloc (l->el,(l->listsize+LISTINCREMENT)*sizeof(elem));
        if(!newbase)exit(0);
        l->el=newbase;
        l->listsize+=LISTINCREMENT;
    }
    elem *q,*p;
    q=&(l->el[i-1]);
    for(p=&(l->el[l->length-1]);p>=q;--p)
    *(p+1)=*p;
    *q=e;
    l->length++;
    //数组下标控制
    /*int j;
    for(j=l->length-1;j>=i-1;j--)
    {
        l->el[j+1]=l->el[j];
    }
    l->el[i-1]=e;
    l->length++;*/
    return 1;
};
int ListDelete_Sq(list *l,int i,elem e)
{
    if(i<1||i>l->length)
    return 0;
    elem *p,*q;
    p=&(l->el[i-1]);
    e=*p;
    q=l->el+l->length-1;
    for(++p;p<=q;++p)
    *(p-1)=*p;
    l->length--;
    return 1;
    //数组下表控制
    /*
    int i,j;
    if(i<1||i>l->length)
    return 0;
    e=l->el[i-1];
    for(j=i-1;j<l->length-1;j++)
    l->el[j]=l->el[j+1];
    l->length--;
    return 1;
    */
}
int main()
{
    elem a={ "asd",18,"a",67};
    elem b={ "lsy",17,"b",100};
    elem c={ "gfd",16,"a",87};
    elem d={ "afe",15,"b",90};
    list l;
    InitList_Sq(&l);
    return 0;
}
