/********************************************************************************
** Form generated from reading UI file 'russian_roulette_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUSSIAN_ROULETTE_WIDGET_H
#define UI_RUSSIAN_ROULETTE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RussianRouletteWidget
{
public:
    QComboBox *russian_roulette_combobox;
    QSpinBox *path_length_max_spinbox;

    void setupUi(QWidget *RussianRouletteWidget)
    {
        if (RussianRouletteWidget->objectName().isEmpty())
            RussianRouletteWidget->setObjectName(QString::fromUtf8("RussianRouletteWidget"));
        RussianRouletteWidget->resize(131, 51);
        russian_roulette_combobox = new QComboBox(RussianRouletteWidget);
        russian_roulette_combobox->setObjectName(QString::fromUtf8("russian_roulette_combobox"));
        russian_roulette_combobox->setGeometry(QRect(0, 0, 131, 21));
        path_length_max_spinbox = new QSpinBox(RussianRouletteWidget);
        path_length_max_spinbox->setObjectName(QString::fromUtf8("path_length_max_spinbox"));
        path_length_max_spinbox->setGeometry(QRect(10, 30, 81, 21));
        path_length_max_spinbox->setKeyboardTracking(false);
        path_length_max_spinbox->setMinimum(1);
        path_length_max_spinbox->setMaximum(999);
        path_length_max_spinbox->setValue(3);

        retranslateUi(RussianRouletteWidget);

        QMetaObject::connectSlotsByName(RussianRouletteWidget);
    } // setupUi

    void retranslateUi(QWidget *RussianRouletteWidget)
    {
        RussianRouletteWidget->setWindowTitle(QCoreApplication::translate("RussianRouletteWidget", "Form", nullptr));
        path_length_max_spinbox->setPrefix(QCoreApplication::translate("RussianRouletteWidget", "Path: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RussianRouletteWidget: public Ui_RussianRouletteWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUSSIAN_ROULETTE_WIDGET_H
