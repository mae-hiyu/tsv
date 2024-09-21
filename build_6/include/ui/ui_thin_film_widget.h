/********************************************************************************
** Form generated from reading UI file 'thin_film_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THIN_FILM_WIDGET_H
#define UI_THIN_FILM_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThinFilmWidget
{
public:
    QDoubleSpinBox *thickness_spinbox;
    QCheckBox *conductor_checkbox;
    QFrame *refractive_index_frame;
    QFrame *extinction_frame;

    void setupUi(QWidget *ThinFilmWidget)
    {
        if (ThinFilmWidget->objectName().isEmpty())
            ThinFilmWidget->setObjectName(QString::fromUtf8("ThinFilmWidget"));
        ThinFilmWidget->resize(251, 41);
        thickness_spinbox = new QDoubleSpinBox(ThinFilmWidget);
        thickness_spinbox->setObjectName(QString::fromUtf8("thickness_spinbox"));
        thickness_spinbox->setGeometry(QRect(110, 0, 131, 16));
        thickness_spinbox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        thickness_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        thickness_spinbox->setKeyboardTracking(false);
        thickness_spinbox->setDecimals(4);
        thickness_spinbox->setMinimum(0.000100000000000);
        thickness_spinbox->setMaximum(1000.000000000000000);
        thickness_spinbox->setValue(10.000000000000000);
        conductor_checkbox = new QCheckBox(ThinFilmWidget);
        conductor_checkbox->setObjectName(QString::fromUtf8("conductor_checkbox"));
        conductor_checkbox->setGeometry(QRect(10, 0, 87, 16));
        conductor_checkbox->setChecked(true);
        refractive_index_frame = new QFrame(ThinFilmWidget);
        refractive_index_frame->setObjectName(QString::fromUtf8("refractive_index_frame"));
        refractive_index_frame->setGeometry(QRect(20, 20, 101, 16));
        refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        refractive_index_frame->setFrameShadow(QFrame::Raised);
        extinction_frame = new QFrame(ThinFilmWidget);
        extinction_frame->setObjectName(QString::fromUtf8("extinction_frame"));
        extinction_frame->setGeometry(QRect(130, 20, 101, 16));
        extinction_frame->setFrameShape(QFrame::StyledPanel);
        extinction_frame->setFrameShadow(QFrame::Raised);

        retranslateUi(ThinFilmWidget);

        QMetaObject::connectSlotsByName(ThinFilmWidget);
    } // setupUi

    void retranslateUi(QWidget *ThinFilmWidget)
    {
        ThinFilmWidget->setWindowTitle(QCoreApplication::translate("ThinFilmWidget", "Form", nullptr));
        thickness_spinbox->setPrefix(QCoreApplication::translate("ThinFilmWidget", "Thickness: ", nullptr));
        thickness_spinbox->setSuffix(QCoreApplication::translate("ThinFilmWidget", " nm", nullptr));
        conductor_checkbox->setText(QCoreApplication::translate("ThinFilmWidget", "conductor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ThinFilmWidget: public Ui_ThinFilmWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THIN_FILM_WIDGET_H
