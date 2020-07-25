#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<arpa/inet.h>


#include "find_password.h"

#define PORT 8081
#define MAX_SIZE 10

struct Msg{
    char *name;
    char message[BUFSIZ];
    int socket;
    int flge;
};



int conn_fd[MAX_SIZE];

void *recv_fun(void *arg);

int main()
{
    struct sockaddr_in sin,cin;
    int sfd,cfd;
    int Length = sizeof(struct sockaddr_in);
    int n;
    if((sfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        printf("socket error\n");
        exit(-1);
    }
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&(sin.sin_zero),8);
    if(bind(sfd,(struct sockaddr *)&sin,sizeof(sin)) < 0)
    {
        printf("bind error\n");
        exit(1);
    }
    printf("Bind success!\n");
    if(listen(sfd,MAX_SIZE) == -1)
    {
        printf("listen error!\n");
        exit(1);
    }
    printf("Listening...\n");
    int i;
    for(i = 0;i < MAX_SIZE;i++)
        conn_fd[i] = -1;

    printf("waiting...\n");
    while(1)
    {
        int i;
        for(i = 0;i < MAX_SIZE;i++)
        {
            if(conn_fd[i] == -1)
                break;
        } 

        if((conn_fd[i] = accept(sfd,(struct sockaddr *)&cin,&Length)) == -1)
        {
            perror("accept error");
            exit(1);
        }
        printf("有人加入编号为：%d\n",i);
        pthread_t th1;
        pthread_create(&th1,NULL,recv_fun,(void *)&conn_fd[i]);
    }
    return 0;

}

void *recv_fun(void *arg)
{
    int fd = *((int *)arg);
    struct Msg msg;
    int flge,num_send,num_recv;
    while(1)
    {
        int n = recv(fd,(char *)&msg,sizeof(msg),0);
        if(n <= 0)
        {
            printf("recv error\n");
            conn_fd[msg.socket] = -1;
            pthread_exit(NULL);
            exit(1);

        }
        int i;
        for(i = 0;i < MAX_SIZE;i++)
        {
            if(fd == conn_fd[i])
                break;

        }
        msg.socket = i;
        printf("接受到编号为：%d，%s消息为：%s，\n\n\n",msg.socket,msg.name,msg.message);

        if(msg.flge == -1)
        {
            for(i = 0;i < MAX_SIZE;i++)
            {
                if(conn_fd[i] != fd && conn_fd[i] != -1)
                {
                    num_send = send(conn_fd[i],(char *)&msg,sizeof(msg),0);
                    if(num_send < 0)
                        printf("send error\n");
                }
            }
        }
        else 
        {
            num_send = send(conn_fd[msg.flge],(char *)&msg,sizeof(msg),0);
            if(num_send < 0)
                printf("send error\n");
        }
    }
}
