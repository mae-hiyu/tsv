/********************************************************************************
** Form generated from reading UI file 'smooth_plastic_surface_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMOOTH_PLASTIC_SURFACE_WIDGET_H
#define UI_SMOOTH_PLASTIC_SURFACE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SmoothPlasticSurfaceWidget
{
public:
    QGroupBox *diffuse_reflectance_box;
    QFrame *diffuse_reflectance_frame;
    QGroupBox *interior_refractive_index_box;
    QFrame *interior_refractive_index_frame;
    QGroupBox *exterior_refractive_index_box;
    QFrame *exterior_refractive_index_frame;
    QGroupBox *specular_weight_box;
    QSpinBox *specular_weight_spinbox;

    void setupUi(QWidget *SmoothPlasticSurfaceWidget)
    {
        if (SmoothPlasticSurfaceWidget->objectName().isEmpty())
            SmoothPlasticSurfaceWidget->setObjectName(QString::fromUtf8("SmoothPlasticSurfaceWidget"));
        SmoothPlasticSurfaceWidget->resize(341, 261);
        diffuse_reflectance_box = new QGroupBox(SmoothPlasticSurfaceWidget);
        diffuse_reflectance_box->setObjectName(QString::fromUtf8("diffuse_reflectance_box"));
        diffuse_reflectance_box->setGeometry(QRect(10, 10, 161, 61));
        diffuse_reflectance_frame = new QFrame(diffuse_reflectance_box);
        diffuse_reflectance_frame->setObjectName(QString::fromUtf8("diffuse_reflectance_frame"));
        diffuse_reflectance_frame->setGeometry(QRect(30, 30, 101, 21));
        diffuse_reflectance_frame->setFrameShape(QFrame::StyledPanel);
        diffuse_reflectance_frame->setFrameShadow(QFrame::Raised);
        interior_refractive_index_box = new QGroupBox(SmoothPlasticSurfaceWidget);
        interior_refractive_index_box->setObjectName(QString::fromUtf8("interior_refractive_index_box"));
        interior_refractive_index_box->setGeometry(QRect(10, 140, 161, 51));
        interior_refractive_index_frame = new QFrame(interior_refractive_index_box);
        interior_refractive_index_frame->setObjectName(QString::fromUtf8("interior_refractive_index_frame"));
        interior_refractive_index_frame->setGeometry(QRect(30, 30, 101, 16));
        interior_refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        interior_refractive_index_frame->setFrameShadow(QFrame::Raised);
        exterior_refractive_index_box = new QGroupBox(SmoothPlasticSurfaceWidget);
        exterior_refractive_index_box->setObjectName(QString::fromUtf8("exterior_refractive_index_box"));
        exterior_refractive_index_box->setGeometry(QRect(10, 80, 161, 51));
        exterior_refractive_index_frame = new QFrame(exterior_refractive_index_box);
        exterior_refractive_index_frame->setObjectName(QString::fromUtf8("exterior_refractive_index_frame"));
        exterior_refractive_index_frame->setGeometry(QRect(30, 30, 101, 16));
        exterior_refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        exterior_refractive_index_frame->setFrameShadow(QFrame::Raised);
        specular_weight_box = new QGroupBox(SmoothPlasticSurfaceWidget);
        specular_weight_box->setObjectName(QString::fromUtf8("specular_weight_box"));
        specular_weight_box->setGeometry(QRect(200, 10, 131, 61));
        specular_weight_spinbox = new QSpinBox(specular_weight_box);
        specular_weight_spinbox->setObjectName(QString::fromUtf8("specular_weight_spinbox"));
        specular_weight_spinbox->setGeometry(QRect(10, 30, 111, 24));
        specular_weight_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        specular_weight_spinbox->setKeyboardTracking(false);
        specular_weight_spinbox->setMinimum(1);
        specular_weight_spinbox->setMaximum(1000000);
        specular_weight_spinbox->setValue(400);

        retranslateUi(SmoothPlasticSurfaceWidget);

        QMetaObject::connectSlotsByName(SmoothPlasticSurfaceWidget);
    } // setupUi

    void retranslateUi(QWidget *SmoothPlasticSurfaceWidget)
    {
        SmoothPlasticSurfaceWidget->setWindowTitle(QCoreApplication::translate("SmoothPlasticSurfaceWidget", "Form", nullptr));
        diffuse_reflectance_box->setTitle(QCoreApplication::translate("SmoothPlasticSurfaceWidget", "Diffuse Reflectance", nullptr));
        interior_refractive_index_box->setTitle(QCoreApplication::translate("SmoothPlasticSurfaceWidget", "Interior refractive index", nullptr));
        exterior_refractive_index_box->setTitle(QCoreApplication::translate("SmoothPlasticSurfaceWidget", "Exterior refractive index", nullptr));
        specular_weight_box->setTitle(QCoreApplication::translate("SmoothPlasticSurfaceWidget", "Specular weight", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SmoothPlasticSurfaceWidget: public Ui_SmoothPlasticSurfaceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMOOTH_PLASTIC_SURFACE_WIDGET_H
