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
        explicit QueryDialog(QWidget *parent, Database& db);
        ~QueryDialog();

private slots:
        void on_day_offset_editingFinished();

private:
        Ui::QueryDialog *ui;

        Database&       db;
};

#endif // QUERYDIALOG_H
