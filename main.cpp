#include "mainwindow.h"
#include "tst_testcsv.h"
#include "tst_testanalysis.h"
#include <iostream>
#include <string>
#include <QApplication>

int main(int argc, char *argv[])
{
        try {
                // test::test_csv();
                test::test_delta_analysis();
        } catch (const std::string& ex) {
                std::cout << ex << std::endl;
        }
        return 0;

        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
}
