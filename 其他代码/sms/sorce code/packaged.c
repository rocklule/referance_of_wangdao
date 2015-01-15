#include "student_system.h"
#include "link_list.h"
#include "file_operation.h"
#include "function.h"


void add_usr_account(char * temp_name)
{
    char temp_pwd1[USR_PWD_LEN], temp_pwd2[USR_PWD_LEN];   
    int temp_role = 0xffffffff; 
    printf("Input his/her password: ");
    scanf("%s", temp_pwd1);
    printf("Confirm the password: ");
    scanf("%s", temp_pwd2);

    while(strcmp(temp_pwd2, temp_pwd1)!=0)
    {
        printf("Wrong, two inputs are not same! ");
        printf("Input his/her password: ");
        scanf("%s", temp_pwd1);
        printf("Confirm the password: ");
        scanf("%s", temp_pwd2);
    }

    while(printf("\nInput his/her Role:\n1.admin  2.normal user.\n")
            ,0==scanf("%d", &temp_role))
    {
        fgets(buff, 100, stdin);
        printf("Wrong! Input his/her Role again: ");
    }

    insert_account(temp_name, temp_pwd1, temp_role);
    save_account();
}


void add_infor(int temp_id)
{
    int temp_score = 0xffffffff;
    char temp_name[USR_NAME_LEN];

    printf("Input his/her name: ");
    scanf("%s", temp_name);

    while(printf("Input his/her score: "),0==scanf("%d", &temp_score))
    {
        fgets(buff, 100, stdin);
        printf("Wrong! Input his/her score again: ");
    }

    insert_infor(temp_id,temp_name,temp_score);
    save_info();
}



void print_single_infor(pUSR_INFOR np)
{
    if(np == NULL)
        printf("Wrong, can't find!");
    else
    {
        printf("ID\tName\t\tScore\n");
        printf("%d\t%s\t\t%d\n", np->usr_id, np->usr_name, np->usr_course_score);
    }
}




void search_by_id(void)
{
    int temp_id = 0xffffffff;
    system("clear");
    printf("\nInput the ID you want to search: ");
    
    while(0==scanf("%d", &temp_id))
    {
        printf("Wrong input! Try again!\n");
        fgets(buff, 100, stdin);
        system("clear");
        printf("\nInput the ID you want to search: ");        
    }
    fgets(buff, 100, stdin);

    print_single_infor(find_infor_ID(temp_id));
    
    getchar();
}



void search_by_name(void)
{
    char temp[USR_NAME_LEN];
    system("clear");
    printf("\nInput the NAME you want to search: ");
    scanf("%s", temp);
    fgets(buff, 100, stdin);
    print_single_infor(find_infor_name(temp));

    getchar();
}



void add_infor_interface(void)
{
    int temp_id = 0xffffffff;
    system("clear");

    while(printf("\nInput his/her ID: "),0==scanf("%d", &temp_id))
        {
            fgets(buff, 100, stdin);
            printf("Wrong! Input his/her ID: ");
        }

    if(find_infor_ID(temp_id)==NULL)
    {
        add_infor(temp_id);
        printf("Insert successfully! \n");
        getchar();
        fgets(buff, 100, stdin);
    }
    else
    {
        printf("Sorry, this ID already exist! Try another one!\n");
        getchar();
        fgets(buff, 100, stdin);
        add_infor_interface();
    }

}




void delete_infor_interface(void)
{
    system("clear");
    int temp_id = 0xffffffff;
    print_infor();
    while(printf("\nInput his/her ID: "),0==scanf("%d", &temp_id))
        {
            fgets(buff, 100, stdin);
            printf("Wrong! Input his/her ID again: ");
        }

    if(-1==delete_infor_byid(temp_id))
    {
        printf("Delet failed! Wrong input, try again!\n");
        delete_infor_interface();
    }
    else
    {
        save_info();

        printf("Delete successfully! \n");
        getchar();
        fgets(buff, 100, stdin);
    }

}



void update_infor_interface(void)
{
    system("clear");
    int temp_id = 0xffffffff, temp_score = 0xffffffff;
    char temp_name[USR_NAME_LEN];
    print_infor();
    while(printf("\nInput his/her ID: "),0==scanf("%d", &temp_id))
        {
            fgets(buff, 100, stdin);
            printf("Wrong! Input his/her ID again: ");
        }
    if(-1==delete_infor_byid(temp_id))
    {
        printf("Wrong input, try again!\n");
        update_infor_interface();
    }
    else
    {
        add_infor(temp_id);
        printf("Update successfully! \n");
        getchar();
        fgets(buff, 100, stdin);
    }        
}




void add_usr_account_interface(void)
{
    char temp_name[USR_NAME_LEN];
    system("clear");

    printf("Input his/her name: ");
    scanf("%s", temp_name);


    if(find_account(temp_name)==NULL)
    {   
        add_usr_account(temp_name);
        printf("Insert successfully! \n");
        getchar();
        fgets(buff, 100, stdin);
    }
    else
    {
        printf("Sorry, this NAME already exist! Try another one!\n");
        getchar();
        fgets(buff, 100, stdin);
        add_usr_account_interface();
    }
}



void print_single_account(pUSR_ACCOUNT np)
{
    if(np == NULL)
        printf("Wrong, can't find!");
    else
    {
        printf("Name\tPassword\tRole\n");
        printf("%s\t%s\t\t%d\n", np->usr_name, np->usr_pwd, np->usr_role);        
    }
}



void search_account(void)
{
    char temp[USR_NAME_LEN];
    system("clear");
    printf("\nInput the NAME you want to search: ");
    scanf("%s", temp);
    fgets(buff, 100, stdin);

    print_single_account(find_account(temp));

    getchar();
}



void delet_account_interface(void)
{
    system("clear");
    char temp_name[USR_NAME_LEN];
    print_account();
    printf("\nInput his/her NAME: ");
    scanf("%s", temp_name);

    if(-1==delete_account_byname(temp_name))
    {
        printf("Delet failed! Wrong input, try again!\n");
        delet_account_interface();
    }
    else
    {
        save_account();
        printf("Delete successfully! \n");
        getchar();
        fgets(buff, 100, stdin);
    }
}




void update_account_interface(void)
{
    char temp_name[USR_NAME_LEN];
    system("clear");
    print_account();
    printf("\nInput his/her NAME: ");
    scanf("%s", temp_name);

    if(-1==delete_account_byname(temp_name))
    {
        printf("Wrong input, try again!\n");
        update_account_interface();
    }
    else
    {
        add_usr_account(temp_name);
        printf("Update successfully! \n");
        getchar();
        fgets(buff, 100, stdin);
    }
}






