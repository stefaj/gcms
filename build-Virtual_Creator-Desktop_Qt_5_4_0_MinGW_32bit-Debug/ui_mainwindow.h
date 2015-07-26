/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "RenderStates/renderstate.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_nodes_file;
    QAction *actionRun;
    QAction *actionInvert_Mouse_Y;
    QAction *actionOpen_Premises_File;
    QWidget *centralWidget;
    RenderState *openGLWidget;
    QDockWidget *dockWidget_add_stuff;
    QWidget *dockWidgetContents;
    QStackedWidget *stackedWidget_side_add;
    QWidget *page_add_node;
    QGroupBox *groupBox_node_settings;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_bike;
    QCheckBox *checkBox_walk;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_vehicle;
    QCheckBox *checkBox_wheelchair;
    QGroupBox *groupBox_node_settings_2;
    QCheckBox *checkbox_significant;
    QLineEdit *lineEdit_node_name;
    QLabel *label;
    QWidget *page_floor_plan;
    QGroupBox *groupBox_floor_plan_settings;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_floor_plan_width;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_floor_plan_height;
    QWidget *widget2;
    QVBoxLayout *verticalLayout;
    QPushButton *button_tree1;
    QPushButton *button_node;
    QPushButton *button_pavement;
    QPushButton *button_link;
    QPushButton *button_wall;
    QPushButton *button_floor_plan;
    QPushButton *button_door;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuBuild;
    QMenu *menuConfiguration;
    QDockWidget *dockWidget_remove_objects;
    QWidget *dockWidgetContents_remove_objects;
    QWidget *widget3;
    QVBoxLayout *verticalLayout_6;
    QPushButton *button_remove_node;
    QPushButton *button_remove_tree;
    QDockWidget *dockWidget_transformations;
    QWidget *dockWidgetContents_transformations;
    QLabel *label_ground_floor;
    QLabel *label_floor_level;
    QSpinBox *spinBox_floor_level;
    QLabel *label_rotation_y;
    QDoubleSpinBox *spin_rotationY;
    QDockWidget *dockWidget_configuration;
    QWidget *dockWidgetContents_configuration;
    QCheckBox *checkBox_inversemouse_y;
    QPushButton *button_execute_virtual_concierge;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setWindowOpacity(1);
        MainWindow->setStyleSheet(QLatin1String("/* Basic Palette\n"
"border styles: dashed | dot-dash | dot-dot-dash | dotted | double | groove | inset | outset | ridge | solid | none\n"
"*/\n"
"\n"
"/* Set the selection colors for all widgets. */\n"
"QWidget\n"
"{\n"
"	color: #111111;\n"
"	border: 0px solid #737373;\n"
"	background: #727272;\n"
"	selection-color: #cccccc;\n"
"	selection-background-color: #686868;\n"
"	padding: 0px;\n"
"	margin: 0px;\n"
"}\n"
"\n"
"QMainWindow\n"
"{\n"
"	background: #727272;\n"
"	padding: 0px;\n"
"	margin: 0px;\n"
"	border: 0px solid #1a1a1a;\n"
"}\n"
"\n"
"QMainWindow::separator:horizontal\n"
"{\n"
"    background: #ff0000;\n"
"    max-width: 2px;\n"
"	width: 2px;\n"
"	border-top: 1px solid #393939;\n"
"	border-bottom: 1px solid #959595;\n"
"}\n"
"\n"
"QMainWindow::separator:vertical\n"
"{\n"
"    background: #ff0000;\n"
"    max-height: 2px;\n"
"	height: 2px;\n"
"	border-left: 1px solid #393939;\n"
"	border-right: 1px solid #959595;\n"
"}\n"
"QMainWindow::separator:hover\n"
"{\n"
"    background: #686868;\n"
"}\n"
"\n"
"/"
                        "* Customize check boxes. */\n"
"QCheckBox \n"
"{\n"
"    spacing: 5px;\n"
"   	/*border: 1px solid #242424;*/\n"
"	/*background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #535353, stop:1 #686868);*/\n"
" 	background: transparent;\n"
"	max-width: 200px;\n"
"    max-height: 13px;\n"
"}\n"
"\n"
"QCheckBox::indicator\n"
"{\n"
"    width: 13px;\n"
"    height: 13px;\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:checked\n"
"{\n"
"    /*image: url(:/checkbox_checked);*/\n"
"}\n"
"\n"
"QCheckBox::indicator:checked:hover\n"
"{\n"
"    /*image: url(:/checkbox_checked_hover);*/\n"
"}\n"
"\n"
"QCheckBox::indicator:checked:pressed\n"
"{\n"
"  /*  image: url(:/checkbox_checked_pressed);*/\n"
"}\n"
"\n"
"/* Combobox */\n"
"QComboBox \n"
"{\n"
"	border: 1px solid #242424;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #535353, stop:1 #373737);\n"
"	color: #c8c8c8;\n"
"	border-top-left-radius: 4px; /* same radius as the QComboBox */\n"
"	border-bottom-left-radius: 4px;\n"
"	border-top-right-radius: 4px;\n"
"	b"
                        "order-bottom-right-radius: 4px;\n"
"	padding: 1px 18px 1px 13px;\n"
"	min-width: 6em;\n"
"	max-height: 15px;\n"
"}\n"
"\n"
"/* The popup */\n"
"QComboBox QAbstractItemView {\n"
"	border: 1px solid #303030;\n"
"	background: #212121;\n"
"	selection-background-color: #484848;\n"
"	selection-color: #ffffff;\n"
"	color: #c8c8c8;\n"
"}\n"
"\n"
"QComboBox:editable\n"
"{\n"
"	border: 1px solid #242424;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #535353, stop:1 #373737);	\n"
"}\n"
"\n"
"QComboBox:!editable, QComboBox::drop-down:editable\n"
"{\n"
"	border: 1px solid #242424;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #535353, stop:1 #373737);\n"
"	\n"
"}\n"
"\n"
"/* QComboBox gets the \"on\" state when the popup is open */\n"
"QComboBox:!editable:on, QComboBox::drop-down:editable:on\n"
"{\n"
"	border: 1px solid #242424;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #535353, stop:1 #373737);\n"
"	\n"
"}\n"
"\n"
"QComboBox:on\n"
"{ \n"
"	/* shift the text when th"
                        "e popup opens */\n"
"	padding-top: 3px;\n"
"	padding-left: 4px;\n"
"	border: 1px solid #242424;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #535353, stop:1 #373737);\n"
"}\n"
"\n"
"/* Drop down button */\n"
"QComboBox::drop-down\n"
"{\n"
"	subcontrol-origin: padding;\n"
"	subcontrol-position: top right;\n"
"	width: 15px;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #535353, stop:1 #373737);\n"
"	border: 0px solid #818181;\n"
"	border-top-right-radius: 6px; /* same radius as the QComboBox */\n"
"	border-bottom-right-radius: 6px;\n"
"}\n"
"\n"
"QComboBox::down-arrow\n"
"{\n"
"     image: url(:/arrow_down);\n"
"     width: 11px;\n"
"     height: 6px;\n"
"}\n"
"\n"
"QComboBox::up-arrow\n"
"{\n"
"     image: url(:/arrow_up);\n"
"     width: 11px;\n"
"     height: 6px;\n"
"}\n"
"\n"
"QDockWidget\n"
"{\n"
"    border-top: 1px solid #1a1a1a;\n"
"	border-bottom: 1px solid #1a1a1a;\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"QDockWidget::title\n"
"{\n"
"    background: qlineargradient("
                        "x1:0, y1:0, x2:0, y2:1, stop:0 #4c4c4c, stop:1 #434343);\n"
"}\n"
"\n"
"QFrame\n"
"{\n"
"     border: 0px solid #737373;\n"
"     border-radius: 0px;\n"
"     padding: 0px;\n"
"     background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
" {\n"
"     border: 1px solid #3a3a3a;\n"
"     background: #727272;\n"
"     border-radius: 5px;\n"
"     margin-top: 20px;\n"
" }\n"
"\n"
"QGroupBox::title\n"
"{\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top left;\n"
"     padding: 0px 0px;\n"
"     color: #0b0b0b;\n"
"     background-color: transparent;\n"
"}\n"
"\n"
"/* Header for ... */\n"
"QHeaderView::section\n"
"{\n"
"	color: #cccccc;\n"
"	background: transparent;\n"
"	padding-left: 4px;\n"
"	border-top: 0px solid #393939;\n"
"	border-bottom: 0px solid #959595;\n"
"	min-height: 15px;\n"
"}\n"
"\n"
"/* Text input box */\n"
"QLineEdit\n"
"{\n"
"	color: #c8c8c8;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #808080, stop:1 #8c8c8c);\n"
"    border: 1px solid #4d4d4d;\n"
"	p"
                        "adding: 0 8px;\n"
"	selection-background-color: #222222;\n"
"	selection-color: #f5f5f5;\n"
"	margin-left: 5px;\n"
"	margin-right: 5px;\n"
"	border-radius: 5px;\n"
"	max-height: 14px;\n"
"	height: 14px;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	margin-left: 5px;\n"
"	margin-right: 5px;\n"
"	background: none;\n"
"	border: 0px;\n"
"}\n"
"\n"
"/* Drop down style */\n"
"QMenu\n"
"{\n"
"	background: #212121;\n"
"	border: 1px solid #303030;\n"
"	color: #eaeaea;\n"
"}\n"
"\n"
"QMenu::separator \n"
"{\n"
"     image: none;\n"
"     border-top: 1px solid #262626;\n"
"}\n"
"\n"
"QMenu::item\n"
"{\n"
"	/* sets background of menu item. set this to something non-transparent\n"
"	if you want menu color and menu item color to be different */\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QMenu::item:selected\n"
"{\n"
"	/* when user selects item using mouse or keyboard */\n"
"	background: #3e3e3e;\n"
"	color: #ffffff;\n"
"}\n"
"\n"
"QMenuBar\n"
"{\n"
"    border-top: 1px solid #8b8b8b;\n"
"	border-left: 0px solid #606060;\n"
"	bord"
                        "er-bottom: 1px solid #939393;\n"
"	border-right: 0px solid #303030;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #686868, stop:0.8 #686868, stop:0.9 #474747, stop:1 #000000);\n"
"	min-height: 20px;\n"
"}\n"
"\n"
"QMenuBar::item\n"
"{\n"
"	spacing: 3px; /* spacing between menu bar items */\n"
"	padding: 1px 4px;\n"
"	background: transparent;\n"
"	color: #111111;\n"
"	max-height: 16px;\n"
"}\n"
"\n"
"/* when selected using mouse or keyboard */\n"
"\n"
"QMenuBar::item:selected\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #565656, stop:1 #464646);\n"
"	color: #ffffff;\n"
"	border-radius: 5px;\n"
"	border:	1px solid #222222;\n"
"}\n"
"\n"
"QMenuBar::item:pressed\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #565656, stop:1 #464646);\n"
"	color: #ffffff;\n"
"	border-radius: 5px;\n"
"	border:	1px solid #222222;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"    color: #0b0b0b;\n"
"    border: 1px solid #353535;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0"
                        ", y2:1, stop:0 #a6a6a6, stop:1 #8a8a8a);\n"
"	border-radius: 3px;\n"
"	padding-left: 5px;\n"
"	padding-right: 5px;\n"
"}\n"
"\n"
"/* all types of push button */\n"
"QPushButton:hover\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #565656, stop:1 #464646);\n"
"	color: #ffffff;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #565656, stop:1 #464646);\n"
"	color: #e5e5e5;\n"
"}\n"
"QPushButton:checked\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #565656, stop:1 #464646);\n"
"	color: #e5e5e5;\n"
"}\n"
"\n"
"\n"
"/* Customize radio buttons. */\n"
"QRadioButton \n"
"{\n"
"    spacing: 5px;\n"
"}\n"
"\n"
"QRadioButton::indicator \n"
"{\n"
"    width: 13px;\n"
"    height: 13px;\n"
"}\n"
"\n"
"QRadioButton::indicator::unchecked\n"
"{\n"
"    image: url(:/radiobutton_unchecked);\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:hover \n"
"{\n"
"    image: url(:/radiobutton_unchecked_hover);\n"
"}\n"
"\n"
"QRadioButto"
                        "n::indicator:unchecked:pressed \n"
"{\n"
"    image: url(:/radiobutton_unchecked_pressed);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked \n"
"{\n"
"    image: url(:/radiobutton_checked);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked:hover \n"
"{\n"
"    image: url(:/radiobutton_checked_hover);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked:pressed \n"
"{\n"
"    image: url(:/radiobutton_checked_pressed);\n"
"}\n"
"\n"
"/* Customize arrows. \n"
"*::down-arrow, *::menu-indicator {\n"
"    image: url(:/arrow_down);\n"
"    width: 9px;\n"
"    height: 9px;\n"
"}\n"
"\n"
"*::down-arrow:disabled, *::down-arrow:off {\n"
"   image: url(:/down_arrow_disabled.png);\n"
"}\n"
"\n"
"*::up-arrow {\n"
"    image: url(:/arrow_up);\n"
"    width: 9px;\n"
"    height: 9px;\n"
"}\n"
"\n"
"*::up-arrow:disabled, *::up-arrow:off {\n"
"   image: url(:/up_arrow_disabled.png);\n"
"}\n"
"\n"
"*/\n"
"\n"
"QScrollBar QAbstractScrollArea\n"
"{\n"
"	background: transparent;\n"
"}\n"
"\n"
"QScrollBar:horizontal\n"
"{\n"
"	max-height: 12p"
                        "x;\n"
"	min-height: 12px;\n"
"	margin: 0px 22px 0px 22px;\n"
"    border: 0px solid #474747;\n"
"    border-radius: 0px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal\n"
"{\n"
"	border: 1px solid #383838;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #969696, stop:1 #7b7b7b);\n"
"	border-radius: 3px;\n"
"	min-height: 8px;\n"
"	max-height: 8px;\n"
"	height: 8px;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal\n"
"{\n"
"	border: 0px solid #1e1e1e;\n"
"    background-color: transparent;\n"
"    width: 0px;\n"
"    subcontrol-position: right;\n"
"    subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal\n"
"{\n"
"	border: 0px solid #1e1e1e;\n"
"    background-color: transparent;\n"
"    width: 0px;\n"
"    subcontrol-position: left;\n"
"    subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::left-arrow:horizontal\n"
"{\n"
"	background-color: transparent;\n"
"    width: 0px;\n"
"    height: 0px;\n"
"}\n"
"  \n"
"QScrollBar::right-arrow:horizonta"
                        "l\n"
"{\n"
"	background-color: transparent;\n"
"    width: 0px;\n"
"    height: 0px;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal\n"
"{\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QScrollBar:vertical \n"
"{\n"
"    border: 0px solid #1e1e1e;\n"
"    border-radius: 0px;\n"
"    background: transparent;\n"
"    max-width: 12px;\n"
"	min-width: 12px;\n"
"	margin: 22px 0px 22px 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical\n"
"{\n"
"	border: 1px solid #383838;\n"
"	background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #969696, stop:1 #7b7b7b);\n"
"	border-radius: 3px;\n"
"	min-width: 8px;\n"
"	max-width: 8px;\n"
"	min-height: 20px;\n"
"	max-height: 20px;\n"
"	width: 8px;\n"
"\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical\n"
"{\n"
"    subcontrol-position: top;\n"
"    subcontrol-origin: margin;\n"
"	border: 0px solid #1e1e1e;\n"
"	background-color: transparent;\n"
"	height: 0px;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical\n"
"{\n"
"    subcontrol-position: bottom"
                        ";\n"
"    subcontrol-origin: margin;\n"
"	border: 0px solid #1e1e1e;\n"
"	background-color: transparent;\n"
"	height: 0px;\n"
"}\n"
"\n"
"QScrollBar::up-arrow:vertical\n"
"{\n"
"	background-color: transparent;\n"
"    width: 0px;\n"
"    height: 0px;\n"
"}\n"
"  \n"
"QScrollBar::down-arrow:vertical\n"
"{\n"
"	background-color: transparent;\n"
"    width: 0px;\n"
"    height: 0px;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QSlider\n"
"{\n"
"	background-color: #808080;\n"
"}\n"
"\n"
"QSlider::groove:vertical\n"
"{\n"
"	background-color: transperant;\n"
"	position: absolute; \n"
"	left: 4px; right: 4px;\n"
"}\n"
"\n"
"QSlider::handle:vertical\n"
"{\n"
"     height: 10px;\n"
"     background: #ff7603;\n"
"     border: 1px solid #62340e;\n"
"     margin: 0 -4px; /* expand outside the groove */\n"
"}\n"
"\n"
"QSlider::add-page:vertical\n"
"{\n"
"     background: #222222;\n"
"}\n"
"\n"
"QSlider::sub-page:vertical\n"
"{\n"
"     "
                        "background: #222222;\n"
"}\n"
"\n"
"QSpinBox \n"
"{\n"
"    padding-right: 15px; /* make room for the arrows */\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #808080, stop:1 #8c8c8c);\n"
"    border: 1px solid #4d4d4d;\n"
"    color: #ffffff;\n"
"   	border-top-left-radius: 3px; /* same radius as the QComboBox */\n"
"	border-bottom-left-radius: 3px;\n"
"}\n"
" \n"
"QSpinBox::up-button\n"
"{\n"
"    subcontrol-origin: border;\n"
"    subcontrol-position: top right; /* position at the top right corner */\n"
"    width: 16px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a6a6a6, stop:1 #979797);\n"
"    border: 1px solid #323232;\n"
"	border-bottom-width: 0;\n"
"}\n"
"\n"
"QSpinBox::up-button:hover\n"
"{\n"
"	background: #3e3e3e;\n"
"}\n"
"\n"
"QSpinBox::up-button:pressed\n"
"{\n"
"	background: #3e3e3e;\n"
"}\n"
"\n"
"QSpinBox::up-arrow\n"
"{\n"
"     image: url(:/arrow_up);\n"
"     width: 11px;\n"
"     height:"
                        " 6px;\n"
"}\n"
"\n"
"QSpinBox::up-arrow:disabled, QSpinBox::up-arrow:off\n"
"{ /* off state when value is max */\n"
"    image: url(:/arrow_up);\n"
"}\n"
"\n"
"QSpinBox::down-button\n"
"{\n"
"    subcontrol-origin: border;\n"
"    subcontrol-position: bottom right; /* position at bottom right corner */\n"
"    width: 16px;\n"
"	border-top: 0px solid #323232;\n"
"	border-left: 1px solid #323232;\n"
"	border-bottom: 1px solid #323232;\n"
"	border-right: 1px solid #323232;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #979797, stop:1 #8a8a8a);\n"
"    border-top-width: 0;\n"
"}\n"
"\n"
"QSpinBox::down-button:hover\n"
"{\n"
"	background: #3e3e3e;\n"
"}\n"
"\n"
"QSpinBox::down-button:pressed\n"
"{\n"
"	background: #3e3e3e;\n"
"}\n"
"\n"
"QSpinBox::down-arrow\n"
"{\n"
"     image: url(:/arrow_down);\n"
"     width: 11px;\n"
"     height: 6px;\n"
"}\n"
"\n"
"QSpinBox::down-arrow:disabled,\n"
"QSpinBox::down-arrow:off \n"
"{ /* off state when value in min */\n"
"    image: url(:/arrow_down);\n"
"}\n"
""
                        "\n"
"QSplitter::handle \n"
"{\n"
"    background: transparent;\n"
"}\n"
"\n"
"QSplitter::handle:horizontal\n"
"{\n"
" 	background: transparent;\n"
" 	min-width: 2px;\n"
"	max-width: 2px;\n"
"	width: 2px;\n"
"	border-left: 1px solid #393939;\n"
"	border-right: 1px solid #959595;\n"
"	padding: 0px;\n"
"	margin: 0px;\n"
"}\n"
"\n"
"QSplitter::handle:vertical\n"
"{\n"
"   	background: transparent;\n"
"   	max-height: 2px;\n"
"	min-height: 2px;\n"
"	height: 2px;\n"
"	border-top: 1px solid #393939;\n"
"	border-bottom: 1px solid #959595;\n"
"	padding: 0px;\n"
"	margin: 0px;\n"
"}\n"
"\n"
"QStatusBar\n"
"{\n"
"   	border: 0px solid #262626;\n"
"	background: #686868;\n"
"}\n"
"\n"
"/* Table View */\n"
"QTableView\n"
"{\n"
"	background: #727272;\n"
"	selection-background-color: #787878;\n"
"	selection-color: #f5f5f5;\n"
"	padding-left: 5px;\n"
"	padding-right: 5px;\n"
"	color: #000000;\n"
"	margin: 5px;\n"
"}\n"
"\n"
"QTreeView\n"
"{\n"
"	margin-top: 1px;\n"
"	border: 0px solid #434343;\n"
"	border-radius: 0px;\n"
"	pad"
                        "ding: 0px;\n"
"	background: #727272;\n"
"	paint-alternating-row-colors-for-empty-area: 1;\n"
"	show-decoration-selected: 1;\n"
"	alternate-background-color: #727272;\n"
"}\n"
"\n"
"QTreeView::item \n"
"{\n"
"	color: #cccccc;\n"
"	padding-left: 10px;\n"
"}\n"
"\n"
"QTreeView::item:hover\n"
"{\n"
"	color: #e5e5e5;\n"
"}\n"
"\n"
"QTreeView::item:selected\n"
"{\n"
"	color: #ffffff;\n"
"	background: #686868;\n"
"}\n"
"\n"
"QTreeView::item:selected:active\n"
"{\n"
"	color: #f5f5f5;\n"
"	background: #686868;\n"
"}\n"
"\n"
"QTreeView::item:selected:!active\n"
"{\n"
"	color: #f5f5f5;\n"
"	background: #686868;\n"
"}\n"
"\n"
"QTreeView::branch:has-siblings:!adjoins-item \n"
"{\n"
"     border-image: url(:/vline) 0;\n"
"}\n"
"\n"
"QTreeView::branch:has-siblings:adjoins-item \n"
"{\n"
"     border-image: url(:/branch-more) 0;\n"
"}\n"
"\n"
"QTreeView::branch:!has-children:!has-siblings:adjoins-item\n"
"{\n"
"     border-image: url(:/branch-end) 0;\n"
"}\n"
"\n"
"QTreeView::branch:has-children:!has-siblings:closed,\n"
"QTre"
                        "eView::branch:closed:has-children:has-siblings\n"
"{\n"
"         image: url(:/branch-closed);\n"
"}\n"
"\n"
"QTreeView::branch:open:has-children:!has-siblings,\n"
"QTreeView::branch:open:has-children:has-siblings\n"
"{\n"
"         border-image: none;\n"
"         image: url(:/branch-open);\n"
"}\n"
"\n"
"/* The tab widget frame */\n"
"QTabWidget::pane\n"
"{\n"
"    border: 1px solid #353535;\n"
"	margin: 0px;\n"
"	padding: 0px;\n"
"	\n"
"}\n"
"\n"
"QTabWidget::tab-bar\n"
"{\n"
"	background: #323232;\n"
"	border: 1px solid #1e1e1e;\n"
"}\n"
"\n"
"/* Style the tab using the tab sub-control. */\n"
"QTabBar::tab\n"
"{\n"
"	border: 1px solid #353535;\n"
"	border-bottom: 0px solid #242424;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #535353, stop:1 #373737);\n"
"	color: #aaaaaa;\n"
"	padding: 3px;\n"
"	border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"	margin-top: 1px;\n"
"	margin-bottom: 0px;\n"
"	margin-left: 5px;\n"
"}\n"
"\n"
"QTabBar::tab:hover\n"
"{\n"
"	color: #fffff"
                        "f;\n"
"}\n"
"\n"
"QTabBar::tab:selected\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a6a6a6, stop:1 #8a8a8a);\n"
"	color: #010101\n"
"}\n"
"\n"
"/* Style for main toolbar */\n"
"QToolBar\n"
"{\n"
"    border: 0px solid #8b8b8b;\n"
"	background-color: transparent;\n"
"	spacing: 2px; /* spacing between items in the tool bar */\n"
"	margin-left: 3px;\n"
"	color: #e5e5e5;\n"
"	max-height: 22px;\n"
"}\n"
"\n"
"QToolBar::handle\n"
"{\n"
"     image: none;\n"
"     background-color: transparent;\n"
"}\n"
" \n"
"QToolBar::separator \n"
"{\n"
"     width: 5px;\n"
"     border: 0px;\n"
"     background-color: transparent;\n"
"}\n"
"\n"
"/* All types of tool button */\n"
"QToolButton\n"
"{\n"
"	border: 1px solid #353535;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a6a6a6, stop:1 #8a8a8a);\n"
"	color: #e5e5e5;\n"
"	border-radius: 5px;\n"
"	max-height: 18px;\n"
"	min-width: 18px;\n"
"}\n"
"\n"
"QToolButton[popupMode=\"1\"]\n"
"{\n"
"	/* only for MenuButtonPopup */\n"
"	padding"
                        "-right: 20px; /* make way for the popup button */\n"
"	/* max-width: 32px; */\n"
"}\n"
"\n"
"QToolButton::menu-button\n"
"{\n"
"     /* 16px width + 4px for border = 20px allocated above */\n"
"	border-top: 1px solid #323232;\n"
"	border-left: 1px solid #222222;\n"
"	border-bottom: 1px solid #323232;\n"
"	border-right: 1px solid #323232;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a6a6a6, stop:1 #8a8a8a);\n"
"	color: #111111;\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e5e5e5, stop:0.2 #a6a6a6, stop:0.8 #8a8a8a, stop:1 #4a4a4a);\n"
"	color: #c8c8c8;\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e5e5e5, stop:0.2 #a6a6a6, stop:0.8 #8a8a8a, stop:1 #4a4a4a);\n"
"	color: #c8c8c8;\n"
"}\n"
"\n"
"QToolTip\n"
"{\n"
"	border: 1px solid #111111;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #363636, stop:0.2 #e5e5e5, stop:0.8 #ffffff, stop:1 #262626);\n"
"	padding"
                        ": 3px;\n"
"	border-radius: 0px;\n"
"	opacity: 150;\n"
"	color: #000000;\n"
"}\n"
"\n"
"QDoubleSpinBox \n"
"{\n"
"    padding-right: 15px; /* make room for the arrows */\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #808080, stop:1 #8c8c8c);\n"
"    border: 1px solid #4d4d4d;\n"
"    color: #ffffff;\n"
"   	border-top-left-radius: 3px; /* same radius as the QComboBox */\n"
"	border-bottom-left-radius: 3px;\n"
"}\n"
" \n"
"QDoubleSpinBox::up-button\n"
"{\n"
"    subcontrol-origin: border;\n"
"    subcontrol-position: top right; /* position at the top right corner */\n"
"    width: 16px; /* 16 + 2*1px border-width = 15px padding + 3px parent border */\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a6a6a6, stop:1 #979797);\n"
"    border: 1px solid #323232;\n"
"	border-bottom-width: 0;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button:hover\n"
"{\n"
"	background: #3e3e3e;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-button:pressed\n"
"{\n"
"	background: #3e3e3e;\n"
"}\n"
"\n"
"QDoubleSpinBox::up-ar"
                        "row\n"
"{\n"
"    /* image: url(:/arrow_up);*/\n"
"     width: 11px;\n"
"     height: 6px;\n"
"}\n"
"\n"
"/*QDoubleSpinBox::up-arrow:disabled, QDoubleSpinBox::up-arrow:off\n"
"{  off state when value is max \n"
"    image: url(:/arrow_up);\n"
"}*/\n"
"\n"
"QDoubleSpinBox::down-button\n"
"{\n"
"    subcontrol-origin: border;\n"
"    subcontrol-position: bottom right; /* position at bottom right corner */\n"
"    width: 16px;\n"
"	border-top: 0px solid #323232;\n"
"	border-left: 1px solid #323232;\n"
"	border-bottom: 1px solid #323232;\n"
"	border-right: 1px solid #323232;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #979797, stop:1 #8a8a8a);\n"
"    border-top-width: 0;\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button:hover\n"
"{\n"
"	background: #3e3e3e;\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button:pressed\n"
"{\n"
"	background: #3e3e3e;\n"
"}\n"
"\n"
"QDoubleSpinBox::down-arrow\n"
"{\n"
"     image: url(:/arrow_down);\n"
"     width: 11px;\n"
"     height: 6px;\n"
"}\n"
"\n"
"QDoubleSpinBox::down-a"
                        "rrow:disabled,\n"
"QDoubleSpinBox::down-arrow:off \n"
"{ /* off state when value in min */\n"
"    image: url(:/arrow_down);\n"
"}\n"
""));
        actionOpen_nodes_file = new QAction(MainWindow);
        actionOpen_nodes_file->setObjectName(QStringLiteral("actionOpen_nodes_file"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        actionInvert_Mouse_Y = new QAction(MainWindow);
        actionInvert_Mouse_Y->setObjectName(QStringLiteral("actionInvert_Mouse_Y"));
        actionInvert_Mouse_Y->setCheckable(true);
        actionOpen_Premises_File = new QAction(MainWindow);
        actionOpen_Premises_File->setObjectName(QStringLiteral("actionOpen_Premises_File"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openGLWidget = new RenderState(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 681, 581));
        MainWindow->setCentralWidget(centralWidget);
        dockWidget_add_stuff = new QDockWidget(MainWindow);
        dockWidget_add_stuff->setObjectName(QStringLiteral("dockWidget_add_stuff"));
        dockWidget_add_stuff->setMinimumSize(QSize(320, 240));
        dockWidget_add_stuff->setMaximumSize(QSize(320, 240));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        stackedWidget_side_add = new QStackedWidget(dockWidgetContents);
        stackedWidget_side_add->setObjectName(QStringLiteral("stackedWidget_side_add"));
        stackedWidget_side_add->setGeometry(QRect(119, 11, 191, 199));
        stackedWidget_side_add->setMidLineWidth(0);
        page_add_node = new QWidget();
        page_add_node->setObjectName(QStringLiteral("page_add_node"));
        groupBox_node_settings = new QGroupBox(page_add_node);
        groupBox_node_settings->setObjectName(QStringLiteral("groupBox_node_settings"));
        groupBox_node_settings->setEnabled(true);
        groupBox_node_settings->setGeometry(QRect(10, 10, 181, 71));
        widget = new QWidget(groupBox_node_settings);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 33, 168, 38));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBox_bike = new QCheckBox(widget);
        checkBox_bike->setObjectName(QStringLiteral("checkBox_bike"));

        horizontalLayout_2->addWidget(checkBox_bike);

        checkBox_walk = new QCheckBox(widget);
        checkBox_walk->setObjectName(QStringLiteral("checkBox_walk"));
        checkBox_walk->setChecked(true);

        horizontalLayout_2->addWidget(checkBox_walk);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox_vehicle = new QCheckBox(widget);
        checkBox_vehicle->setObjectName(QStringLiteral("checkBox_vehicle"));

        horizontalLayout->addWidget(checkBox_vehicle);

        checkBox_wheelchair = new QCheckBox(widget);
        checkBox_wheelchair->setObjectName(QStringLiteral("checkBox_wheelchair"));

        horizontalLayout->addWidget(checkBox_wheelchair);


        verticalLayout_5->addLayout(horizontalLayout);

        groupBox_node_settings_2 = new QGroupBox(page_add_node);
        groupBox_node_settings_2->setObjectName(QStringLiteral("groupBox_node_settings_2"));
        groupBox_node_settings_2->setEnabled(true);
        groupBox_node_settings_2->setGeometry(QRect(10, 90, 181, 101));
        checkbox_significant = new QCheckBox(groupBox_node_settings_2);
        checkbox_significant->setObjectName(QStringLiteral("checkbox_significant"));
        checkbox_significant->setGeometry(QRect(20, 30, 101, 13));
        checkbox_significant->setChecked(true);
        lineEdit_node_name = new QLineEdit(groupBox_node_settings_2);
        lineEdit_node_name->setObjectName(QStringLiteral("lineEdit_node_name"));
        lineEdit_node_name->setGeometry(QRect(11, 80, 134, 16));
        label = new QLabel(groupBox_node_settings_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(11, 57, 131, 16));
        stackedWidget_side_add->addWidget(page_add_node);
        page_floor_plan = new QWidget();
        page_floor_plan->setObjectName(QStringLiteral("page_floor_plan"));
        groupBox_floor_plan_settings = new QGroupBox(page_floor_plan);
        groupBox_floor_plan_settings->setObjectName(QStringLiteral("groupBox_floor_plan_settings"));
        groupBox_floor_plan_settings->setEnabled(true);
        groupBox_floor_plan_settings->setGeometry(QRect(10, 20, 171, 161));
        widget1 = new QWidget(groupBox_floor_plan_settings);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(20, 30, 121, 116));
        verticalLayout_4 = new QVBoxLayout(widget1);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_2 = new QLabel(widget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        doubleSpinBox_floor_plan_width = new QDoubleSpinBox(widget1);
        doubleSpinBox_floor_plan_width->setObjectName(QStringLiteral("doubleSpinBox_floor_plan_width"));
        doubleSpinBox_floor_plan_width->setMinimum(1);
        doubleSpinBox_floor_plan_width->setMaximum(1000);

        verticalLayout_3->addWidget(doubleSpinBox_floor_plan_width);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(widget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        doubleSpinBox_floor_plan_height = new QDoubleSpinBox(widget1);
        doubleSpinBox_floor_plan_height->setObjectName(QStringLiteral("doubleSpinBox_floor_plan_height"));
        doubleSpinBox_floor_plan_height->setMinimum(1);
        doubleSpinBox_floor_plan_height->setMaximum(1000);

        verticalLayout_2->addWidget(doubleSpinBox_floor_plan_height);


        verticalLayout_4->addLayout(verticalLayout_2);

        stackedWidget_side_add->addWidget(page_floor_plan);
        widget2 = new QWidget(dockWidgetContents);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(10, 10, 110, 199));
        verticalLayout = new QVBoxLayout(widget2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        button_tree1 = new QPushButton(widget2);
        button_tree1->setObjectName(QStringLiteral("button_tree1"));

        verticalLayout->addWidget(button_tree1);

        button_node = new QPushButton(widget2);
        button_node->setObjectName(QStringLiteral("button_node"));

        verticalLayout->addWidget(button_node);

        button_pavement = new QPushButton(widget2);
        button_pavement->setObjectName(QStringLiteral("button_pavement"));

        verticalLayout->addWidget(button_pavement);

        button_link = new QPushButton(widget2);
        button_link->setObjectName(QStringLiteral("button_link"));

        verticalLayout->addWidget(button_link);

        button_wall = new QPushButton(widget2);
        button_wall->setObjectName(QStringLiteral("button_wall"));

        verticalLayout->addWidget(button_wall);

        button_floor_plan = new QPushButton(widget2);
        button_floor_plan->setObjectName(QStringLiteral("button_floor_plan"));

        verticalLayout->addWidget(button_floor_plan);

        button_door = new QPushButton(widget2);
        button_door->setObjectName(QStringLiteral("button_door"));

        verticalLayout->addWidget(button_door);

        dockWidget_add_stuff->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_add_stuff);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 23));
        menuBar->setMinimumSize(QSize(0, 22));
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(true);
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menuBuild = new QMenu(menuBar);
        menuBuild->setObjectName(QStringLiteral("menuBuild"));
        menuConfiguration = new QMenu(menuBar);
        menuConfiguration->setObjectName(QStringLiteral("menuConfiguration"));
        MainWindow->setMenuBar(menuBar);
        dockWidget_remove_objects = new QDockWidget(MainWindow);
        dockWidget_remove_objects->setObjectName(QStringLiteral("dockWidget_remove_objects"));
        dockWidget_remove_objects->setMinimumSize(QSize(320, 100));
        dockWidget_remove_objects->setMaximumSize(QSize(320, 100));
        dockWidgetContents_remove_objects = new QWidget();
        dockWidgetContents_remove_objects->setObjectName(QStringLiteral("dockWidgetContents_remove_objects"));
        widget3 = new QWidget(dockWidgetContents_remove_objects);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(11, 11, 106, 54));
        verticalLayout_6 = new QVBoxLayout(widget3);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        button_remove_node = new QPushButton(widget3);
        button_remove_node->setObjectName(QStringLiteral("button_remove_node"));

        verticalLayout_6->addWidget(button_remove_node);

        button_remove_tree = new QPushButton(widget3);
        button_remove_tree->setObjectName(QStringLiteral("button_remove_tree"));

        verticalLayout_6->addWidget(button_remove_tree);

        dockWidget_remove_objects->setWidget(dockWidgetContents_remove_objects);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_remove_objects);
        dockWidget_transformations = new QDockWidget(MainWindow);
        dockWidget_transformations->setObjectName(QStringLiteral("dockWidget_transformations"));
        dockWidget_transformations->setMinimumSize(QSize(320, 150));
        dockWidget_transformations->setMaximumSize(QSize(320, 150));
        dockWidgetContents_transformations = new QWidget();
        dockWidgetContents_transformations->setObjectName(QStringLiteral("dockWidgetContents_transformations"));
        label_ground_floor = new QLabel(dockWidgetContents_transformations);
        label_ground_floor->setObjectName(QStringLiteral("label_ground_floor"));
        label_ground_floor->setGeometry(QRect(190, 50, 115, 21));
        label_floor_level = new QLabel(dockWidgetContents_transformations);
        label_floor_level->setObjectName(QStringLiteral("label_floor_level"));
        label_floor_level->setGeometry(QRect(23, 50, 93, 21));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_floor_level->sizePolicy().hasHeightForWidth());
        label_floor_level->setSizePolicy(sizePolicy);
        spinBox_floor_level = new QSpinBox(dockWidgetContents_transformations);
        spinBox_floor_level->setObjectName(QStringLiteral("spinBox_floor_level"));
        spinBox_floor_level->setGeometry(QRect(122, 50, 61, 25));
        sizePolicy.setHeightForWidth(spinBox_floor_level->sizePolicy().hasHeightForWidth());
        spinBox_floor_level->setSizePolicy(sizePolicy);
        label_rotation_y = new QLabel(dockWidgetContents_transformations);
        label_rotation_y->setObjectName(QStringLiteral("label_rotation_y"));
        label_rotation_y->setGeometry(QRect(22, 17, 70, 16));
        spin_rotationY = new QDoubleSpinBox(dockWidgetContents_transformations);
        spin_rotationY->setObjectName(QStringLiteral("spin_rotationY"));
        spin_rotationY->setGeometry(QRect(124, 17, 78, 18));
        spin_rotationY->setMinimum(-180);
        spin_rotationY->setMaximum(180);
        dockWidget_transformations->setWidget(dockWidgetContents_transformations);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_transformations);
        dockWidget_configuration = new QDockWidget(MainWindow);
        dockWidget_configuration->setObjectName(QStringLiteral("dockWidget_configuration"));
        dockWidget_configuration->setEnabled(true);
        dockWidget_configuration->setMinimumSize(QSize(320, 150));
        dockWidget_configuration->setMaximumSize(QSize(320, 150));
        dockWidget_configuration->setContextMenuPolicy(Qt::DefaultContextMenu);
        dockWidget_configuration->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dockWidgetContents_configuration = new QWidget();
        dockWidgetContents_configuration->setObjectName(QStringLiteral("dockWidgetContents_configuration"));
        checkBox_inversemouse_y = new QCheckBox(dockWidgetContents_configuration);
        checkBox_inversemouse_y->setObjectName(QStringLiteral("checkBox_inversemouse_y"));
        checkBox_inversemouse_y->setGeometry(QRect(30, 20, 200, 13));
        checkBox_inversemouse_y->setMaximumSize(QSize(200, 13));
        button_execute_virtual_concierge = new QPushButton(dockWidgetContents_configuration);
        button_execute_virtual_concierge->setObjectName(QStringLiteral("button_execute_virtual_concierge"));
        button_execute_virtual_concierge->setGeometry(QRect(20, 40, 161, 23));
        dockWidget_configuration->setWidget(dockWidgetContents_configuration);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_configuration);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget_configuration->raise();

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuBuild->menuAction());
        menuBar->addAction(menuConfiguration->menuAction());
        menu_File->addAction(actionOpen_nodes_file);
        menu_File->addAction(actionOpen_Premises_File);
        menuBuild->addAction(actionRun);
        menuConfiguration->addAction(actionInvert_Mouse_Y);

        retranslateUi(MainWindow);
        QObject::connect(actionInvert_Mouse_Y, SIGNAL(triggered(bool)), checkBox_inversemouse_y, SLOT(click()));
        QObject::connect(actionRun, SIGNAL(triggered()), button_execute_virtual_concierge, SLOT(click()));

        stackedWidget_side_add->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Virtual Concierge Creator", 0));
        actionOpen_nodes_file->setText(QApplication::translate("MainWindow", "Open Nodes File", 0));
        actionRun->setText(QApplication::translate("MainWindow", "Run", 0));
        actionInvert_Mouse_Y->setText(QApplication::translate("MainWindow", "Invert Mouse Y", 0));
        actionOpen_Premises_File->setText(QApplication::translate("MainWindow", "Open Premises File", 0));
#ifndef QT_NO_ACCESSIBILITY
        dockWidget_add_stuff->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        dockWidget_add_stuff->setWindowTitle(QApplication::translate("MainWindow", "Add Objects", 0));
        groupBox_node_settings->setTitle(QApplication::translate("MainWindow", "Accessible with/by/through", 0));
        checkBox_bike->setText(QApplication::translate("MainWindow", "Bike", 0));
        checkBox_walk->setText(QApplication::translate("MainWindow", "Walking", 0));
        checkBox_vehicle->setText(QApplication::translate("MainWindow", "Vehicle", 0));
        checkBox_wheelchair->setText(QApplication::translate("MainWindow", "Wheelchair", 0));
        groupBox_node_settings_2->setTitle(QApplication::translate("MainWindow", "Node Settings", 0));
        checkbox_significant->setText(QApplication::translate("MainWindow", "Add Button", 0));
        lineEdit_node_name->setText(QApplication::translate("MainWindow", "default_node", 0));
        label->setText(QApplication::translate("MainWindow", "Node Description", 0));
        groupBox_floor_plan_settings->setTitle(QApplication::translate("MainWindow", "Floor Plan Settings", 0));
        label_2->setText(QApplication::translate("MainWindow", "Width", 0));
        doubleSpinBox_floor_plan_width->setSuffix(QApplication::translate("MainWindow", "m", 0));
        label_3->setText(QApplication::translate("MainWindow", "Height", 0));
        doubleSpinBox_floor_plan_height->setPrefix(QString());
        doubleSpinBox_floor_plan_height->setSuffix(QApplication::translate("MainWindow", "m", 0));
        button_tree1->setText(QApplication::translate("MainWindow", "Add Tree", 0));
        button_node->setText(QApplication::translate("MainWindow", "Add Node", 0));
        button_pavement->setText(QApplication::translate("MainWindow", "Add Pavement", 0));
        button_link->setText(QApplication::translate("MainWindow", "Add Link", 0));
        button_wall->setText(QApplication::translate("MainWindow", "Add Wall", 0));
        button_floor_plan->setText(QApplication::translate("MainWindow", "Add Floor Plan", 0));
        button_door->setText(QApplication::translate("MainWindow", "Add Door", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuBuild->setTitle(QApplication::translate("MainWindow", "Build", 0));
        menuConfiguration->setTitle(QApplication::translate("MainWindow", "Configuration", 0));
        dockWidget_remove_objects->setWindowTitle(QApplication::translate("MainWindow", "Remove Objects", 0));
        button_remove_node->setText(QApplication::translate("MainWindow", "Remove Node", 0));
        button_remove_tree->setText(QApplication::translate("MainWindow", "Remove Tree", 0));
        dockWidget_transformations->setWindowTitle(QApplication::translate("MainWindow", "Transformations", 0));
        label_ground_floor->setText(QApplication::translate("MainWindow", "(Ground Floor)", 0));
        label_floor_level->setText(QApplication::translate("MainWindow", "Floor Level", 0));
        label_rotation_y->setText(QApplication::translate("MainWindow", "Rotation Y:", 0));
        dockWidget_configuration->setWindowTitle(QApplication::translate("MainWindow", "Configuration", 0));
        checkBox_inversemouse_y->setText(QApplication::translate("MainWindow", "Invert Mouse Y", 0));
        button_execute_virtual_concierge->setText(QApplication::translate("MainWindow", "Show Virtual Conciege", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
