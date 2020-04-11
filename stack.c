/*************************************************************************
	> File Name: stack.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月10日 星期五 11时24分10秒
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<stdbool.h> //TRUE 1 FALUSE 0
#include<stdlib.h>
typedef struct Node
{
    int data;
    struct Node *pNext;
}NODE;
typedef struct stack
{
    NODE *pTop;
    NODE *pBottom;
}STACK;

void init(STACK *);
void push(STACK *,int );
void traverse(STACK *);
bool pop(STACK *,int *);
bool empty(STACK *);
void clear(STACK *);

int main(void)
{
    STACK ps;
    init(&ps);
    int n;
    printf("请输入要压入栈内的元素个数：");
    scanf("%d",&n);
    int val;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&val);
        push(&ps,val);
    }
    traverse(&ps);
    if(pop(&ps,&val) == true)
    {
        printf("出栈成功，出栈元素是 ： %d \n",val);
    }
    else
        printf("出栈失败！\n");
    traverse(&ps);
    clear(&ps);
    traverse(&ps);

}
//初始化栈
void init(STACK * ps)
{
    ps->pTop = (NODE *)malloc(sizeof(NODE));
    if(ps->pTop == NULL)
    {
        printf("malloc fail!\n");
        exit(-1);
    }
    ps->pBottom = ps->pTop;
    ps->pTop->pNext = NULL;
}
//压栈
void push(STACK *ps,int val)
{
    NODE *pNew = (NODE *)malloc(sizeof(NODE));
    pNew->data = val;
    pNew->pNext = ps->pTop;
    ps->pTop = pNew;
}
//遍历栈
void traverse(STACK *ps)
{
    NODE *p = NULL;
    p = ps->pTop;
    while(p != ps->pBottom)
    {
        printf("%d  ",p->data);
        p=p->pNext;
    }
    printf("\n");

}
//对ps出栈一次，并把栈顶元素的值保存下来，如果出栈失败返回false，成功返回true
bool pop(STACK *ps,int *pval)
{
    if(empty(ps) == true)
        return false;
    else
    {
        NODE *r = NULL;
        r = ps->pTop;
        *pval = r->data;
        ps->pTop = r->pNext;
        free(r);
        r = NULL;
        return true;
    }

}
//判断是否为空栈
bool empty(STACK *ps)
{
    if(ps->pTop == ps->pBottom)
        return true;
    else
        return false;
}
//清空栈
void clear(STACK *ps)
{
    NODE *p,*q;
    p = ps->pTop;
    while(p != ps->pBottom)
    {
        q=p->pNext;
        free(p);
        p=q;
    }
    ps->pTop = ps->pBottom;
}
