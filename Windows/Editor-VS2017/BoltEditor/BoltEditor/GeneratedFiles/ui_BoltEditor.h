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
    QTabWidget *tabWidget;
    QWidget *WorldEditor;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter_2;
    MyCanvas *widget;
    QSplitter *splitter;
    QListView *listView;
    cEntityProperty *entityPropertyWidget;
    QWidget *PrototypeEditor;
    QMenuBar *menuBar;
    QMenu *menuFiles;
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
        centralWidget = new QWidget(BoltEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        WorldEditor = new QWidget();
        WorldEditor->setObjectName(QStringLiteral("WorldEditor"));
        horizontalLayout = new QHBoxLayout(WorldEditor);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter_2 = new QSplitter(WorldEditor);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        widget = new MyCanvas(splitter_2);
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

        tabWidget->addTab(WorldEditor, QString());
        PrototypeEditor = new QWidget();
        PrototypeEditor->setObjectName(QStringLiteral("PrototypeEditor"));
        tabWidget->addTab(PrototypeEditor, QString());

        horizontalLayout_2->addWidget(tabWidget);

        BoltEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BoltEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
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
        QObject::connect(widget, SIGNAL(SelectionChanged(::nECS::cEntity*)), entityPropertyWidget, SLOT(selectedEntitiesChanged(::nECS::cEntity*)));
        QObject::connect(listView, SIGNAL(doubleClicked(QModelIndex)), BoltEditorClass, SLOT(PrototypeEditionAsked(QModelIndex)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(BoltEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *BoltEditorClass)
    {
        BoltEditorClass->setWindowTitle(QApplication::translate("BoltEditorClass", "BoltEditor", nullptr));
        actionExit->setText(QApplication::translate("BoltEditorClass", "Exit", nullptr));
        actionSave->setText(QApplication::translate("BoltEditorClass", "Save", nullptr));
        actionLoad->setText(QApplication::translate("BoltEditorClass", "Load", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(WorldEditor), QApplication::translate("BoltEditorClass", "WorldEditor", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(PrototypeEditor), QApplication::translate("BoltEditorClass", "PrototypeEditor", nullptr));
        menuFiles->setTitle(QApplication::translate("BoltEditorClass", "Files", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BoltEditorClass: public Ui_BoltEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOLTEDITOR_H
