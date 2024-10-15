/********************************************************************************
** Form generated from reading UI file 'unicolor_texture_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNICOLOR_TEXTURE_WIDGET_H
#define UI_UNICOLOR_TEXTURE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UnicolorTextureWidget
{
public:
    QGroupBox *color_box;
    QFrame *color_frame;

    void setupUi(QWidget *UnicolorTextureWidget)
    {
        if (UnicolorTextureWidget->objectName().isEmpty())
            UnicolorTextureWidget->setObjectName(QString::fromUtf8("UnicolorTextureWidget"));
        UnicolorTextureWidget->resize(341, 261);
        color_box = new QGroupBox(UnicolorTextureWidget);
        color_box->setObjectName(QString::fromUtf8("color_box"));
        color_box->setGeometry(QRect(10, 10, 181, 51));
        color_frame = new QFrame(color_box);
        color_frame->setObjectName(QString::fromUtf8("color_frame"));
        color_frame->setGeometry(QRect(10, 30, 161, 16));
        color_frame->setFrameShape(QFrame::StyledPanel);
        color_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(UnicolorTextureWidget);

        QMetaObject::connectSlotsByName(UnicolorTextureWidget);
    } // setupUi

    void retranslateUi(QWidget *UnicolorTextureWidget)
    {
        UnicolorTextureWidget->setWindowTitle(QCoreApplication::translate("UnicolorTextureWidget", "Form", nullptr));
        color_box->setTitle(QCoreApplication::translate("UnicolorTextureWidget", "Color", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UnicolorTextureWidget: public Ui_UnicolorTextureWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNICOLOR_TEXTURE_WIDGET_H
