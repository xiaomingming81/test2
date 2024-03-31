#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef unsigned char Sstring[256] ;

typedef struct {
    char *ch;
    int length;
}Hstring;
int index(Sstring s,Sstring t,int pos)
{
    int i,j;
    i=pos;
    j=1;
    while (i<=s[0]&&j<=t[0])
    {
        if(s[i]==t[j])
        {
            i++;
            j++;
        }
        else 
        {
            i=i-j+2;
            j=1;
        }
        if(j>t[0])
        return i-t[0];
        else return 0;   
    }
}
int StrAssign(Hstring *t,char *chars)
{
    int i;
    char c;
    if(t->ch)
    free(t->ch);
    for(i=0,c=chars;c;i++,c++);
    if(!i)
    {
        t->ch=NULL;
        t->length=0;
    }
    else{
        if(!(t->ch=(char*)malloc(i*sizeof(char))))
        exit(0);
        for (int j=0;j<i;j++)
        t->ch[j]=chars[j];
        t->length=i;
    }
    return 1;
}
int Strinsert(Hstring *s,int pos,Hstring t)
{
    int i,j;
    if(pos<1||pos>s->length+1)
    return 0;
    if(t.length)
    {
        if(!(s->ch=(char*)realloc(s->ch,(s->length+t.length)*sizeof(char))))
        exit(0);
        for(i=s->length-1;i>=pos-1;i--)
        {
            s->ch[i+t.length]=s->ch[i];
        }
        for(j=pos-1;j<pos+t.length-1;j++)
        {
            int n=0;
            s->ch[j]=t.ch[n];
            n++;
        }
        s->length+=t.length;
    }
    return 1;
}
int index_kmp(Sstring s,Sstring t,int pos,int *next)
{
    int i,j;
    i=pos;
    j=1;
    while (i<=s[0]&&j<=t[0])
    {
        if(j==0||s[i]==t[j])
        {
            i++;
            j++;
        }
        else 
        j=next[j];
    }
    if(j>t[0])
        return i-t[0];
    else 
        return 0;
}
void get_next(Sstring t,int next[])
{
    int j=1;
    int k=0;
    next[1]=0;
    while (j<t[0])
    {
        if(k==0||t[j]==t[k])
        {
            j++;
            k++;
            next[j]=k;
        }
        else k=next[k];
    }   
}