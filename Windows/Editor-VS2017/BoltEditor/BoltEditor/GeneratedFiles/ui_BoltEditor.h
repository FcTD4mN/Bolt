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
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "Editor.BoltQtWidgets.Editors.ComponentEditor.h"
#include "Editor.BoltQtWidgets.Editors.PrototypeEditor.h"
#include "Editor.BoltQtWidgets.EntityProperty.h"
#include "Editor.BoltQtWidgets.SFMLCanvas.h"

QT_BEGIN_NAMESPACE

class Ui_BoltEditorClass
{
public:
    QAction *actionExit;
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionToogle_Grid;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *WorldEditorTab;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter_2;
    SFMLCanvas *widget;
    QSplitter *splitter;
    QListView *listView;
    cEntityProperty *entityPropertyWidget;
    QWidget *PrototypeEditorTab;
    QHBoxLayout *horizontalLayout_3;
    cPrototypeEditor *PrototypeEditor;
    QWidget *ComponentEditor;
    QHBoxLayout *horizontalLayout_4;
    cComponentEditor *widget_2;
    QMenuBar *menuBar;
    QMenu *menuFiles;
    QMenu *menuView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BoltEditorClass)
    {
        if (BoltEditorClass->objectName().isEmpty())
            BoltEditorClass->setObjectName(QStringLiteral("BoltEditorClass"));
        BoltEditorClass->resize(1024, 798);
        actionExit = new QAction(BoltEditorClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSave = new QAction(BoltEditorClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionLoad = new QAction(BoltEditorClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionToogle_Grid = new QAction(BoltEditorClass);
        actionToogle_Grid->setObjectName(QStringLiteral("actionToogle_Grid"));
        centralWidget = new QWidget(BoltEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        WorldEditorTab = new QWidget();
        WorldEditorTab->setObjectName(QStringLiteral("WorldEditorTab"));
        horizontalLayout = new QHBoxLayout(WorldEditorTab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter_2 = new QSplitter(WorldEditorTab);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        widget = new SFMLCanvas(splitter_2);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(50);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        splitter_2->addWidget(widget);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setOrientation(Qt::Vertical);
        listView = new QListView(splitter);
        listView->setObjectName(QStringLiteral("listView"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
        listView->setSizePolicy(sizePolicy2);
        splitter->addWidget(listView);
        entityPropertyWidget = new cEntityProperty(splitter);
        entityPropertyWidget->setObjectName(QStringLiteral("entityPropertyWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(entityPropertyWidget->sizePolicy().hasHeightForWidth());
        entityPropertyWidget->setSizePolicy(sizePolicy3);
        splitter->addWidget(entityPropertyWidget);
        splitter_2->addWidget(splitter);

        horizontalLayout->addWidget(splitter_2);

        tabWidget->addTab(WorldEditorTab, QString());
        PrototypeEditorTab = new QWidget();
        PrototypeEditorTab->setObjectName(QStringLiteral("PrototypeEditorTab"));
        horizontalLayout_3 = new QHBoxLayout(PrototypeEditorTab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        PrototypeEditor = new cPrototypeEditor(PrototypeEditorTab);
        PrototypeEditor->setObjectName(QStringLiteral("PrototypeEditor"));

        horizontalLayout_3->addWidget(PrototypeEditor);

        tabWidget->addTab(PrototypeEditorTab, QString());
        ComponentEditor = new QWidget();
        ComponentEditor->setObjectName(QStringLiteral("ComponentEditor"));
        horizontalLayout_4 = new QHBoxLayout(ComponentEditor);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        widget_2 = new cComponentEditor(ComponentEditor);
        widget_2->setObjectName(QStringLiteral("widget_2"));

        horizontalLayout_4->addWidget(widget_2);

        tabWidget->addTab(ComponentEditor, QString());

        horizontalLayout_2->addWidget(tabWidget);

        BoltEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BoltEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        menuFiles = new QMenu(menuBar);
        menuFiles->setObjectName(QStringLiteral("menuFiles"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        BoltEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BoltEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BoltEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BoltEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BoltEditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFiles->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFiles->addAction(actionSave);
        menuFiles->addAction(actionLoad);
        menuFiles->addSeparator();
        menuFiles->addAction(actionExit);
        menuView->addAction(actionToogle_Grid);

        retranslateUi(BoltEditorClass);
        QObject::connect(widget, SIGNAL(SelectionChanged(::nECS::cEntity*,::nQt::nModels::cEntityModel*)), entityPropertyWidget, SLOT(selectedEntitiesChanged(::nECS::cEntity*,::nQt::nModels::cEntityModel*)));
        QObject::connect(listView, SIGNAL(doubleClicked(QModelIndex)), BoltEditorClass, SLOT(PrototypeEditionAsked(QModelIndex)));
        QObject::connect(listView, SIGNAL(doubleClicked(QModelIndex)), PrototypeEditor, SLOT(PrototypeEditionAsked(QModelIndex)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(BoltEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *BoltEditorClass)
    {
        BoltEditorClass->setWindowTitle(QApplication::translate("BoltEditorClass", "BoltEditor", nullptr));
        actionExit->setText(QApplication::translate("BoltEditorClass", "Exit", nullptr));
        actionSave->setText(QApplication::translate("BoltEditorClass", "Save", nullptr));
        actionLoad->setText(QApplication::translate("BoltEditorClass", "Load", nullptr));
        actionToogle_Grid->setText(QApplication::translate("BoltEditorClass", "Toogle Grid", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(WorldEditorTab), QApplication::translate("BoltEditorClass", "WorldEditor", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(PrototypeEditorTab), QApplication::translate("BoltEditorClass", "PrototypeEditor", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ComponentEditor), QApplication::translate("BoltEditorClass", "ComponentEditor", nullptr));
        menuFiles->setTitle(QApplication::translate("BoltEditorClass", "Files", nullptr));
        menuView->setTitle(QApplication::translate("BoltEditorClass", "View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BoltEditorClass: public Ui_BoltEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOLTEDITOR_H
