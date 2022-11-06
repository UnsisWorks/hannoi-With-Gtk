#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

MYSQL *con;
MYSQL_RES *res;
MYSQL_ROW row;

char *server = "127.0.0.1";
char *user = "unsis";
char *pass = "CETI";
char *database = "zury";

int main() {

    //conexion

    con = mysql_init(NULL);
    if(!mysql_real_connect(con, server, user, pass, database, 3306, NULL, 0)){

        fprintf(stderr, "%s ERROR \n", mysql_error(con));
    }


    //comandos:

    if(mysql_query(con, "show tables")){
        fprintf(stderr, "%s\n", mysql_error(con) );
        exit(1);

    }

    res = mysql_use_result(con);
    printf("las tablas son:\n");
    while((row = mysql_fetch_row(res)) != NULL)
        printf("%s\n", row[0]);

    //Cerramosconxion
    mysql_free_result(res);
    mysql_close(con);

    return 0;

}