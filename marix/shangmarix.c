#include<string.h>
#include<stdio.h>
void print(int c[], int n)
{//n阶上三角矩阵按矩阵方式输出，其中矩阵采用压缩存储方式
	int i, j, k;
	c[n * (n + 1) / 2] = 0;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (i <= j)
				k = (i - 1) * (2 * n - i + 2)/2 + (j - i);
			else {
				
				k = n * (n + 1) / 2;
			}
			printf("%3d ", c[k]);
		}
		printf("\n");
	}
}
int main()
{
	int a[] = { 1,2,3,4,5,6 };
	int n = 3;
	print(a, n);
}
