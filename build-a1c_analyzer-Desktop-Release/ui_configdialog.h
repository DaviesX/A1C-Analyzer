/********************************************************************************
** Form generated from reading UI file 'configdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConfigDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPlainTextEdit *output_path;
    QPushButton *choose_file;
    QLabel *label;
    QDoubleSpinBox *a1c_margin;
    QCheckBox *is_output;

    void setupUi(QDialog *ConfigDialog)
    {
        if (ConfigDialog->objectName().isEmpty())
            ConfigDialog->setObjectName(QStringLiteral("ConfigDialog"));
        ConfigDialog->resize(401, 180);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConfigDialog->sizePolicy().hasHeightForWidth());
        ConfigDialog->setSizePolicy(sizePolicy);
        buttonBox = new QDialogButtonBox(ConfigDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 120, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        output_path = new QPlainTextEdit(ConfigDialog);
        output_path->setObjectName(QStringLiteral("output_path"));
        output_path->setGeometry(QRect(10, 40, 271, 31));
        output_path->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        output_path->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        choose_file = new QPushButton(ConfigDialog);
        choose_file->setObjectName(QStringLiteral("choose_file"));
        choose_file->setGeometry(QRect(300, 50, 80, 22));
        label = new QLabel(ConfigDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 80, 121, 21));
        a1c_margin = new QDoubleSpinBox(ConfigDialog);
        a1c_margin->setObjectName(QStringLiteral("a1c_margin"));
        a1c_margin->setGeometry(QRect(140, 80, 66, 23));
        a1c_margin->setDecimals(1);
        a1c_margin->setValue(7.5);
        is_output = new QCheckBox(ConfigDialog);
        is_output->setObjectName(QStringLiteral("is_output"));
        is_output->setGeometry(QRect(10, 10, 371, 26));

        retranslateUi(ConfigDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConfigDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConfigDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigDialog)
    {
        ConfigDialog->setWindowTitle(QApplication::translate("ConfigDialog", "Analysis Parameters", 0));
        output_path->setPlainText(QApplication::translate("ConfigDialog", "output csv file", 0));
        choose_file->setText(QApplication::translate("ConfigDialog", "Choose", 0));
        label->setText(QApplication::translate("ConfigDialog", "A1C Filter Level", 0));
        is_output->setText(QApplication::translate("ConfigDialog", "Output data file", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigDialog: public Ui_ConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
