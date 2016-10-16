#include <iostream>
#include <vector>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configdialog.h"
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
        QString filename = QFileDialog::getOpenFileName(this,
                                                        tr("Lab File"),
                                                        ".",
                                                        "CSV File (*.csv)");
        if (filename.isEmpty())
                return;
        this->lab_files.push_back(filename);
        ui->file_list->addItem("Lab: " + filename);
        ui->file_list->item(ui->file_list->count()-1)->setForeground(Qt::darkGreen);
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
        ui->file_list->item(ui->file_list->count()-1)->setForeground(Qt::darkBlue);
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
                for (QString order_file: this->order_files)
                        csv::load_medication_order(order_file.toStdString(),
                                                   orders);
                for (QString lab_file: this->lab_files)
                        csv::load_lab_measure(lab_file.toStdString(),
                                              measures);
        } catch (const std::string& ex) {
                QMessageBox::information(this, "Couldn't load file", QString::fromStdString(ex), QMessageBox::Critical);
                ui->status_bar->showMessage("Failed to load dataset");
                return;
        }

        std::vector<DeltaAnalysis> delta, filtered;
        analysis::delta(measures, orders, delta);
        analysis::filter(delta, a1c_margin, filtered);

        csv::write_delta_analysis(output_file.toStdString(), filtered);

        QMessageBox::information(this, "Great", "Finished processing delta, saved to " + output_file, QMessageBox::Information);
        ui->status_bar->showMessage("Finished");
}

void MainWindow::on_clear_all_files_triggered()
{
        this->lab_files.clear();
        this->order_files.clear();
        ui->file_list->clear();
}
