#include "student_system.h"
#include "function.h"

char *config_file_name = "configuration.txt";

//---------------GLOBLE VER-------------------------

USR_ACCOUNT_NUM usr_account_num = 0;    //账户计数器
USR_INFOR_NUM usr_infor_num = 0;        //用户信息计数器
pUSR_ACCOUNT pUsr_Account = NULL;       //用户账户链表指针
pUSR_INFOR pUsr_Infor = NULL;           //用户信息链表指针

char address_account[100];              //账户文件地址
char address_info[100];                 //信息文件地址
char buff[100];                        //用于清空缓冲区

USR_ROLE usr_role = 0;
SYSTEM_MENU_TYPE system_menu = 0;       //int，暂存用户选项

//--------------------------------------------------


int main(int argc, char const *argv[])
{

    system_init(config_file_name, &pUsr_Account, &pUsr_Infor,
                &usr_account_num, &usr_infor_num);  //修改全局变量


    while (system_menu != EXIT)
    {

        switch (system_menu)
        {
        case 0 : role_confirm_interface();    //用户登录界面
            break;

        case 1 : show_system_menu(); 
            break;

        case 2 : show_search_menu();  
            break;
        }
    }
    return 0;
}