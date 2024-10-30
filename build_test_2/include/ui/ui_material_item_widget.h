/********************************************************************************
** Form generated from reading UI file 'material_item_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIAL_ITEM_WIDGET_H
#define UI_MATERIAL_ITEM_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MaterialItemWidget
{
public:
    QFrame *material_type_frame;
    QComboBox *material_type_combobox;

    void setupUi(QWidget *MaterialItemWidget)
    {
        if (MaterialItemWidget->objectName().isEmpty())
            MaterialItemWidget->setObjectName(QString::fromUtf8("MaterialItemWidget"));
        MaterialItemWidget->resize(341, 301);
        material_type_frame = new QFrame(MaterialItemWidget);
        material_type_frame->setObjectName(QString::fromUtf8("material_type_frame"));
        material_type_frame->setGeometry(QRect(0, 40, 341, 261));
        material_type_frame->setFrameShape(QFrame::StyledPanel);
        material_type_frame->setFrameShadow(QFrame::Raised);
        material_type_combobox = new QComboBox(MaterialItemWidget);
        material_type_combobox->setObjectName(QString::fromUtf8("material_type_combobox"));
        material_type_combobox->setGeometry(QRect(10, 10, 121, 21));

        retranslateUi(MaterialItemWidget);

        QMetaObject::connectSlotsByName(MaterialItemWidget);
    } // setupUi

    void retranslateUi(QWidget *MaterialItemWidget)
    {
        MaterialItemWidget->setWindowTitle(QCoreApplication::translate("MaterialItemWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MaterialItemWidget: public Ui_MaterialItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIAL_ITEM_WIDGET_H
