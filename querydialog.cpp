#include <sstream>
#include "querydialog.h"
#include "ui_querydialog.h"
#include "database.h"
#include "dataset.h"


QueryDialog::QueryDialog(QWidget *parent, dataset::Database& db) :
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
        unsigned before_date = static_cast<unsigned>(ui->day_offset->value());

        dataset::patient_records_t::iterator record_iter = db.records.find(pid);
        if (record_iter != db.records.end()) {
                std::vector<csv::MedicationOrder> orders;
                record_iter->second.get_analysis(before_date, orders);

                // Write query result to list.
                ui->med_orde_list->clear();
                for (csv::MedicationOrder order: orders) {
                        /*std::stringstream ss;
                          ss << order;*/

                        QString s(order.order_name.c_str());
                        //s.fromStdString(ss.str());
                        ui->med_orde_list->addItem(s);
                }
        }
}
