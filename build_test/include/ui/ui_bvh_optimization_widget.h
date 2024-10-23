/********************************************************************************
** Form generated from reading UI file 'bvh_optimization_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BVH_OPTIMIZATION_WIDGET_H
#define UI_BVH_OPTIMIZATION_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BvhOptimizationWidget
{
public:
    QComboBox *optimization_combobox;
    QFrame *optimization_frame;

    void setupUi(QWidget *BvhOptimizationWidget)
    {
        if (BvhOptimizationWidget->objectName().isEmpty())
            BvhOptimizationWidget->setObjectName(QString::fromUtf8("BvhOptimizationWidget"));
        BvhOptimizationWidget->resize(201, 251);
        optimization_combobox = new QComboBox(BvhOptimizationWidget);
        optimization_combobox->setObjectName(QString::fromUtf8("optimization_combobox"));
        optimization_combobox->setGeometry(QRect(10, 10, 181, 21));
        optimization_frame = new QFrame(BvhOptimizationWidget);
        optimization_frame->setObjectName(QString::fromUtf8("optimization_frame"));
        optimization_frame->setGeometry(QRect(10, 40, 181, 201));
        optimization_frame->setFrameShape(QFrame::StyledPanel);
        optimization_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(BvhOptimizationWidget);

        QMetaObject::connectSlotsByName(BvhOptimizationWidget);
    } // setupUi

    void retranslateUi(QWidget *BvhOptimizationWidget)
    {
        BvhOptimizationWidget->setWindowTitle(QCoreApplication::translate("BvhOptimizationWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BvhOptimizationWidget: public Ui_BvhOptimizationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BVH_OPTIMIZATION_WIDGET_H
