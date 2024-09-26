#include "pch.h"
#include <iostream>

#include "jdbc/mysql_driver.h"
#include "jdbc/cppconn/resultset.h"
#include "jdbc/cppconn/statement.h"

int main()
{
    try
    {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

        const std::string host_name = "tcp://own-game-engine.cdyyimi0op9h.ap-southeast-2.rds.amazonaws.com";
        const std::string user_name = "admin";
        const std::string password = "dnwls3388";

        std::unique_ptr<sql::Connection> connection(driver->connect(host_name, user_name, password));
        connection->setSchema("socket_db");

        std::unique_ptr<sql::Statement> statement(connection->createStatement());
        std::unique_ptr<sql::ResultSet> result_set(statement->executeQuery("SELECT * FROM account_info"));
        
        while (result_set->next())
        {
            std::cout << "id: " << result_set->getInt("id") << ", password: " << result_set->getString("password") << std::endl;
        }
    }
    catch (sql::SQLException e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

