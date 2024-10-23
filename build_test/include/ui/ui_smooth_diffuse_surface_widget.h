/********************************************************************************
** Form generated from reading UI file 'smooth_diffuse_surface_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMOOTH_DIFFUSE_SURFACE_WIDGET_H
#define UI_SMOOTH_DIFFUSE_SURFACE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SmoothDiffuseSurfaceWidget
{
public:
    QGroupBox *reflectance_box;
    QFrame *reflectance_frame;

    void setupUi(QWidget *SmoothDiffuseSurfaceWidget)
    {
        if (SmoothDiffuseSurfaceWidget->objectName().isEmpty())
            SmoothDiffuseSurfaceWidget->setObjectName(QString::fromUtf8("SmoothDiffuseSurfaceWidget"));
        SmoothDiffuseSurfaceWidget->resize(341, 261);
        reflectance_box = new QGroupBox(SmoothDiffuseSurfaceWidget);
        reflectance_box->setObjectName(QString::fromUtf8("reflectance_box"));
        reflectance_box->setGeometry(QRect(10, 10, 161, 61));
        reflectance_frame = new QFrame(reflectance_box);
        reflectance_frame->setObjectName(QString::fromUtf8("reflectance_frame"));
        reflectance_frame->setGeometry(QRect(30, 30, 101, 21));
        reflectance_frame->setFrameShape(QFrame::StyledPanel);
        reflectance_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(SmoothDiffuseSurfaceWidget);

        QMetaObject::connectSlotsByName(SmoothDiffuseSurfaceWidget);
    } // setupUi

    void retranslateUi(QWidget *SmoothDiffuseSurfaceWidget)
    {
        SmoothDiffuseSurfaceWidget->setWindowTitle(QCoreApplication::translate("SmoothDiffuseSurfaceWidget", "Form", nullptr));
        reflectance_box->setTitle(QCoreApplication::translate("SmoothDiffuseSurfaceWidget", "Reflectance", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SmoothDiffuseSurfaceWidget: public Ui_SmoothDiffuseSurfaceWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMOOTH_DIFFUSE_SURFACE_WIDGET_H
