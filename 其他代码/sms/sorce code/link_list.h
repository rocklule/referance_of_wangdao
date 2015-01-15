
pUSR_ACCOUNT init_account(void);

int delete_account_byname(char * name);

void print_account(void);

void insert_account(char *usr_name, char*usr_pwd, USR_ROLE usr_role);

pUSR_ACCOUNT find_account(char*usr_name);







pUSR_INFOR init_infor(void);

int delete_infor_byid(int usr_id);

void print_infor(void);

void insert_infor(int usr_id , char *usr_name, int usr_course_score);

pUSR_INFOR find_infor_name( char *usr_name);

pUSR_INFOR find_infor_ID(int usr_id);

void sort_info_by_id(void);












