#include "userdata.hpp"

UserData::UserData(std::string date, QString text)
{
    this->date = date;
    this->text = text;
}

void UserData::setData(std::string date, QString text)
{
    this->date = date;
    this->text = text;
}

void UserData::setText(QString text)
{
    this->text = text;
}

std::string UserData::getDate()
{
    return date;
}

QString UserData::getText()
{
    return text;
}
