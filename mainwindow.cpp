#include <iostream>
#include <vector>
#include <QFileDialog>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
        ui->setupUi(this);
}

MainWindow::~MainWindow()
{
        delete ui;
}

void MainWindow::on_lab_triggered()
{
        QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Lab File"),
                                                        ".",
                                                        "CSV File (*.csv)");
        if (filename.isEmpty())
                return;
        this->lab_files.push_back(filename);
        ui->file_list->addItem("Lab: " + filename);
        ui->file_list->item(ui->file_list->count()-1)->setForeground(Qt::green);
}

void MainWindow::on_order_triggered()
{
        QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Medication Order File"),
                                                        ".",
                                                        "CSV File (*.csv)");
        if (filename.isEmpty())
                return;
        this->order_files.push_back(filename);
        ui->file_list->addItem("Order: " + filename);
        ui->file_list->item(ui->file_list->count()-1)->setForeground(Qt::red);
}

void MainWindow::on_analyze_triggered()
{
}

void MainWindow::on_clear_all_files_triggered()
{
        this->lab_files.clear();
        this->order_files.clear();
        ui->file_list->clear();
}
