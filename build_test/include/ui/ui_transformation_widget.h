/********************************************************************************
** Form generated from reading UI file 'transformation_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFORMATION_WIDGET_H
#define UI_TRANSFORMATION_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TransformationWidget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *transformation_layout;
    QPushButton *down_button;
    QPushButton *translation_button;
    QPushButton *scaling_button;
    QPushButton *rotation_button;
    QPushButton *delete_button;
    QPushButton *up_button;
    QListWidget *transformation_list;

    void setupUi(QWidget *TransformationWidget)
    {
        if (TransformationWidget->objectName().isEmpty())
            TransformationWidget->setObjectName(QString::fromUtf8("TransformationWidget"));
        TransformationWidget->resize(311, 291);
        gridLayoutWidget = new QWidget(TransformationWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 240, 291, 51));
        transformation_layout = new QGridLayout(gridLayoutWidget);
        transformation_layout->setObjectName(QString::fromUtf8("transformation_layout"));
        transformation_layout->setContentsMargins(0, 0, 0, 0);
        down_button = new QPushButton(gridLayoutWidget);
        down_button->setObjectName(QString::fromUtf8("down_button"));
        down_button->setEnabled(false);

        transformation_layout->addWidget(down_button, 1, 1, 1, 1);

        translation_button = new QPushButton(gridLayoutWidget);
        translation_button->setObjectName(QString::fromUtf8("translation_button"));

        transformation_layout->addWidget(translation_button, 0, 0, 1, 1);

        scaling_button = new QPushButton(gridLayoutWidget);
        scaling_button->setObjectName(QString::fromUtf8("scaling_button"));

        transformation_layout->addWidget(scaling_button, 0, 1, 1, 1);

        rotation_button = new QPushButton(gridLayoutWidget);
        rotation_button->setObjectName(QString::fromUtf8("rotation_button"));

        transformation_layout->addWidget(rotation_button, 0, 2, 1, 1);

        delete_button = new QPushButton(gridLayoutWidget);
        delete_button->setObjectName(QString::fromUtf8("delete_button"));
        delete_button->setEnabled(false);

        transformation_layout->addWidget(delete_button, 1, 2, 1, 1);

        up_button = new QPushButton(gridLayoutWidget);
        up_button->setObjectName(QString::fromUtf8("up_button"));
        up_button->setEnabled(false);

        transformation_layout->addWidget(up_button, 1, 0, 1, 1);

        transformation_list = new QListWidget(TransformationWidget);
        transformation_list->setObjectName(QString::fromUtf8("transformation_list"));
        transformation_list->setGeometry(QRect(10, 10, 291, 221));
        transformation_list->setSpacing(1);

        retranslateUi(TransformationWidget);

        QMetaObject::connectSlotsByName(TransformationWidget);
    } // setupUi

    void retranslateUi(QWidget *TransformationWidget)
    {
        TransformationWidget->setWindowTitle(QCoreApplication::translate("TransformationWidget", "Form", nullptr));
        down_button->setText(QCoreApplication::translate("TransformationWidget", "Down", nullptr));
        translation_button->setText(QCoreApplication::translate("TransformationWidget", "Translation", nullptr));
        scaling_button->setText(QCoreApplication::translate("TransformationWidget", "Scaling", nullptr));
        rotation_button->setText(QCoreApplication::translate("TransformationWidget", "Rotation", nullptr));
        delete_button->setText(QCoreApplication::translate("TransformationWidget", "Delete", nullptr));
        up_button->setText(QCoreApplication::translate("TransformationWidget", "Up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TransformationWidget: public Ui_TransformationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFORMATION_WIDGET_H
