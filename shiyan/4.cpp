#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct Student{
	int id;
	char name[10];
	int grade;
};
bool cmp1(Student a,Student b)
{
	return a.id<b.id;
}
bool cmp2(Student a,Student b)
{
	if(strcmp(a.name,b.name)!=0) return strcmp(a.name,b.name)<0;
	else return a.id<b.id; 
}
bool cmp3(Student a,Student b)
{
	if(a.grade!=b.grade) return a.grade<b.grade;
	else return a.id<b.id;
}
int main()
{
	int N,C,testnum=0;
	while(scanf("%d %d",&N,&C)!=EOF)
	{ 
	    if(N==0) break;
	    else{
		     Student stu[N];
		     for(int i=0;i<N;i++)
		      {
			   scanf("%d%s%d",&stu[i].id,stu[i].name,&stu[i].grade);
		      }
		      if(C==1) sort(stu,stu+N,cmp1);
			  if(C==2) sort(stu,stu+N,cmp2);
	          if(C==3) sort(stu,stu+N,cmp3);
			  for(int i=0;i<N;i++)
			   {
			        printf("%06d %s %d\n",stu[i].id,stu[i].name,stu[i].grade); 
				} 
		    }
	}
	return 0;	
}