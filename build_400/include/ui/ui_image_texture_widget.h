/********************************************************************************
** Form generated from reading UI file 'image_texture_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGE_TEXTURE_WIDGET_H
#define UI_IMAGE_TEXTURE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageTextureWidget
{
public:
    QPushButton *image_open_button;
    QLabel *image_viewer;

    void setupUi(QWidget *ImageTextureWidget)
    {
        if (ImageTextureWidget->objectName().isEmpty())
            ImageTextureWidget->setObjectName(QString::fromUtf8("ImageTextureWidget"));
        ImageTextureWidget->resize(341, 261);
        image_open_button = new QPushButton(ImageTextureWidget);
        image_open_button->setObjectName(QString::fromUtf8("image_open_button"));
        image_open_button->setGeometry(QRect(20, 20, 131, 16));
        image_viewer = new QLabel(ImageTextureWidget);
        image_viewer->setObjectName(QString::fromUtf8("image_viewer"));
        image_viewer->setGeometry(QRect(10, 50, 321, 201));
        image_viewer->setFrameShape(QFrame::StyledPanel);
        image_viewer->setAlignment(Qt::AlignCenter);

        retranslateUi(ImageTextureWidget);

        QMetaObject::connectSlotsByName(ImageTextureWidget);
    } // setupUi

    void retranslateUi(QWidget *ImageTextureWidget)
    {
        ImageTextureWidget->setWindowTitle(QCoreApplication::translate("ImageTextureWidget", "Form", nullptr));
        image_open_button->setText(QCoreApplication::translate("ImageTextureWidget", "Open", nullptr));
        image_viewer->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ImageTextureWidget: public Ui_ImageTextureWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGE_TEXTURE_WIDGET_H
