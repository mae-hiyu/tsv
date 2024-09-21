/********************************************************************************
** Form generated from reading UI file 'camera_item_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_ITEM_WIDGET_H
#define UI_CAMERA_ITEM_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraItemWidget
{
public:
    QTabWidget *setting_tab;
    QWidget *Transformation;
    QFrame *transformation_frame;
    QWidget *CameraModel;
    QFrame *camera_widget_frame;
    QComboBox *camera_model_combobox;
    QWidget *Film;
    QGroupBox *image_size_box;
    QSpinBox *width_spinbox;
    QSpinBox *height_spinbox;
    QLabel *label;
    QComboBox *size_template_combobox;
    QCheckBox *jittering_checkbox;

    void setupUi(QWidget *CameraItemWidget)
    {
        if (CameraItemWidget->objectName().isEmpty())
            CameraItemWidget->setObjectName(QString::fromUtf8("CameraItemWidget"));
        CameraItemWidget->resize(322, 321);
        CameraItemWidget->setStyleSheet(QString::fromUtf8(""));
        setting_tab = new QTabWidget(CameraItemWidget);
        setting_tab->setObjectName(QString::fromUtf8("setting_tab"));
        setting_tab->setGeometry(QRect(0, 0, 321, 321));
        setting_tab->setStyleSheet(QString::fromUtf8("background-color: rgb(114, 114, 114);"));
        Transformation = new QWidget();
        Transformation->setObjectName(QString::fromUtf8("Transformation"));
        transformation_frame = new QFrame(Transformation);
        transformation_frame->setObjectName(QString::fromUtf8("transformation_frame"));
        transformation_frame->setGeometry(QRect(0, 0, 311, 291));
        transformation_frame->setFrameShape(QFrame::NoFrame);
        transformation_frame->setFrameShadow(QFrame::Raised);
        setting_tab->addTab(Transformation, QString());
        CameraModel = new QWidget();
        CameraModel->setObjectName(QString::fromUtf8("CameraModel"));
        camera_widget_frame = new QFrame(CameraModel);
        camera_widget_frame->setObjectName(QString::fromUtf8("camera_widget_frame"));
        camera_widget_frame->setGeometry(QRect(10, 40, 301, 241));
        camera_widget_frame->setFrameShape(QFrame::StyledPanel);
        camera_widget_frame->setFrameShadow(QFrame::Raised);
        camera_model_combobox = new QComboBox(CameraModel);
        camera_model_combobox->setObjectName(QString::fromUtf8("camera_model_combobox"));
        camera_model_combobox->setGeometry(QRect(10, 10, 91, 21));
        setting_tab->addTab(CameraModel, QString());
        Film = new QWidget();
        Film->setObjectName(QString::fromUtf8("Film"));
        image_size_box = new QGroupBox(Film);
        image_size_box->setObjectName(QString::fromUtf8("image_size_box"));
        image_size_box->setGeometry(QRect(10, 10, 141, 91));
        width_spinbox = new QSpinBox(image_size_box);
        width_spinbox->setObjectName(QString::fromUtf8("width_spinbox"));
        width_spinbox->setGeometry(QRect(10, 60, 51, 21));
        width_spinbox->setReadOnly(true);
        width_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        width_spinbox->setKeyboardTracking(false);
        width_spinbox->setMaximum(10000);
        height_spinbox = new QSpinBox(image_size_box);
        height_spinbox->setObjectName(QString::fromUtf8("height_spinbox"));
        height_spinbox->setGeometry(QRect(80, 60, 51, 21));
        height_spinbox->setReadOnly(true);
        height_spinbox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        height_spinbox->setKeyboardTracking(false);
        height_spinbox->setMaximum(10000);
        label = new QLabel(image_size_box);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(62, 63, 16, 16));
        label->setAlignment(Qt::AlignCenter);
        size_template_combobox = new QComboBox(image_size_box);
        size_template_combobox->setObjectName(QString::fromUtf8("size_template_combobox"));
        size_template_combobox->setGeometry(QRect(10, 30, 121, 21));
        jittering_checkbox = new QCheckBox(Film);
        jittering_checkbox->setObjectName(QString::fromUtf8("jittering_checkbox"));
        jittering_checkbox->setGeometry(QRect(20, 110, 87, 20));
        jittering_checkbox->setChecked(true);
        setting_tab->addTab(Film, QString());

        retranslateUi(CameraItemWidget);

        setting_tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CameraItemWidget);
    } // setupUi

    void retranslateUi(QWidget *CameraItemWidget)
    {
        CameraItemWidget->setWindowTitle(QCoreApplication::translate("CameraItemWidget", "Form", nullptr));
        setting_tab->setTabText(setting_tab->indexOf(Transformation), QCoreApplication::translate("CameraItemWidget", "Transformation", nullptr));
        setting_tab->setTabText(setting_tab->indexOf(CameraModel), QCoreApplication::translate("CameraItemWidget", "CameraModel", nullptr));
        image_size_box->setTitle(QCoreApplication::translate("CameraItemWidget", "ImageSize", nullptr));
        width_spinbox->setPrefix(QCoreApplication::translate("CameraItemWidget", "w: ", nullptr));
        height_spinbox->setPrefix(QCoreApplication::translate("CameraItemWidget", "h: ", nullptr));
        label->setText(QCoreApplication::translate("CameraItemWidget", "x", nullptr));
        jittering_checkbox->setText(QCoreApplication::translate("CameraItemWidget", "jittering", nullptr));
        setting_tab->setTabText(setting_tab->indexOf(Film), QCoreApplication::translate("CameraItemWidget", "Film", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraItemWidget: public Ui_CameraItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_ITEM_WIDGET_H
