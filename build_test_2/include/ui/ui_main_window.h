/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QTabWidget *setting_tab;
    QWidget *system_tab;
    QFrame *system_frame;
    QWidget *Color;
    QFrame *color_frame;
    QWidget *RenderingMethod;
    QFrame *rendering_method_frame;
    QWidget *BVH;
    QFrame *bvh_frame;
    QWidget *EmitterModel;
    QFrame *emitter_model_frame;
    QWidget *SurfaceModel;
    QFrame *surface_model_frame;
    QWidget *Texture;
    QFrame *texture_frame;
    QWidget *gridLayoutWidget;
    QGridLayout *operation_button_layout;
    QPushButton *load_button;
    QPushButton *save_button;
    QPushButton *undo_button;
    QPushButton *redo_button;
    QPushButton *stop_button;
    QPushButton *preview_button;
    QPushButton *render_button;
    QFrame *command_log_frame;
    QLabel *image_view;
    QPlainTextEdit *message_log_view;
    QFrame *object_view;
    QFrame *object_frame;
    QFrame *object_setting_frame;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        MainWindow->setMinimumSize(QSize(1280, 720));
        MainWindow->setMaximumSize(QSize(1280, 720));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(57, 57, 57);"));
        setting_tab = new QTabWidget(MainWindow);
        setting_tab->setObjectName(QString::fromUtf8("setting_tab"));
        setting_tab->setGeometry(QRect(660, 360, 611, 351));
        setting_tab->setStyleSheet(QString::fromUtf8("background-color: rgb(114, 114, 114);"));
        setting_tab->setTabShape(QTabWidget::Rounded);
        system_tab = new QWidget();
        system_tab->setObjectName(QString::fromUtf8("system_tab"));
        system_frame = new QFrame(system_tab);
        system_frame->setObjectName(QString::fromUtf8("system_frame"));
        system_frame->setGeometry(QRect(0, 0, 601, 321));
        system_frame->setFrameShape(QFrame::NoFrame);
        system_frame->setFrameShadow(QFrame::Raised);
        setting_tab->addTab(system_tab, QString());
        Color = new QWidget();
        Color->setObjectName(QString::fromUtf8("Color"));
        color_frame = new QFrame(Color);
        color_frame->setObjectName(QString::fromUtf8("color_frame"));
        color_frame->setGeometry(QRect(0, 0, 601, 321));
        color_frame->setFrameShape(QFrame::NoFrame);
        color_frame->setFrameShadow(QFrame::Raised);
        setting_tab->addTab(Color, QString());
        RenderingMethod = new QWidget();
        RenderingMethod->setObjectName(QString::fromUtf8("RenderingMethod"));
        rendering_method_frame = new QFrame(RenderingMethod);
        rendering_method_frame->setObjectName(QString::fromUtf8("rendering_method_frame"));
        rendering_method_frame->setGeometry(QRect(0, 0, 601, 321));
        rendering_method_frame->setFrameShape(QFrame::NoFrame);
        rendering_method_frame->setFrameShadow(QFrame::Raised);
        setting_tab->addTab(RenderingMethod, QString());
        BVH = new QWidget();
        BVH->setObjectName(QString::fromUtf8("BVH"));
        bvh_frame = new QFrame(BVH);
        bvh_frame->setObjectName(QString::fromUtf8("bvh_frame"));
        bvh_frame->setGeometry(QRect(0, 0, 601, 321));
        bvh_frame->setFrameShape(QFrame::NoFrame);
        bvh_frame->setFrameShadow(QFrame::Raised);
        setting_tab->addTab(BVH, QString());
        EmitterModel = new QWidget();
        EmitterModel->setObjectName(QString::fromUtf8("EmitterModel"));
        emitter_model_frame = new QFrame(EmitterModel);
        emitter_model_frame->setObjectName(QString::fromUtf8("emitter_model_frame"));
        emitter_model_frame->setGeometry(QRect(0, 0, 601, 321));
        emitter_model_frame->setFrameShape(QFrame::StyledPanel);
        emitter_model_frame->setFrameShadow(QFrame::Raised);
        setting_tab->addTab(EmitterModel, QString());
        SurfaceModel = new QWidget();
        SurfaceModel->setObjectName(QString::fromUtf8("SurfaceModel"));
        surface_model_frame = new QFrame(SurfaceModel);
        surface_model_frame->setObjectName(QString::fromUtf8("surface_model_frame"));
        surface_model_frame->setGeometry(QRect(0, 0, 601, 321));
        surface_model_frame->setFrameShape(QFrame::StyledPanel);
        surface_model_frame->setFrameShadow(QFrame::Raised);
        setting_tab->addTab(SurfaceModel, QString());
        Texture = new QWidget();
        Texture->setObjectName(QString::fromUtf8("Texture"));
        texture_frame = new QFrame(Texture);
        texture_frame->setObjectName(QString::fromUtf8("texture_frame"));
        texture_frame->setGeometry(QRect(0, 0, 601, 321));
        texture_frame->setFrameShape(QFrame::StyledPanel);
        texture_frame->setFrameShadow(QFrame::Raised);
        setting_tab->addTab(Texture, QString());
        gridLayoutWidget = new QWidget(MainWindow);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 500, 321, 76));
        operation_button_layout = new QGridLayout(gridLayoutWidget);
        operation_button_layout->setObjectName(QString::fromUtf8("operation_button_layout"));
        operation_button_layout->setSizeConstraint(QLayout::SetFixedSize);
        operation_button_layout->setContentsMargins(0, 0, 0, 0);
        load_button = new QPushButton(gridLayoutWidget);
        load_button->setObjectName(QString::fromUtf8("load_button"));

        operation_button_layout->addWidget(load_button, 0, 1, 1, 1);

        save_button = new QPushButton(gridLayoutWidget);
        save_button->setObjectName(QString::fromUtf8("save_button"));

        operation_button_layout->addWidget(save_button, 2, 1, 1, 1);

        undo_button = new QPushButton(gridLayoutWidget);
        undo_button->setObjectName(QString::fromUtf8("undo_button"));
        undo_button->setEnabled(false);
        undo_button->setStyleSheet(QString::fromUtf8(""));

        operation_button_layout->addWidget(undo_button, 0, 0, 1, 1);

        redo_button = new QPushButton(gridLayoutWidget);
        redo_button->setObjectName(QString::fromUtf8("redo_button"));
        redo_button->setEnabled(false);

        operation_button_layout->addWidget(redo_button, 2, 0, 1, 1);

        stop_button = new QPushButton(gridLayoutWidget);
        stop_button->setObjectName(QString::fromUtf8("stop_button"));
        stop_button->setEnabled(false);

        operation_button_layout->addWidget(stop_button, 2, 3, 1, 1);

        preview_button = new QPushButton(gridLayoutWidget);
        preview_button->setObjectName(QString::fromUtf8("preview_button"));

        operation_button_layout->addWidget(preview_button, 0, 2, 1, 1);

        render_button = new QPushButton(gridLayoutWidget);
        render_button->setObjectName(QString::fromUtf8("render_button"));
        render_button->setStyleSheet(QString::fromUtf8(""));

        operation_button_layout->addWidget(render_button, 2, 2, 1, 1);

        command_log_frame = new QFrame(MainWindow);
        command_log_frame->setObjectName(QString::fromUtf8("command_log_frame"));
        command_log_frame->setGeometry(QRect(360, 500, 291, 71));
        command_log_frame->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 170);"));
        command_log_frame->setFrameShape(QFrame::StyledPanel);
        command_log_frame->setFrameShadow(QFrame::Plain);
        image_view = new QLabel(MainWindow);
        image_view->setObjectName(QString::fromUtf8("image_view"));
        image_view->setGeometry(QRect(10, 10, 640, 480));
        image_view->setFrameShape(QFrame::StyledPanel);
        image_view->setScaledContents(false);
        message_log_view = new QPlainTextEdit(MainWindow);
        message_log_view->setObjectName(QString::fromUtf8("message_log_view"));
        message_log_view->setGeometry(QRect(10, 580, 641, 131));
        message_log_view->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 170, 170);"));
        message_log_view->setFrameShadow(QFrame::Plain);
        message_log_view->setUndoRedoEnabled(false);
        message_log_view->setReadOnly(true);
        message_log_view->setMaximumBlockCount(100);
        object_view = new QFrame(MainWindow);
        object_view->setObjectName(QString::fromUtf8("object_view"));
        object_view->setGeometry(QRect(660, 10, 611, 341));
        object_view->setFrameShape(QFrame::StyledPanel);
        object_view->setFrameShadow(QFrame::Raised);
        object_frame = new QFrame(object_view);
        object_frame->setObjectName(QString::fromUtf8("object_frame"));
        object_frame->setGeometry(QRect(340, 10, 261, 321));
        object_frame->setFrameShape(QFrame::StyledPanel);
        object_frame->setFrameShadow(QFrame::Raised);
        object_setting_frame = new QFrame(object_view);
        object_setting_frame->setObjectName(QString::fromUtf8("object_setting_frame"));
        object_setting_frame->setGeometry(QRect(10, 10, 321, 321));
        object_setting_frame->setFrameShape(QFrame::StyledPanel);
        object_setting_frame->setFrameShadow(QFrame::Plain);

        retranslateUi(MainWindow);

        setting_tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Reflect", nullptr));
        setting_tab->setTabText(setting_tab->indexOf(system_tab), QCoreApplication::translate("MainWindow", "System", nullptr));
        setting_tab->setTabText(setting_tab->indexOf(Color), QCoreApplication::translate("MainWindow", "Color", nullptr));
        setting_tab->setTabText(setting_tab->indexOf(RenderingMethod), QCoreApplication::translate("MainWindow", "RendererMethod", nullptr));
        setting_tab->setTabText(setting_tab->indexOf(BVH), QCoreApplication::translate("MainWindow", "BVH", nullptr));
        setting_tab->setTabText(setting_tab->indexOf(EmitterModel), QCoreApplication::translate("MainWindow", "EmitterModel", nullptr));
        setting_tab->setTabText(setting_tab->indexOf(SurfaceModel), QCoreApplication::translate("MainWindow", "SurfaceModel", nullptr));
        setting_tab->setTabText(setting_tab->indexOf(Texture), QCoreApplication::translate("MainWindow", "Texture", nullptr));
        load_button->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        save_button->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        undo_button->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
#if QT_CONFIG(shortcut)
        undo_button->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        redo_button->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
#if QT_CONFIG(shortcut)
        redo_button->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        stop_button->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        preview_button->setText(QCoreApplication::translate("MainWindow", "Preview", nullptr));
        render_button->setText(QCoreApplication::translate("MainWindow", "Render", nullptr));
        image_view->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
