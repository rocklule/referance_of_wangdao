#include "student_system.h"
#include "function.h"


FILE * open_file_read(char * path)
{
    FILE* temp = fopen(path, "rb");
    if (temp == NULL)
    {
        printf("Failed to open %s!\n", path);
        exit(0);
    }
    return temp;
}

FILE * open_file_write(char * path)
{
    FILE* temp = fopen(path, "wb");
    if (temp == NULL)
    {
        printf("Failed to open %s!\n", path);
        exit(0);
    }
    return temp;
}


void save_info(void)
{
    FILE *temp_file = open_file_write(address_info);

    pUSR_INFOR temp = pUsr_Infor->pNext_Usr_Infor;

    while (temp != NULL)
    {
        fprintf(temp_file, "%d\t%s\t%d\n", temp->usr_id, temp->usr_name, temp->usr_course_score);
        temp = temp->pNext_Usr_Infor;
    }

    fclose(temp_file);
    system_init(config_file_name, &pUsr_Account, &pUsr_Infor,
               &usr_account_num, &usr_infor_num);     
}


void save_account(void)
{
    FILE *temp_file = open_file_write(address_account);

    pUSR_ACCOUNT temp = pUsr_Account->pNext_Usr_Account;

    while (temp != NULL)
    {
        fprintf(temp_file, "%s\t%s\t%d\n", temp->usr_name, temp->usr_pwd, temp->usr_role);
        temp = temp->pNext_Usr_Account;
    }

    fclose(temp_file);
    system_init(config_file_name, &pUsr_Account, &pUsr_Infor,
               &usr_account_num, &usr_infor_num);     
}








