/********************************************************************************
** Form generated from reading UI file 'pinhole_camera_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PINHOLE_CAMERA_WIDGET_H
#define UI_PINHOLE_CAMERA_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PinholeCameraWidget
{
public:
    QGroupBox *angle_box;
    QDoubleSpinBox *angle_spinbox;

    void setupUi(QWidget *PinholeCameraWidget)
    {
        if (PinholeCameraWidget->objectName().isEmpty())
            PinholeCameraWidget->setObjectName(QString::fromUtf8("PinholeCameraWidget"));
        PinholeCameraWidget->resize(301, 201);
        angle_box = new QGroupBox(PinholeCameraWidget);
        angle_box->setObjectName(QString::fromUtf8("angle_box"));
        angle_box->setGeometry(QRect(10, 10, 91, 61));
        angle_spinbox = new QDoubleSpinBox(angle_box);
        angle_spinbox->setObjectName(QString::fromUtf8("angle_spinbox"));
        angle_spinbox->setGeometry(QRect(10, 30, 71, 21));
        angle_spinbox->setAlignment(Qt::AlignCenter);
        angle_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        angle_spinbox->setKeyboardTracking(false);
        angle_spinbox->setDecimals(6);
        angle_spinbox->setMinimum(1.000000000000000);
        angle_spinbox->setMaximum(179.000000000000000);
        angle_spinbox->setValue(45.000000000000000);

        retranslateUi(PinholeCameraWidget);

        QMetaObject::connectSlotsByName(PinholeCameraWidget);
    } // setupUi

    void retranslateUi(QWidget *PinholeCameraWidget)
    {
        PinholeCameraWidget->setWindowTitle(QCoreApplication::translate("PinholeCameraWidget", "Form", nullptr));
        angle_box->setTitle(QCoreApplication::translate("PinholeCameraWidget", "Angle of view", nullptr));
        angle_spinbox->setSuffix(QCoreApplication::translate("PinholeCameraWidget", "\313\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PinholeCameraWidget: public Ui_PinholeCameraWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PINHOLE_CAMERA_WIDGET_H
