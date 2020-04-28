/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_open;
    QAction *action_quit;
    QAction *action_close;
    QAction *action_aboutQt;
    QAction *action_about;
    QAction *action_export_current_page_to_image;
    QAction *action_export_all_pages_to_images;
    QAction *action_property;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/HTYPDF.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_open = new QAction(MainWindow);
        action_open->setObjectName(QStringLiteral("action_open"));
        action_quit = new QAction(MainWindow);
        action_quit->setObjectName(QStringLiteral("action_quit"));
        action_close = new QAction(MainWindow);
        action_close->setObjectName(QStringLiteral("action_close"));
        action_aboutQt = new QAction(MainWindow);
        action_aboutQt->setObjectName(QStringLiteral("action_aboutQt"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QStringLiteral("action_about"));
        action_export_current_page_to_image = new QAction(MainWindow);
        action_export_current_page_to_image->setObjectName(QStringLiteral("action_export_current_page_to_image"));
        action_export_all_pages_to_images = new QAction(MainWindow);
        action_export_all_pages_to_images->setObjectName(QStringLiteral("action_export_all_pages_to_images"));
        action_property = new QAction(MainWindow);
        action_property->setObjectName(QStringLiteral("action_property"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 798, 529));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(action_open);
        menu->addAction(action_close);
        menu->addAction(action_property);
        menu->addAction(action_export_current_page_to_image);
        menu->addAction(action_export_all_pages_to_images);
        menu->addAction(action_quit);
        menu_2->addAction(action_aboutQt);
        menu_2->addAction(action_about);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\265\267\345\244\251\351\271\260PDF", Q_NULLPTR));
        action_open->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", Q_NULLPTR));
        action_open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
        action_quit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        action_quit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
        action_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", Q_NULLPTR));
        action_close->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", Q_NULLPTR));
        action_aboutQt->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216Qt", Q_NULLPTR));
        action_about->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", Q_NULLPTR));
        action_about->setShortcut(QApplication::translate("MainWindow", "F1", Q_NULLPTR));
        action_export_current_page_to_image->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\345\275\223\345\211\215\351\241\265\351\235\242\344\270\272\345\233\276\347\211\207", Q_NULLPTR));
        action_export_all_pages_to_images->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\346\211\200\346\234\211\351\241\265\351\235\242\344\270\272\345\233\276\347\211\207", Q_NULLPTR));
        action_property->setText(QApplication::translate("MainWindow", "\345\261\236\346\200\247", Q_NULLPTR));
        label->setText(QString());
        menu->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
