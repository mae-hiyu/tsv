/********************************************************************************
** Form generated from reading UI file 'median_split_bvh_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIAN_SPLIT_BVH_WIDGET_H
#define UI_MEDIAN_SPLIT_BVH_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MedianSplitBvhWidget
{
public:
    QFrame *bvh_optimization_frame;

    void setupUi(QWidget *MedianSplitBvhWidget)
    {
        if (MedianSplitBvhWidget->objectName().isEmpty())
            MedianSplitBvhWidget->setObjectName(QString::fromUtf8("MedianSplitBvhWidget"));
        MedianSplitBvhWidget->resize(581, 271);
        bvh_optimization_frame = new QFrame(MedianSplitBvhWidget);
        bvh_optimization_frame->setObjectName(QString::fromUtf8("bvh_optimization_frame"));
        bvh_optimization_frame->setGeometry(QRect(370, 10, 201, 251));
        bvh_optimization_frame->setFrameShape(QFrame::StyledPanel);
        bvh_optimization_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(MedianSplitBvhWidget);

        QMetaObject::connectSlotsByName(MedianSplitBvhWidget);
    } // setupUi

    void retranslateUi(QWidget *MedianSplitBvhWidget)
    {
        MedianSplitBvhWidget->setWindowTitle(QCoreApplication::translate("MedianSplitBvhWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MedianSplitBvhWidget: public Ui_MedianSplitBvhWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIAN_SPLIT_BVH_WIDGET_H
