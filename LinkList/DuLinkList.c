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
typedef struct DuLNode{
elem data;
struct DuLNode *prior;
struct DuLNode *next;
} DuLNode,*DuLinkList;


