/********************************************************************************
** Form generated from reading UI file 'group_item_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUP_ITEM_WIDGET_H
#define UI_GROUP_ITEM_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupItemWidget
{
public:
    QTabWidget *group_setting_tab;
    QWidget *Geometry;
    QCheckBox *visibility_checkbox;
    QWidget *Transformation;
    QFrame *transformation_frame;

    void setupUi(QWidget *GroupItemWidget)
    {
        if (GroupItemWidget->objectName().isEmpty())
            GroupItemWidget->setObjectName(QString::fromUtf8("GroupItemWidget"));
        GroupItemWidget->resize(321, 321);
        group_setting_tab = new QTabWidget(GroupItemWidget);
        group_setting_tab->setObjectName(QString::fromUtf8("group_setting_tab"));
        group_setting_tab->setGeometry(QRect(0, 0, 321, 321));
        group_setting_tab->setStyleSheet(QString::fromUtf8("background-color: rgb(114, 114, 114);"));
        Geometry = new QWidget();
        Geometry->setObjectName(QString::fromUtf8("Geometry"));
        visibility_checkbox = new QCheckBox(Geometry);
        visibility_checkbox->setObjectName(QString::fromUtf8("visibility_checkbox"));
        visibility_checkbox->setGeometry(QRect(20, 20, 71, 20));
        visibility_checkbox->setChecked(true);
        group_setting_tab->addTab(Geometry, QString());
        Transformation = new QWidget();
        Transformation->setObjectName(QString::fromUtf8("Transformation"));
        transformation_frame = new QFrame(Transformation);
        transformation_frame->setObjectName(QString::fromUtf8("transformation_frame"));
        transformation_frame->setGeometry(QRect(0, 0, 311, 291));
        transformation_frame->setFrameShape(QFrame::NoFrame);
        transformation_frame->setFrameShadow(QFrame::Raised);
        group_setting_tab->addTab(Transformation, QString());

        retranslateUi(GroupItemWidget);

        group_setting_tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GroupItemWidget);
    } // setupUi

    void retranslateUi(QWidget *GroupItemWidget)
    {
        GroupItemWidget->setWindowTitle(QCoreApplication::translate("GroupItemWidget", "Form", nullptr));
        visibility_checkbox->setText(QCoreApplication::translate("GroupItemWidget", "Visibility", nullptr));
        group_setting_tab->setTabText(group_setting_tab->indexOf(Geometry), QCoreApplication::translate("GroupItemWidget", "Geometry", nullptr));
        group_setting_tab->setTabText(group_setting_tab->indexOf(Transformation), QCoreApplication::translate("GroupItemWidget", "Transformation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupItemWidget: public Ui_GroupItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUP_ITEM_WIDGET_H
