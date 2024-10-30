/********************************************************************************
** Form generated from reading UI file 'scaling_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCALING_WIDGET_H
#define UI_SCALING_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScalingWidget
{
public:
    QDoubleSpinBox *x_spinbox;
    QDoubleSpinBox *y_spinbox;
    QDoubleSpinBox *z_spinbox;

    void setupUi(QWidget *ScalingWidget)
    {
        if (ScalingWidget->objectName().isEmpty())
            ScalingWidget->setObjectName(QString::fromUtf8("ScalingWidget"));
        ScalingWidget->resize(271, 41);
        ScalingWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(160, 160, 160);"));
        x_spinbox = new QDoubleSpinBox(ScalingWidget);
        x_spinbox->setObjectName(QString::fromUtf8("x_spinbox"));
        x_spinbox->setGeometry(QRect(20, 10, 71, 21));
        x_spinbox->setAlignment(Qt::AlignCenter);
        x_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        x_spinbox->setKeyboardTracking(false);
        x_spinbox->setDecimals(6);
        x_spinbox->setMinimum(0.000001000000000);
        x_spinbox->setMaximum(10000.000000000000000);
        x_spinbox->setValue(1.000000000000000);
        y_spinbox = new QDoubleSpinBox(ScalingWidget);
        y_spinbox->setObjectName(QString::fromUtf8("y_spinbox"));
        y_spinbox->setGeometry(QRect(100, 10, 71, 21));
        y_spinbox->setAlignment(Qt::AlignCenter);
        y_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        y_spinbox->setKeyboardTracking(false);
        y_spinbox->setDecimals(6);
        y_spinbox->setMinimum(0.000001000000000);
        y_spinbox->setMaximum(10000.000000000000000);
        y_spinbox->setValue(1.000000000000000);
        z_spinbox = new QDoubleSpinBox(ScalingWidget);
        z_spinbox->setObjectName(QString::fromUtf8("z_spinbox"));
        z_spinbox->setGeometry(QRect(180, 10, 71, 21));
        z_spinbox->setAlignment(Qt::AlignCenter);
        z_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        z_spinbox->setKeyboardTracking(false);
        z_spinbox->setDecimals(6);
        z_spinbox->setMinimum(0.000001000000000);
        z_spinbox->setMaximum(10000.000000000000000);
        z_spinbox->setValue(1.000000000000000);

        retranslateUi(ScalingWidget);

        QMetaObject::connectSlotsByName(ScalingWidget);
    } // setupUi

    void retranslateUi(QWidget *ScalingWidget)
    {
        ScalingWidget->setWindowTitle(QCoreApplication::translate("ScalingWidget", "Form", nullptr));
        x_spinbox->setPrefix(QCoreApplication::translate("ScalingWidget", "X: ", nullptr));
        y_spinbox->setPrefix(QCoreApplication::translate("ScalingWidget", "Y: ", nullptr));
        z_spinbox->setPrefix(QCoreApplication::translate("ScalingWidget", "Z: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScalingWidget: public Ui_ScalingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCALING_WIDGET_H
