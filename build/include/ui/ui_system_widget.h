/********************************************************************************
** Form generated from reading UI file 'system_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEM_WIDGET_H
#define UI_SYSTEM_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SystemWidget
{
public:
    QGroupBox *thread_box;
    QSpinBox *thread_spinbox;
    QPushButton *thread_auto_button;
    QGroupBox *scene_name_box;
    QLineEdit *scene_name_editor;
    QGroupBox *random_seed_box;
    QSpinBox *random_seed_spinbox;
    QPushButton *random_button;
    QGroupBox *ldr_image_format_box;
    QComboBox *ldr_image_format_combobox;
    QCheckBox *spectra_image_checkbox;
    QCheckBox *hdr_image_checkbox;
    QCheckBox *image_saving_checkbox;
    QGroupBox *image_saving_interval_box;
    QSpinBox *image_saving_interval_spinbox;
    QGroupBox *termination_pass_box;
    QSpinBox *termination_pass_spinbox;
    QCheckBox *open_cl_checkbox;
    QCheckBox *open_cl_cpu_checkbox;
    QCheckBox *open_cl_use_multiple_gpus_checkbox;

    void setupUi(QWidget *SystemWidget)
    {
        if (SystemWidget->objectName().isEmpty())
            SystemWidget->setObjectName(QString::fromUtf8("SystemWidget"));
        SystemWidget->resize(601, 321);
        thread_box = new QGroupBox(SystemWidget);
        thread_box->setObjectName(QString::fromUtf8("thread_box"));
        thread_box->setGeometry(QRect(10, 80, 111, 91));
        thread_box->setFlat(false);
        thread_box->setCheckable(false);
        thread_spinbox = new QSpinBox(thread_box);
        thread_spinbox->setObjectName(QString::fromUtf8("thread_spinbox"));
        thread_spinbox->setGeometry(QRect(20, 30, 71, 24));
        thread_spinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        thread_spinbox->setKeyboardTracking(false);
        thread_spinbox->setMinimum(1);
        thread_spinbox->setMaximum(99);
        thread_auto_button = new QPushButton(thread_box);
        thread_auto_button->setObjectName(QString::fromUtf8("thread_auto_button"));
        thread_auto_button->setGeometry(QRect(20, 60, 71, 16));
        scene_name_box = new QGroupBox(SystemWidget);
        scene_name_box->setObjectName(QString::fromUtf8("scene_name_box"));
        scene_name_box->setGeometry(QRect(10, 10, 151, 61));
        scene_name_editor = new QLineEdit(scene_name_box);
        scene_name_editor->setObjectName(QString::fromUtf8("scene_name_editor"));
        scene_name_editor->setGeometry(QRect(10, 30, 131, 21));
        scene_name_editor->setFrame(true);
        scene_name_editor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        scene_name_editor->setDragEnabled(true);
        random_seed_box = new QGroupBox(SystemWidget);
        random_seed_box->setObjectName(QString::fromUtf8("random_seed_box"));
        random_seed_box->setGeometry(QRect(10, 180, 111, 91));
        random_seed_spinbox = new QSpinBox(random_seed_box);
        random_seed_spinbox->setObjectName(QString::fromUtf8("random_seed_spinbox"));
        random_seed_spinbox->setGeometry(QRect(10, 30, 91, 24));
        random_seed_spinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        random_seed_spinbox->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        random_seed_spinbox->setKeyboardTracking(false);
        random_seed_spinbox->setMaximum(2147483647);
        random_seed_spinbox->setValue(0);
        random_button = new QPushButton(random_seed_box);
        random_button->setObjectName(QString::fromUtf8("random_button"));
        random_button->setGeometry(QRect(20, 60, 71, 16));
        ldr_image_format_box = new QGroupBox(SystemWidget);
        ldr_image_format_box->setObjectName(QString::fromUtf8("ldr_image_format_box"));
        ldr_image_format_box->setGeometry(QRect(170, 140, 141, 61));
        ldr_image_format_combobox = new QComboBox(ldr_image_format_box);
        ldr_image_format_combobox->setObjectName(QString::fromUtf8("ldr_image_format_combobox"));
        ldr_image_format_combobox->setGeometry(QRect(20, 30, 101, 21));
        spectra_image_checkbox = new QCheckBox(SystemWidget);
        spectra_image_checkbox->setObjectName(QString::fromUtf8("spectra_image_checkbox"));
        spectra_image_checkbox->setEnabled(true);
        spectra_image_checkbox->setGeometry(QRect(170, 20, 231, 20));
        spectra_image_checkbox->setChecked(false);
        hdr_image_checkbox = new QCheckBox(SystemWidget);
        hdr_image_checkbox->setObjectName(QString::fromUtf8("hdr_image_checkbox"));
        hdr_image_checkbox->setEnabled(false);
        hdr_image_checkbox->setGeometry(QRect(170, 40, 231, 20));
        hdr_image_checkbox->setChecked(false);
        image_saving_checkbox = new QCheckBox(SystemWidget);
        image_saving_checkbox->setObjectName(QString::fromUtf8("image_saving_checkbox"));
        image_saving_checkbox->setEnabled(true);
        image_saving_checkbox->setGeometry(QRect(170, 60, 231, 20));
        image_saving_checkbox->setChecked(true);
        image_saving_interval_box = new QGroupBox(SystemWidget);
        image_saving_interval_box->setObjectName(QString::fromUtf8("image_saving_interval_box"));
        image_saving_interval_box->setGeometry(QRect(170, 80, 141, 61));
        image_saving_interval_spinbox = new QSpinBox(image_saving_interval_box);
        image_saving_interval_spinbox->setObjectName(QString::fromUtf8("image_saving_interval_spinbox"));
        image_saving_interval_spinbox->setGeometry(QRect(20, 30, 101, 21));
        image_saving_interval_spinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        image_saving_interval_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        image_saving_interval_spinbox->setKeyboardTracking(false);
        image_saving_interval_spinbox->setMinimum(100);
        image_saving_interval_spinbox->setMaximum(2147483647);
        image_saving_interval_spinbox->setValue(600000);
        termination_pass_box = new QGroupBox(SystemWidget);
        termination_pass_box->setObjectName(QString::fromUtf8("termination_pass_box"));
        termination_pass_box->setGeometry(QRect(170, 200, 141, 61));
        termination_pass_spinbox = new QSpinBox(termination_pass_box);
        termination_pass_spinbox->setObjectName(QString::fromUtf8("termination_pass_spinbox"));
        termination_pass_spinbox->setGeometry(QRect(20, 30, 101, 21));
        termination_pass_spinbox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        termination_pass_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        termination_pass_spinbox->setKeyboardTracking(false);
        termination_pass_spinbox->setMaximum(2147483647);
        open_cl_checkbox = new QCheckBox(SystemWidget);
        open_cl_checkbox->setObjectName(QString::fromUtf8("open_cl_checkbox"));
        open_cl_checkbox->setEnabled(true);
        open_cl_checkbox->setGeometry(QRect(400, 20, 191, 20));
        open_cl_checkbox->setChecked(false);
        open_cl_cpu_checkbox = new QCheckBox(SystemWidget);
        open_cl_cpu_checkbox->setObjectName(QString::fromUtf8("open_cl_cpu_checkbox"));
        open_cl_cpu_checkbox->setEnabled(true);
        open_cl_cpu_checkbox->setGeometry(QRect(400, 40, 191, 20));
        open_cl_cpu_checkbox->setChecked(false);
        open_cl_use_multiple_gpus_checkbox = new QCheckBox(SystemWidget);
        open_cl_use_multiple_gpus_checkbox->setObjectName(QString::fromUtf8("open_cl_use_multiple_gpus_checkbox"));
        open_cl_use_multiple_gpus_checkbox->setEnabled(true);
        open_cl_use_multiple_gpus_checkbox->setGeometry(QRect(400, 60, 191, 20));
        open_cl_use_multiple_gpus_checkbox->setChecked(false);

        retranslateUi(SystemWidget);

        QMetaObject::connectSlotsByName(SystemWidget);
    } // setupUi

    void retranslateUi(QWidget *SystemWidget)
    {
        SystemWidget->setWindowTitle(QCoreApplication::translate("SystemWidget", "Form", nullptr));
        thread_box->setTitle(QCoreApplication::translate("SystemWidget", "Thread", nullptr));
        thread_auto_button->setText(QCoreApplication::translate("SystemWidget", "Auto", nullptr));
        scene_name_box->setTitle(QCoreApplication::translate("SystemWidget", "Scene name", nullptr));
        scene_name_editor->setText(QCoreApplication::translate("SystemWidget", "Scene", nullptr));
        random_seed_box->setTitle(QCoreApplication::translate("SystemWidget", "Random seed", nullptr));
        random_button->setText(QCoreApplication::translate("SystemWidget", "Random", nullptr));
        ldr_image_format_box->setTitle(QCoreApplication::translate("SystemWidget", "LDR Image format", nullptr));
        spectra_image_checkbox->setText(QCoreApplication::translate("SystemWidget", "Save spectra image", nullptr));
        hdr_image_checkbox->setText(QCoreApplication::translate("SystemWidget", "Save HDR image (OpenEXR)", nullptr));
        image_saving_checkbox->setText(QCoreApplication::translate("SystemWidget", "Save image at power of 2 of pass", nullptr));
        image_saving_interval_box->setTitle(QCoreApplication::translate("SystemWidget", "Image saving interval", nullptr));
        image_saving_interval_spinbox->setSuffix(QCoreApplication::translate("SystemWidget", " ms", nullptr));
        termination_pass_box->setTitle(QCoreApplication::translate("SystemWidget", "Termination pass", nullptr));
        open_cl_checkbox->setText(QCoreApplication::translate("SystemWidget", "Rendering with OpenCL", nullptr));
        open_cl_cpu_checkbox->setText(QCoreApplication::translate("SystemWidget", "OpenCL CPU", nullptr));
        open_cl_use_multiple_gpus_checkbox->setText(QCoreApplication::translate("SystemWidget", "Use multiple GPUs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SystemWidget: public Ui_SystemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEM_WIDGET_H
