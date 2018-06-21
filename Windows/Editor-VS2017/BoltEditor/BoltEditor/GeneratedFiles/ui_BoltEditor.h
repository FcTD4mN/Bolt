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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Editor.BoltQtWidgets.Editors.ComponentEditor.h"
#include "Editor.BoltQtWidgets.Editors.ProjectEditor.h"
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
    QAction *actionSnapGrid;
    QAction *actionOpen;
    QAction *actionNew_Project;
    QAction *actionSave_As;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QTabWidget *tabWidget;
    QWidget *ProjectEditorTab;
    QVBoxLayout *verticalLayout;
    cProjectEditor *projectEditor;
    QWidget *ScreenEditorTab;
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
    QMenu *menuSettings;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BoltEditorClass)
    {
        if (BoltEditorClass->objectName().isEmpty())
            BoltEditorClass->setObjectName(QStringLiteral("BoltEditorClass"));
        BoltEditorClass->resize(653, 495);
        actionExit = new QAction(BoltEditorClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionSave = new QAction(BoltEditorClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionLoad = new QAction(BoltEditorClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        actionToogle_Grid = new QAction(BoltEditorClass);
        actionToogle_Grid->setObjectName(QStringLiteral("actionToogle_Grid"));
        actionSnapGrid = new QAction(BoltEditorClass);
        actionSnapGrid->setObjectName(QStringLiteral("actionSnapGrid"));
        actionOpen = new QAction(BoltEditorClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionNew_Project = new QAction(BoltEditorClass);
        actionNew_Project->setObjectName(QStringLiteral("actionNew_Project"));
        actionSave_As = new QAction(BoltEditorClass);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        centralWidget = new QWidget(BoltEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        ProjectEditorTab = new QWidget();
        ProjectEditorTab->setObjectName(QStringLiteral("ProjectEditorTab"));
        verticalLayout = new QVBoxLayout(ProjectEditorTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        projectEditor = new cProjectEditor(ProjectEditorTab);
        projectEditor->setObjectName(QStringLiteral("projectEditor"));

        verticalLayout->addWidget(projectEditor);

        tabWidget->addTab(ProjectEditorTab, QString());
        ScreenEditorTab = new QWidget();
        ScreenEditorTab->setObjectName(QStringLiteral("ScreenEditorTab"));
        horizontalLayout = new QHBoxLayout(ScreenEditorTab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter_2 = new QSplitter(ScreenEditorTab);
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

        tabWidget->addTab(ScreenEditorTab, QString());
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
        menuBar->setGeometry(QRect(0, 0, 653, 22));
        menuFiles = new QMenu(menuBar);
        menuFiles->setObjectName(QStringLiteral("menuFiles"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        BoltEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BoltEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BoltEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BoltEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BoltEditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFiles->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuFiles->addAction(actionNew_Project);
        menuFiles->addAction(actionOpen);
        menuFiles->addAction(actionSave);
        menuFiles->addAction(actionSave_As);
        menuFiles->addSeparator();
        menuFiles->addAction(actionExit);
        menuView->addAction(actionToogle_Grid);
        menuSettings->addAction(actionSnapGrid);

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
        actionSnapGrid->setText(QApplication::translate("BoltEditorClass", "SnapGrid", nullptr));
        actionOpen->setText(QApplication::translate("BoltEditorClass", "Open", nullptr));
        actionNew_Project->setText(QApplication::translate("BoltEditorClass", "New Project", nullptr));
        actionSave_As->setText(QApplication::translate("BoltEditorClass", "Save As", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ProjectEditorTab), QApplication::translate("BoltEditorClass", "ProjectEditor", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ScreenEditorTab), QApplication::translate("BoltEditorClass", "ScreenEditor", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(PrototypeEditorTab), QApplication::translate("BoltEditorClass", "PrototypeEditor", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ComponentEditor), QApplication::translate("BoltEditorClass", "ComponentEditor", nullptr));
        menuFiles->setTitle(QApplication::translate("BoltEditorClass", "Files", nullptr));
        menuView->setTitle(QApplication::translate("BoltEditorClass", "View", nullptr));
        menuSettings->setTitle(QApplication::translate("BoltEditorClass", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BoltEditorClass: public Ui_BoltEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOLTEDITOR_H
