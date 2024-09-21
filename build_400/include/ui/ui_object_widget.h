/********************************************************************************
** Form generated from reading UI file 'object_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECT_WIDGET_H
#define UI_OBJECT_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectWidget
{
public:
    QTreeWidget *object_tree;
    QWidget *gridLayoutWidget;
    QGridLayout *object_button_layout;
    QPushButton *group_add_button;
    QPushButton *delete_button;
    QPushButton *object_add_button;
    QPushButton *move_button;
    QPushButton *cancel_button;
    QPushButton *top_button;

    void setupUi(QWidget *ObjectWidget)
    {
        if (ObjectWidget->objectName().isEmpty())
            ObjectWidget->setObjectName(QString::fromUtf8("ObjectWidget"));
        ObjectWidget->resize(261, 321);
        object_tree = new QTreeWidget(ObjectWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        object_tree->setHeaderItem(__qtreewidgetitem);
        object_tree->setObjectName(QString::fromUtf8("object_tree"));
        object_tree->setGeometry(QRect(0, 0, 261, 261));
        object_tree->setStyleSheet(QString::fromUtf8("background-color: rgb(114, 114, 114);\n"
"alternate-background-color: rgb(120, 120, 120);"));
        object_tree->setEditTriggers(QAbstractItemView::DoubleClicked);
        object_tree->setAlternatingRowColors(true);
        object_tree->setIndentation(10);
        object_tree->setExpandsOnDoubleClick(false);
        object_tree->setColumnCount(1);
        object_tree->header()->setVisible(false);
        gridLayoutWidget = new QWidget(ObjectWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 260, 261, 61));
        object_button_layout = new QGridLayout(gridLayoutWidget);
        object_button_layout->setObjectName(QString::fromUtf8("object_button_layout"));
        object_button_layout->setContentsMargins(0, 0, 0, 0);
        group_add_button = new QPushButton(gridLayoutWidget);
        group_add_button->setObjectName(QString::fromUtf8("group_add_button"));

        object_button_layout->addWidget(group_add_button, 0, 1, 1, 1);

        delete_button = new QPushButton(gridLayoutWidget);
        delete_button->setObjectName(QString::fromUtf8("delete_button"));
        delete_button->setEnabled(false);

        object_button_layout->addWidget(delete_button, 0, 2, 1, 1);

        object_add_button = new QPushButton(gridLayoutWidget);
        object_add_button->setObjectName(QString::fromUtf8("object_add_button"));

        object_button_layout->addWidget(object_add_button, 0, 0, 1, 1);

        move_button = new QPushButton(gridLayoutWidget);
        move_button->setObjectName(QString::fromUtf8("move_button"));
        move_button->setEnabled(false);

        object_button_layout->addWidget(move_button, 1, 0, 1, 1);

        cancel_button = new QPushButton(gridLayoutWidget);
        cancel_button->setObjectName(QString::fromUtf8("cancel_button"));
        cancel_button->setEnabled(false);

        object_button_layout->addWidget(cancel_button, 1, 1, 1, 1);

        top_button = new QPushButton(gridLayoutWidget);
        top_button->setObjectName(QString::fromUtf8("top_button"));
        top_button->setEnabled(false);

        object_button_layout->addWidget(top_button, 1, 2, 1, 1);


        retranslateUi(ObjectWidget);

        QMetaObject::connectSlotsByName(ObjectWidget);
    } // setupUi

    void retranslateUi(QWidget *ObjectWidget)
    {
        ObjectWidget->setWindowTitle(QCoreApplication::translate("ObjectWidget", "Form", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = object_tree->headerItem();
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ObjectWidget", "Name", nullptr));
        group_add_button->setText(QCoreApplication::translate("ObjectWidget", "Add group", nullptr));
        delete_button->setText(QCoreApplication::translate("ObjectWidget", "Delete", nullptr));
        object_add_button->setText(QCoreApplication::translate("ObjectWidget", "Add object", nullptr));
        move_button->setText(QCoreApplication::translate("ObjectWidget", "Move", nullptr));
        cancel_button->setText(QCoreApplication::translate("ObjectWidget", "Cancel", nullptr));
        top_button->setText(QCoreApplication::translate("ObjectWidget", "Top", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ObjectWidget: public Ui_ObjectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECT_WIDGET_H
