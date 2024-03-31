#include<stdio.h>
#include<string.h>

typedef struct temp
{
	char a[100];
}temp;

void Getnext(int *, char *);

void KMP(char *, char *,int *);

int main()
{
	temp gene[10];
	char string[100];
	int next[100],a[2],c[2];
	int n,i,m,max=0,maxi=0;
	double b;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%s", gene[i].a);
	}
	scanf("%s", string);
	for(i=0;i<n;i++)
	{
		KMP(gene[i].a,string,a);
		//printf("\n%d",a[1]);
		if(a[1]>max)
		{
			max=a[1];
			maxi=i;
			c[0]=a[0];
			c[1]=a[1];
		}
	}
	b=(double)max/(double)strlen(string)*100;
	if(b!=0)
	printf("%d %d %.2lf%%",maxi+1,c[0],b);
	else 
	printf("0 0 0.00%%");
	return 0;
 }
 
 
void Getnext(int *next, char *temp)
{
	 	int i = 0, j = -1;
	 	next[0] = -1;
	 	while(i <= strlen(temp))
	 	{
	 		if(j == -1 || temp[i] == temp[j])
		 	{
		 		i++;j++;
		 		next[i] = j;
			 }
			 else
			 {
			 	j = next[j];
			 }
		 }
	 	
  } 
  
void KMP(char *string, char *temp,int*a)
{
	int next[100];
	int i = 0, j = 0,max=0,faulti;
	Getnext(next, temp);
//	
//	for(i = 0; i < strlen(temp); i++)
//	{
//		printf("%d\t",next[i]);
//	}
//	i = 0, j = 0;

	int l_str = strlen(string), l_t = strlen(temp); 
	while(i < l_str && j < l_t)
	{
		if(j == -1 || string[i]==temp[j] )
		{
			i++;
			j++;
			if(j!=-1&&j>max)
			faulti=i;
		}
		else
		{
			if(j>max)
			max=j;
			j = next[j];
			//printf("**%d\t",j);
		}
		
	}
	int c = strlen(temp);
	//可能是编译器的问题，如果我不拿个c存放这个长度，直接反倒条件判断里面运行不出来 
	
	if( j >= c )
	{
		//printf("\n%d位置:找到了。",i-strlen(temp) + 1);
		a[0]=i-strlen(temp) + 1;
		a[1]=strlen(temp);
		return ;
	}
	else
	{
		//printf("\n没有找到匹配的部分。%d",max);
		a[0]=faulti-max + 1;
		a[1]=max;
		return ;
	}
	
}
  