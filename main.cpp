#include <QApplication>
#include <QIcon>
#include "diarywindow.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DiaryWindow w;
    w.setWindowTitle("Diary");
    w.show();

    return a.exec();
}
