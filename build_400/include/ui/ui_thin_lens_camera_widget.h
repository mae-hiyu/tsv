/********************************************************************************
** Form generated from reading UI file 'thin_lens_camera_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THIN_LENS_CAMERA_WIDGET_H
#define UI_THIN_LENS_CAMERA_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThinLensCameraWidget
{
public:
    QGroupBox *angle_box;
    QDoubleSpinBox *angle_spinbox;
    QGroupBox *aperture_box;
    QDoubleSpinBox *aperture_spinbox;
    QGroupBox *focal_distance_box;
    QDoubleSpinBox *focal_distance_spinbox;

    void setupUi(QWidget *ThinLensCameraWidget)
    {
        if (ThinLensCameraWidget->objectName().isEmpty())
            ThinLensCameraWidget->setObjectName(QString::fromUtf8("ThinLensCameraWidget"));
        ThinLensCameraWidget->resize(301, 201);
        angle_box = new QGroupBox(ThinLensCameraWidget);
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
        aperture_box = new QGroupBox(ThinLensCameraWidget);
        aperture_box->setObjectName(QString::fromUtf8("aperture_box"));
        aperture_box->setGeometry(QRect(10, 70, 91, 61));
        aperture_spinbox = new QDoubleSpinBox(aperture_box);
        aperture_spinbox->setObjectName(QString::fromUtf8("aperture_spinbox"));
        aperture_spinbox->setGeometry(QRect(10, 30, 71, 21));
        aperture_spinbox->setAlignment(Qt::AlignCenter);
        aperture_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        aperture_spinbox->setKeyboardTracking(false);
        aperture_spinbox->setDecimals(6);
        aperture_spinbox->setMinimum(0.000001000000000);
        aperture_spinbox->setMaximum(1000000.000000000000000);
        aperture_spinbox->setValue(0.000001000000000);
        focal_distance_box = new QGroupBox(ThinLensCameraWidget);
        focal_distance_box->setObjectName(QString::fromUtf8("focal_distance_box"));
        focal_distance_box->setGeometry(QRect(10, 130, 91, 61));
        focal_distance_spinbox = new QDoubleSpinBox(focal_distance_box);
        focal_distance_spinbox->setObjectName(QString::fromUtf8("focal_distance_spinbox"));
        focal_distance_spinbox->setGeometry(QRect(10, 30, 71, 21));
        focal_distance_spinbox->setAlignment(Qt::AlignCenter);
        focal_distance_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        focal_distance_spinbox->setKeyboardTracking(false);
        focal_distance_spinbox->setDecimals(6);
        focal_distance_spinbox->setMinimum(0.000001000000000);
        focal_distance_spinbox->setMaximum(1000000.000000000000000);
        focal_distance_spinbox->setValue(0.050000000000000);

        retranslateUi(ThinLensCameraWidget);

        QMetaObject::connectSlotsByName(ThinLensCameraWidget);
    } // setupUi

    void retranslateUi(QWidget *ThinLensCameraWidget)
    {
        ThinLensCameraWidget->setWindowTitle(QCoreApplication::translate("ThinLensCameraWidget", "Form", nullptr));
        angle_box->setTitle(QCoreApplication::translate("ThinLensCameraWidget", "Angle of view", nullptr));
        angle_spinbox->setSuffix(QCoreApplication::translate("ThinLensCameraWidget", "\313\232", nullptr));
        aperture_box->setTitle(QCoreApplication::translate("ThinLensCameraWidget", "Aperture", nullptr));
        aperture_spinbox->setSuffix(QCoreApplication::translate("ThinLensCameraWidget", "m", nullptr));
        focal_distance_box->setTitle(QCoreApplication::translate("ThinLensCameraWidget", "Focal distance", nullptr));
        focal_distance_spinbox->setSuffix(QCoreApplication::translate("ThinLensCameraWidget", "m", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThinLensCameraWidget: public Ui_ThinLensCameraWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THIN_LENS_CAMERA_WIDGET_H
