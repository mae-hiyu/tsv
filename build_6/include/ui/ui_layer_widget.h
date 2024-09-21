/********************************************************************************
** Form generated from reading UI file 'layer_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYER_WIDGET_H
#define UI_LAYER_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LayerWidget
{
public:
    QCheckBox *enable_checkbox;
    QLabel *name_label;
    QFrame *layer_frame;

    void setupUi(QWidget *LayerWidget)
    {
        if (LayerWidget->objectName().isEmpty())
            LayerWidget->setObjectName(QString::fromUtf8("LayerWidget"));
        LayerWidget->resize(271, 61);
        LayerWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(160, 160, 160);"));
        enable_checkbox = new QCheckBox(LayerWidget);
        enable_checkbox->setObjectName(QString::fromUtf8("enable_checkbox"));
        enable_checkbox->setGeometry(QRect(10, 0, 41, 21));
        enable_checkbox->setChecked(true);
        name_label = new QLabel(LayerWidget);
        name_label->setObjectName(QString::fromUtf8("name_label"));
        name_label->setGeometry(QRect(60, 0, 151, 21));
        name_label->setAlignment(Qt::AlignCenter);
        layer_frame = new QFrame(LayerWidget);
        layer_frame->setObjectName(QString::fromUtf8("layer_frame"));
        layer_frame->setGeometry(QRect(10, 20, 251, 41));
        layer_frame->setFrameShape(QFrame::StyledPanel);
        layer_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(LayerWidget);

        QMetaObject::connectSlotsByName(LayerWidget);
    } // setupUi

    void retranslateUi(QWidget *LayerWidget)
    {
        LayerWidget->setWindowTitle(QCoreApplication::translate("LayerWidget", "Form", nullptr));
        enable_checkbox->setText(QCoreApplication::translate("LayerWidget", "0", nullptr));
        name_label->setText(QCoreApplication::translate("LayerWidget", "Layer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LayerWidget: public Ui_LayerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYER_WIDGET_H
