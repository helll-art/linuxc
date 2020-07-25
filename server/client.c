#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<arpa/inet.h> 
#include"mysql.h"

#include "find_password.h"

#define PORT 8081

struct Msg{
    char name[20];
    char message[BUFSIZ];
    int socket;
    int flge;
};

void *send_fun(void *arg);
void *recv_fun(void *arg);

struct Msg msg;

int main(void)
{
    int fd;
    int serv_port = PORT;
    struct sockaddr_in serv_addr;
    char recv_buf[BUFSIZ];
    char send_buf[BUFSIZ];
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv_port);
    inet_aton("127.0.0.1",&serv_addr.sin_addr);
    fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
        my_err("socket",__LINE__);
    if(connect(fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) == -1)
    {
        close(fd);
        my_err("connect",__LINE__);
    }
    int k = 0;
    char *string = Username_Password(&k);
    strcmp(msg.name,string);
    if(k == 2)
    {
        pthread_t th1,th2;
        if(pthread_create(&th1,NULL,send_fun,(void *)&fd))
            my_err("Create send pthread error\n",__LINE__);
        if(pthread_create(&th2,NULL,recv_fun,(void *)&fd))
            my_err("create recv pthread error\n",__LINE__);

        pthread_join(th1,NULL);
        pthread_join(th2,NULL);
        close(fd);
        return 0;
    }
    else 
    {
        return -1;
    }
   /* pthread_t th1,th2;
    pthread_create(&th1,NULL,send_fun,(void *)&fd);
    pthread_create(&th2,NULL,recv_fun,(void *)&fd);

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    close(fd);
    return 0;
*/
}
void *send_fun(void *data)
{
    int fd = *((int *)data);
    while(1)
    {
        printf("请选择聊天方式：");
        printf("-1 群聊\n");
        printf("输入客户端编号私聊\n");
        printf("请选择：");
        scanf("%d",&msg.flge);
        printf("请输入聊天内容：");
        scanf("%s",msg.message);
        int n = send(fd,(char *)&msg,sizeof(msg),0);
        if(n != sizeof(msg))
        {
            perror("send error!\n");
            exit(1);
        }
    }
}

void *recv_fun(void *data)
{
    int fd = *((int *)data);
    struct Msg msg;
    while(1)
    {
        int n;
         n == recv(fd,(char *)&msg,sizeof(msg),0);
        if(n == -1)
        {
            my_err("recv error",__LINE__);
            exit(1);
        }
        printf("\n姓名为：%s\n,发的信息为：%s\n\n",msg.name,msg.message);
    }
}