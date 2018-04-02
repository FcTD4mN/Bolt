/********************************************************************************
** Form generated from reading UI file 'BoltEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOLTEDITOR_H
#define UI_BOLTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtWidgets/TestCanvas.h"

QT_BEGIN_NAMESPACE

class Ui_BoltEditorClass
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    MyCanvas *widget;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QMenuBar *menuBar;
    QMenu *menuFiles;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BoltEditorClass)
    {
        if (BoltEditorClass->objectName().isEmpty())
            BoltEditorClass->setObjectName(QStringLiteral("BoltEditorClass"));
        BoltEditorClass->resize(600, 400);
        actionExit = new QAction(BoltEditorClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(BoltEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget = new MyCanvas(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout_2->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(listWidget);


        horizontalLayout_2->addLayout(verticalLayout);

        BoltEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BoltEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        menuFiles = new QMenu(menuBar);
        menuFiles->setObjectName(QStringLiteral("menuFiles"));
        BoltEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BoltEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BoltEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BoltEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BoltEditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFiles->menuAction());
        menuFiles->addAction(actionExit);

        retranslateUi(BoltEditorClass);

        QMetaObject::connectSlotsByName(BoltEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *BoltEditorClass)
    {
        BoltEditorClass->setWindowTitle(QApplication::translate("BoltEditorClass", "BoltEditor", nullptr));
        actionExit->setText(QApplication::translate("BoltEditorClass", "Exit", nullptr));
        menuFiles->setTitle(QApplication::translate("BoltEditorClass", "Files", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BoltEditorClass: public Ui_BoltEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOLTEDITOR_H
