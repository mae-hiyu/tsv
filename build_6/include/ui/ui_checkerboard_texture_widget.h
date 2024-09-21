/********************************************************************************
** Form generated from reading UI file 'checkerboard_texture_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKERBOARD_TEXTURE_WIDGET_H
#define UI_CHECKERBOARD_TEXTURE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CheckerboardTextureWidget
{
public:
    QGroupBox *num_of_tiles_box;
    QSpinBox *width_number_spinbox;
    QLabel *cross_label;
    QSpinBox *height_number_spinbox;
    QGroupBox *color1_box;
    QFrame *color1_frame;
    QGroupBox *color2_box;
    QFrame *color2_frame;

    void setupUi(QWidget *CheckerboardTextureWidget)
    {
        if (CheckerboardTextureWidget->objectName().isEmpty())
            CheckerboardTextureWidget->setObjectName(QString::fromUtf8("CheckerboardTextureWidget"));
        CheckerboardTextureWidget->resize(341, 261);
        num_of_tiles_box = new QGroupBox(CheckerboardTextureWidget);
        num_of_tiles_box->setObjectName(QString::fromUtf8("num_of_tiles_box"));
        num_of_tiles_box->setGeometry(QRect(10, 10, 141, 61));
        width_number_spinbox = new QSpinBox(num_of_tiles_box);
        width_number_spinbox->setObjectName(QString::fromUtf8("width_number_spinbox"));
        width_number_spinbox->setGeometry(QRect(10, 30, 51, 21));
        width_number_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        width_number_spinbox->setKeyboardTracking(false);
        width_number_spinbox->setMinimum(1);
        width_number_spinbox->setValue(5);
        cross_label = new QLabel(num_of_tiles_box);
        cross_label->setObjectName(QString::fromUtf8("cross_label"));
        cross_label->setGeometry(QRect(60, 30, 21, 16));
        cross_label->setAlignment(Qt::AlignCenter);
        height_number_spinbox = new QSpinBox(num_of_tiles_box);
        height_number_spinbox->setObjectName(QString::fromUtf8("height_number_spinbox"));
        height_number_spinbox->setGeometry(QRect(80, 30, 51, 21));
        height_number_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        height_number_spinbox->setKeyboardTracking(false);
        height_number_spinbox->setMinimum(1);
        height_number_spinbox->setValue(5);
        cross_label->raise();
        width_number_spinbox->raise();
        height_number_spinbox->raise();
        color1_box = new QGroupBox(CheckerboardTextureWidget);
        color1_box->setObjectName(QString::fromUtf8("color1_box"));
        color1_box->setGeometry(QRect(10, 80, 181, 51));
        color1_frame = new QFrame(color1_box);
        color1_frame->setObjectName(QString::fromUtf8("color1_frame"));
        color1_frame->setGeometry(QRect(10, 30, 161, 16));
        color1_frame->setFrameShape(QFrame::StyledPanel);
        color1_frame->setFrameShadow(QFrame::Raised);
        color2_box = new QGroupBox(CheckerboardTextureWidget);
        color2_box->setObjectName(QString::fromUtf8("color2_box"));
        color2_box->setGeometry(QRect(10, 140, 181, 51));
        color2_frame = new QFrame(color2_box);
        color2_frame->setObjectName(QString::fromUtf8("color2_frame"));
        color2_frame->setGeometry(QRect(10, 30, 161, 16));
        color2_frame->setFrameShape(QFrame::StyledPanel);
        color2_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(CheckerboardTextureWidget);

        QMetaObject::connectSlotsByName(CheckerboardTextureWidget);
    } // setupUi

    void retranslateUi(QWidget *CheckerboardTextureWidget)
    {
        CheckerboardTextureWidget->setWindowTitle(QCoreApplication::translate("CheckerboardTextureWidget", "Form", nullptr));
        num_of_tiles_box->setTitle(QCoreApplication::translate("CheckerboardTextureWidget", "The number of tiles", nullptr));
        width_number_spinbox->setPrefix(QCoreApplication::translate("CheckerboardTextureWidget", "w: ", nullptr));
        cross_label->setText(QCoreApplication::translate("CheckerboardTextureWidget", "x", nullptr));
        height_number_spinbox->setPrefix(QCoreApplication::translate("CheckerboardTextureWidget", "h: ", nullptr));
        color1_box->setTitle(QCoreApplication::translate("CheckerboardTextureWidget", "Color1", nullptr));
        color2_box->setTitle(QCoreApplication::translate("CheckerboardTextureWidget", "Color2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CheckerboardTextureWidget: public Ui_CheckerboardTextureWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKERBOARD_TEXTURE_WIDGET_H
