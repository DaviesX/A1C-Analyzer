#include "mainwindow.h"
//#include "tst_testlinkedlist.h"
#include "tst_testbst.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//        test_linked_list();
        test_bst();

        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
}
