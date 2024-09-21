/********************************************************************************
** Form generated from reading UI file 'path_tracing_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATH_TRACING_WIDGET_H
#define UI_PATH_TRACING_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PathTracingWidget
{
public:

    void setupUi(QWidget *PathTracingWidget)
    {
        if (PathTracingWidget->objectName().isEmpty())
            PathTracingWidget->setObjectName(QString::fromUtf8("PathTracingWidget"));
        PathTracingWidget->resize(421, 271);

        retranslateUi(PathTracingWidget);

        QMetaObject::connectSlotsByName(PathTracingWidget);
    } // setupUi

    void retranslateUi(QWidget *PathTracingWidget)
    {
        PathTracingWidget->setWindowTitle(QCoreApplication::translate("PathTracingWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PathTracingWidget: public Ui_PathTracingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATH_TRACING_WIDGET_H
