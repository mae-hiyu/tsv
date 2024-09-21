/********************************************************************************
** Form generated from reading UI file 'probabilistic_ppm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROBABILISTIC_PPM_H
#define UI_PROBABILISTIC_PPM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProbabilisticPpmWidget
{
public:
    QGroupBox *initial_radius_box;
    QDoubleSpinBox *initial_radius_spinbox;
    QGroupBox *num_of_photons_box;
    QSpinBox *num_of_photons_spinbox;
    QGroupBox *alpha_box;
    QDoubleSpinBox *alpha_spinbox;
    QGroupBox *k_nearest_neighbor_box;
    QSpinBox *k_spinbox;
    QGroupBox *filter_kernel_box;
    QComboBox *filter_kernel_combobox;

    void setupUi(QWidget *ProbabilisticPpmWidget)
    {
        if (ProbabilisticPpmWidget->objectName().isEmpty())
            ProbabilisticPpmWidget->setObjectName(QString::fromUtf8("ProbabilisticPpmWidget"));
        ProbabilisticPpmWidget->resize(421, 271);
        initial_radius_box = new QGroupBox(ProbabilisticPpmWidget);
        initial_radius_box->setObjectName(QString::fromUtf8("initial_radius_box"));
        initial_radius_box->setGeometry(QRect(10, 80, 121, 61));
        initial_radius_spinbox = new QDoubleSpinBox(initial_radius_box);
        initial_radius_spinbox->setObjectName(QString::fromUtf8("initial_radius_spinbox"));
        initial_radius_spinbox->setGeometry(QRect(20, 30, 81, 21));
        initial_radius_spinbox->setAlignment(Qt::AlignCenter);
        initial_radius_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        initial_radius_spinbox->setKeyboardTracking(false);
        initial_radius_spinbox->setDecimals(6);
        initial_radius_spinbox->setMinimum(0.000001000000000);
        initial_radius_spinbox->setMaximum(1.000000000000000);
        initial_radius_spinbox->setValue(0.025000000000000);
        num_of_photons_box = new QGroupBox(ProbabilisticPpmWidget);
        num_of_photons_box->setObjectName(QString::fromUtf8("num_of_photons_box"));
        num_of_photons_box->setGeometry(QRect(10, 10, 121, 61));
        num_of_photons_spinbox = new QSpinBox(num_of_photons_box);
        num_of_photons_spinbox->setObjectName(QString::fromUtf8("num_of_photons_spinbox"));
        num_of_photons_spinbox->setGeometry(QRect(20, 30, 81, 21));
        num_of_photons_spinbox->setAlignment(Qt::AlignCenter);
        num_of_photons_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        num_of_photons_spinbox->setKeyboardTracking(false);
        num_of_photons_spinbox->setMinimum(1);
        num_of_photons_spinbox->setMaximum(2147483647);
        num_of_photons_spinbox->setValue(100000);
        alpha_box = new QGroupBox(ProbabilisticPpmWidget);
        alpha_box->setObjectName(QString::fromUtf8("alpha_box"));
        alpha_box->setGeometry(QRect(10, 150, 121, 61));
        alpha_spinbox = new QDoubleSpinBox(alpha_box);
        alpha_spinbox->setObjectName(QString::fromUtf8("alpha_spinbox"));
        alpha_spinbox->setGeometry(QRect(20, 30, 81, 21));
        alpha_spinbox->setAlignment(Qt::AlignCenter);
        alpha_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        alpha_spinbox->setKeyboardTracking(false);
        alpha_spinbox->setDecimals(6);
        alpha_spinbox->setMinimum(0.000001000000000);
        alpha_spinbox->setMaximum(1.000000000000000);
        alpha_spinbox->setValue(0.666667000000000);
        k_nearest_neighbor_box = new QGroupBox(ProbabilisticPpmWidget);
        k_nearest_neighbor_box->setObjectName(QString::fromUtf8("k_nearest_neighbor_box"));
        k_nearest_neighbor_box->setGeometry(QRect(140, 10, 121, 61));
        k_spinbox = new QSpinBox(k_nearest_neighbor_box);
        k_spinbox->setObjectName(QString::fromUtf8("k_spinbox"));
        k_spinbox->setGeometry(QRect(20, 30, 81, 21));
        k_spinbox->setAlignment(Qt::AlignCenter);
        k_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        k_spinbox->setKeyboardTracking(false);
        k_spinbox->setMinimum(1);
        k_spinbox->setMaximum(2147483647);
        k_spinbox->setValue(10);
        filter_kernel_box = new QGroupBox(ProbabilisticPpmWidget);
        filter_kernel_box->setObjectName(QString::fromUtf8("filter_kernel_box"));
        filter_kernel_box->setGeometry(QRect(270, 10, 131, 61));
        filter_kernel_combobox = new QComboBox(filter_kernel_box);
        filter_kernel_combobox->setObjectName(QString::fromUtf8("filter_kernel_combobox"));
        filter_kernel_combobox->setGeometry(QRect(10, 30, 111, 21));

        retranslateUi(ProbabilisticPpmWidget);

        QMetaObject::connectSlotsByName(ProbabilisticPpmWidget);
    } // setupUi

    void retranslateUi(QWidget *ProbabilisticPpmWidget)
    {
        ProbabilisticPpmWidget->setWindowTitle(QCoreApplication::translate("ProbabilisticPpmWidget", "Form", nullptr));
        initial_radius_box->setTitle(QCoreApplication::translate("ProbabilisticPpmWidget", "Initial radius", nullptr));
        num_of_photons_box->setTitle(QCoreApplication::translate("ProbabilisticPpmWidget", "Number of photons", nullptr));
        alpha_box->setTitle(QCoreApplication::translate("ProbabilisticPpmWidget", "Alpha", nullptr));
        k_nearest_neighbor_box->setTitle(QCoreApplication::translate("ProbabilisticPpmWidget", "K nearest neighbor", nullptr));
        k_spinbox->setSuffix(QString());
        k_spinbox->setPrefix(QString());
        filter_kernel_box->setTitle(QCoreApplication::translate("ProbabilisticPpmWidget", "Filter kernel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProbabilisticPpmWidget: public Ui_ProbabilisticPpmWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROBABILISTIC_PPM_H
