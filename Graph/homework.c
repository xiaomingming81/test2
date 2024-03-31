#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef enum{DG,DN,UDG,UDN} Graphkind;
typedef struct AreCell{
    int adj;
    int *info;
}AreCell,AdjMatrix[20][20];
/*typedef struct 
{
    int vesx[20];
    int arcs [20][20];
    int vexnum,arcnum;
    Graphkind kind;
}mgraph;*/
typedef struct 
{
    int base [100];
    int front;
    int rear;
}SqQueue;
typedef struct 
{
    int vexs[20];
    AdjMatrix arcs;
    int vexnum,arcnum;
    Graphkind kind;
}mgraph;

void creatgraph(mgraph *g)
{
    int i,j,k,l=1,m,n,a,b;
    float w;
    scanf("%d %d",&n,&m);
    fflush(stdin);
    g->vexnum=n;
    g->arcnum=m;
    for(i=1;i<=g->vexnum;i++)
    {
        g->vexs[i]=i;
    }
    for(i=1;i<=g->vexnum;i++)
      for(j=1;j<=g->vexnum;j++)
      {
        g->arcs[i][j].adj=100;
        g->arcs[i][j].info=NULL;
      }
    for(k=1;k<=g->arcnum;k++)
    {
        //printf("请输入边的行列\n");
        fflush(stdin);
        scanf("%d %d",&a,&b);
        for(l=1;l<=g->vexnum;l++)
        {
            if(g->vexs[l]==a)
            i=l;
            if(g->vexs[l]==b)
            j=l;
        }
        g->arcs[i][j].adj=1;
        g->arcs[j][i].adj=1;
    }
}
int dfs(mgraph g,int v,int *visited,int *count,int sum)
{
    count[sum]++;
    visited[v]=1;
    int w;
    for(w=1;w<=g.vexnum;w++)
    if(g.arcs[v][w].adj!=100&&visited[w]!=1)
    dfs(g,w,visited,count,sum);
    if(count[sum]==1)
    {
        count[sum]=0;
        return 0;
    }
    else 
    return 1;
}
void dfstraverse(mgraph g,int *visited)
{
    int count[g.vexnum];
    int sum=0;
    int v,i,j,min=100,minnum;
    for(v=1;v<=g.vexnum;v++)
    visited[v]=0;
    for(v=1;v<=g.vexnum;v++)
    {
     if(visited[v]==0)
     {
        if(dfs(g,v,visited,count,sum)==1)
        sum++;
     }
    }
    printf("%d",sum);
    printf("\n");
    for(i=0;count[i]!=0;i++)
    {
        min=100;
        for(j=i;count[j]!=0;j++)
        {
            if(count[j]<min)
            {
                min=count[j];
                minnum=j;
            }
        }
        count[minnum]=count[i];
        count[i]=min;
    }
    for(i=0;count[i]!=0;i++)
    printf("%d ",count[i]);

}
void ShortestPath_DIJ(mgraph g,int v0,int *p,int *d)
{
    int i=0,j,v,w,min,final[g.vexnum+1];
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
            {
                if(d[w]<min)
                {
                v=w;
                min=d[w];
                }
            }
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
    /*for(i=1;i<=g.vexnum;i++)
    {
        int pre;
        printf("%d\n%d",d[i],i);
        pre=p[i];
        while (pre!=-1)
        {
            printf("<-%d",pre);
            pre=p[pre];
        }
    }*/
    int count=0;
    for(i=1;i<=g.vexnum;i++)
    {
        if(d[i]<=6)
        count++;
    }
    printf("%d: %.2f%%\n",v0,(float)(count+1)/g.vexnum*100);
}
void ShortestPath_FLOYD(mgraph g)
{
    int p[g.vexnum+1];
    int d[g.vexnum+1];
    int i;
    for(i=1;i<=g.vexnum;i++)
    {
        ShortestPath_DIJ(g,i,p,d);
    }
}
int main()
{
    mgraph g;
    creatgraph(&g);
    int visited[g.vexnum];
    ShortestPath_FLOYD(g);
}