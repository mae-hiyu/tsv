/********************************************************************************
** Form generated from reading UI file 'non_bvh_optimization_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NON_BVH_OPTIMIZATION_WIDGET_H
#define UI_NON_BVH_OPTIMIZATION_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_non_bvh_optimization_widget
{
public:

    void setupUi(QWidget *non_bvh_optimization_widget)
    {
        if (non_bvh_optimization_widget->objectName().isEmpty())
            non_bvh_optimization_widget->setObjectName(QString::fromUtf8("non_bvh_optimization_widget"));
        non_bvh_optimization_widget->resize(181, 201);

        retranslateUi(non_bvh_optimization_widget);

        QMetaObject::connectSlotsByName(non_bvh_optimization_widget);
    } // setupUi

    void retranslateUi(QWidget *non_bvh_optimization_widget)
    {
        non_bvh_optimization_widget->setWindowTitle(QCoreApplication::translate("non_bvh_optimization_widget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class non_bvh_optimization_widget: public Ui_non_bvh_optimization_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NON_BVH_OPTIMIZATION_WIDGET_H
