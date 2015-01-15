
#ifndef func
#define func



void system_init(const char * config_file_name, 
    pUSR_ACCOUNT * pUsr_Account, pUSR_INFOR *pUsr_Infor, 
    USR_ACCOUNT_NUM* usr_account_num, USR_INFOR_NUM * usr_infor_num);



USR_ROLE role_confirm (pUSR_ACCOUNT pUsr_Account, char * usr_name,
    char * usr_pwd) ;


void show_system_menu(void);
void show_search_menu(void);

void role_confirm_interface(void);


#endif




