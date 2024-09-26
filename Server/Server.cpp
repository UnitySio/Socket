#include "pch.h"
#include <iostream>

#include "jdbc/mysql_driver.h"

int main()
{
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

    return 0;
}

