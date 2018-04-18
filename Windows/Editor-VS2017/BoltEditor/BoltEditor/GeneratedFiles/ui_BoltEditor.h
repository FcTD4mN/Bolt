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
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Editor.BoltQtWidgets.EntityProperty.h"
#include "Editor.BoltQtWidgets.TestCanvas.h"

QT_BEGIN_NAMESPACE

class Ui_BoltEditorClass
{
public:
    QAction *actionExit;
    QAction *actionSave;
    QAction *actionLoad;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    MyCanvas *widget;
    QVBoxLayout *verticalLayout;
    QListView *listView;
    cEntityProperty *entityPropertyWidget;
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
        actionSave = new QAction(BoltEditorClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionLoad = new QAction(BoltEditorClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        centralWidget = new QWidget(BoltEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget = new MyCanvas(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        sizePolicy.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(listView);

        entityPropertyWidget = new cEntityProperty(centralWidget);
        entityPropertyWidget->setObjectName(QStringLiteral("entityPropertyWidget"));
        sizePolicy.setHeightForWidth(entityPropertyWidget->sizePolicy().hasHeightForWidth());
        entityPropertyWidget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(entityPropertyWidget);


        horizontalLayout_2->addLayout(verticalLayout);

        BoltEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BoltEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
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
        menuFiles->addAction(actionSave);
        menuFiles->addAction(actionLoad);
        menuFiles->addSeparator();
        menuFiles->addAction(actionExit);

        retranslateUi(BoltEditorClass);
        QObject::connect(listView, SIGNAL(doubleClicked(QModelIndex)), entityPropertyWidget, SLOT(selectedEntityChanged(QModelIndex)));
        QObject::connect(widget, SIGNAL(SelectionChanged(::nECS::cEntity*)), entityPropertyWidget, SLOT(selectedEntitiesChanged(::nECS::cEntity*)));

        QMetaObject::connectSlotsByName(BoltEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *BoltEditorClass)
    {
        BoltEditorClass->setWindowTitle(QApplication::translate("BoltEditorClass", "BoltEditor", nullptr));
        actionExit->setText(QApplication::translate("BoltEditorClass", "Exit", nullptr));
        actionSave->setText(QApplication::translate("BoltEditorClass", "Save", nullptr));
        actionLoad->setText(QApplication::translate("BoltEditorClass", "Load", nullptr));
        menuFiles->setTitle(QApplication::translate("BoltEditorClass", "Files", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BoltEditorClass: public Ui_BoltEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOLTEDITOR_H
