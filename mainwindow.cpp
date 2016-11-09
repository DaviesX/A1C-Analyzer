#include <iostream>
#include <vector>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configdialog.h"
#include "linkedbst.h"
#include "analyzer.h"
#include "labmeasure.h"
#include "medicationorder.h"
#include "deltaanalysis.h"
#include "csv.h"


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
        ui->setupUi(this);

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
        }
}

void MainWindow::on_analyze_triggered()
{
        ConfigDialog dialog(this);
        dialog.exec();

        if (dialog.is_canceled())
                return ;

        QString output_file = dialog.get_output_file();
        float a1c_margin = dialog.get_a1c_margin();

        ui->status_bar->showMessage("Analyzing... just a moment");

        std::vector<MedicationOrder> orders;
        std::vector<LabMeasure> measures;
        try {
                for (std::pair<int, std::string> pair: this->order_files)
                        csv::load_medication_order(pair.second, orders);

                for (std::pair<int, std::string> pair: this->lab_files)
                        csv::load_lab_measure(pair.second, measures);
        } catch (const std::string& ex) {
                QMessageBox::information(this, "Couldn't load file", QString::fromStdString(ex), QMessageBox::Critical);
                ui->status_bar->showMessage("Failed to load dataset");
                return;
        }

        std::vector<DeltaAnalysis> joined, delta;
        std::set<int> lab_patients;
        LinkedBST<LabMeasure> cleaned_lab;
        LinkedBST<MedicationOrder> cleaned_orders;
        analysis::preprocess(measures, "A1C", 0.0f, lab_patients, cleaned_lab);
        std::vector<DrugFilter> filter;
        analysis::preprocess(orders, filter, cleaned_orders);
        analysis::join(cleaned_lab, lab_patients, cleaned_orders, joined);
        analysis::delta(joined, delta, a1c_margin);

        csv::write_delta_analysis(output_file.toStdString(), delta);

        QMessageBox::information(this, "Great", "Finished processing delta, saved to " + output_file, QMessageBox::Information);
        ui->status_bar->showMessage("Finished");
}

void MainWindow::on_clear_all_files_triggered()
{
        this->lab_files.clear();
        this->order_files.clear();
        ui->file_list->clear();
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

                        ui->file_list->takeItem(row);
                }
                break;
        }
}
