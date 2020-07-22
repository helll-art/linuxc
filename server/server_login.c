#include<stdio.h>
#include<signal.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<errno.h>
#include "my_recv.h"

#define SERV_PORT 4507
#define LISTENQ 12


#define USERNAME 0
#define PASSWORD 1

int sock_fd,conn_fd;

void signal_fun(int signo)
{
    printf("Exit!\n");
    close(sock_fd);
    close(conn_fd);
    exit(-1);
}

struct userinfo
{
    char username[32];
    char password[32];
};
struct userinfo users[] = 
{
    {"linux","unix"},
    {"4507","4508"},
    {"clh","clh"},
    {"xl","xl"},
    {" "," "}
};

int find_name(const char *name)
{
    int i;
    if(name == NULL)
    {
        printf("in find_name,NULL pointer\n");
        return -2;
    }
    for(int i = 0 ;users[i].username[0] != ' ';i++)
    {
        if(strcmp(users[i].username,name) == 0)
        {
            return i;
        }
    }
    return -1;
}
void my_err(const char * string,int line)
{
    fprintf(stderr,"line : %d  ",line);
    perror(string);
    exit(0);
}
void send_data(int conn_fd,const char *string)
{
    if(send(conn_fd,string,strlen(string),0) < 0)
        my_err("send",__LINE__);
}
int main(void)
{
    signal(SIGINT,signal_fun);
    int pid;
    int user_num;
    
    socklen_t cli_len;
    struct sockaddr_in cli_addr,serv_addr;
    char recv_buf[BUFSIZ];
    sock_fd = socket(AF_INET,SOCK_STREAM,0);
    if(sock_fd < 0)
        my_err("socket",__LINE__);
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    cli_len = sizeof(struct sockaddr_in);
    int bindid = bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in));
    if(bindid < 0)
        my_err("bind",__LINE__);
    int listenid = listen(sock_fd,LISTENQ);
    if(listenid < 0)
        my_err("listen",__LINE__);
    //conn_fd = accept(sock_fd,(struct sockaddr *)&cli_addr,&cli_len);
    while(1)
    {
        //客户端与子进程进行连接，解放掉主进程，为了主进程能够去连接另一个客户端
        conn_fd = accept(sock_fd,(struct sockaddr *)&cli_addr,&cli_len);
        if(conn_fd < 0)
            my_err("connect",__LINE__);
        printf("accept a new client, ip : %s\n",inet_ntoa(cli_addr.sin_addr));
        int flag_recv = USERNAME;
        pid = fork();
        if (pid < 0)
            my_err("fork",__LINE__);
        if(pid == 0)
        {
            int name_num = 4;
            while(1)
            {
                if(flag_recv == USERNAME)
                {
                    strcpy(recv_buf,"请输入用户名：");
                    send_data(conn_fd,recv_buf);
                    int ret = recv(conn_fd,recv_buf,sizeof(recv_buf),0);
                    recv_buf[ret - 1] = '\0';
                    name_num = find_name(recv_buf);
                    if(name_num < 0 )
                    {
                        printf("find name failed\n");
                    }
                    flag_recv = PASSWORD;
                    //这里不能break，break后会直接跳出循环，不会输入密码
                    
                }
                if(flag_recv == PASSWORD)
                {
                    strcpy(recv_buf,"请输入密码：");
                    send_data(conn_fd,recv_buf);
                    int ret = recv(conn_fd,recv_buf,sizeof(recv_buf),0);
                    //recv 返回读取到的数据大小
                    //因为fgets函数会读取回车，所以需要 - 1
                    recv_buf[ret - 1] = '\0';
                    if(strcmp(recv_buf,users[name_num].password) == 0)
                    {
                        strcpy(recv_buf,"Welcome to login my tcp server\n");
                        send(conn_fd,recv_buf,strlen(recv_buf),0);
                        printf("%s login \n",users[name_num].username);
                        break;
                    }
                }
                
            }
        }
        else 
        {
            close(conn_fd);
        }
    }
    return 0;
}

