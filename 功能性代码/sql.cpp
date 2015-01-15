#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HOST "127.0.0.1"
#define PORT 3306
#define USR "root"
#define PASSWORD "12345"
#define DB "student"
#define TABLE "student_info"

#define MAXLEN 50



int main(int argc, char const *argv[])
{
    char query[MAXLEN];         //用于暂存需要传送的查询语句
    MYSQL * connect = mysql_init(NULL);     //初始化＃链接结构体＃，返回指针
    MYSQL_RES * sql_res;                //暂存查询返回的内容
    MYSQL_ROW row;                  //＃行＃结构体，表示一行数据
    
    
    if (!mysql_real_connect(connect ,HOST, USR, PASSWORD, DB, PORT, NULL, 0)) {  //连接登录
        printf("Failed to connect database!");
        exit(-1);
    }
    
    sprintf(query, "select * from %s", TABLE);    
    if(mysql_real_query(connect, query, strlen(query))){        //投送查询语句
        printf("Failed to send query message!");
    }
    else{
        sql_res = mysql_store_result(connect);      //取得返回数据
    }
    
    row = mysql_fetch_row(sql_res);     //每次取一行，注意，row的类型是char**，相当于二维数组／指针的指针
    
    printf("%s\n", row[1]);     //打印第2列数据
    
    
    return 0;
}


