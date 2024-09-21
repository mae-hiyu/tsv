/********************************************************************************
** Form generated from reading UI file 'value_texture_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VALUE_TEXTURE_WIDGET_H
#define UI_VALUE_TEXTURE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ValueTextureWidget
{
public:
    QGroupBox *value_box;
    QDoubleSpinBox *value_spinbox;

    void setupUi(QWidget *ValueTextureWidget)
    {
        if (ValueTextureWidget->objectName().isEmpty())
            ValueTextureWidget->setObjectName(QString::fromUtf8("ValueTextureWidget"));
        ValueTextureWidget->resize(341, 261);
        value_box = new QGroupBox(ValueTextureWidget);
        value_box->setObjectName(QString::fromUtf8("value_box"));
        value_box->setGeometry(QRect(10, 10, 141, 51));
        value_spinbox = new QDoubleSpinBox(value_box);
        value_spinbox->setObjectName(QString::fromUtf8("value_spinbox"));
        value_spinbox->setGeometry(QRect(20, 20, 101, 21));
        value_spinbox->setAlignment(Qt::AlignCenter);
        value_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        value_spinbox->setKeyboardTracking(false);
        value_spinbox->setDecimals(6);
        value_spinbox->setMaximum(1.000000000000000);
        value_spinbox->setValue(0.500000000000000);

        retranslateUi(ValueTextureWidget);

        QMetaObject::connectSlotsByName(ValueTextureWidget);
    } // setupUi

    void retranslateUi(QWidget *ValueTextureWidget)
    {
        ValueTextureWidget->setWindowTitle(QCoreApplication::translate("ValueTextureWidget", "Form", nullptr));
        value_box->setTitle(QCoreApplication::translate("ValueTextureWidget", "Value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ValueTextureWidget: public Ui_ValueTextureWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VALUE_TEXTURE_WIDGET_H
