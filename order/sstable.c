#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define EQ(a,b) ((a==b))
#define LT(a,b) ((a)<(b))
#define LQ(a,b) ((a)<=(b))

// #define EQ(a,b) (!strcmp((a),(b)))
// #define LT(a,b)  (strcmp((a),b)<0)
// #define LQ(a,b)  (strcmp((a),b)<=0)

typedef struct 
{
    int key;
}Elemtype;

typedef struct 
{
    Elemtype *data;
    int length;
}sstable;

typedef struct 
{
    int key;
    int addr;
}indextype;

typedef struct 
{
    indextype index[100];
    int block;
}Intable;


int search_seq(sstable st,int key)
{
    int i;
    st.data[0].key=key;
    for(i=st.length;st.data[i].key!=key;i--)
    return i;
}

//(n+1)/2平均查找长度
int search_bin(sstable st,int key)
{
    int low=0,high,mid;
    high=st.length-1;
    while (low==high)
    {
        mid=(low+high)/2;
        if(key==st.data[mid].key)
        return mid;
        else if(key<st.data[mid].key)
        high=mid-1;
        else 
        low=mid+1;
    }
    return 0;
}

//h=log2(n+1) 1/n*求和(1--i)2^(i-1)*i

int search(sstable st,Intable ix,int key)
{
    int s,e;
    int i=0;
    while ((key>ix.index[i].key)&&(i<ix.block))
        i++;
    if(i<ix.block)
    {
        s=ix.index[i].addr;
        if(i==ix.block-1)
            e=st.length-1;
        else
            e=ix.index[i+1].addr-1;
        while (key!=st.data[s].key&&(s<=e))
            s++;
        if(s<=e)
        return s;
    }
    return -1;
}

//索引表长度为b，快的平均长度为l，(b+1)/2+(l+1)/2 分成sqrt(n)快时平均查找次数最少