#include<string.h>
#include<stdio.h>

typedef struct 
{
    int i,j;
    int e;
}triple;

typedef struct 
{
    triple data [100];
    int mu,nu,tu;
}TSMatrix;

int TransposeMatrix(TSMatrix m,TSMatrix *t)
{
    int p,q,col;
    t->mu=m.nu;
    t->nu=m.mu;
    t->tu=m.tu;
    if(t->tu)
    {
        q=1;
        for (col=1;col<m.nu;col++)
        {
            for (p=1;p<m.tu;p++)
          {
            if(m.data[p].j==col)
            {
                t->data[q].i=m.data[p].j;
                t->data[q].j=m.data[p].i;
                t->data[q].e=m.data[p].e;
                q++;
            }
          }
        }
    }
    return 1;
}
int main()
{
    TSMatrix m1,m2;
    int i=1;
    scanf("%d %d %d",&m1.mu,&m1.nu,&m1.tu);
    for(i=0;i<m1.tu;i++)
        scanf("%d %d %d",&m1.data[i].i,&m1.data[i].j,&m1.data[i].e);
    TransposeMatrix(m1,&m2);
    printf("%d %d %d\n",m2.mu,m2.nu,m2.tu);
    for(i=0;i<m2.tu;i++)
        printf ("%d %d %d\n",m2.data[i].i,m2.data[i].j,m2.data[i].e);
    
}

