#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <regex>
#include <string>
#include <exception>

#include <boost/filesystem.hpp>
#include <pugixml.hpp>

#include "config.hpp"
#include "messenger.hpp"
#include "userdata.hpp"

class Database
{
private:
    static Database* instance;
    Messenger* msg;
    std::string location;
    std::string file_location;
    QListWidget* wdList = nullptr;
    std::vector<UserData> list;

    Database();
    Database(QListWidget *wdList);
    void updateView();
    void updateDatabase();
    void loadData();
    void setPath();
    size_t indexOf(const std::string date);

public:
    static Database* getInstance();
    UserData getData(const int index);
    void setView(QListWidget *wdList);
    void addData(UserData data);
    void editData(UserData Data);
    void removeData(UserData data);
    void removeData(const int index);
};

#endif //DATABASE_HPP
