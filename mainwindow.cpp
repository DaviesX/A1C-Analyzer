#include <iostream>
#include <vector>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configdialog.h"
#include "querydialog.h"

#include "linkedbst.h"
#include "analyzer.h"
#include "csv.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
        ui->setupUi(this);

        config_dialog = new ConfigDialog(this);
        query_dialog = new QueryDialog(this);
        ui->status_bar->showMessage("A1C Analyzer Started");
}

MainWindow::~MainWindow()
{
        delete ui;
}

void MainWindow::on_lab_triggered()
{
        QStringList filenames = QFileDialog::getOpenFileNames(this,
                                                              tr("Lab File"),
                                                              ".",
                                                              "CSV File (*.csv)");
        for (QString filename: filenames) {
                this->lab_files.insert(std::pair<int, std::string>(ui->file_list->count(), filename.toStdString()));
                ui->file_list->addItem("Lab: " + filename);
                ui->file_list->item(ui->file_list->count()-1)->setForeground(Qt::darkGreen);

                needs_analysis = true;
        }
}

void MainWindow::on_order_triggered()
{
        QStringList filenames = QFileDialog::getOpenFileNames(this,
                                                              tr("Medication Order File"),
                                                              ".",
                                                              "CSV File (*.csv)");
        for (QString filename: filenames) {
                this->order_files.insert(std::pair<int, std::string>(ui->file_list->count(), filename.toStdString()));
                ui->file_list->addItem("Order: " + filename);
                ui->file_list->item(ui->file_list->count()-1)->setForeground(Qt::darkBlue);

                needs_analysis = true;
        }
}

void MainWindow::on_filter_triggered()
{
        QStringList filenames = QFileDialog::getOpenFileNames(this,
                                                              tr("Medication Filter File"),
                                                              ".",
                                                              "CSV File (*.csv)");
        for (QString filename: filenames) {
                this->order_files.insert(std::pair<int, std::string>(ui->file_list->count(), filename.toStdString()));
                ui->file_list->addItem("Filter: " + filename);
                ui->file_list->item(ui->file_list->count()-1)->setForeground(Qt::darkGray);

                needs_analysis = true;
        }
}

void MainWindow::on_analyze_triggered()
{
        config_dialog->exec();

        if (config_dialog->is_canceled())
                return ;

        QString output_file = config_dialog->get_output_file();
        float a1c_margin = config_dialog->get_a1c_margin();

        ui->status_bar->showMessage("Analyzing... just a moment");

        db.reset();

        try {
                for (std::pair<int, std::string> pair: this->order_files)
                        csv::load_medication_order(pair.second, db.orders);

                for (std::pair<int, std::string> pair: this->lab_files)
                        csv::load_lab_measure(pair.second, db.measures);

                for (std::pair<int, std::string> pair: this->filter_files)
                        csv::load_drug_filter(pair.second, db.filter);
        } catch (const std::string& ex) {
                QMessageBox::information(this, "Couldn't load file", QString::fromStdString(ex), QMessageBox::Critical);
                ui->status_bar->showMessage("Failed to load dataset");
                return;
        }

        LinkedBST<LabMeasure> cleaned_lab;
        LinkedBST<MedicationOrder> cleaned_orders;
        analysis::preprocess(db.measures, "A1C", 0.0f, db.lab_patients, cleaned_lab);
        analysis::preprocess(db.orders, db.filter, cleaned_orders);
        analysis::join(cleaned_lab, db.lab_patients, cleaned_orders, db.joined);
        analysis::extract_delta(db.joined, db.delta, a1c_margin);

        if (config_dialog->needs_output()) {
                csv::write_delta_analysis(output_file.toStdString(), db.delta);
                QMessageBox::information(this, "Great", "Finished processing the data, saved to " + output_file, QMessageBox::Information);
        } else {
                QMessageBox::information(this, "Great", "Finished processing the data", QMessageBox::Information);
        }
        ui->status_bar->showMessage("Finished");

        needs_analysis = false;
}

void MainWindow::on_query_triggered()
{
        if(needs_analysis)
                on_analyze_triggered();

        query_dialog->exec();
}

void MainWindow::on_clear_all_files_triggered()
{
        this->lab_files.clear();
        this->order_files.clear();
        this->filter_files.clear();
        ui->file_list->clear();

       needs_analysis = true;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
        switch (event->key()) {
        case Qt::Key_Delete:
                // Pressed delete key.
                QList<QListWidgetItem*> items = ui->file_list->selectedItems();
                for (QListWidgetItem* item: items) {
                        int row = ui->file_list->row(item);

                        auto it = lab_files.find(row);
                        if (it != lab_files.end())
                                lab_files.erase(it);

                        auto it2 = order_files.find(row);
                        if (it2 != order_files.end())
                                order_files.erase(it2);

                        auto it3 = filter_files.find(row);
                        if (it3 != filter_files.end())
                                filter_files.erase(it2);

                        ui->file_list->takeItem(row);
                }
                needs_analysis = true;
                break;
        }
}
