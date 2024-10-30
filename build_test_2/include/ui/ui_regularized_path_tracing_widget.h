/********************************************************************************
** Form generated from reading UI file 'regularized_path_tracing_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGULARIZED_PATH_TRACING_WIDGET_H
#define UI_REGULARIZED_PATH_TRACING_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegularizedPathTracingWidget
{
public:
    QGroupBox *russian_roulette_box;
    QFrame *russian_roulette_frame;
    QGroupBox *regularization_angle_box;
    QDoubleSpinBox *regularization_angle_spinbox;

    void setupUi(QWidget *RegularizedPathTracingWidget)
    {
        if (RegularizedPathTracingWidget->objectName().isEmpty())
            RegularizedPathTracingWidget->setObjectName(QString::fromUtf8("RegularizedPathTracingWidget"));
        RegularizedPathTracingWidget->resize(581, 271);
        russian_roulette_box = new QGroupBox(RegularizedPathTracingWidget);
        russian_roulette_box->setObjectName(QString::fromUtf8("russian_roulette_box"));
        russian_roulette_box->setGeometry(QRect(10, 10, 151, 91));
        russian_roulette_frame = new QFrame(russian_roulette_box);
        russian_roulette_frame->setObjectName(QString::fromUtf8("russian_roulette_frame"));
        russian_roulette_frame->setGeometry(QRect(10, 30, 131, 51));
        russian_roulette_frame->setFrameShape(QFrame::StyledPanel);
        russian_roulette_frame->setFrameShadow(QFrame::Raised);
        regularization_angle_box = new QGroupBox(RegularizedPathTracingWidget);
        regularization_angle_box->setObjectName(QString::fromUtf8("regularization_angle_box"));
        regularization_angle_box->setGeometry(QRect(10, 110, 171, 61));
        regularization_angle_spinbox = new QDoubleSpinBox(regularization_angle_box);
        regularization_angle_spinbox->setObjectName(QString::fromUtf8("regularization_angle_spinbox"));
        regularization_angle_spinbox->setGeometry(QRect(50, 30, 71, 20));
        regularization_angle_spinbox->setAlignment(Qt::AlignCenter);
        regularization_angle_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        regularization_angle_spinbox->setKeyboardTracking(false);

        retranslateUi(RegularizedPathTracingWidget);

        QMetaObject::connectSlotsByName(RegularizedPathTracingWidget);
    } // setupUi

    void retranslateUi(QWidget *RegularizedPathTracingWidget)
    {
        RegularizedPathTracingWidget->setWindowTitle(QCoreApplication::translate("RegularizedPathTracingWidget", "Form", nullptr));
        russian_roulette_box->setTitle(QCoreApplication::translate("RegularizedPathTracingWidget", "Russian roulette", nullptr));
        regularization_angle_box->setTitle(QCoreApplication::translate("RegularizedPathTracingWidget", "Initial regularization angle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegularizedPathTracingWidget: public Ui_RegularizedPathTracingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGULARIZED_PATH_TRACING_WIDGET_H
