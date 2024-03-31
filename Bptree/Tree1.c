#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
typedef struct CSnode
{
    char data;
    struct CSnode *firstchild,*nextsibling;
}CSnode,*CStree;

typedef struct Queue
{
    int first;
    CStree data[100];
    int final;
}Queue;

typedef struct 
{
    CStree base [100];
    int top;
}SqStack;

int enQueue(Queue *q,CSnode * T){     //入队 
	if(q->final==100-1){
		return 0;
	}
	q->data[q->final]=T;
    q->final++;
	return 1;
}
int deQueue(Queue *q,CSnode *T){     //出队 
	if(q->first==q->final){
		return 0;
	}
	T=q->data[q->first];
    q->first++;
	return 1;
}
void gethaed(Queue *q,CSnode *T)
{
    T=q->data[q->first];
}
int emptyQueue(Queue *q){     //判断队列是否为空 
	if(q->first==q->final){
		return 1;
	}
	else{
		return 0;
	}
}

/*
CStree creatree(CStree t) {
    Queue q;
    q.final = q.first = 0;
    q.data[0] = NULL;
    CStree p, s, r;
    char input[100];  // Assuming the input line won't exceed 100 characters
    char fa, ch;
    t = NULL;

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;  // Exit the loop if no more input
        }
        if (sscanf(input, "%c,%c", &fa, &ch) != 2) {
            // Input format doesn't match expected format
            printf("Invalid input format. Please enter in the format 'char,char'\n");
            continue;
        }
        if (ch == '#') {
            break;  // Assuming '#' marks the end of input
        }
        p = (CSnode*)malloc(sizeof(CSnode));
        p->firstchild = p->nextsibling = NULL;
        p->data = ch;
        enQueue(&q, p);
        if (fa == '#') {
            t = p;
        }
        else {
            s = q.data[q.first];
            while (s->data != fa) {
                deQueue(&q, s);
                s = q.data[q.first];
            }
            if (!(s->firstchild)) {
                s->firstchild = p;
                r = p;
            }
            else {
                r->nextsibling = p;
                r = p;
            }
        }
    }
    return t;
}
*/
CStree creatree(CStree t)
{
    Queue q;
    q.final=q.first=0;
    q.data[0]=NULL;
    CStree p,s,r;
    char fa,ch;
    t=NULL;
    for(scanf("%c,%c",&fa,&ch);ch!='#';scanf("%c,%c",&fa,&ch))
    {
        fflush(stdin);
        p=(CSnode*)malloc(sizeof(CSnode));
        p->firstchild=p->nextsibling=NULL;
        p->data=ch;
        enQueue(&q,p);
        if(fa=='#')
            t=p;
        else
        {
            s=q.data[q.first];
            while (s->data!=fa)
            {
                deQueue(&q,s);
                s=q.data[q.first];
            }
            if(!(s->firstchild))
            {
                s->firstchild=p;
                r=p;
            }
            else 
            {
                r->nextsibling=p;
                r=p;
            }
        }
    }
    return t;
}

int Printelement (char e)
{
    printf("%c",e);
    return 1;
}
void Preorder(CStree t,int (*Printelement)(char e))
{
    if(t!=NULL)
    {
        Printelement(t->data);
        Preorder(t->firstchild,Printelement);
        Preorder(t->nextsibling,Printelement);
    }
}
void Inorder(CStree t,int (*Printelement)(char e))
{
    if(t!=NULL)
    {
        Inorder(t->firstchild,Printelement);
        Printelement(t->data);
        Inorder(t->nextsibling,Printelement);
    }
}
void Nextorder(CStree t,int (*Printelement)(char e))
{
    if(t!=NULL)
    {
        Nextorder(t->firstchild,Printelement);
        Nextorder(t->nextsibling,Printelement);
        Printelement(t->data);
    }
}
void levelOrderTraversal(CStree root) {
    if (root == NULL) {
        return;
    }
    Queue queue;
    queue.first = 0;
    queue.final = 0;
    enQueue(&queue,root);
    while (emptyQueue(&queue)==0) {
        CSnode *current;
        current=queue.data[queue.first];
        queue.first++;
        printf("%c", current->data);
        CSnode *child = current->firstchild;
        while (child != NULL) {
            enQueue(&queue, child);
            child = child->nextsibling;
        }
    }
}
int TreeDepth(CStree T) 
{
    int h1,h2;
    if(!T) return 0;
    else {
    h1 = TreeDepth( T->firstchild );
    h2 = TreeDepth( T->nextsibling);
    return(fmax(h1+1, h2));
    }
}
int leafnum(CStree root)
{
    int count=0;
    if (root == NULL) {
        return 0;
    }
    Queue queue;
    queue.first = 0;
    queue.final = 0;
    enQueue(&queue,root);
    while (emptyQueue(&queue)==0) {
        CSnode *current;
        current=queue.data[queue.first];
        queue.first++;
        if(current->firstchild==NULL)
        count++;
        CSnode *child = current->firstchild;
        while (child != NULL) {
            enQueue(&queue, child);
            child = child->nextsibling;
        }
    }
    return count;
}
void Outpath (CStree t,SqStack *s)
{
    int i;
    while (t)
    {
        s->top++;
        s->base[s->top]=t;
        if(!t->firstchild)
        {
            for(i=0;i<=s->top;i++)
            printf("%c",s->base[i]->data);
            printf("\n");
        }
        else 
        Outpath(t->firstchild,s);
        s->top--;
        t=t->nextsibling;
    }
    
}
int main()
{
    CStree t;
    SqStack s;
    s.top=-1;
    t=creatree(t);
    Preorder(t,Printelement);
    printf("\n");
    Inorder(t,Printelement);
    printf("\n");
    levelOrderTraversal(t);
    printf("\n");
    printf("%d",TreeDepth(t));
    printf("\n");
    printf("%d",leafnum(t));
    printf("\n");
    Outpath(t,&s);
}