/* @author: Zhaonian Luan, Copyright 2016 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <iostream>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    vector<QString> lab_files;
    vector<QString> order_files;

private slots:

    void on_start_clicked();

    void on_lab_triggered();

    void on_order_triggered();

    void on_reset_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
