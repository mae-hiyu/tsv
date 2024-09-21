/********************************************************************************
** Form generated from reading UI file 'rgb_palette_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RGB_PALETTE_WIDGET_H
#define UI_RGB_PALETTE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RgbPaletteWidget
{
public:
    QLabel *color_label;
    QPushButton *palette_button;

    void setupUi(QWidget *RgbPaletteWidget)
    {
        if (RgbPaletteWidget->objectName().isEmpty())
            RgbPaletteWidget->setObjectName(QString::fromUtf8("RgbPaletteWidget"));
        RgbPaletteWidget->resize(101, 16);
        color_label = new QLabel(RgbPaletteWidget);
        color_label->setObjectName(QString::fromUtf8("color_label"));
        color_label->setGeometry(QRect(0, 0, 21, 16));
        color_label->setAutoFillBackground(false);
        color_label->setFrameShape(QFrame::StyledPanel);
        palette_button = new QPushButton(RgbPaletteWidget);
        palette_button->setObjectName(QString::fromUtf8("palette_button"));
        palette_button->setGeometry(QRect(30, 0, 71, 16));

        retranslateUi(RgbPaletteWidget);

        QMetaObject::connectSlotsByName(RgbPaletteWidget);
    } // setupUi

    void retranslateUi(QWidget *RgbPaletteWidget)
    {
        RgbPaletteWidget->setWindowTitle(QCoreApplication::translate("RgbPaletteWidget", "Form", nullptr));
        color_label->setText(QString());
        palette_button->setText(QCoreApplication::translate("RgbPaletteWidget", "Palette", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RgbPaletteWidget: public Ui_RgbPaletteWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RGB_PALETTE_WIDGET_H
