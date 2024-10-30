/********************************************************************************
** Form generated from reading UI file 'multilayer_thin_film_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTILAYER_THIN_FILM_WIDGET_H
#define UI_MULTILAYER_THIN_FILM_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MultilayerThinFilmWidget
{
public:
    QListWidget *thin_film_layer_list;
    QGroupBox *exterior_medium_box;
    QFrame *exterior_refractive_index_frame;
    QGroupBox *interior_medium_box;
    QCheckBox *interior_conductor_checkbox;
    QFrame *interior_refractive_index_frame;
    QFrame *interior_extinction_frame;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *layer_button_layout;
    QPushButton *add_button;
    QPushButton *up_button;
    QPushButton *down_button;
    QPushButton *delete_button;

    void setupUi(QWidget *MultilayerThinFilmWidget)
    {
        if (MultilayerThinFilmWidget->objectName().isEmpty())
            MultilayerThinFilmWidget->setObjectName(QString::fromUtf8("MultilayerThinFilmWidget"));
        MultilayerThinFilmWidget->resize(341, 261);
        thin_film_layer_list = new QListWidget(MultilayerThinFilmWidget);
        thin_film_layer_list->setObjectName(QString::fromUtf8("thin_film_layer_list"));
        thin_film_layer_list->setGeometry(QRect(10, 50, 321, 141));
        thin_film_layer_list->setSpacing(1);
        exterior_medium_box = new QGroupBox(MultilayerThinFilmWidget);
        exterior_medium_box->setObjectName(QString::fromUtf8("exterior_medium_box"));
        exterior_medium_box->setGeometry(QRect(10, 0, 321, 41));
        exterior_refractive_index_frame = new QFrame(exterior_medium_box);
        exterior_refractive_index_frame->setObjectName(QString::fromUtf8("exterior_refractive_index_frame"));
        exterior_refractive_index_frame->setGeometry(QRect(100, 20, 101, 16));
        exterior_refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        exterior_refractive_index_frame->setFrameShadow(QFrame::Raised);
        interior_medium_box = new QGroupBox(MultilayerThinFilmWidget);
        interior_medium_box->setObjectName(QString::fromUtf8("interior_medium_box"));
        interior_medium_box->setGeometry(QRect(10, 220, 321, 41));
        interior_conductor_checkbox = new QCheckBox(interior_medium_box);
        interior_conductor_checkbox->setObjectName(QString::fromUtf8("interior_conductor_checkbox"));
        interior_conductor_checkbox->setGeometry(QRect(10, 20, 81, 16));
        interior_conductor_checkbox->setChecked(true);
        interior_refractive_index_frame = new QFrame(interior_medium_box);
        interior_refractive_index_frame->setObjectName(QString::fromUtf8("interior_refractive_index_frame"));
        interior_refractive_index_frame->setGeometry(QRect(100, 20, 101, 16));
        interior_refractive_index_frame->setFrameShape(QFrame::StyledPanel);
        interior_refractive_index_frame->setFrameShadow(QFrame::Raised);
        interior_extinction_frame = new QFrame(interior_medium_box);
        interior_extinction_frame->setObjectName(QString::fromUtf8("interior_extinction_frame"));
        interior_extinction_frame->setGeometry(QRect(210, 20, 101, 16));
        interior_extinction_frame->setFrameShape(QFrame::StyledPanel);
        interior_extinction_frame->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget = new QWidget(MultilayerThinFilmWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 190, 321, 28));
        layer_button_layout = new QHBoxLayout(horizontalLayoutWidget);
        layer_button_layout->setObjectName(QString::fromUtf8("layer_button_layout"));
        layer_button_layout->setContentsMargins(0, 0, 0, 0);
        add_button = new QPushButton(horizontalLayoutWidget);
        add_button->setObjectName(QString::fromUtf8("add_button"));

        layer_button_layout->addWidget(add_button);

        up_button = new QPushButton(horizontalLayoutWidget);
        up_button->setObjectName(QString::fromUtf8("up_button"));

        layer_button_layout->addWidget(up_button);

        down_button = new QPushButton(horizontalLayoutWidget);
        down_button->setObjectName(QString::fromUtf8("down_button"));

        layer_button_layout->addWidget(down_button);

        delete_button = new QPushButton(horizontalLayoutWidget);
        delete_button->setObjectName(QString::fromUtf8("delete_button"));

        layer_button_layout->addWidget(delete_button);


        retranslateUi(MultilayerThinFilmWidget);

        QMetaObject::connectSlotsByName(MultilayerThinFilmWidget);
    } // setupUi

    void retranslateUi(QWidget *MultilayerThinFilmWidget)
    {
        MultilayerThinFilmWidget->setWindowTitle(QCoreApplication::translate("MultilayerThinFilmWidget", "Form", nullptr));
        exterior_medium_box->setTitle(QCoreApplication::translate("MultilayerThinFilmWidget", "Exterior medium", nullptr));
        interior_medium_box->setTitle(QCoreApplication::translate("MultilayerThinFilmWidget", "Interior medium", nullptr));
        interior_conductor_checkbox->setText(QCoreApplication::translate("MultilayerThinFilmWidget", "Conductor", nullptr));
        add_button->setText(QCoreApplication::translate("MultilayerThinFilmWidget", "Add", nullptr));
        up_button->setText(QCoreApplication::translate("MultilayerThinFilmWidget", "Up", nullptr));
        down_button->setText(QCoreApplication::translate("MultilayerThinFilmWidget", "Down", nullptr));
        delete_button->setText(QCoreApplication::translate("MultilayerThinFilmWidget", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MultilayerThinFilmWidget: public Ui_MultilayerThinFilmWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTILAYER_THIN_FILM_WIDGET_H
