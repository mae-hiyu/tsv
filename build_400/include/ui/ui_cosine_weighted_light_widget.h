/********************************************************************************
** Form generated from reading UI file 'cosine_weighted_light_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COSINE_WEIGHTED_LIGHT_WIDGET_H
#define UI_COSINE_WEIGHTED_LIGHT_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CosineWeightedLightWidget
{
public:
    QGroupBox *radiant_emittance_box;
    QDoubleSpinBox *radiant_emittance_spinbox;
    QGroupBox *property_box;
    QFrame *property_frame;
    QGroupBox *cosine_weight_box;
    QDoubleSpinBox *cosine_weight_spinbox;

    void setupUi(QWidget *CosineWeightedLightWidget)
    {
        if (CosineWeightedLightWidget->objectName().isEmpty())
            CosineWeightedLightWidget->setObjectName(QString::fromUtf8("CosineWeightedLightWidget"));
        CosineWeightedLightWidget->resize(341, 261);
        radiant_emittance_box = new QGroupBox(CosineWeightedLightWidget);
        radiant_emittance_box->setObjectName(QString::fromUtf8("radiant_emittance_box"));
        radiant_emittance_box->setGeometry(QRect(10, 80, 121, 61));
        radiant_emittance_spinbox = new QDoubleSpinBox(radiant_emittance_box);
        radiant_emittance_spinbox->setObjectName(QString::fromUtf8("radiant_emittance_spinbox"));
        radiant_emittance_spinbox->setGeometry(QRect(20, 30, 81, 24));
        radiant_emittance_spinbox->setAlignment(Qt::AlignCenter);
        radiant_emittance_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        radiant_emittance_spinbox->setKeyboardTracking(false);
        radiant_emittance_spinbox->setDecimals(6);
        radiant_emittance_spinbox->setMinimum(0.000000000000000);
        radiant_emittance_spinbox->setMaximum(100000.000000000000000);
        radiant_emittance_spinbox->setValue(0.010000000000000);
        property_box = new QGroupBox(CosineWeightedLightWidget);
        property_box->setObjectName(QString::fromUtf8("property_box"));
        property_box->setGeometry(QRect(10, 10, 181, 61));
        property_frame = new QFrame(property_box);
        property_frame->setObjectName(QString::fromUtf8("property_frame"));
        property_frame->setGeometry(QRect(10, 30, 161, 21));
        property_frame->setFrameShape(QFrame::StyledPanel);
        property_frame->setFrameShadow(QFrame::Raised);
        cosine_weight_box = new QGroupBox(CosineWeightedLightWidget);
        cosine_weight_box->setObjectName(QString::fromUtf8("cosine_weight_box"));
        cosine_weight_box->setEnabled(true);
        cosine_weight_box->setGeometry(QRect(10, 150, 121, 61));
        cosine_weight_spinbox = new QDoubleSpinBox(cosine_weight_box);
        cosine_weight_spinbox->setObjectName(QString::fromUtf8("cosine_weight_spinbox"));
        cosine_weight_spinbox->setGeometry(QRect(20, 30, 81, 24));
        cosine_weight_spinbox->setAlignment(Qt::AlignCenter);
        cosine_weight_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        cosine_weight_spinbox->setKeyboardTracking(false);
        cosine_weight_spinbox->setDecimals(6);
        cosine_weight_spinbox->setMaximum(100000.000000000000000);

        retranslateUi(CosineWeightedLightWidget);

        QMetaObject::connectSlotsByName(CosineWeightedLightWidget);
    } // setupUi

    void retranslateUi(QWidget *CosineWeightedLightWidget)
    {
        CosineWeightedLightWidget->setWindowTitle(QCoreApplication::translate("CosineWeightedLightWidget", "Form", nullptr));
        radiant_emittance_box->setTitle(QCoreApplication::translate("CosineWeightedLightWidget", "Radiant emittance", nullptr));
        property_box->setTitle(QCoreApplication::translate("CosineWeightedLightWidget", "Property", nullptr));
        cosine_weight_box->setTitle(QCoreApplication::translate("CosineWeightedLightWidget", "Cosine weight", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CosineWeightedLightWidget: public Ui_CosineWeightedLightWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COSINE_WEIGHTED_LIGHT_WIDGET_H
