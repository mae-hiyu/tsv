/********************************************************************************
** Form generated from reading UI file 'texture_weight_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTURE_WEIGHT_WIDGET_H
#define UI_TEXTURE_WEIGHT_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextureWeightWidget
{
public:
    QComboBox *texture_combobox;

    void setupUi(QWidget *TextureWeightWidget)
    {
        if (TextureWeightWidget->objectName().isEmpty())
            TextureWeightWidget->setObjectName(QString::fromUtf8("TextureWeightWidget"));
        TextureWeightWidget->resize(101, 21);
        texture_combobox = new QComboBox(TextureWeightWidget);
        texture_combobox->setObjectName(QString::fromUtf8("texture_combobox"));
        texture_combobox->setGeometry(QRect(0, 0, 101, 21));

        retranslateUi(TextureWeightWidget);

        QMetaObject::connectSlotsByName(TextureWeightWidget);
    } // setupUi

    void retranslateUi(QWidget *TextureWeightWidget)
    {
        TextureWeightWidget->setWindowTitle(QCoreApplication::translate("TextureWeightWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TextureWeightWidget: public Ui_TextureWeightWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTURE_WEIGHT_WIDGET_H
