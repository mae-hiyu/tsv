/********************************************************************************
** Form generated from reading UI file 'rendering_method_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERING_METHOD_WIDGET_H
#define UI_RENDERING_METHOD_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenderingMethodWidget
{
public:
    QFrame *rendering_method_frame;
    QComboBox *rendering_method_combobox;
    QGroupBox *russian_roulette_box;
    QFrame *russian_roulette_frame;
    QGroupBox *ray_cast_epsilon_box;
    QDoubleSpinBox *ray_cast_epsilon_spinbox;

    void setupUi(QWidget *RenderingMethodWidget)
    {
        if (RenderingMethodWidget->objectName().isEmpty())
            RenderingMethodWidget->setObjectName(QString::fromUtf8("RenderingMethodWidget"));
        RenderingMethodWidget->resize(601, 321);
        rendering_method_frame = new QFrame(RenderingMethodWidget);
        rendering_method_frame->setObjectName(QString::fromUtf8("rendering_method_frame"));
        rendering_method_frame->setGeometry(QRect(170, 40, 421, 271));
        rendering_method_frame->setFrameShape(QFrame::StyledPanel);
        rendering_method_frame->setFrameShadow(QFrame::Raised);
        rendering_method_combobox = new QComboBox(RenderingMethodWidget);
        rendering_method_combobox->setObjectName(QString::fromUtf8("rendering_method_combobox"));
        rendering_method_combobox->setGeometry(QRect(10, 10, 161, 21));
        russian_roulette_box = new QGroupBox(RenderingMethodWidget);
        russian_roulette_box->setObjectName(QString::fromUtf8("russian_roulette_box"));
        russian_roulette_box->setGeometry(QRect(10, 110, 151, 91));
        russian_roulette_frame = new QFrame(russian_roulette_box);
        russian_roulette_frame->setObjectName(QString::fromUtf8("russian_roulette_frame"));
        russian_roulette_frame->setGeometry(QRect(10, 30, 131, 51));
        russian_roulette_frame->setFrameShape(QFrame::StyledPanel);
        russian_roulette_frame->setFrameShadow(QFrame::Raised);
        ray_cast_epsilon_box = new QGroupBox(RenderingMethodWidget);
        ray_cast_epsilon_box->setObjectName(QString::fromUtf8("ray_cast_epsilon_box"));
        ray_cast_epsilon_box->setGeometry(QRect(10, 40, 151, 61));
        ray_cast_epsilon_spinbox = new QDoubleSpinBox(ray_cast_epsilon_box);
        ray_cast_epsilon_spinbox->setObjectName(QString::fromUtf8("ray_cast_epsilon_spinbox"));
        ray_cast_epsilon_spinbox->setGeometry(QRect(30, 30, 91, 21));
        ray_cast_epsilon_spinbox->setAlignment(Qt::AlignCenter);
        ray_cast_epsilon_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ray_cast_epsilon_spinbox->setKeyboardTracking(false);
        ray_cast_epsilon_spinbox->setDecimals(6);
        ray_cast_epsilon_spinbox->setMinimum(0.000001000000000);
        ray_cast_epsilon_spinbox->setMaximum(1.000000000000000);
        ray_cast_epsilon_spinbox->setSingleStep(0.000001000000000);
        ray_cast_epsilon_spinbox->setValue(0.000001000000000);

        retranslateUi(RenderingMethodWidget);

        QMetaObject::connectSlotsByName(RenderingMethodWidget);
    } // setupUi

    void retranslateUi(QWidget *RenderingMethodWidget)
    {
        RenderingMethodWidget->setWindowTitle(QCoreApplication::translate("RenderingMethodWidget", "Form", nullptr));
        russian_roulette_box->setTitle(QCoreApplication::translate("RenderingMethodWidget", "Russian roulette", nullptr));
        ray_cast_epsilon_box->setTitle(QCoreApplication::translate("RenderingMethodWidget", "Ray cast epsilon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RenderingMethodWidget: public Ui_RenderingMethodWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERING_METHOD_WIDGET_H
