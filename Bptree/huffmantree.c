#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct 
{
    char data;
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTnode,*huffmantree;


typedef char ** HuffmanCode;

typedef struct 
{
    int w;
    char data;
}we[26];

//HT数组中存放的哈夫曼树，end表示HT数组中存放结点的最终位置，s1和s2传递的是HT数组中权重值最小的两个结点在数组中的位置
void Select(huffmantree HT, int end, int *s1, int *s2)
{
    int min1, min2;
    //遍历数组初始下标为 1
    int i = 1;
    //找到还没构建树的结点
    while(HT[i].parent != 0 && i <= end){
        i++;
    }
    min1 = HT[i].weight;
    *s1 = i;
   
    i++;
    while(HT[i].parent != 0 && i <= end){
        i++;
    }
    //对找到的两个结点比较大小，min2为大的，min1为小的
    if(HT[i].weight < min1){
        min2 = min1;
        *s2 = *s1;
        min1 = HT[i].weight;
        *s1 = i;
    }else{
        min2 = HT[i].weight;
        *s2 = i;
    }
    //两个结点和后续的所有未构建成树的结点做比较
    for(int j=i+1; j <= end; j++)
    {
        //如果有父结点，直接跳过，进行下一个
        if(HT[j].parent != 0){
            continue;
        }
        //如果比最小的还小，将min2=min1，min1赋值新的结点的下标
        if(HT[j].weight < min1){
            min2 = min1;
            min1 = HT[j].weight;
            *s2 = *s1;
            *s1 = j;
        }
        //如果介于两者之间，min2赋值为新的结点的位置下标
        else if(HT[j].weight >= min1 && HT[j].weight < min2){
            min2 = HT[j].weight;
            *s2 = j;
        }
    }
}

//HT为地址传递的存储哈夫曼树的数组，w为存储结点权重值的数组，n为结点个数
void CreateHuffmanTree(huffmantree *HT, we h, int n)
{
    if(n<=1) return; // 如果只有一个编码就相当于0
    int m = 2*n-1; // 哈夫曼树总节点数，n就是叶子结点
    *HT = (huffmantree) malloc((m+1) * sizeof(HTnode)); // 0号位置不用
    huffmantree p = *HT;
    // 初始化哈夫曼树中的所有结点
    for(int i = 1; i <= n; i++)
    {
        (p+i)->weight = h[i-1].w;
        (p+i)->parent = 0;
        (p+i)->lchild = 0;
        (p+i)->rchild = 0;
        (p+i)->data=h[i-1].data;
    }
    //从树组的下标 n+1 开始初始化哈夫曼树中除叶子结点外的结点
    for(int i = n+1; i <= m; i++)
    {
        (p+i)->weight = 0;
        (p+i)->parent = 0;
        (p+i)->lchild = 0;
        (p+i)->rchild = 0;
        (p+i)->data=NULL;
    }
    //构建哈夫曼树
    for(int i = n+1; i <= m; i++)
    {
        int s1, s2;
        Select(*HT, i-1, &s1, &s2);
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}

//HT为哈夫曼树，HC为存储结点哈夫曼编码的二维动态数组，n为结点的个数
void HuffmanCoding(huffmantree HT, HuffmanCode *HC,int n){
    *HC = (HuffmanCode) malloc((n+1) * sizeof(char *));
    char *cd = (char *)malloc(n*sizeof(char)); //存放结点哈夫曼编码的字符串数组
    cd[n-1] = '\0';//字符串结束符
   
    for(int i=1; i<=n; i++){
        //从叶子结点出发，得到的哈夫曼编码是逆序的，需要在字符串数组中逆序存放
        int start = n-1;
        //当前结点在数组中的位置
        int c = i;
        //当前结点的父结点在数组中的位置
        int j = HT[i].parent;
        // 一直寻找到根结点
        while(j != 0){
            // 如果该结点是父结点的左孩子则对应路径编码为0，否则为右孩子编码为1
            if(HT[j].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
            //以父结点为孩子结点，继续朝树根的方向遍历
            c = j;
            j = HT[j].parent;
        }
        //跳出循环后，cd数组中从下标 start 开始，存放的就是该结点的哈夫曼编码
        (*HC)[i] = (char *)malloc((n-start)*sizeof(char));
        strcpy((*HC)[i], &cd[start]);
    }
    //使用malloc申请的cd动态数组需要手动释放
    free(cd);
}


void PrintHuffmanCode(HuffmanCode htable,we h,int n)
{
    int i;
    for(i=1;i<=n;i++)
    {
    printf("%c(%d)%s\n",h[i-1].data,h[i-1].w,htable[i]);
    }
}
//计算WPL，可以采用层序遍历，也可以用随便一种遍历方式的，但是要传递该节点所在的层次
void GetWPL(huffmantree *ht,int n)
{
    int i,wpl=0,deep=0,par;
    for(i=1;i<=n;i++)
    {
        deep=0;
        par=(*ht)[i].parent;
        while (par!=2*n-1)
        {
            deep++;
            par=(*ht)[par].parent;
        }
        wpl+=(deep+1)*(*ht)[i].weight;
    }
    printf("%d",wpl);
}


int main()
{
    huffmantree ht;
    HuffmanCode htable;
    we h;
    char str[256];
    scanf("%[^\n]",str);
    int i,j,n=0,flag,minw,minnum;
    char min;
    for(i=0;i<sizeof(h)/8;i++)
    {
        h[i].data='0';
        h[i].w=0;
    }
    for(i=0;i<strlen(str);i++)
    {
        flag=0;
        for(j=0;j<sizeof(h)/8;j++)
        {
            if(str[i]==h[j].data)
            {
                h[j].w++;
                flag=1;
                break;
            }
        }
        if(flag==0&&str[i]<='z'&&str[i]>='a')
        {
        h[n].data=str[i];
        h[n].w++;
        n++;
        }
    }
   for(i=0;i<n;i++)
    {
        min='z';
        for(j=i;j<n;j++)
        {
            if(h[j].data<min)
            {
                min=h[j].data;
                minnum=j;
            }
        }
        minw=h[minnum].w;
        h[minnum]=h[i];
        h[i].data=min;
        h[i].w=minw;
    }
    for(i=0;i<n;i++)
    {
        printf("%c%d ",h[i].data,h[i].w);
    }
    CreateHuffmanTree(&ht,h,n);
    HuffmanCoding(ht,&htable,n);
    PrintHuffmanCode(htable,h,n);
    GetWPL(&ht,n);
}

