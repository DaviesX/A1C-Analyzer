#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
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

void MainWindow::open_lab()
{

}

void MainWindow::on_lab_triggered()
{
    cout << "lab triggered!" << endl;
}

void MainWindow::on_order_triggered()
{
    cout << "order triggered!" << endl;
}
