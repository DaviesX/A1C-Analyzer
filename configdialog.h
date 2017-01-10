#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <cmath>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog: public QDialog
{
        Q_OBJECT
public:
        ConfigDialog();
        explicit ConfigDialog(QWidget *parent = 0);
        ~ConfigDialog();

        QString         get_output_file() const;
        float           get_a1c_margin() const;
        bool            is_canceled() const;
        bool            needs_output() const;
private slots:

        void on_buttonBox_accepted();

        void on_choose_file_clicked();

        void on_buttonBox_rejected();

private:
        QString                 m_output_file = "";
        float                   m_a1c_margin = INFINITY;
        bool                    m_is_canceled = true;
        bool                    m_needs_output = false;

        Ui::ConfigDialog*       ui;
};

#endif // CONFIGDIALOG_H
