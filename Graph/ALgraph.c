#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct arcnode{
    int adjvex;
    int adj;
    struct arcnode *nextarc;
    int *info;
}arcnode;

typedef struct vnode{
    int data;
    arcnode *firstarc;
}vnode,adjlist[20];

typedef struct {
    adjlist vertices;
    int vexnum,arcnum;
    int kind;
}algraph;

typedef struct 
{
    int a[50];
    int top;
}seqstack;

void Createadjlist(algraph *g)
{
    int i,j,k,w,c;
    arcnode *s;
    scanf("%d,%d,%d",&g->vexnum,&g->arcnum,&g->kind);
    for(i=0;i<g->vexnum;i++)
    {
        scanf("%d",&c);
        g->vertices[i].data=c;
        g->vertices[i].firstarc=NULL;
    }
    for(k=0;k<g->arcnum;k++)
    {
        scanf("%d,%d,%d",&i,&j,&w);
        s=(arcnode*)malloc(sizeof(arcnode));
        s->adjvex=j;
        s->adj=w;
        s->info=NULL;
        s->nextarc=g->vertices[i].firstarc;
        g->vertices[i].firstarc=s;
    }
}
void findindegree(algraph g,int indegree[])
{
    int i;
    arcnode *p;
    for(i=0;i<g.vexnum;i++)
    {
        p=g.vertices[i].firstarc;
        while (p)
        {
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
}
int TopologicalSort(algraph g)
{
    seqstack s;
    s.top=-1;
    int count,k,i,j;
    arcnode *p;
    int indegree[g.vexnum];
    findindegree(g,indegree);
    for(i=0;i<g.vexnum;i++)
    {
        if(!indegree[i])
        {
            s.top++;
            s.a[s.top]=i;
        }
    }
    count=0;
    while (s.top!=-1)
    {
        i=s.a[s.top];
        s.top--;
        printf("%d %c",i,g.vertices[i].data);
        count++;
        for(p=g.vertices[i].firstarc;p;p=p->nextarc)
        {
            k=p->adjvex;
            if(!(--indegree[k]))
            {
                s.top++;
                s.a[s.top]=k;
            }
        }
    }
    if(count<g.vexnum)
    return 0;
    else return 1;
}
int TopologicalOrder(algraph g,seqstack *t,int *ve)
{
    seqstack s;
    int count=0,k,j=0;
    int indegree[g.vexnum];
    arcnode *p;
    s.top=-1;
    findindegree(g,indegree);
    for(j=0;j<g.vexnum;j++)
    {
        if(indegree[j]==0)
        s.top++;
        s.a[s.top]=j;
    }
    t->top=-1;
    while(s.top!=-1)
    {
        t->top++;
        t->a[t->top]=s.a[s.top];
        s.top--;
        count++;
        for(p=g.vertices[j].firstarc;p;p=p->nextarc)
        {
            k=p->adjvex;
            if(--indegree[k]==0)
            {
                s.top++;
                s.a[s.top]=k;
            }
            if(ve[j]+p->adj>ve[k])
            ve[k]=ve[j]+p->adj;
        }
    }
    if(count<g.vexnum)
    return 0;
    else return 1;
}
int CriticalPath(algraph g,int *ve)
{
    seqstack *s;
    int a,j,k,el,ee,dut;
    int vl[g.vexnum];
    char tag;
    arcnode *p;
    if(TopologicalOrder(g,&s,ve)==0)
    return 0;
    for(a=0;a<g.vexnum;a++)
    vl[a]=ve[g.vexnum-1];
    while (s->top!=-1)       
    for(j=s->a[s->top],s->top--,p=g.vertices[j].firstarc;p;p=p->nextarc)
        {
            k=p->adjvex;
            dut=p->adj;
            if(vl[k]-dut<vl[j])
            vl[j]=vl[k]-dut;
        }
    for(j=0;j<g.vexnum;j++)
        for(p=g.vertices[j].firstarc;p;p=p->nextarc)
        {
        k=p->adjvex;
        dut=p->adj;
        ee=ve[j];
        el=vl[k]-dut;
        tag=(ee==el)?'*':' ';
        printf("%d,%d,%d,%d,%d,%c",j,k,dut,ee,el,tag);
        }
    return 1;
}
int main()
{
    printf("1");
}