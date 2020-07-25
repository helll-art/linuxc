#ifndef FIND_PASSWORD_H
#define FIND_PASSWORD_H
char getch();
void my_err(const char *string,int line);
int Check_Password(const char *string,const char *findPw);
int GetPassword(char* passwd) ;
char * Username_Password(int *);
#endif