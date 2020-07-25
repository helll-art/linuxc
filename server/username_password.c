#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"find_password.h"
#include"mysql.h"

//总函数：
//int  Username_Password(void);

char getch()
{
	char c;
	system("stty -echo");  //不回显
	system("stty -icanon");//设置一次性读完操作，如使用getchar()读操作，不需要按enter
	c=getchar();
	system("stty icanon");//取消上面的设置
	system("stty echo");//回显
	return c;
}

void my_err(const char *string,int line)
{
    fprintf(stderr,"line : %d",line);
    perror(string);
    exit(-1);

}

int Check_Password(const char *string,const char *findPw)
{
    MYSQL mysql;
    if(NULL == (mysql_init(&mysql)))
        my_err("mysql init error!",__LINE__);
    if((mysql_library_init(0,NULL,NULL)) != 0)
        my_err("mysql library init error!",__LINE__);
    if(NULL == (mysql_real_connect(&mysql,"127.0.0.1","root","123456","test",0,NULL,0)))
        my_err("mysql real connect error!",__LINE__);
    if((mysql_set_character_set(&mysql,"utf8")) < 0)
        my_err("mysql set character set",__LINE__);

    MYSQL_RES *result;
    unsigned int num_fields;
    MYSQL_FIELD *field;
    MYSQL_ROW row;
    int ret;
    if((ret = mysql_query(&mysql,string)))
    {
        exit(-1);
    }
    if((result = mysql_store_result(&mysql)) == 0)
        my_err("mysql store result ",__LINE__);

    num_fields = mysql_num_fields(result);
    if(num_fields <= 0)
        printf("mysql num fields error!\n");
    if((row = mysql_fetch_row(result)) == NULL)
    {
        printf("\n该用户不存在！\n");
        return 2;
    }
    else
    {
        if((strcmp(findPw,row[0])) == 0)
            return 1;
        else 
            return -1;
    }
    
    /*while(row = mysql_fetch_row(result))
    {
        for(int i = 0 ; i < num_fields;i++)
        {
            if((strcmp(findPw,row[i])) == 0)
                return 1;
            else return -1;
        }
    }
    */
    return -1;
}
int Find_Back_Password(const char * string)
{
    MYSQL mysql;
    if(NULL == (mysql_init(&mysql)))
        my_err("mysql init error!",__LINE__);
    if((mysql_library_init(0,NULL,NULL)) != 0)
        my_err("mysql library init error!",__LINE__);
    if(NULL == (mysql_real_connect(&mysql,"127.0.0.1","root","123456","test",0,NULL,0)))
        my_err("mysql real connect error!",__LINE__);
    if((mysql_set_character_set(&mysql,"utf8")) < 0)
        my_err("mysql set character set",__LINE__);

    MYSQL_RES *result;
    unsigned int num_fields;
    MYSQL_FIELD *field;
    MYSQL_ROW row;
    int ret;
    ret = mysql_query(&mysql,string);
    if(ret != 0)
    {
        my_err("mysql query",__LINE__);
        exit(-1);
    }
    result = mysql_store_result(&mysql);
    if(result == 0)
        my_err("mysql store result ",__LINE__);
    num_fields = mysql_num_fields(result);
    if(num_fields <= 0)
        my_err("mysql num fields",__LINE__);
    if((row = mysql_fetch_row(result)) == NULL)
    {
        printf("该用户不存在！\n");
        return -1;
    }
    else 
    {
        while((field = mysql_fetch_field(result)))
        {
            printf("%-20s",field->name);
        }
        printf("\n");
        for( int i = 0 ; i< num_fields;i++)
        {
            printf("%-20s",row[i]);
        }
        printf("\n");
        
    }
    
}
int Insert_Account(const char *username,const char *password)
{
    char string[1024]="\0";
    MYSQL mysql;
    if(NULL == (mysql_init(&mysql)))
        my_err("mysql init error!",__LINE__);
    if((mysql_library_init(0,NULL,NULL)) != 0)
        my_err("mysql library init error!",__LINE__);
    if(NULL == (mysql_real_connect(&mysql,"127.0.0.1","root","123456","test",0,NULL,0)))
        my_err("mysql real connect error!",__LINE__);
    if((mysql_set_character_set(&mysql,"utf8")) < 0)
        my_err("mysql set character set",__LINE__);

    MYSQL_RES *result;
    unsigned int num_fields;
    MYSQL_FIELD *field;
    MYSQL_ROW row;
    sprintf(string,"insert into account values('%s','%s')",username,password);
    int ret;
    if((ret = mysql_query(&mysql,string)) != 0)
    {
        printf("注册用户失败，请重新注册！\n");
        exit(-1);
    }
    else
    {
        printf("注册成功！\n");
    }
    
}
int GetPassword(char* passwd) 
{ 
   int c;  
    int n = 0; 
    do
    { 
        c=getch(); 
        if (c != '\n'&& c!='\r' && c!=127)
        { 
            passwd[n] = c; 
            printf("*");
            n++;                   
        } 
        else if ((c != '\n'|c!='\r')&&c==127)//判断是否是回车或者是退格           
        {                           
            if(n>0)
            {
                n--;
                printf("\b \b");//输出退格                                                                      
            }
               
        } 
           
    }while(c != '\n' && c !='\r' ); 
    passwd[n] = '\0';  //消除一个多余的回车
    return n;
}
char * Username_Password(int *return_int )
{

    int choose = 0;
    char username[32]="\0";
    char password[32]="\0";
    char string[1024]="\0";
    printf("\t\t\t\t\t====================================================\n");
    printf("\t\t\t\t\t||                 \033[1m\033[32m欢迎来到聊天室\033[0m                 ||\n");
    printf("\t\t\t\t\t====================================================\n");
    printf("\t\t\t\t\t|                  \033[1m\033[34m请输入正确选项 :\033[0m                |\n ");
    printf("\t\t\t\t\t|                                                  |\n");
    printf("\t\t\t\t\t|                   \033[1m\033[34m1.注册账户.\033[0m                    |\n");
    printf("\t\t\t\t\t|                   \033[1m\033[34m2.登录账户.\033[0m                    |\n");
    printf("\t\t\t\t\t|                   \033[1m\033[34m3.找回密码.\033[0m                    |\n");
    printf("\t\t\t\t\t|                                                  |\n");
    printf("\t\t\t\t\t====================================================\n");
    printf("请输入：");
    scanf("%d",&choose);
    getch();
    if(choose == 1)
    {
        
        char Repassword[32]= "\0";
        printf("请输入用户名：");
        fgets(username,sizeof(username),stdin);
        username[strlen(username) - 1] = '\0';
        printf("请输入密码：");
        GetPassword(password);
        printf("\n请再次输入密码：");
        GetPassword(Repassword);
        if((strcmp(password,Repassword)) == 0)
        {
            
            Insert_Account(username,password);
            *return_int = 1;
        }
        else 
        {
            printf("Bye\n");
            *return_int = 1;
        }

    }
    else if(choose == 2)
    {
        int ret;
        printf("请输入账户：");
        fgets(username,sizeof(username),stdin); 
        username[strlen(username) -1 ] = '\0';
        sprintf(string,"select password from account where username = '%s'",username);
           
        printf("请输入密码：");
        GetPassword(password);
        //password[strlen(password) - 1] = '\0';
        if((ret = Check_Password(string,password)) == 1)
        {
            printf("密码正确！\n");
            *return_int = 2;
        }
        else 
        {
            for(int i = 2;i > 0;i--)
            {
                if(ret == 2)
                {
                    *return_int = 2;
                }
                printf("\n");
            
                printf("请重新输入密码（还有%d次机会）：",i);
                GetPassword(password);
                //password[strlen(password) - 1] = '\0';
                
                if((Check_Password(string,password)) == 1)
                {
                    printf("密码正确!\n");
                    *return_int = 2;
                }
            }
        }
    }  
    else if (choose ==3)
    {
        printf("请输入要找回密码的账户:");
        fgets(username,sizeof(username),stdin);
        username[strlen(username) -1 ] = '\0';
        sprintf(string,"select *from account where username = '%s'",username);
        Find_Back_Password(string);
        *return_int = 3;
    }
   char *return_string = username;
   return return_string;
}