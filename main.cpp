#include "mainwindow.h"
#include "tst_testlinkedlist.h"
#include "tst_testbst.h"
#include "tst_testcsv.h"
#include "tst_testanalysis.h"
#include <iostream>
#include <string>
#include <QApplication>

int main(int argc, char *argv[])
{
//      try {
//        test_linked_list();
//        test_bst_speed();
//        test_csv();
//        test_delta_analysis();
//        } catch (const std::string& ex) {
//                std::cout << ex << std::endl;
//        }
        //test_bst();
//        return 0;

        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
}
