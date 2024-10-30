/********************************************************************************
** Form generated from reading UI file 'single_object_item_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLE_OBJECT_ITEM_WIDGET_H
#define UI_SINGLE_OBJECT_ITEM_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SingleObjectItemWidget
{
public:
    QTabWidget *single_object_setting_tab;
    QWidget *Geometry;
    QCheckBox *visibility_checkbox;
    QGroupBox *geometry_type_box;
    QComboBox *geometry_type_combobox;
    QPushButton *open_object_file_button;
    QGroupBox *polygon_options_box;
    QCheckBox *smoothing_checkbox;
    QCheckBox *nagata_patch_checkbox;
    QWidget *Transformation;
    QFrame *transformation_frame;
    QWidget *Material;
    QGroupBox *surface_scattering_box;
    QComboBox *surface_scattering_combobox;
    QGroupBox *emitter_box;
    QComboBox *emitter_combobox;
    QCheckBox *light_source_checkbox;

    void setupUi(QWidget *SingleObjectItemWidget)
    {
        if (SingleObjectItemWidget->objectName().isEmpty())
            SingleObjectItemWidget->setObjectName(QString::fromUtf8("SingleObjectItemWidget"));
        SingleObjectItemWidget->resize(321, 321);
        single_object_setting_tab = new QTabWidget(SingleObjectItemWidget);
        single_object_setting_tab->setObjectName(QString::fromUtf8("single_object_setting_tab"));
        single_object_setting_tab->setGeometry(QRect(0, 0, 321, 321));
        single_object_setting_tab->setStyleSheet(QString::fromUtf8("background-color: rgb(114, 114, 114);"));
        Geometry = new QWidget();
        Geometry->setObjectName(QString::fromUtf8("Geometry"));
        visibility_checkbox = new QCheckBox(Geometry);
        visibility_checkbox->setObjectName(QString::fromUtf8("visibility_checkbox"));
        visibility_checkbox->setGeometry(QRect(20, 20, 71, 20));
        visibility_checkbox->setChecked(true);
        geometry_type_box = new QGroupBox(Geometry);
        geometry_type_box->setObjectName(QString::fromUtf8("geometry_type_box"));
        geometry_type_box->setGeometry(QRect(10, 50, 141, 91));
        geometry_type_combobox = new QComboBox(geometry_type_box);
        geometry_type_combobox->setObjectName(QString::fromUtf8("geometry_type_combobox"));
        geometry_type_combobox->setGeometry(QRect(10, 30, 121, 21));
        open_object_file_button = new QPushButton(geometry_type_box);
        open_object_file_button->setObjectName(QString::fromUtf8("open_object_file_button"));
        open_object_file_button->setEnabled(false);
        open_object_file_button->setGeometry(QRect(10, 60, 121, 21));
        polygon_options_box = new QGroupBox(Geometry);
        polygon_options_box->setObjectName(QString::fromUtf8("polygon_options_box"));
        polygon_options_box->setGeometry(QRect(10, 150, 151, 80));
        smoothing_checkbox = new QCheckBox(polygon_options_box);
        smoothing_checkbox->setObjectName(QString::fromUtf8("smoothing_checkbox"));
        smoothing_checkbox->setGeometry(QRect(10, 30, 131, 20));
        smoothing_checkbox->setChecked(true);
        nagata_patch_checkbox = new QCheckBox(polygon_options_box);
        nagata_patch_checkbox->setObjectName(QString::fromUtf8("nagata_patch_checkbox"));
        nagata_patch_checkbox->setGeometry(QRect(10, 50, 131, 20));
        nagata_patch_checkbox->setChecked(true);
        single_object_setting_tab->addTab(Geometry, QString());
        Transformation = new QWidget();
        Transformation->setObjectName(QString::fromUtf8("Transformation"));
        transformation_frame = new QFrame(Transformation);
        transformation_frame->setObjectName(QString::fromUtf8("transformation_frame"));
        transformation_frame->setGeometry(QRect(0, 0, 311, 291));
        transformation_frame->setFrameShape(QFrame::NoFrame);
        transformation_frame->setFrameShadow(QFrame::Raised);
        single_object_setting_tab->addTab(Transformation, QString());
        Material = new QWidget();
        Material->setObjectName(QString::fromUtf8("Material"));
        surface_scattering_box = new QGroupBox(Material);
        surface_scattering_box->setObjectName(QString::fromUtf8("surface_scattering_box"));
        surface_scattering_box->setGeometry(QRect(10, 10, 141, 61));
        surface_scattering_combobox = new QComboBox(surface_scattering_box);
        surface_scattering_combobox->setObjectName(QString::fromUtf8("surface_scattering_combobox"));
        surface_scattering_combobox->setGeometry(QRect(10, 30, 121, 21));
        emitter_box = new QGroupBox(Material);
        emitter_box->setObjectName(QString::fromUtf8("emitter_box"));
        emitter_box->setGeometry(QRect(160, 10, 141, 61));
        emitter_combobox = new QComboBox(emitter_box);
        emitter_combobox->setObjectName(QString::fromUtf8("emitter_combobox"));
        emitter_combobox->setGeometry(QRect(30, 30, 101, 21));
        light_source_checkbox = new QCheckBox(emitter_box);
        light_source_checkbox->setObjectName(QString::fromUtf8("light_source_checkbox"));
        light_source_checkbox->setGeometry(QRect(10, 30, 16, 20));
        single_object_setting_tab->addTab(Material, QString());

        retranslateUi(SingleObjectItemWidget);

        single_object_setting_tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SingleObjectItemWidget);
    } // setupUi

    void retranslateUi(QWidget *SingleObjectItemWidget)
    {
        SingleObjectItemWidget->setWindowTitle(QCoreApplication::translate("SingleObjectItemWidget", "Form", nullptr));
        visibility_checkbox->setText(QCoreApplication::translate("SingleObjectItemWidget", "Visibility", nullptr));
        geometry_type_box->setTitle(QCoreApplication::translate("SingleObjectItemWidget", "Geometry type", nullptr));
        open_object_file_button->setText(QCoreApplication::translate("SingleObjectItemWidget", "Open object file", nullptr));
        polygon_options_box->setTitle(QCoreApplication::translate("SingleObjectItemWidget", "Polygon options", nullptr));
        smoothing_checkbox->setText(QCoreApplication::translate("SingleObjectItemWidget", "Enable smoothing", nullptr));
        nagata_patch_checkbox->setText(QCoreApplication::translate("SingleObjectItemWidget", "Use Nagata patch", nullptr));
        single_object_setting_tab->setTabText(single_object_setting_tab->indexOf(Geometry), QCoreApplication::translate("SingleObjectItemWidget", "Geometry", nullptr));
        single_object_setting_tab->setTabText(single_object_setting_tab->indexOf(Transformation), QCoreApplication::translate("SingleObjectItemWidget", "Transformation", nullptr));
        surface_scattering_box->setTitle(QCoreApplication::translate("SingleObjectItemWidget", "Surface scattering", nullptr));
        emitter_box->setTitle(QCoreApplication::translate("SingleObjectItemWidget", "Emitter", nullptr));
        light_source_checkbox->setText(QString());
        single_object_setting_tab->setTabText(single_object_setting_tab->indexOf(Material), QCoreApplication::translate("SingleObjectItemWidget", "Material", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SingleObjectItemWidget: public Ui_SingleObjectItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLE_OBJECT_ITEM_WIDGET_H
