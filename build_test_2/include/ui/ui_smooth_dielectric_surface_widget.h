/********************************************************************************
** Form generated from reading UI file 'smooth_dielectric_surface_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMOOTH_DIELECTRIC_SURFACE_WIDGET_H
#define UI_SMOOTH_DIELECTRIC_SURFACE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SmoothDielectricSurfaceWidget
{
public:
    QGroupBox *exterior_refractive_index_box;
    QFrame *exterior_refractive_index_frame;
    QGroupBox *interior_refractive_index_box;
    QFrame *interior_refractive_index_frame;

    void setupUi(QWidget *SmoothDielectricSurfaceWidget)
    {
        if (SmoothDielectricSurfaceWidget->objectName().isEmpty())
            SmoothDielectricSurfaceWidget->setObjectName(QString::fromUtf8("SmoothDielectricSurfaceWidget"));
        SmoothDielectricSurfaceWidget->resize(341, 261);
        exterior_refractive_index_box = new QGroupBox(SmoothDielectricSurfaceWidget);
        exterior_refractive_index_box->setObjectName(QString::fromUtf8("exterior_refractive_index_box"));
        exterior_refractive_index_box->setGeometry(QRect(10, 10, 161, 51));
        exterior_refractive_index_frame = new QFrame(exterior_refractive_index_box);
        exterior_refractive_index_frame->setObjectName(QString::fromUtf8("exterior_refractive_index_frame"));
        exterior_refractive_index_frame->setGeometry(QRect(30, 30, 101, 16));
        exterior_refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        exterior_refractive_index_frame->setFrameShadow(QFrame::Raised);
        interior_refractive_index_box = new QGroupBox(SmoothDielectricSurfaceWidget);
        interior_refractive_index_box->setObjectName(QString::fromUtf8("interior_refractive_index_box"));
        interior_refractive_index_box->setGeometry(QRect(10, 70, 161, 51));
        interior_refractive_index_frame = new QFrame(interior_refractive_index_box);
        interior_refractive_index_frame->setObjectName(QString::fromUtf8("interior_refractive_index_frame"));
        interior_refractive_index_frame->setGeometry(QRect(30, 30, 101, 16));
        interior_refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        interior_refractive_index_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(SmoothDielectricSurfaceWidget);

        QMetaObject::connectSlotsByName(SmoothDielectricSurfaceWidget);
    } // setupUi

    void retranslateUi(QWidget *SmoothDielectricSurfaceWidget)
    {
        SmoothDielectricSurfaceWidget->setWindowTitle(QCoreApplication::translate("SmoothDielectricSurfaceWidget", "Form", nullptr));
        exterior_refractive_index_box->setTitle(QCoreApplication::translate("SmoothDielectricSurfaceWidget", "Exterior refractive index", nullptr));
        interior_refractive_index_box->setTitle(QCoreApplication::translate("SmoothDielectricSurfaceWidget", "Interior refractive index", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SmoothDielectricSurfaceWidget: public Ui_SmoothDielectricSurfaceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMOOTH_DIELECTRIC_SURFACE_WIDGET_H
