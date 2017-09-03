#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <iostream>

#include <QMessageBox>
#include <QString>

using namespace std;

class Messenger
{
private:
    Messenger();
    static Messenger* instance;
public:
    static Messenger* getInstance();
    void displayMessage(QString message);
};

#endif // MESSENGER_HPP
