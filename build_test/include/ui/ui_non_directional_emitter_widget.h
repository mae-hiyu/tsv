/********************************************************************************
** Form generated from reading UI file 'non_directional_emitter_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NON_DIRECTIONAL_EMITTER_WIDGET_H
#define UI_NON_DIRECTIONAL_EMITTER_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NonDirectionalEmitterWidget
{
public:
    QGroupBox *radiant_emittance_box;
    QDoubleSpinBox *radiant_emittance_spinbox;
    QGroupBox *property_box;
    QFrame *property_frame;

    void setupUi(QWidget *NonDirectionalEmitterWidget)
    {
        if (NonDirectionalEmitterWidget->objectName().isEmpty())
            NonDirectionalEmitterWidget->setObjectName(QString::fromUtf8("NonDirectionalEmitterWidget"));
        NonDirectionalEmitterWidget->resize(341, 261);
        radiant_emittance_box = new QGroupBox(NonDirectionalEmitterWidget);
        radiant_emittance_box->setObjectName(QString::fromUtf8("radiant_emittance_box"));
        radiant_emittance_box->setGeometry(QRect(10, 80, 121, 61));
        radiant_emittance_spinbox = new QDoubleSpinBox(radiant_emittance_box);
        radiant_emittance_spinbox->setObjectName(QString::fromUtf8("radiant_emittance_spinbox"));
        radiant_emittance_spinbox->setGeometry(QRect(20, 30, 81, 21));
        radiant_emittance_spinbox->setAlignment(Qt::AlignCenter);
        radiant_emittance_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        radiant_emittance_spinbox->setKeyboardTracking(false);
        radiant_emittance_spinbox->setDecimals(6);
        radiant_emittance_spinbox->setMinimum(0.000000000000000);
        radiant_emittance_spinbox->setMaximum(100000.000000000000000);
        radiant_emittance_spinbox->setValue(10.000000000000000);
        property_box = new QGroupBox(NonDirectionalEmitterWidget);
        property_box->setObjectName(QString::fromUtf8("property_box"));
        property_box->setGeometry(QRect(10, 10, 181, 51));
        property_frame = new QFrame(property_box);
        property_frame->setObjectName(QString::fromUtf8("property_frame"));
        property_frame->setGeometry(QRect(10, 30, 161, 16));
        property_frame->setFrameShape(QFrame::StyledPanel);
        property_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(NonDirectionalEmitterWidget);

        QMetaObject::connectSlotsByName(NonDirectionalEmitterWidget);
    } // setupUi

    void retranslateUi(QWidget *NonDirectionalEmitterWidget)
    {
        NonDirectionalEmitterWidget->setWindowTitle(QCoreApplication::translate("NonDirectionalEmitterWidget", "Form", nullptr));
        radiant_emittance_box->setTitle(QCoreApplication::translate("NonDirectionalEmitterWidget", "Radiant emittance", nullptr));
        property_box->setTitle(QCoreApplication::translate("NonDirectionalEmitterWidget", "Property", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NonDirectionalEmitterWidget: public Ui_NonDirectionalEmitterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NON_DIRECTIONAL_EMITTER_WIDGET_H
