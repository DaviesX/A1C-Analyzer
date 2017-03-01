/********************************************************************************
** Form generated from reading UI file 'querydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYDIALOG_H
#define UI_QUERYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_QueryDialog
{
public:
    QLabel *label;
    QListWidget *med_orde_list;
    QSpinBox *day_offset;
    QScrollBar *scroll0;
    QScrollBar *scroll1;
    QLabel *label_2;
    QSpinBox *patient_id;

    void setupUi(QDialog *QueryDialog)
    {
        if (QueryDialog->objectName().isEmpty())
            QueryDialog->setObjectName(QStringLiteral("QueryDialog"));
        QueryDialog->resize(572, 410);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QueryDialog->sizePolicy().hasHeightForWidth());
        QueryDialog->setSizePolicy(sizePolicy);
        label = new QLabel(QueryDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 110, 41, 21));
        med_orde_list = new QListWidget(QueryDialog);
        med_orde_list->setObjectName(QStringLiteral("med_orde_list"));
        med_orde_list->setGeometry(QRect(145, 110, 421, 291));
        day_offset = new QSpinBox(QueryDialog);
        day_offset->setObjectName(QStringLiteral("day_offset"));
        day_offset->setGeometry(QRect(10, 110, 71, 21));
        day_offset->setMaximum(10000);
        scroll0 = new QScrollBar(QueryDialog);
        scroll0->setObjectName(QStringLiteral("scroll0"));
        scroll0->setGeometry(QRect(10, 50, 551, 16));
        scroll0->setOrientation(Qt::Horizontal);
        scroll1 = new QScrollBar(QueryDialog);
        scroll1->setObjectName(QStringLiteral("scroll1"));
        scroll1->setGeometry(QRect(10, 80, 551, 16));
        scroll1->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(QueryDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 10, 51, 21));
        patient_id = new QSpinBox(QueryDialog);
        patient_id->setObjectName(QStringLiteral("patient_id"));
        patient_id->setGeometry(QRect(80, 10, 121, 21));
        patient_id->setMaximum(100000);
        patient_id->setValue(1);

        retranslateUi(QueryDialog);

        QMetaObject::connectSlotsByName(QueryDialog);
    } // setupUi

    void retranslateUi(QDialog *QueryDialog)
    {
        QueryDialog->setWindowTitle(QApplication::translate("QueryDialog", "Medicaion Query", 0));
        label->setText(QApplication::translate("QueryDialog", "Days", 0));
        label_2->setText(QApplication::translate("QueryDialog", "Patient", 0));
    } // retranslateUi

};

namespace Ui {
    class QueryDialog: public Ui_QueryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYDIALOG_H
