#include <iostream>
#include <QFileDialog>
#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ConfigDialog)
{
        ui->setupUi(this);
}

ConfigDialog::~ConfigDialog()
{
        delete ui;
}


void ConfigDialog::on_buttonBox_accepted()
{
        m_a1c_margin = ui->a1c_margin->value();
        m_needs_output = ui->is_output->isChecked();
        m_is_canceled = false;
}

bool ConfigDialog::is_canceled() const
{
        return m_is_canceled;
}

bool ConfigDialog::needs_output() const
{
        return m_needs_output;
}

QString ConfigDialog::get_output_file() const
{
        return m_output_file;
}

float ConfigDialog::get_a1c_margin() const
{
        return m_a1c_margin;
}

void ConfigDialog::on_choose_file_clicked()
{
        QString filename = QFileDialog::getSaveFileName(this, "Delta file", ".", "CSV File (*.csv)");
        if (filename.isEmpty())
                return ;
        ui->output_path->clear();
        ui->output_path->insertPlainText(filename);
        m_output_file = filename;
}

void ConfigDialog::on_buttonBox_rejected()
{
        m_is_canceled = true;
}
