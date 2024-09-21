/********************************************************************************
** Form generated from reading UI file 'smooth_conductor_surface_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMOOTH_CONDUCTOR_SURFACE_WIDGET_H
#define UI_SMOOTH_CONDUCTOR_SURFACE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SmoothConductorSurfaceWidget
{
public:
    QGroupBox *exterior_refractive_index_box;
    QFrame *exterior_refractive_index_frame;
    QGroupBox *interior_refractive_index_box;
    QFrame *interior_refractive_index_frame;
    QGroupBox *interior_extinction_box;
    QFrame *interior_extinction_frame;

    void setupUi(QWidget *SmoothConductorSurfaceWidget)
    {
        if (SmoothConductorSurfaceWidget->objectName().isEmpty())
            SmoothConductorSurfaceWidget->setObjectName(QString::fromUtf8("SmoothConductorSurfaceWidget"));
        SmoothConductorSurfaceWidget->resize(341, 261);
        exterior_refractive_index_box = new QGroupBox(SmoothConductorSurfaceWidget);
        exterior_refractive_index_box->setObjectName(QString::fromUtf8("exterior_refractive_index_box"));
        exterior_refractive_index_box->setGeometry(QRect(10, 10, 161, 51));
        exterior_refractive_index_frame = new QFrame(exterior_refractive_index_box);
        exterior_refractive_index_frame->setObjectName(QString::fromUtf8("exterior_refractive_index_frame"));
        exterior_refractive_index_frame->setGeometry(QRect(30, 30, 101, 16));
        exterior_refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        exterior_refractive_index_frame->setFrameShadow(QFrame::Raised);
        interior_refractive_index_box = new QGroupBox(SmoothConductorSurfaceWidget);
        interior_refractive_index_box->setObjectName(QString::fromUtf8("interior_refractive_index_box"));
        interior_refractive_index_box->setGeometry(QRect(10, 70, 161, 51));
        interior_refractive_index_frame = new QFrame(interior_refractive_index_box);
        interior_refractive_index_frame->setObjectName(QString::fromUtf8("interior_refractive_index_frame"));
        interior_refractive_index_frame->setGeometry(QRect(30, 30, 101, 16));
        interior_refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        interior_refractive_index_frame->setFrameShadow(QFrame::Raised);
        interior_extinction_box = new QGroupBox(SmoothConductorSurfaceWidget);
        interior_extinction_box->setObjectName(QString::fromUtf8("interior_extinction_box"));
        interior_extinction_box->setGeometry(QRect(180, 70, 141, 51));
        interior_extinction_frame = new QFrame(interior_extinction_box);
        interior_extinction_frame->setObjectName(QString::fromUtf8("interior_extinction_frame"));
        interior_extinction_frame->setGeometry(QRect(20, 30, 101, 16));
        interior_extinction_frame->setFrameShape(QFrame::StyledPanel);
        interior_extinction_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(SmoothConductorSurfaceWidget);

        QMetaObject::connectSlotsByName(SmoothConductorSurfaceWidget);
    } // setupUi

    void retranslateUi(QWidget *SmoothConductorSurfaceWidget)
    {
        SmoothConductorSurfaceWidget->setWindowTitle(QCoreApplication::translate("SmoothConductorSurfaceWidget", "Form", nullptr));
        exterior_refractive_index_box->setTitle(QCoreApplication::translate("SmoothConductorSurfaceWidget", "Exterior refractive index", nullptr));
        interior_refractive_index_box->setTitle(QCoreApplication::translate("SmoothConductorSurfaceWidget", "Interior refractive index", nullptr));
        interior_extinction_box->setTitle(QCoreApplication::translate("SmoothConductorSurfaceWidget", "Interior extinction", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SmoothConductorSurfaceWidget: public Ui_SmoothConductorSurfaceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMOOTH_CONDUCTOR_SURFACE_WIDGET_H
