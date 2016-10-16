/* @author: Zhaonian Luan, Copyright 2016 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    std::vector<QString>        lab_files;
    std::vector<QString>        order_files;

private slots:

    void on_lab_triggered();

    void on_order_triggered();

    void on_analyze_triggered();

    void on_clear_all_files_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
