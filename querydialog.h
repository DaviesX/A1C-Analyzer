#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class QueryDialog;
}

class QueryDialog : public QDialog
{
        Q_OBJECT

public:
        explicit QueryDialog(QWidget *parent, dataset::Database& db);
        ~QueryDialog();

private slots:
        void on_day_offset_editingFinished();

private:
        Ui::QueryDialog *ui;

        dataset::Database&	db;
};

#endif // QUERYDIALOG_H
