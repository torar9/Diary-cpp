#ifndef DIARYWINDOW_HPP
#define DIARYWINDOW_HPP

#include <iostream>
#include <QMainWindow>

#include "database.hpp"
#include "config.hpp"

using namespace std;

namespace Ui{ class DiaryWindow; }

class DiaryWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::DiaryWindow *ui;
    Database* database = nullptr;
    bool isEdited = false;
    int selectedItem = -1;

    std::string getTimeFormat();
    void displayMessage();
    void clearInput();
    void setDefault();

private slots:
    void on_RemoveButton_clicked();
    void on_EditButton_clicked();
    void on_list_clicked(const QModelIndex &index);
    void on_list_doubleClicked(const QModelIndex &index);
    void on_save_button_clicked();
    void on_tabBar_tabBarClicked(int index);

public:
    explicit DiaryWindow(QWidget *parent = 0);
    ~DiaryWindow();
};

#endif // DIARYWINDOW_HPP
