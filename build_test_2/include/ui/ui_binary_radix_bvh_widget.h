/********************************************************************************
** Form generated from reading UI file 'binary_radix_bvh_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINARY_RADIX_BVH_WIDGET_H
#define UI_BINARY_RADIX_BVH_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BinaryRadixBvhWidget
{
public:
    QFrame *bvh_optimization_frame;

    void setupUi(QWidget *BinaryRadixBvhWidget)
    {
        if (BinaryRadixBvhWidget->objectName().isEmpty())
            BinaryRadixBvhWidget->setObjectName(QString::fromUtf8("BinaryRadixBvhWidget"));
        BinaryRadixBvhWidget->resize(581, 271);
        bvh_optimization_frame = new QFrame(BinaryRadixBvhWidget);
        bvh_optimization_frame->setObjectName(QString::fromUtf8("bvh_optimization_frame"));
        bvh_optimization_frame->setGeometry(QRect(370, 10, 201, 251));
        bvh_optimization_frame->setFrameShape(QFrame::StyledPanel);
        bvh_optimization_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(BinaryRadixBvhWidget);

        QMetaObject::connectSlotsByName(BinaryRadixBvhWidget);
    } // setupUi

    void retranslateUi(QWidget *BinaryRadixBvhWidget)
    {
        BinaryRadixBvhWidget->setWindowTitle(QCoreApplication::translate("BinaryRadixBvhWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BinaryRadixBvhWidget: public Ui_BinaryRadixBvhWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINARY_RADIX_BVH_WIDGET_H
