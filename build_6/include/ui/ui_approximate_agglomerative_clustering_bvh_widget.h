/********************************************************************************
** Form generated from reading UI file 'approximate_agglomerative_clustering_bvh_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPROXIMATE_AGGLOMERATIVE_CLUSTERING_BVH_WIDGET_H
#define UI_APPROXIMATE_AGGLOMERATIVE_CLUSTERING_BVH_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApproximateAgglomerativeClusteringBvhWidget
{
public:
    QFrame *bvh_optimization_frame;
    QGroupBox *delta_box;
    QSpinBox *delta_spinbox;
    QGroupBox *epsilon_box;
    QDoubleSpinBox *epsilon_spinbox;

    void setupUi(QWidget *ApproximateAgglomerativeClusteringBvhWidget)
    {
        if (ApproximateAgglomerativeClusteringBvhWidget->objectName().isEmpty())
            ApproximateAgglomerativeClusteringBvhWidget->setObjectName(QString::fromUtf8("ApproximateAgglomerativeClusteringBvhWidget"));
        ApproximateAgglomerativeClusteringBvhWidget->resize(581, 271);
        bvh_optimization_frame = new QFrame(ApproximateAgglomerativeClusteringBvhWidget);
        bvh_optimization_frame->setObjectName(QString::fromUtf8("bvh_optimization_frame"));
        bvh_optimization_frame->setGeometry(QRect(370, 10, 201, 251));
        bvh_optimization_frame->setFrameShape(QFrame::StyledPanel);
        bvh_optimization_frame->setFrameShadow(QFrame::Raised);
        delta_box = new QGroupBox(ApproximateAgglomerativeClusteringBvhWidget);
        delta_box->setObjectName(QString::fromUtf8("delta_box"));
        delta_box->setGeometry(QRect(10, 10, 111, 61));
        delta_spinbox = new QSpinBox(delta_box);
        delta_spinbox->setObjectName(QString::fromUtf8("delta_spinbox"));
        delta_spinbox->setGeometry(QRect(10, 30, 91, 24));
        delta_spinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        delta_spinbox->setKeyboardTracking(false);
        delta_spinbox->setMinimum(4);
        delta_spinbox->setMaximum(100);
        delta_spinbox->setValue(4);
        epsilon_box = new QGroupBox(ApproximateAgglomerativeClusteringBvhWidget);
        epsilon_box->setObjectName(QString::fromUtf8("epsilon_box"));
        epsilon_box->setGeometry(QRect(10, 80, 111, 61));
        epsilon_spinbox = new QDoubleSpinBox(epsilon_box);
        epsilon_spinbox->setObjectName(QString::fromUtf8("epsilon_spinbox"));
        epsilon_spinbox->setGeometry(QRect(10, 30, 91, 24));
        epsilon_spinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        epsilon_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        epsilon_spinbox->setKeyboardTracking(false);
        epsilon_spinbox->setDecimals(6);
        epsilon_spinbox->setMinimum(0.000001000000000);
        epsilon_spinbox->setMaximum(1000000.000000000000000);
        epsilon_spinbox->setValue(0.200000000000000);

        retranslateUi(ApproximateAgglomerativeClusteringBvhWidget);

        QMetaObject::connectSlotsByName(ApproximateAgglomerativeClusteringBvhWidget);
    } // setupUi

    void retranslateUi(QWidget *ApproximateAgglomerativeClusteringBvhWidget)
    {
        ApproximateAgglomerativeClusteringBvhWidget->setWindowTitle(QCoreApplication::translate("ApproximateAgglomerativeClusteringBvhWidget", "Form", nullptr));
        delta_box->setTitle(QCoreApplication::translate("ApproximateAgglomerativeClusteringBvhWidget", "Delta", nullptr));
        epsilon_box->setTitle(QCoreApplication::translate("ApproximateAgglomerativeClusteringBvhWidget", "Epsilon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApproximateAgglomerativeClusteringBvhWidget: public Ui_ApproximateAgglomerativeClusteringBvhWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPROXIMATE_AGGLOMERATIVE_CLUSTERING_BVH_WIDGET_H
