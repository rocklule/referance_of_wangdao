#ifndef head
#define head 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define USR_NAME_LEN 15
#define USR_PWD_LEN 10
#define USER 0
#define ADMIN 1
#define EXIT 9

typedef int USR_ACCOUNT_NUM;
typedef int USR_INFOR_NUM;
typedef int USR_ROLE;           //1管理员，0普通用户
typedef int SYSTEM_MENU_TYPE;   //1管理员，0普通用户


typedef struct usr_account_tag
{
    char usr_name[USR_NAME_LEN];
    char usr_pwd[USR_PWD_LEN];
    USR_ROLE  usr_role ;
    struct usr_account_tag * pNext_Usr_Account ;
} USR_ACCOUNT, *pUSR_ACCOUNT;

typedef struct usr_infor_tag
{
    int usr_id ;
    char usr_name[USR_NAME_LEN] ;
    int usr_course_score;
    struct usr_infor_tag *pNext_Usr_Infor ;
} USR_INFOR, *pUSR_INFOR;


extern char * config_file_name;

extern USR_ACCOUNT_NUM usr_account_num;
extern USR_INFOR_NUM usr_infor_num;
extern pUSR_ACCOUNT pUsr_Account;
extern pUSR_INFOR pUsr_Infor;
extern USR_ROLE usr_role;
extern SYSTEM_MENU_TYPE system_menu;
extern char address_info[100]; 
extern char address_account[100];
extern char buff[100];  


#endif


