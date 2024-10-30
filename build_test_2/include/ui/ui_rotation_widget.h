/********************************************************************************
** Form generated from reading UI file 'rotation_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROTATION_WIDGET_H
#define UI_ROTATION_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RotationWidget
{
public:
    QComboBox *axis_combobox;
    QDoubleSpinBox *angle_spinbox;
    QComboBox *unit_combobox;

    void setupUi(QWidget *RotationWidget)
    {
        if (RotationWidget->objectName().isEmpty())
            RotationWidget->setObjectName(QString::fromUtf8("RotationWidget"));
        RotationWidget->resize(271, 41);
        RotationWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(160, 160, 160);"));
        axis_combobox = new QComboBox(RotationWidget);
        axis_combobox->setObjectName(QString::fromUtf8("axis_combobox"));
        axis_combobox->setGeometry(QRect(20, 10, 71, 21));
        angle_spinbox = new QDoubleSpinBox(RotationWidget);
        angle_spinbox->setObjectName(QString::fromUtf8("angle_spinbox"));
        angle_spinbox->setGeometry(QRect(100, 10, 71, 21));
        angle_spinbox->setAlignment(Qt::AlignCenter);
        angle_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        angle_spinbox->setKeyboardTracking(false);
        angle_spinbox->setDecimals(6);
        angle_spinbox->setMinimum(-10000.000000000000000);
        angle_spinbox->setMaximum(10000.000000000000000);
        unit_combobox = new QComboBox(RotationWidget);
        unit_combobox->setObjectName(QString::fromUtf8("unit_combobox"));
        unit_combobox->setGeometry(QRect(180, 10, 71, 21));

        retranslateUi(RotationWidget);

        QMetaObject::connectSlotsByName(RotationWidget);
    } // setupUi

    void retranslateUi(QWidget *RotationWidget)
    {
        RotationWidget->setWindowTitle(QCoreApplication::translate("RotationWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RotationWidget: public Ui_RotationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROTATION_WIDGET_H
