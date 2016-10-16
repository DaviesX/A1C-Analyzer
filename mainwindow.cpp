#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <QFileDialog>
#include <QFile>
using namespace std;

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

void MainWindow::on_start_clicked()
{
    cout << "start clicked!" << endl;
}


void MainWindow::on_lab_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "C://",
                                                    "CSV File (*.csv)");
    this->lab_files.push_back(filename);
    ui->listWidget->addItem("Lab: " + filename);
    ui->listWidget->item(ui->listWidget->count()-1)->setForeground(Qt::green);
}

void MainWindow::on_order_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "C://",
                                                    "CSV File (*.csv)");
    this->order_files.push_back(filename);
    ui->listWidget->addItem("Order: " + filename);
    ui->listWidget->item(ui->listWidget->count()-1)->setForeground(Qt::red);
}

void MainWindow::on_reset_clicked()
{
    this->lab_files.clear();
    this->order_files.clear();
    ui->listWidget->clear();
}

