/********************************************************************************
** Form generated from reading UI file 'PrototypeEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROTOTYPEEDITOR_H
#define UI_PROTOTYPEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Editor.BoltQtWidgets.EntityProperty.h"

QT_BEGIN_NAMESPACE

class Ui_PrototypeEditor
{
public:
    QListView *listViewAllPrototypes;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QGraphicsView *graphicsViewPreview;
    cEntityProperty *treeViewPrototype;

    void setupUi(QWidget *PrototypeEditor)
    {
        if (PrototypeEditor->objectName().isEmpty())
            PrototypeEditor->setObjectName(QStringLiteral("PrototypeEditor"));
        PrototypeEditor->resize(887, 692);
        listViewAllPrototypes = new QListView(PrototypeEditor);
        listViewAllPrototypes->setObjectName(QStringLiteral("listViewAllPrototypes"));
        listViewAllPrototypes->setGeometry(QRect(480, 110, 256, 461));
        layoutWidget = new QWidget(PrototypeEditor);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 60, 421, 541));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        graphicsViewPreview = new QGraphicsView(layoutWidget);
        graphicsViewPreview->setObjectName(QStringLiteral("graphicsViewPreview"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsViewPreview->sizePolicy().hasHeightForWidth());
        graphicsViewPreview->setSizePolicy(sizePolicy);
        graphicsViewPreview->setMaximumSize(QSize(60, 60));

        horizontalLayout_3->addWidget(graphicsViewPreview);


        verticalLayout_2->addLayout(horizontalLayout_3);

        treeViewPrototype = new cEntityProperty(layoutWidget);
        treeViewPrototype->setObjectName(QStringLiteral("treeViewPrototype"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeViewPrototype->sizePolicy().hasHeightForWidth());
        treeViewPrototype->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(treeViewPrototype);


        retranslateUi(PrototypeEditor);
        QObject::connect(listViewAllPrototypes, SIGNAL(doubleClicked(QModelIndex)), PrototypeEditor, SLOT(PrototypeEditionAsked(QModelIndex)));

        QMetaObject::connectSlotsByName(PrototypeEditor);
    } // setupUi

    void retranslateUi(QWidget *PrototypeEditor)
    {
        PrototypeEditor->setWindowTitle(QApplication::translate("PrototypeEditor", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrototypeEditor: public Ui_PrototypeEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTOTYPEEDITOR_H
