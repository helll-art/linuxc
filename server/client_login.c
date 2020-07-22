#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include "my_recv.h"

#define SERV_PORT 4507
#define LISTENQ 12
#define INVALID_USERINFO 'n'
#define VALID_USERINFO 'y'

#define USERNAME 0
#define PASSWORD 1

int conn_fd;

int main(void)
{
    int serv_port = SERV_PORT;
    struct sockaddr_in serv_addr;
    char recv_buf[BUFSIZ];
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv_port);
    inet_aton("127.0.0.1",&serv_addr.sin_addr);
    conn_fd = socket(AF_INET,SOCK_STREAM,0);
    connect(conn_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr));
    printf("链接成功！\n");
    while(1)
    {
        recv(conn_fd,recv_buf,sizeof(recv_buf),0);
        printf("%s",recv_buf);
        fgets(recv_buf,sizeof(recv_buf),stdin);
        send(conn_fd,recv_buf,strlen(recv_buf),0);
    }
}