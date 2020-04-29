#include "managerbroker.h"

ManagerBroker* ManagerBroker::m_instance = new ManagerBroker();

ManagerBroker::ManagerBroker()
{

}

ManagerBroker::~ManagerBroker()
{
    delete m_instance;
}

void ManagerBroker::initManagers()
{
    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "Manager:Connect MYSQL failed." << std::endl;
    }else{
        std::cout << "Manager:Connect MYSQL succeed." << std::endl;
    }

    std::string sql = "select * from Manager;";

    if(mysql_query(mysql,sql.data())){
        std::cout << "查询失败(Manager)" << std::endl;
    }
    else
    {
        result = mysql_use_result(mysql);
        while(1)
        {
            row = mysql_fetch_row(result);
            if(row == nullptr){
                break;
            }else{
                std::string name;
                for(unsigned int i=0;i<mysql_num_fields(result);++i){
                    Manager *m = new Manager(std::string(row[0]),atoi(row[1]));
                    m_managers[row[0]] = m;
                }
            }
        }
    }
}

bool ManagerBroker::login(std::string number, std::string password)
{
    if(m_managers.find(number) != m_managers.end())
    {
        MYSQL *mysql;
        mysql = new MYSQL;

        MYSQL_RES *result;
        MYSQL_ROW row;

        mysql_init(mysql);
        if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
            std::cout << "Manager Connect MYSQL failed." << std::endl;
        }else{
            std::cout << "Manager Connect MYSQL succeed." << std::endl;
        }


        std::string sql = "select * from Manager where number = '"+ number
                + "' and password = '"+ password +"';";

        std::cout << sql << std::endl;

        if(mysql_query(mysql,sql.data())){
            std::cout << "查询失败(Manager login)" << std::endl;
            return false;
        }
        else
        {
            result = mysql_use_result(mysql);
            while(1)
            {
                row = mysql_fetch_row(result);
                if(row == nullptr){
                    return false;
                }else{
                    for(unsigned int i=0;i<mysql_num_fields(result);++i){
                        m_logined.push_back(m_managers[number]);
                    }

                    return true;
                }
            }
        }
        if(mysql != nullptr)
            mysql_close(mysql);
    }
    return false;
}

int ManagerBroker::managerIdentity(std::string number)
{
    return m_managers[number]->identity();
}

