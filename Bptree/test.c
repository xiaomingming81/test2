#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *left, *right;
} Node;

//先序遍历和中序遍历建树
Node *PreInCreate(char pre[], char in[], int s1, int t1, int s2, int t2){
    //s1,t1为先序遍历序列的第一个结点和最后一个结点的下标
    //s2,t2为中序遍历序列的第一个结点和最后一个结点的下标
    //初始时s1=s2=0, t1=t2=n-1
    Node *root = (Node *)malloc(sizeof(Node)); //建立根结点
    root->data = pre[s1]; //根结点
    int i;
    for(i=s2; in[i]!=root->data; i++); //找根结点在中序遍历序列中的位置
    int llen = i-s2; //左子树长度
    int rlen = t2-i; //右子树长度
    if(llen != 0) //递归建立左子树
        root->left = PreInCreate(pre, in, s1+1, s1+llen, s2, s2+llen-1);
    else //左子树为空
        root->left = NULL;
    if(rlen != 0)//递归建立右子树
        root->right = PreInCreate(pre, in, t1-rlen+1, t1, t2-rlen+1, t2);
    else //右子树为空
        root->right = NULL; 
    return root;
}
int depth(Node *t)
{
    int deep,depthleft,depthright;
    if(!t)
    deep=0;
    else
    {
        depthleft=depth(t->left);
        depthright=depth(t->right);
        deep=1+(depthleft>depthright?depthleft:depthright);
    }
    return deep;
}
int leafnum(Node* t)
{
    if(!t)
    return 0;
    if(t&&!t->left&&!t->right)
    return 1;
    return (leafnum(t->left)+leafnum(t->right));
}
//根据表达式建树
Node* newNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
int isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 1;
    return 0;
}
int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
int isalpha(char operator)
{
    if((operator<='z'&&operator>='a')||(operator<='Z'&&operator>='A'))
    return 1;
    else 
    return 0;
}
Node* constructTree(char* infix) {
    Node *stack[25], *t;
    char opStack[25];
    int top = -1, opTop = -1, i;
    for (i=0; i<strlen(infix); i++) {
        if (infix[i] == '(') {
            opStack[++opTop] = infix[i];
        } else if (isalpha(infix[i])) {
            t = newNode(infix[i]);
            stack[++top] = t;
        } else if (isOperator(infix[i])) {
            while (opTop != -1 && precedence(opStack[opTop]) >= precedence(infix[i])) {
                t = newNode(opStack[opTop--]);
                t->right = stack[top--];
                t->left = stack[top--];
                stack[++top] = t;
            }
            opStack[++opTop] = infix[i];
        } else if (infix[i] == ')') {
            while (opTop != -1 && opStack[opTop] != '(') {
                t = newNode(opStack[opTop--]);
                t->right = stack[top--];
                t->left = stack[top--];
                stack[++top] = t;
            }
            opTop--;  // pop '('
        }
    }
    while (opTop != -1) {
        t = newNode(opStack[opTop--]);
        t->right = stack[top--];
        t->left = stack[top--];
        stack[++top] = t;
    }
    return stack[top];
}
void preorder(Node* root) {
    if (root) {
        printf("%c", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%c", root->data);
        inorder(root->right);
    }
}
void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%c", root->data);
    }
}
int main()
{
    char pre[100],in[100];
    scanf("%s",pre);
    fflush(stdin);
    scanf("%s",in);
    int s1=0,s2=0,t1,t2,i;
    Node* b;
    t1=strlen(pre)-1;
    t2=strlen(in)-1;
    b=PreInCreate(pre,in,s1,t1,s2,t2);
    printf("%d\n",depth(b));
    printf("%d",leafnum(b));
}

