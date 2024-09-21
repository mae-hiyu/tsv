/********************************************************************************
** Form generated from reading UI file 'color_palette_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLOR_PALETTE_WIDGET_H
#define UI_COLOR_PALETTE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ColorPaletteWidget
{
public:
    QFrame *palette_frame;
    QPushButton *toggle_button;

    void setupUi(QWidget *ColorPaletteWidget)
    {
        if (ColorPaletteWidget->objectName().isEmpty())
            ColorPaletteWidget->setObjectName(QString::fromUtf8("ColorPaletteWidget"));
        ColorPaletteWidget->resize(161, 16);
        palette_frame = new QFrame(ColorPaletteWidget);
        palette_frame->setObjectName(QString::fromUtf8("palette_frame"));
        palette_frame->setGeometry(QRect(60, 0, 101, 16));
        palette_frame->setFrameShape(QFrame::StyledPanel);
        palette_frame->setFrameShadow(QFrame::Raised);
        toggle_button = new QPushButton(ColorPaletteWidget);
        toggle_button->setObjectName(QString::fromUtf8("toggle_button"));
        toggle_button->setGeometry(QRect(0, 0, 51, 16));

        retranslateUi(ColorPaletteWidget);

        QMetaObject::connectSlotsByName(ColorPaletteWidget);
    } // setupUi

    void retranslateUi(QWidget *ColorPaletteWidget)
    {
        ColorPaletteWidget->setWindowTitle(QCoreApplication::translate("ColorPaletteWidget", "Form", nullptr));
        toggle_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ColorPaletteWidget: public Ui_ColorPaletteWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLOR_PALETTE_WIDGET_H
