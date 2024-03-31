/*#include<stdio.h>
#include<string.h>
#include<malloc.h>

int main()
{
    char src[100];
    scanf("%s",src);
    int i,a,b;
    for(i=0;sizeof(src);i=i+2)
    {
        a=(int)src[i];
        b=(int)src[i+2];
        printf("%d %d ",b*(a-1),b-1);
    }
}
*/
#include<stdio.h>
int main(void){
    int k,n,flag=0,cnt=0;
    while(scanf("%d%d",&k,&n)!=EOF){
        if(flag==0&&n) flag=1;
        if(flag&&n){
            if(cnt++) printf(" ");
            printf("%d %d",k*n,n-1);
        }
        else if(flag==0) printf("0 0");
    }
    return 0;
}