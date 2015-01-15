#include "student_system.h"



//---------------------ACCOUNT BEGIN---------------------------


pUSR_ACCOUNT init_account(void)
{
    pUSR_ACCOUNT l;
    l = (pUSR_ACCOUNT) malloc(sizeof(struct usr_account_tag));
    l->pNext_Usr_Account = NULL;
    return l;
}


int delete_account_byname(char * name)   //search by name
{
    pUSR_ACCOUNT pre = pUsr_Account;    
    pUSR_ACCOUNT temp = pUsr_Account->pNext_Usr_Account;
    while (temp != NULL && strcmp(name, temp->usr_name)!=0)
    {
        pre = temp;
        temp = temp->pNext_Usr_Account;
    }

    if(temp == NULL) return -1;

    pre->pNext_Usr_Account = temp->pNext_Usr_Account;
    free(pre);
    return 0;
}


void print_account(void)
{
    pUSR_ACCOUNT np = pUsr_Account;

    printf("Account list:\n");
    printf("Name\tPassword\tRole\n");

    while (np->pNext_Usr_Account != NULL)
    {
        np = np->pNext_Usr_Account;
        printf("%s\t%s\t\t%d\n", np->usr_name, np->usr_pwd, np->usr_role);
    }
    printf("Totally %d records.\n", usr_account_num);
}



void insert_account(char *usr_name, char *usr_pwd, USR_ROLE usr_role)
{
    pUSR_ACCOUNT temp;

    temp = (pUSR_ACCOUNT) malloc(sizeof(struct usr_account_tag));

    strcpy(temp->usr_name, usr_name);
    strcpy(temp->usr_pwd, usr_pwd);
    temp->usr_role = usr_role;

    temp->pNext_Usr_Account = pUsr_Account->pNext_Usr_Account;
    pUsr_Account->pNext_Usr_Account = temp;
}




pUSR_ACCOUNT find_account(char *usr_name)
{
    pUSR_ACCOUNT temp = pUsr_Account->pNext_Usr_Account;
    while (temp != NULL &&
            strcmp(temp->usr_name , usr_name) != 0 )
    {   
///     printf("%lu,%lu,%s\n",strlen(temp->usr_name),strlen(usr_name),temp->usr_name);
        temp = temp->pNext_Usr_Account;
    }

    return temp;
}



//---------------------ACCOUNT END---------------------------



//==========================================================



//---------------------STUDENT INFO BEGIN--------------------





pUSR_INFOR init_infor(void)
{
    pUSR_INFOR l;
    l = (pUSR_INFOR) malloc(sizeof(struct usr_infor_tag));
    l->pNext_Usr_Infor = NULL;
    return l;
}


int delete_infor_byid(int usr_id)   //search by id
{
    pUSR_INFOR pre = pUsr_Infor;    
    pUSR_INFOR temp = pUsr_Infor->pNext_Usr_Infor;
    while (temp != NULL && temp->usr_id != usr_id)
    {
        pre = temp;
        temp = temp->pNext_Usr_Infor;
    }

    if(temp == NULL) return -1;

    pre->pNext_Usr_Infor = temp->pNext_Usr_Infor;
    free(pre);
    return 0;
}



void print_infor(void)
{
    pUSR_INFOR np = pUsr_Infor;

    printf("\nStudent Informaiton List:\n");
    printf("ID\tName\t\tScore\n");

    while (np->pNext_Usr_Infor != NULL)
    {
        np = np->pNext_Usr_Infor;
        printf("%d\t%s\t\t%d\n", np->usr_id, np->usr_name, np->usr_course_score);
    }
    printf("Totally %d records.\n", usr_infor_num);
}




void insert_infor(int usr_id , char *usr_name, int usr_course_score)
{
    pUSR_INFOR temp;

    temp = (pUSR_INFOR) malloc(sizeof(struct usr_infor_tag));

    strcpy(temp->usr_name, usr_name);
    temp->usr_id = usr_id;
    temp->usr_course_score = usr_course_score;

    temp->pNext_Usr_Infor = pUsr_Infor->pNext_Usr_Infor;
    pUsr_Infor->pNext_Usr_Infor = temp;
}




pUSR_INFOR find_infor_name(char *usr_name)
{
    pUSR_INFOR temp = pUsr_Infor->pNext_Usr_Infor;
    while (temp != NULL && strcmp(temp->usr_name , usr_name) != 0 )
    {
        temp = temp->pNext_Usr_Infor;
    }
    return temp;
}


pUSR_INFOR find_infor_ID(int usr_id)
{
    pUSR_INFOR temp = pUsr_Infor->pNext_Usr_Infor;
    while (temp != NULL && temp->usr_id != usr_id)
    {
        temp = temp->pNext_Usr_Infor;
    }
    return temp;
}


void sort_info_by_id(void)
{
    pUSR_INFOR sweep = pUsr_Infor->pNext_Usr_Infor->pNext_Usr_Infor , insert, pre, temp;
    pUsr_Infor->pNext_Usr_Infor->pNext_Usr_Infor = NULL;

    while (sweep != NULL)
    {

        insert = pUsr_Infor->pNext_Usr_Infor;
        pre = pUsr_Infor;

        while (insert != NULL &&
                insert->usr_id < sweep->usr_id)
        {
            pre = insert;
            insert = insert->pNext_Usr_Infor;
        }
        temp = sweep->pNext_Usr_Infor;
        sweep->pNext_Usr_Infor = insert;
        pre->pNext_Usr_Infor = sweep;

        sweep = temp;
    }
}





