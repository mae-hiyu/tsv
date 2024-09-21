/********************************************************************************
** Form generated from reading UI file 'spectrum_palette_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPECTRUM_PALETTE_WIDGET_H
#define UI_SPECTRUM_PALETTE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpectrumPaletteWidget
{
public:
    QPushButton *open_spectra_file_button;

    void setupUi(QWidget *SpectrumPaletteWidget)
    {
        if (SpectrumPaletteWidget->objectName().isEmpty())
            SpectrumPaletteWidget->setObjectName(QString::fromUtf8("SpectrumPaletteWidget"));
        SpectrumPaletteWidget->resize(101, 16);
        open_spectra_file_button = new QPushButton(SpectrumPaletteWidget);
        open_spectra_file_button->setObjectName(QString::fromUtf8("open_spectra_file_button"));
        open_spectra_file_button->setGeometry(QRect(0, 0, 101, 16));

        retranslateUi(SpectrumPaletteWidget);

        QMetaObject::connectSlotsByName(SpectrumPaletteWidget);
    } // setupUi

    void retranslateUi(QWidget *SpectrumPaletteWidget)
    {
        SpectrumPaletteWidget->setWindowTitle(QCoreApplication::translate("SpectrumPaletteWidget", "Form", nullptr));
        open_spectra_file_button->setText(QCoreApplication::translate("SpectrumPaletteWidget", "Open", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpectrumPaletteWidget: public Ui_SpectrumPaletteWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPECTRUM_PALETTE_WIDGET_H
