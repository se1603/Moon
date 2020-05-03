/*
 * Author:guchangrong 2016051604218
 * date:2020-03-12
 * 用户管理的数据库代管者具体实现，对数据库进行查找和修改操作，并将查询的数据存入容器
 */
#include "manageuserbroker.h"
#include <iostream>
#include <vector>
#include "manageuser.h"

ManageUserBroker* ManageUserBroker::m_instance = new ManageUserBroker();

ManageUserBroker::ManageUserBroker()
{

}

ManageUserBroker::~ManageUserBroker()
{
    delete m_instance;
}

void ManageUserBroker::getInfoFromDataBase(std::vector<std::string> &v)
{
    MYSQL *mysql;
    mysql = new MYSQL;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql, "localhost", "root", "root", "Moon", 0, NULL, 0)){
        std::cout << "In getManageUser::Connect MYSQL failed." << std::endl;
    } else {
        std::cout << "In getManageUser::Connect MYSQL succeed." << std::endl;
    }
    std::string sql = "select * from ManageUser;";
    if(mysql_query(mysql, sql.data())){
        std::cout << "ManageUsers get failed." << std::endl;
    } else {
        result = mysql_use_result(mysql); //获取结果集
        while(1){
            row = mysql_fetch_row(result);   //获取下一行
            if(row == nullptr) break;
            std::vector<std::string> res;
            for(unsigned i = 0; i < mysql_num_fields(result); ++i){
                res.push_back(row[i]);
                v.push_back(row[i]);
                std::cout << i << " " << row[i] << std::endl;
            }
        }
        mysql_free_result(result);
        result = nullptr;
    }
    if(mysql != nullptr){
        mysql_close(mysql);
    }
    mysql_library_end();
}

void ManageUserBroker::initManageUser(std::string id, std::string informer, std::string bereported, std::string comment, std::string date, std::string informcount, std::string informmark)
{
    ManageUser manageuser = ManageUser(id, informer, bereported, comment, date, informcount, informmark);
    std::cout << "initreport mark" + informmark << std::endl;
    m_manageusers.insert(std::pair<std::string, ManageUser>(id, manageuser));
}

void ManageUserBroker::getManageUserInfo(std::string informmark, std::vector<std::string> &v)
{
    for(auto report = m_manageusers.begin(); report != m_manageusers.end(); report++){
        if(report->second.findByInformmark(informmark)){
            report->second.manageUserInfo(v);
        }
    }
}

void ManageUserBroker::getManageUserInfoByID(std::string id, std::vector<std::string> &v)
{
    auto report = m_manageusers.find(id);
    if(report != m_manageusers.end()){
        for(int i = 0; i != m_manageusers.count(id);i++,report++){
           report->second.manageUserInfo(v);
        }
    }
}

bool ManageUserBroker::ManageUserInfoSize()
{
    std::cout << m_manageusers.size() << std::endl;
    if(m_manageusers.size() != 0){
        return true;
    } else{
        return false;
    }
}

bool ManageUserBroker::addInformInfo(std::string id, std::string informer, std::string bereported, std::string comment, std::string date, std::string count)
{
    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "ManageUser connect failed" << std::endl;
    }else{
        std::cout << "ManageUser connect Successed" << std::endl;
    }

    std::cout << "add inform"  << std::endl;
    std::cout << id << std::endl;
    std::cout << informer << std::endl;
    std::cout << bereported << std::endl;
    std::cout << comment << std::endl;
    std::cout << date << std::endl;
    std::cout << count << std::endl;
    std::string sql = "insert into ManageUser(inform_id,imformer,bereported,comment,date,inform_count,inform_mark) values('"+id+"','"+informer+"','"+bereported+"','"+comment+"', '"+date+"', '"+count+"', 'untreated');";
    mysql_query(mysql,"set names gbk;");
    if(mysql_query(mysql,sql.data())){
        std::cout <<"insert failed"<< std::endl;
        return false;
    }else{
        return true;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
}

int ManageUserBroker::getbereportedcount(std::string bereported, std::vector<std::string> &v)
{
    int temp = 0;
    for(int i = 2; i < v.size(); i += 7){
        if(v[i] == bereported){
            temp++;
        }
    }
    return temp;
}

bool ManageUserBroker::updateCount(std::string bereported, std::string count)
{
    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "ManageUser connect failed" << std::endl;
    }else{
        std::cout << "ManageUser connect Successed" << std::endl;
    }

    std::cout << "update ManageUser"  << std::endl;
    std::string sql = "update ManageUser set inform_count = '"+count+"' where bereported  = '"+bereported+"';";
    if(mysql_query(mysql,sql.data())){
        std::cout <<"update failed"<< std::endl;
        return false;
    }else{
        return true;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
}

bool ManageUserBroker::updateInformmark(std::string id)
{
    MYSQL* mysql;
    mysql = new MYSQL;

    mysql_init(mysql);
    if(!mysql_real_connect(mysql,"localhost","root","root","Moon",0,NULL,0)){
        std::cout << "ManageUser connect failed" << std::endl;
    }else{
        std::cout << "ManageUser connect Successed" << std::endl;
    }

    std::cout << "update ManageUser"  << std::endl;
    std::string sql = "update ManageUser set inform_mark = 'processed' where inform_id  = '"+id+"';";
    if(mysql_query(mysql,sql.data())){
        std::cout <<"update failed"<< std::endl;
        return false;
    }else{
        return true;
    }
    if(mysql != nullptr)
        mysql_close(mysql);
}




