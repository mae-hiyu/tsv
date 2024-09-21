/********************************************************************************
** Form generated from reading UI file 'color_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLOR_WIDGET_H
#define UI_COLOR_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorWidget
{
public:
    QCheckBox *rgb_checkbox;
    QGroupBox *spectrum_sampling_box;
    QComboBox *spectrum_sampling_combobox;
    QGroupBox *color_space_box;
    QComboBox *color_space_combobox;
    QGroupBox *color_matching_function_box;
    QComboBox *standard_observer_combobox;
    QLabel *standard_observer_label;
    QLabel *standard_illuminant_label;
    QComboBox *standard_illuminant_combobox;
    QGroupBox *tonemapping_box;
    QComboBox *tonemapping_combobox;
    QFrame *tonemapping_frame;
    QGroupBox *gamma_box;
    QDoubleSpinBox *gamma_spinbox;

    void setupUi(QWidget *ColorWidget)
    {
        if (ColorWidget->objectName().isEmpty())
            ColorWidget->setObjectName(QString::fromUtf8("ColorWidget"));
        ColorWidget->resize(601, 321);
        rgb_checkbox = new QCheckBox(ColorWidget);
        rgb_checkbox->setObjectName(QString::fromUtf8("rgb_checkbox"));
        rgb_checkbox->setGeometry(QRect(10, 10, 161, 20));
        spectrum_sampling_box = new QGroupBox(ColorWidget);
        spectrum_sampling_box->setObjectName(QString::fromUtf8("spectrum_sampling_box"));
        spectrum_sampling_box->setGeometry(QRect(10, 150, 161, 61));
        spectrum_sampling_combobox = new QComboBox(spectrum_sampling_box);
        spectrum_sampling_combobox->setObjectName(QString::fromUtf8("spectrum_sampling_combobox"));
        spectrum_sampling_combobox->setGeometry(QRect(10, 30, 141, 21));
        color_space_box = new QGroupBox(ColorWidget);
        color_space_box->setObjectName(QString::fromUtf8("color_space_box"));
        color_space_box->setGeometry(QRect(10, 210, 161, 61));
        color_space_combobox = new QComboBox(color_space_box);
        color_space_combobox->setObjectName(QString::fromUtf8("color_space_combobox"));
        color_space_combobox->setGeometry(QRect(10, 30, 141, 21));
        color_matching_function_box = new QGroupBox(ColorWidget);
        color_matching_function_box->setObjectName(QString::fromUtf8("color_matching_function_box"));
        color_matching_function_box->setGeometry(QRect(10, 30, 161, 121));
        standard_observer_combobox = new QComboBox(color_matching_function_box);
        standard_observer_combobox->setObjectName(QString::fromUtf8("standard_observer_combobox"));
        standard_observer_combobox->setGeometry(QRect(10, 40, 141, 21));
        standard_observer_label = new QLabel(color_matching_function_box);
        standard_observer_label->setObjectName(QString::fromUtf8("standard_observer_label"));
        standard_observer_label->setGeometry(QRect(10, 20, 141, 20));
        standard_observer_label->setAlignment(Qt::AlignCenter);
        standard_illuminant_label = new QLabel(color_matching_function_box);
        standard_illuminant_label->setObjectName(QString::fromUtf8("standard_illuminant_label"));
        standard_illuminant_label->setGeometry(QRect(10, 70, 141, 21));
        standard_illuminant_label->setAlignment(Qt::AlignCenter);
        standard_illuminant_combobox = new QComboBox(color_matching_function_box);
        standard_illuminant_combobox->setObjectName(QString::fromUtf8("standard_illuminant_combobox"));
        standard_illuminant_combobox->setGeometry(QRect(10, 90, 141, 21));
        tonemapping_box = new QGroupBox(ColorWidget);
        tonemapping_box->setObjectName(QString::fromUtf8("tonemapping_box"));
        tonemapping_box->setGeometry(QRect(330, 10, 141, 61));
        tonemapping_combobox = new QComboBox(tonemapping_box);
        tonemapping_combobox->setObjectName(QString::fromUtf8("tonemapping_combobox"));
        tonemapping_combobox->setGeometry(QRect(10, 30, 121, 21));
        tonemapping_frame = new QFrame(ColorWidget);
        tonemapping_frame->setObjectName(QString::fromUtf8("tonemapping_frame"));
        tonemapping_frame->setGeometry(QRect(330, 80, 261, 231));
        tonemapping_frame->setFrameShape(QFrame::StyledPanel);
        tonemapping_frame->setFrameShadow(QFrame::Raised);
        gamma_box = new QGroupBox(ColorWidget);
        gamma_box->setObjectName(QString::fromUtf8("gamma_box"));
        gamma_box->setGeometry(QRect(180, 10, 141, 61));
        gamma_spinbox = new QDoubleSpinBox(gamma_box);
        gamma_spinbox->setObjectName(QString::fromUtf8("gamma_spinbox"));
        gamma_spinbox->setGeometry(QRect(10, 30, 121, 24));
        gamma_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        gamma_spinbox->setKeyboardTracking(false);
        gamma_spinbox->setMinimum(0.100000000000000);
        gamma_spinbox->setMaximum(10.000000000000000);
        gamma_spinbox->setValue(2.200000000000000);

        retranslateUi(ColorWidget);

        QMetaObject::connectSlotsByName(ColorWidget);
    } // setupUi

    void retranslateUi(QWidget *ColorWidget)
    {
        ColorWidget->setWindowTitle(QCoreApplication::translate("ColorWidget", "Form", nullptr));
        rgb_checkbox->setText(QCoreApplication::translate("ColorWidget", "RGB rendering", nullptr));
        spectrum_sampling_box->setTitle(QCoreApplication::translate("ColorWidget", "Spectrum sampling", nullptr));
        color_space_box->setTitle(QCoreApplication::translate("ColorWidget", "Color space", nullptr));
        color_matching_function_box->setTitle(QCoreApplication::translate("ColorWidget", "Color maching function", nullptr));
        standard_observer_label->setText(QCoreApplication::translate("ColorWidget", "Standard observer", nullptr));
        standard_illuminant_label->setText(QCoreApplication::translate("ColorWidget", "Standard illuminant", nullptr));
        tonemapping_box->setTitle(QCoreApplication::translate("ColorWidget", "Tonemapping", nullptr));
        gamma_box->setTitle(QCoreApplication::translate("ColorWidget", "Gamma correction", nullptr));
        gamma_spinbox->setPrefix(QCoreApplication::translate("ColorWidget", "Gamma: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ColorWidget: public Ui_ColorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLOR_WIDGET_H
