#include "messenger.hpp"

Messenger* Messenger::instance = nullptr;

Messenger::Messenger()
{

}

Messenger* Messenger::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Messenger();
    }

    return instance;
}

void Messenger::displayMessage(QString message)
{
    QMessageBox* msg = new QMessageBox();

    msg->setAttribute(Qt::WA_DeleteOnClose);
    msg->setModal(true);
    msg->setText(message);
    msg->show();
}
