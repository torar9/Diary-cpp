#include "diarywindow.hpp"
#include "ui_diarywindow.h"

DiaryWindow::DiaryWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::DiaryWindow)
{
    ui->setupUi(this);
    database = database->getInstance();
    database->setView(ui->list);
}

DiaryWindow::~DiaryWindow()
{
    delete ui;
}

std::string DiaryWindow::getTimeFormat()
{
    time_t now;
    struct tm* info;
    char buffer[80];

    time (&now);
    info = localtime(&now);

    strftime(buffer,sizeof(buffer),"%H:%M:%S_%d.%m.%Y", info);
    string ftime(buffer);
    ftime += "#" + to_string(rand() % 10000 + 1);

    return ftime;
}

void DiaryWindow::clearInput()
{
    ui->text_field->clear();
    ui->text_label->clear();
}

void DiaryWindow::setDefault()
{
    isEdited = false;
    clearInput();
    ui->tabBar->setCurrentIndex(LIST_TAB);
}

void DiaryWindow::on_RemoveButton_clicked()
{
    if(selectedItem >= 0)
    {
        database->removeData(selectedItem);
    }
    ui->EditButton->setEnabled(false);
    selectedItem = -1;
}

void DiaryWindow::on_EditButton_clicked()
{
    if(selectedItem >= 0)
    {
        try
        {
            UserData eData = database->getData(selectedItem);
            ui->tabBar->setCurrentIndex(NEW_TAB);
            ui->text_field->setPlainText(eData.getText());
            ui->text_label->setText(QString(eData.getDate().c_str()));
            isEdited = true;
        }
        catch(std::out_of_range &e)
        {
            cerr << e.what() << endl;
        }
    }
    ui->EditButton->setEnabled(false);
    selectedItem = -1;
}

void DiaryWindow::on_list_clicked(const QModelIndex &index)
{
    ui->EditButton->setEnabled(true);
    selectedItem = index.row();
}

void DiaryWindow::on_list_doubleClicked(const QModelIndex &index)
{
    selectedItem = index.row();
    on_EditButton_clicked();
}

void DiaryWindow::on_save_button_clicked()
{
    if(isEdited)
    {
        UserData data(ui->text_label->text().toStdString(), ui->text_field->toPlainText());
        if(data.getText().isEmpty())
            database->removeData(data);
        else
        {
            database->editData(data);
        }
        isEdited = false;
        clearInput();
        ui->tabBar->setCurrentIndex(LIST_TAB);
    }
    else
    {
        QString text = ui->text_field->toPlainText();
        if(!text.isEmpty())
        {
            UserData usd(getTimeFormat(), text);
            database->addData(usd);
        }
        clearInput();
        ui->tabBar->setCurrentIndex(LIST_TAB);
    }
}

void DiaryWindow::on_tabBar_tabBarClicked(int index)
{
    if(index == 0)
    {
        isEdited = false;
        clearInput();
    }
}
