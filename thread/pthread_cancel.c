/*************************************************************************
	> File Name: two_pth.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月07日 星期四 21时40分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<signal.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define SECON_PTH_NUMS 2
#define PTHEXIT        0
typedef struct pthread_arg
{
    pthread_t tid;
    int pthno;
    int fd;
}ptharg;
    ptharg pth_arg[SECON_PTH_NUMS];
//设置为全局变量便于传参，
//学会封装全局变量
//
//
//typedef struct gloable_va
//{
//     ptharg pth_arg[SECON_PTH_NUMS];
//     int pth_exit_flag{SECON_PTH_NUMS};
//}glbva;
//
//注意  ： 以这种方式给pthread_create传参时，第二个参数应为glbva.pth_arg[i];
void print_err(char *,int ,int );
void *pth_fun(void *);
void signal_fun(int );
int main(void)
{
    int fd = 0;

    //ptharg pth_arg[SECON_PTH_NUMS];
    fd = open("./file.txt",O_RDWR | O_CREAT | O_TRUNC, 0664);
    if(fd == -1)
        print_err("open ./file.txt",__LINE__ ,errno);

    int i = 0 ;
    int ret = 0;
    //线程共享相同的文件描述符
    for(i = 0; i < SECON_PTH_NUMS ; i++)
    {
        pth_arg[i].fd = fd;
        pth_arg[i].pthno = i;
// int pthread_create (pthread_t *thread,constpthread_attr_t *attr,
        //              void *(*start_routine )(void *),void *arg);
        ret = pthread_create(&pth_arg[i].tid,NULL,pth_fun,(void *)&pth_arg[i]);
        //函数成功返回0 ，错误返回错误号  但不是errno
        if(ret != 0)
            print_err("pthread_create failed",__LINE__,ret);
    }

    signal(SIGALRM,signal_fun);
    alarm(2);
    int t = -1;
    while(1)
    {
        t++;
        printf("main thread : hello \n");
        
    }
}
void print_err(char *buf,int line,int err_no)
{
    printf("%d : %s , %s\n",line,buf,strerror(err_no));
    exit(-1);
}
void *pth_fun(void *pth_arg)
{
    int fd = ((ptharg *) pth_arg)->fd;
    int flag = ((ptharg * )pth_arg) ->pthno;
    int i = -1;
    while(1)
    {
        if(flag == 0)
            write(fd,"11111\n",5);
        if(flag == 1)
            write(fd,"22222\n",5);

        printf("%d : hello\n",((ptharg *)pth_arg)->pthno);


        //这种退出方式更加温柔，pthread_cancel 不管你执行到哪，直接终止
        //if(pth_exit_flag[pthno] == PTHEXIT)
        //{
        //      break;
        //}
    }
    return NULL;
}
void signal_fun(int signo)
{
    if(SIGALRM == signo)
    {
        int i = 0;
        for(i = 0; i < SECON_PTH_NUMS ;i++)
        {
            pthread_cancel(pth_arg[i].tid);

            //pth_exit_flag[i] = PTHEXIT;
            //设置为退出状态
        }
    }
}
