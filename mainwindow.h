/* @author: Zhaonian Luan, Copyright 2016 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QKeyEvent>
#include <map>
#include <utility>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void keyPressEvent(QKeyEvent* event);

private slots:
        void on_lab_triggered();

        void on_order_triggered();

        void on_analyze_triggered();

        void on_clear_all_files_triggered();

        void on_filter_triggered();

private:
        std::map<int, std::string>      lab_files;
        std::map<int, std::string>      order_files;
        std::map<int, std::string>      filter_files;

        Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
