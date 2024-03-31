#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct chunk
{
    /* data */
    char ch[50];
    struct chunk *next;
}Chunk;

typedef struct 
{
    Chunk *head;
    Chunk *tail;
    int curlen;
}Lstring;
 