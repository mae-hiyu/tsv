/********************************************************************************
** Form generated from reading UI file 'material_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIAL_WIDGET_H
#define UI_MATERIAL_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MaterialWidget
{
public:
    QListWidget *material_list;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *material_button_layout;
    QPushButton *add_material_button;
    QPushButton *delete_material_button;
    QFrame *material_item_frame;

    void setupUi(QWidget *MaterialWidget)
    {
        if (MaterialWidget->objectName().isEmpty())
            MaterialWidget->setObjectName(QString::fromUtf8("MaterialWidget"));
        MaterialWidget->resize(601, 321);
        material_list = new QListWidget(MaterialWidget);
        material_list->setObjectName(QString::fromUtf8("material_list"));
        material_list->setGeometry(QRect(360, 10, 231, 261));
        horizontalLayoutWidget_2 = new QWidget(MaterialWidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(360, 280, 231, 32));
        material_button_layout = new QHBoxLayout(horizontalLayoutWidget_2);
        material_button_layout->setObjectName(QString::fromUtf8("material_button_layout"));
        material_button_layout->setContentsMargins(0, 0, 0, 0);
        add_material_button = new QPushButton(horizontalLayoutWidget_2);
        add_material_button->setObjectName(QString::fromUtf8("add_material_button"));

        material_button_layout->addWidget(add_material_button);

        delete_material_button = new QPushButton(horizontalLayoutWidget_2);
        delete_material_button->setObjectName(QString::fromUtf8("delete_material_button"));
        delete_material_button->setEnabled(false);

        material_button_layout->addWidget(delete_material_button);

        material_item_frame = new QFrame(MaterialWidget);
        material_item_frame->setObjectName(QString::fromUtf8("material_item_frame"));
        material_item_frame->setGeometry(QRect(10, 10, 341, 301));
        material_item_frame->setFrameShape(QFrame::StyledPanel);
        material_item_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(MaterialWidget);

        QMetaObject::connectSlotsByName(MaterialWidget);
    } // setupUi

    void retranslateUi(QWidget *MaterialWidget)
    {
        MaterialWidget->setWindowTitle(QCoreApplication::translate("MaterialWidget", "Form", nullptr));
        add_material_button->setText(QCoreApplication::translate("MaterialWidget", "Add", nullptr));
        delete_material_button->setText(QCoreApplication::translate("MaterialWidget", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MaterialWidget: public Ui_MaterialWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIAL_WIDGET_H
