/*************************************************************************
	> File Name: test1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年07月18日 星期六 08时55分54秒
 ************************************************************************/





//面向对象语言中子类可以调用父类的函数，在GTK+中只要使用一些宏将自雷强转为父类即可
#include<stdio.h>
#include<stdlib.h>
#define FATHER(child) (struct Father *)(child)
//将child型变量强转为struct Father型变量

void print1(int i)
{
    printf("this is father and i = %d\n",i);

}
void print2(int i )
{
    printf("this is child and i = %d\n",i);
}
struct Father
{
    int a;
    void (*pointer1_to_function)(int);
};
    struct Child
    {
        struct Father f;
        int b;
        void (*pointer2_to_function)(int);
    };

void father_member_funtion(struct Father *f,char *string)
{
    printf("\n");
    f->pointer1_to_function(f->a);
    printf("%s\n\n",string);
}

int main()
{
    struct Child *p_child;
    p_child = (struct Child*)malloc(sizeof(struct Child));
    p_child -> f.a = 10;
    p_child->f.pointer1_to_function = print1;
    p_child->b = 20;
    p_child->f.pointer1_to_function (p_child->f.a);
    p_child->pointer2_to_function = print2;
    p_child->pointer2_to_function(p_child->b);
    struct Father *p_father = FATHER(p_child);
    p_father->pointer1_to_function (p_father->a);
    father_member_funtion(p_father,"hello");
    return 0;
}
