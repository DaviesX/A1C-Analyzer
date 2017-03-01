/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *lab;
    QAction *order;
    QAction *analyze;
    QAction *clear_all_files;
    QAction *filter;
    QAction *query;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QListWidget *file_list;
    QGraphicsView *chart_area;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuData;
    QStatusBar *status_bar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(500, 350);
        lab = new QAction(MainWindow);
        lab->setObjectName(QStringLiteral("lab"));
        order = new QAction(MainWindow);
        order->setObjectName(QStringLiteral("order"));
        analyze = new QAction(MainWindow);
        analyze->setObjectName(QStringLiteral("analyze"));
        clear_all_files = new QAction(MainWindow);
        clear_all_files->setObjectName(QStringLiteral("clear_all_files"));
        filter = new QAction(MainWindow);
        filter->setObjectName(QStringLiteral("filter"));
        query = new QAction(MainWindow);
        query->setObjectName(QStringLiteral("query"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        file_list = new QListWidget(centralWidget);
        file_list->setObjectName(QStringLiteral("file_list"));
        file_list->setAutoFillBackground(false);

        gridLayout->addWidget(file_list, 0, 0, 1, 1);

        chart_area = new QGraphicsView(centralWidget);
        chart_area->setObjectName(QStringLiteral("chart_area"));

        gridLayout->addWidget(chart_area, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 29));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuData = new QMenu(menuBar);
        menuData->setObjectName(QStringLiteral("menuData"));
        MainWindow->setMenuBar(menuBar);
        status_bar = new QStatusBar(MainWindow);
        status_bar->setObjectName(QStringLiteral("status_bar"));
        MainWindow->setStatusBar(status_bar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuData->menuAction());
        menuFile->addAction(lab);
        menuFile->addAction(order);
        menuFile->addAction(filter);
        menuFile->addAction(clear_all_files);
        menuData->addAction(analyze);
        menuData->addAction(query);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "A1C Data Analyzer", 0));
#ifndef QT_NO_STATUSTIP
        MainWindow->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        lab->setText(QApplication::translate("MainWindow", "Load lab data", 0));
        order->setText(QApplication::translate("MainWindow", "Load order data", 0));
        analyze->setText(QApplication::translate("MainWindow", "Confirm data", 0));
        clear_all_files->setText(QApplication::translate("MainWindow", "Clear All", 0));
        filter->setText(QApplication::translate("MainWindow", "Load filter", 0));
        query->setText(QApplication::translate("MainWindow", "Query", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuData->setTitle(QApplication::translate("MainWindow", "Analyze", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
