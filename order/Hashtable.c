#include<stdio.h>
#include<string.h>
#include<malloc.h>


typedef struct 
{
    int key;
}Elemtype;

typedef struct 
{
    Elemtype *elem;
    int count;
    int sizeindex;
}Hashtable;

int hash(int k)
{
    return k%11;
}


