#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *lchild, *rchild; // 原始的左右子节点
    struct Node *left, *right; // 线索化后的左右节点
    int ltag, rtag; // 0表示指向孩子，1表示指向前驱或后继
} Node, *Tree;

Tree pre; // 全局变量，始终指向刚刚访问过的结点
int index = 0; // 全局变量，用于跟踪字符串中的字符

// 创建二叉树
void createTree(Tree *T, char *str) {
    char c = str[index++];
    if (c == '#') {
        *T = NULL;
    } else {
        *T = (Node *)malloc(sizeof(Node));
        (*T)->data = c;
        (*T)->ltag = (*T)->rtag = 0; // 初始化标志位
        createTree(&(*T)->lchild, str);
        createTree(&(*T)->rchild, str);
        (*T)->left = (*T)->lchild;
        (*T)->right = (*T)->rchild;
    }
}
// 中序遍历线索化
void inThreading(Tree T) {
    if (T) {
        inThreading(T->left);
        if (!T->left) {
            T->ltag = 1;
            T->left = pre;
        }
        if (pre && !pre->right) {
            pre->rtag = 1;
            pre->right = T;
        }
        pre = T;
        inThreading(T->right);
    }
}
int InOrderThreading(Tree T,Tree thrt)
{
    if(!(thrt=(Tree)malloc(sizeof(Node))));
    exit(0);
    thrt->ltag=0;
    thrt->rtag=1;
    thrt->rchild=thrt;
    if(!T)
    thrt->lchild=thrt;
    else{
        thrt->lchild=T;
        pre=thrt;
        inThreading(T);
        pre->rchild=thrt;
        pre->rtag=1;
        thrt->rchild=pre;
    }
}
// 中序遍历线索二叉树
void inOrderTraverse(Tree T) {
    while (T) {
        while (!T->ltag) {
            T = T->left;
        }
        printf("%c", T->data);
        while (T->rtag && T->right) {
            T = T->right;
            printf("%c", T->data);
        }
        T = T->right;
    }
    printf("\n");
}
// 计算一度节点数量
int countDegreeOne(Tree T) {
    if (!T) {
        return 0;
    }
    int count = 0;
    Tree queue[100];
    int front = 0, rear = 0;
    queue[rear++] = T;
    while (front != rear) {
        Tree node = queue[front++];
        int degree = (node->lchild ? 1 : 0) + (node->rchild ? 1 : 0);
        if (degree == 1) {
            count++;
        }
        if (node->lchild) {
            queue[rear++] = node->lchild;
        }
        if (node->rchild) {
            queue[rear++] = node->rchild;
        }
    }
    return count;
}

int main() {
    Tree T;
    char str[100];
    scanf("%s",str);
    createTree(&T, str);
    inThreading(T);
    inOrderTraverse(T);
    printf("%d\n", countDegreeOne(T)+1);
    return 0;
}