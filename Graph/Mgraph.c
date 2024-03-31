#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef enum{DG,DN,UDG,UDN} Graphkind;
/*typedef struct 
{
    int vesx[20];
    int arcs [20][20];
    int vexnum,arcnum;
    Graphkind kind;
}mgraph;*/
typedef struct AreCell{
    int adj;
    int *info;
}AreCell,AdjMatrix[20][20];
typedef struct 
{
    char vexs[20];
    AdjMatrix arcs;
    int vexnum,arcnum;
    Graphkind kind;
}mgraph;
typedef struct 
{
    int base [100];
    int front;
    int rear;
}SqQueue;
typedef struct 
{
    char adjvex;
    int lowcost;
}closedge[100];
void Creatgraph(mgraph *g)
{
    int i, j, k, l = 1;
    char c[100];
    char m, n, h;
    float w;
    scanf("%d %d %d", &g->kind, &g->vexnum, &g->arcnum);
    getchar(); // consume the newline character
    fgets(c, 100, stdin); // use fgets instead of gets
    for (i = 1; i <= g->vexnum * 2 - 1;)
    {
        g->vexs[l] = c[i - 1];
        i = i + 2;
        l++;
    }
    for (i = 1; i <= g->vexnum; i++)
        for (j = 1; j <= g->vexnum; j++)
        {
            g->arcs[i][j].adj = 100;
            g->arcs[i][j].info = NULL;
        }
    if (g->kind == 0 || g->kind == 2)
    {
        for (k = 1; k <= g->arcnum; k++)
        {
            scanf(" %c %c", &m, &n); // add a space before %c to consume the newline character
            getchar(); // consume the newline character
            for (l = 1; l <= g->vexnum; l++)
            {
                if (g->vexs[l] == m)
                    i = l;
                if (g->vexs[l] == n)
                    j = l;
            }
             g->arcs[i][j].adj = 1;
            if (g->kind == 2) {
                g->arcs[j][i].adj = 1;
            }
        }
    }
    if (g->kind == 1 || g->kind == 3)
    {
        for (k = 1; k <= g->arcnum; k++)
        {
            scanf(" %c %c %f", &m, &n, &w); // add a space before %c to consume the newline character
            getchar(); // consume the newline character
            for (l = 1; l <= g->vexnum; l++)
            {
                if (g->vexs[l] == m)
                    i = l;
                if (g->vexs[l] == n)
                    j = l;
            }
            g->arcs[i][j].adj = w;
            if (g->kind == 3) {
                g->arcs[j][i].adj = w;
            }
        }
    }
}
void dfs(mgraph g,int v,int *visited)
{
    visited[v]=1;
    printf("%c",g.vexs[v]);
    int w;
    for(w=1;w<=g.vexnum;w++)
    if(g.arcs[v][w].adj!=100&&visited[w]!=1)
    dfs(g,w,visited);
}
void dfstraverse(mgraph g,int i,int *visited)
{
    int v;
    for(v=1;v<=g.vexnum;v++)
    visited[v]=0;
    dfs(g,i,visited);
    for(v=1;v<=g.vexnum;v++)
    {
     if(visited[v]==0)
        dfs(g,v,visited);
    }
}
void bfstraverse(mgraph g,int *visited)
{
    SqQueue q;
    q.front=q.rear=1;
    int v,p,i;
    q.base[q.front]=1;
    for(v=1;v<=g.vexnum;v++)
    {
        visited[v]=0;
    }
    for(v=1;v<=g.vexnum;v++)
        if(visited[v]==0)
        {
        visited[v]=1;
        printf("%c",g.vexs[v]);
        q.base[q.rear]=v;
        q.rear++;
        while(q.front!=q.rear)
        {
            p=q.base[q.front];
            q.front++;
            for(i=1;i<=g.vexnum;i++)
            {
                if((g.arcs[p][i].adj!=100)&&(visited[i]==0))
                {
                    visited[i]=1;
                    printf("%c",g.vexs[i]);
                    q.base[q.rear]=i;
                    q.rear++;
                }
            }
            
        }
        }
}
int locatevex(mgraph g,char u)
{
    int k,i;
     for(k=1;k<=g.vexnum;k++)
    {
        if(g.vexs[k]==u)
        {
            i=k;
        }
    }
    return i;
}
int minimum(closedge close,mgraph g)
{
    int k=100,i;
    for(i=1;i<=g.vexnum;i++)
    {
        if(close[i].lowcost<k&&close[i].lowcost!=0)
        k=i;
    }
    return k;
}
void MiniSpanTree_p(mgraph g,char u)
{
    int i,j,k;
    k=locatevex(g,u);
    closedge close;
    for(j=1;j<=g.vexnum;j++)
        if(j!=k)
        {
            close[j].adjvex=u;
            close[j].lowcost=g.arcs[k][j].adj;
        }
    close[k].lowcost=0;
    for(i=1;i<g.vexnum;i++)
    {
        k=minimum(close,g);
        printf("%c %c\n",close[k].adjvex,g.vexs[k]);
        close[k].lowcost=0;
        for(j=1;j<=g.vexnum;j++)
        {
            if(g.arcs[k][j].adj<close[j].lowcost)
            {
                close[j].adjvex=g.vexs[k];
                close[j].lowcost=g.arcs[k][j].adj;
            }
        }
    }
}
void ShortestPath_DIJ(mgraph g,int v0,int *p,float *d)
{
    int i=0,j,v,w,min,final[100];
    for(v=1;v<=g.vexnum;v++)
    {
        final[v]=0;
        d[v]=g.arcs[v0][v].adj;
        p[v]=-1;
        if(d[v]<100)
        p[v]=v0;
    }
    final[v0]=1;
    p[v0]=-1;
    for(i=2;i<=g.vexnum;i++)
    {
        min=100;
        for(w=1;w<=g.vexnum;w++)
        {
            if(final[w]==0)
            if(d[w]<min)
            {
                v=w;
                min=d[w];
            }
            final[v]=1;
            for(w=1;w<=g.vexnum;w++)
            {
                if(final[w]==0&&(min+g.arcs[v][w].adj<d[w]))
                {
                    d[w]=min+g.arcs[v][w].adj;
                    p[w]=v;
                }
            }

        }
    }
    for(i=1;i<=g.vexnum;i++)
    {
        int pre;
        printf("%f\n%d",d[i],j);
        pre=p[i];
        while (pre!=-1)
        {
            printf("<-%d",pre);
            pre=p[pre];
        }
    }
}
void ShortestPath_FLOYD(mgraph g)
{
    int v,w,u,i;
    for(v=1;v<g.vexnum;++v)
    for(w=0;w<g.vexnum;++w)
    {
        
    }
}
int main()
{
    mgraph g;
    Creatgraph(&g);
    char m,h;
    int k,i,j;
    int visited[100];
    fflush(stdin);
    scanf("%c",&m);
    for(k=1;k<=g.vexnum;k++)
    {
        if(g.vexs[k]==m)
        {
            i=k;
        }
    }
    dfstraverse(g,i,visited);
    //printf("\n");
    //bfstraverse(g,visited);
    //printf("\n");
    //MiniSpanTree_p(g,m);
}
