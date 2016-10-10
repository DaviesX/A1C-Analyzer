#include "mainwindow.h"
#include "tst_testlinkedlist.h"
#include <QApplication>

int main(int argc, char *argv[])
{
        test_linked_list();

        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
}
