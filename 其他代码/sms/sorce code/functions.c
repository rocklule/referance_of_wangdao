#include "student_system.h"
#include "link_list.h"
#include "file_operation.h"
#include "packaged.h"


//----------------------raw----------------------------------

void system_init(const char *config_file_name,
                 pUSR_ACCOUNT *pUsr_Account, pUSR_INFOR *pUsr_Infor,
                 USR_ACCOUNT_NUM *usr_account_num, USR_INFOR_NUM *usr_infor_num)
{
    system("clear");
    //-----------------GET CONFIG FILE--------------------
    FILE *config_file = fopen(config_file_name, "rb");
    if (config_file == NULL)
    {
        printf("Failed to open config file!\n");
        exit(0);
    }


    //------------GET THE PATH OF DATA BASE-----------------

    fscanf(config_file, "%s", address_account);
    fscanf(config_file, "%s", address_info);

    if (strlen(address_account) == 0 || strlen(address_info) == 0)
    {
        printf("Failed to load data base!\n");
        exit(0);
    }


    //------------OPEN TWO DATA BASES-----------------------

    FILE *usr_account_file = open_file_read(address_account);
    FILE *usr_infor_file = open_file_read(address_info);


    //-------------------------------------------------------
    const int temp_maxlen = USR_PWD_LEN + USR_NAME_LEN + 5;
    char temp[temp_maxlen], temp_usr_name[USR_NAME_LEN];
    //--------------------CREATE ACCOUNT LIST---------------

    char temp_usr_pwd[USR_PWD_LEN];
    USR_ROLE temp_usr_role = 0;

    *pUsr_Account = init_account();     //指针的指针


    while (memset(temp, 0, temp_maxlen),
            fgets(temp, temp_maxlen, usr_account_file) != NULL)
    {
        if (0 == sscanf(temp, "%s %s %d", temp_usr_name, temp_usr_pwd, &temp_usr_role))
        {
            printf("Failed to get user account!\n");
            exit(0);
        }
        insert_account(temp_usr_name, temp_usr_pwd, temp_usr_role);
        (*usr_account_num)++;
    }
    ////print_account(*pUsr_Account);

    //-----------------CREATE STUDENT INFO LIST--------------------

    int temp_usr_id, temp_usr_score;

    *pUsr_Infor = init_infor();     //指针的指针


    while (memset(temp, 0, temp_maxlen),
            fgets(temp, temp_maxlen, usr_infor_file) != NULL)
    {
        if (0 == sscanf(temp, "%d %s %d", &temp_usr_id, temp_usr_name, &temp_usr_score))
        {
            printf("Failed to get user account!\n");
            exit(0);
        }
        insert_infor(temp_usr_id, temp_usr_name, temp_usr_score);
        (*usr_infor_num)++;
    }

    sort_info_by_id();

    ///print_infor(*pUsr_Infor);
    ///printf("account num:%d, infor num:%d\n",*usr_account_num ,*usr_infor_num);
    ///getchar();
    ///exit(0);
    fclose(config_file);
    fclose(usr_account_file);
    fclose(usr_infor_file);    
}







USR_ROLE role_confirm (pUSR_ACCOUNT pUsr_Account, char *usr_name,
                       char *usr_pwd)          //返回用户权限级别
{
    ///printf("%s\n",usr_name );
    pUSR_ACCOUNT temp = find_account(usr_name);

    if (temp == NULL)
    {
        printf("\nYour name is not listed!\n");
        getchar(); fgets(buff, 100, stdin);
        system_menu = 0;
        return  0;
    }
    else if (strcmp(temp->usr_pwd, usr_pwd) == 0)
    {
        printf("Welcome %s!\tPress any key to continue...\n", usr_name);
        getchar();   fgets(buff, 100, stdin);
        system_menu = 1;
        return temp->usr_role;
    }
    else
    {
        printf("\nWorng password or username!\n");
        printf("Try again!\n");
        getchar();  fgets(buff, 100, stdin);
        system_menu = 0;
        return  0 ;
    }

}






void show_system_menu(void)
{
    system("clear");
    int choice = 10;

    printf(" |===========================================================|\n");
    printf(" |---------------- Student Management System ----------------|\n");
    printf(" |-----------------------------------------------------------|\n");
    printf(" |----------------------- ver:1.0 -- 2014.06.14 -- by:Rock Lu|\n");
    printf(" |===========================================================|\n\n");
    printf("\t1. Search student information.\n");
    if (usr_role == 1)
    {
        printf("\t2. Add student information.\n");
        printf("\t3. Update student information.\n");
        printf("\t4. Delete student information.\n");
        printf("\t5. Add user account.\n");
        printf("\t6. Update user account.\n");
        printf("\t7. Delete user account.\n");
        printf("\t8. Search user account.\n");
    }
    printf("\t9. Switch user / Relogin.\n");
    printf("\t0. Exit.\n\n");

    printf(" Select your operation by press the number: ");

    scanf("%d", &choice);
    fgets(buff, 100, stdin);

    if (usr_role == 0 && choice >= 2 && choice <= 8)
        choice = 10;             //防止普通用户选高级功能


    switch (choice)
    {
    case 1 :    system_menu = 2;
        break;
    case 2 :    add_infor_interface();
        break;
    case 3 :    update_infor_interface();
        break;
    case 4 :    delete_infor_interface();
        break;
    case 5 :    add_usr_account_interface();
        break;
    case 6 :    update_account_interface();
        break;
    case 7 :    delet_account_interface();
        break;
    case 8 :    search_account();
        break;
    case 9 :    system_menu = 0;
        break;
    case 0 :    system_menu = 9;
        break;
    }

}





void show_search_menu(void)
{
    system("clear");
    int choice = 10;

    printf(" ===================================================== \n");
    printf(" ------------------------ Search --------------------- \n");
    printf(" ===================================================== \n\n");
    if (usr_role == 1)
    {
        printf("\t0. List all.\n");
    }
    printf("\t1. Search by ID.\n");
    printf("\t2. Search by name\n");
    printf("\t3. Return main manual.\n\n");
    printf(" Select your operation by press the number: ");

    scanf("%d", &choice);
    fgets(buff, 100, stdin);

    if (usr_role == 0 && choice == 0)
        choice = 10;             //防止普通用户选高级功能


    switch (choice){
        case 0 :    print_infor(); getchar();
            break;
        case 1 :    search_by_id();
            break;
        case 2 :    search_by_name();
            break;
        case 3 :   system_menu = 1;
            break;
    }

}


void role_confirm_interface(void)
{
    system("clear");

    char usr_name[USR_NAME_LEN];
    char usr_pwd[USR_PWD_LEN];


    printf("===================================================== \n");
    printf("----------------------wlecome!----------------------- \n");
    printf("===================================================== \n");
    printf("\n");

    printf("Please input your user name:  (Or input \"0\" to exit)\n");
    scanf("%s", usr_name);
    if(atoi(usr_name)==0) exit(0);

    printf("And your password please:\n");
    scanf("%s", usr_pwd);
    printf("\n");


    usr_role = role_confirm (pUsr_Account, usr_name, usr_pwd) ;

}




























