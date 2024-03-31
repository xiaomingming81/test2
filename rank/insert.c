#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct 
{
    int key;
}Redtype;

typedef struct 
{
    /* data */
    Redtype r[10001];
    int length;
}sqlist;
typedef struct Queue
{
    int first;
    Redtype data[100];
    int final;
}Queue;
void insertionsort(sqlist *l)
{
    int i,j;
    for(i=2;i<=l->length;i++)
    {
        if(l->r[i].key<l->r[i-1].key)
        {
            l->r[0]=l->r[i];
            for(j=i-1;l->r[0].key<l->r[j].key;j--)
            {
                l->r[j+1]=l->r[j];
            }
            l->r[j+1]=l->r[0];
        }
    }
}
void insertionsort(sqlist *l)
{
    int i,j,m;
    int low,high;
    for(i=2;i<=l->length;i++)
    {
        if(l->r[i].key<l->r[i-1].key)
        {
            l->r[0]=l->r[i];
            low=1;
            high=i-1;
            while (low<=high)
            {
                m=(low+high)/2;
                if(l->r[0].key<l->r[m].key)
                high=m-1;
                else low=m+1;
            }
            for(j=i-1;j>=high+1;j--)
            {
                l->r[j+1]=l->r[j];
            }
            l->r[j+1]=l->r[0];
        }
    }
}
void ShellInsert(sqlist *l,int dk)
{
    int i,j;
    for(i=dk+1;i<=l->length;++i)
    {
        if(l->r[i].key<l->r[i-dk].key)
        {
            l->r[0]=l->r[i];
            for(j=i-dk;j>0&&l->r[0].key<l->r[j].key;j-=dk)
              l->r[j+dk]=l->r[j];
            l->r[j+dk]=l->r[0];
        }
    }
}
void shellsort(sqlist *l,int dlta[],int t)
{
    int k;
    for(k=0;k<t;k++)
    {
        ShellInsert(&l,dlta[k]);
    }
}
void BubbleSort(sqlist *l,int n)
{
    int i=n,j;
    Redtype e;
    int lastExcangeIndex=1;
    while (i>1)
    {
        lastExcangeIndex=1;
        for(j=1;j<i;j++)
        if(l->r[j+1].key<l->r[j].key)
        {
            e=l->r[j];
            l->r[j]=l->r[j+1];
            l->r[j+1]=e;
            lastExcangeIndex=j;
        }
        i=lastExcangeIndex;
    }
}
int Partition(sqlist *l,int low,int high)
{
    int pivotkey;
    pivotkey=l->r[low].key;
    l->r[0]=l->r[low];
    while (low<high)
    {
        while (low<high&&l->r[high].key>=pivotkey)
        high--;
        l->r[low]=l->r[high];
        while (low<high&&l->r[low].key<=pivotkey)
        low++;
        l->r[high]=l->r[low];
    }
    l->r[low]=l->r[0];
    return low;
}
void Qsort(sqlist *l,int low,int high)
{
    int pivotioc;
    if(low<high){
        pivotioc=Partition(&l,low,high);
        Qsort(&l,low,pivotioc-1);
        Qsort(&l,pivotioc+1,high);
    }
}
void SelectSort(sqlist l)
{
    int i,j,min;
    for(i=1;i<l.length;i++)
    {
        min=i;
        for(j=i+1;j<=l.length;j++)
        {
            if(l.r[j].key<l.r[min].key)
            min=j;
        }
        if(min!=i)
        {
            l.r[0]=l.r[i];
            l.r[i]=l.r[min];
            l.r[min]=l.r[0];
        }
    }
}
void HeapAdjust(sqlist *l,int s,int m)
{
    int j;
    Redtype rc=l->r[s];
    for(j=2*s;j<m;j*=2)
    {
        if(j<m&&l->r[j].key<l->r[j+1].key)
        j++;
        if(rc.key>=l->r[j].key)
        break;
        l->r[s]=l->r[j];
        s=j;
    }
    l->r[s]=rc;
}
void Heapsort(sqlist *l){
    int i;
    Redtype temp;
    for(i=l->length/2;i>0;--i)
    HeapAdjust(l,i,l->length);
    for(i=l->length;i>1;--i){
        temp=l->r[i];
        l->r[i]=l->r[1];
        l->r[i]=temp;
        HeapAdjust(l,1,i-1);
    }
}
void Merge(Redtype sr[],Redtype tr[],int i,int m,int n)
{
    int j,k;
    for(j=m+1,k=i;i<=m&&j<=n;++k)
    {
        if(sr[i].key<sr[j].key)
        tr[k]=sr[i++];
        else
        tr[k]=sr[j++];
    }
    if(i<=m)
    while(k<=n&&i<=m)
    tr[k++]=sr[i++];
    if(j<=n)
    while(k<=n&&j<=n)
    tr[k++]=sr[j++];
}
void Msort(Redtype sr[],Redtype tr1[],int s,int t)
{
    Redtype tr2[100];
    int m;
    if(s==t)
    tr1[s]=sr[s];
    else{
        m=(s+t)/2;
        Msort(sr,tr1,s,m);
        Msort(sr,tr1,m+1,t);
        merge(tr1,tr2,s,m,t);
    }
}
void mergesort(Redtype a[],int n)
{
    int l=1;
    Redtype b[100];
    while (l<n)
    {
        Msort(a,b,n,l);
        l=l*2;
        if(l>=n)
        break;
        Msort(b,a,n,l);
        l=l*2;
    }
}
void makenull(Queue q)
{

}
void radixsort(int figure,Queue *a)
{
    Redtype m;
    m.key=0;
    Queue q[10];
    int pass,r,i;
    for(pass=1;pass<=figure;pass++)
    {
        makenull(q[i]);//置空队列
        while(a->final!=a->first)
        {
            
        }

    }
}