/********************************************************************************
** Form generated from reading UI file 'rough_dielectric_surface_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROUGH_DIELECTRIC_SURFACE_WIDGET_H
#define UI_ROUGH_DIELECTRIC_SURFACE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoughDielectricSurfaceWidget
{
public:
    QGroupBox *exterior_refractive_index_box;
    QFrame *exterior_refractive_index_frame;
    QGroupBox *interior_refractive_index_box;
    QFrame *interior_refractive_index_frame;
    QGroupBox *roughness_box;
    QFrame *roughness_frame;

    void setupUi(QWidget *RoughDielectricSurfaceWidget)
    {
        if (RoughDielectricSurfaceWidget->objectName().isEmpty())
            RoughDielectricSurfaceWidget->setObjectName(QString::fromUtf8("RoughDielectricSurfaceWidget"));
        RoughDielectricSurfaceWidget->resize(341, 261);
        exterior_refractive_index_box = new QGroupBox(RoughDielectricSurfaceWidget);
        exterior_refractive_index_box->setObjectName(QString::fromUtf8("exterior_refractive_index_box"));
        exterior_refractive_index_box->setGeometry(QRect(10, 10, 161, 51));
        exterior_refractive_index_frame = new QFrame(exterior_refractive_index_box);
        exterior_refractive_index_frame->setObjectName(QString::fromUtf8("exterior_refractive_index_frame"));
        exterior_refractive_index_frame->setGeometry(QRect(30, 30, 101, 16));
        exterior_refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        exterior_refractive_index_frame->setFrameShadow(QFrame::Raised);
        interior_refractive_index_box = new QGroupBox(RoughDielectricSurfaceWidget);
        interior_refractive_index_box->setObjectName(QString::fromUtf8("interior_refractive_index_box"));
        interior_refractive_index_box->setGeometry(QRect(10, 70, 161, 51));
        interior_refractive_index_frame = new QFrame(interior_refractive_index_box);
        interior_refractive_index_frame->setObjectName(QString::fromUtf8("interior_refractive_index_frame"));
        interior_refractive_index_frame->setGeometry(QRect(30, 30, 101, 16));
        interior_refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        interior_refractive_index_frame->setFrameShadow(QFrame::Raised);
        roughness_box = new QGroupBox(RoughDielectricSurfaceWidget);
        roughness_box->setObjectName(QString::fromUtf8("roughness_box"));
        roughness_box->setGeometry(QRect(10, 130, 161, 61));
        roughness_frame = new QFrame(roughness_box);
        roughness_frame->setObjectName(QString::fromUtf8("roughness_frame"));
        roughness_frame->setGeometry(QRect(30, 30, 101, 21));
        roughness_frame->setFrameShape(QFrame::StyledPanel);
        roughness_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(RoughDielectricSurfaceWidget);

        QMetaObject::connectSlotsByName(RoughDielectricSurfaceWidget);
    } // setupUi

    void retranslateUi(QWidget *RoughDielectricSurfaceWidget)
    {
        RoughDielectricSurfaceWidget->setWindowTitle(QCoreApplication::translate("RoughDielectricSurfaceWidget", "Form", nullptr));
        exterior_refractive_index_box->setTitle(QCoreApplication::translate("RoughDielectricSurfaceWidget", "Exterior refractive index", nullptr));
        interior_refractive_index_box->setTitle(QCoreApplication::translate("RoughDielectricSurfaceWidget", "Interior refractive index", nullptr));
        roughness_box->setTitle(QCoreApplication::translate("RoughDielectricSurfaceWidget", "Roughness", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoughDielectricSurfaceWidget: public Ui_RoughDielectricSurfaceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROUGH_DIELECTRIC_SURFACE_WIDGET_H
