#include <sstream>
#include "querydialog.h"
#include "ui_querydialog.h"
#include "database.h"
#include "analyzer.h"

QueryDialog::QueryDialog(QWidget *parent, Database& db) :
        QDialog(parent),
        ui(new Ui::QueryDialog),
        db(db)
{
        ui->setupUi(this);
}

QueryDialog::~QueryDialog()
{
        delete ui;
}

void QueryDialog::on_day_offset_editingFinished()
{
        // Query.
        int pid = ui->patient_id->value();
        int before_date = ui->day_offset->value();
        std::vector<MedicationOrder> orders;
        analysis::extract_medication_set(db.delta, pid, before_date, orders);

        // Write query result to list.
        ui->med_orde_list->clear();
        for (MedicationOrder order: orders) {
                /*std::stringstream ss;
                ss << order;*/

                QString s(order.order_name.c_str());
                //s.fromStdString(ss.str());
                ui->med_orde_list->addItem(s);
        }
}
