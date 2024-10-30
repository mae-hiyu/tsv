/********************************************************************************
** Form generated from reading UI file 'bvh_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BVH_WIDGET_H
#define UI_BVH_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BvhWidget
{
public:
    QFrame *bvh_frame;
    QComboBox *bvh_combobox;

    void setupUi(QWidget *BvhWidget)
    {
        if (BvhWidget->objectName().isEmpty())
            BvhWidget->setObjectName(QString::fromUtf8("BvhWidget"));
        BvhWidget->resize(601, 321);
        bvh_frame = new QFrame(BvhWidget);
        bvh_frame->setObjectName(QString::fromUtf8("bvh_frame"));
        bvh_frame->setGeometry(QRect(10, 40, 581, 271));
        bvh_frame->setFrameShape(QFrame::StyledPanel);
        bvh_frame->setFrameShadow(QFrame::Raised);
        bvh_combobox = new QComboBox(BvhWidget);
        bvh_combobox->setObjectName(QString::fromUtf8("bvh_combobox"));
        bvh_combobox->setGeometry(QRect(10, 10, 141, 21));

        retranslateUi(BvhWidget);

        QMetaObject::connectSlotsByName(BvhWidget);
    } // setupUi

    void retranslateUi(QWidget *BvhWidget)
    {
        BvhWidget->setWindowTitle(QCoreApplication::translate("BvhWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BvhWidget: public Ui_BvhWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BVH_WIDGET_H
