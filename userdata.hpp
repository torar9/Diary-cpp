#ifndef USERDATA_HPP
#define USERDATA_HPP

#include <ctime>
#include <QListWidgetItem>
#include <QString>

class UserData
{
private:
    std::string date;
    QString text;

public:
    UserData(std::string date, QString text);
    void setData(std::string date, QString text);
    void setText(QString text);
    QString getText();
    std::string getDate();
};

#endif // USERDATA_HPP
