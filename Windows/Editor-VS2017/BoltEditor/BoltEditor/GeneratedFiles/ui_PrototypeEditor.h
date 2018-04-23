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
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Editor.BoltQtWidgets.EntityProperty.h"

QT_BEGIN_NAMESPACE

class Ui_PrototypeEditor
{
public:
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QGraphicsView *graphicsViewPreview;
    cEntityProperty *treeViewPrototype;
    QPushButton *buttonSavePrototype;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QListView *listViewAllPrototypes;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonAddPrototype;
    QPushButton *buttonRemovePrototype;

    void setupUi(QWidget *PrototypeEditor)
    {
        if (PrototypeEditor->objectName().isEmpty())
            PrototypeEditor->setObjectName(QStringLiteral("PrototypeEditor"));
        PrototypeEditor->resize(757, 417);
        horizontalLayout_4 = new QHBoxLayout(PrototypeEditor);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        graphicsViewPreview = new QGraphicsView(PrototypeEditor);
        graphicsViewPreview->setObjectName(QStringLiteral("graphicsViewPreview"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsViewPreview->sizePolicy().hasHeightForWidth());
        graphicsViewPreview->setSizePolicy(sizePolicy);
        graphicsViewPreview->setMaximumSize(QSize(60, 60));

        horizontalLayout_3->addWidget(graphicsViewPreview);


        verticalLayout_2->addLayout(horizontalLayout_3);

        treeViewPrototype = new cEntityProperty(PrototypeEditor);
        treeViewPrototype->setObjectName(QStringLiteral("treeViewPrototype"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeViewPrototype->sizePolicy().hasHeightForWidth());
        treeViewPrototype->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(treeViewPrototype);


        verticalLayout->addLayout(verticalLayout_2);

        buttonSavePrototype = new QPushButton(PrototypeEditor);
        buttonSavePrototype->setObjectName(QStringLiteral("buttonSavePrototype"));

        verticalLayout->addWidget(buttonSavePrototype);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(PrototypeEditor);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        listViewAllPrototypes = new QListView(PrototypeEditor);
        listViewAllPrototypes->setObjectName(QStringLiteral("listViewAllPrototypes"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listViewAllPrototypes->sizePolicy().hasHeightForWidth());
        listViewAllPrototypes->setSizePolicy(sizePolicy2);
        listViewAllPrototypes->setMaximumSize(QSize(200, 16777215));

        verticalLayout_3->addWidget(listViewAllPrototypes);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        buttonAddPrototype = new QPushButton(PrototypeEditor);
        buttonAddPrototype->setObjectName(QStringLiteral("buttonAddPrototype"));

        horizontalLayout->addWidget(buttonAddPrototype);

        buttonRemovePrototype = new QPushButton(PrototypeEditor);
        buttonRemovePrototype->setObjectName(QStringLiteral("buttonRemovePrototype"));

        horizontalLayout->addWidget(buttonRemovePrototype);


        verticalLayout_3->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_3);


        horizontalLayout_4->addLayout(horizontalLayout_2);


        retranslateUi(PrototypeEditor);
        QObject::connect(listViewAllPrototypes, SIGNAL(doubleClicked(QModelIndex)), PrototypeEditor, SLOT(PrototypeEditionAsked(QModelIndex)));
        QObject::connect(buttonSavePrototype, SIGNAL(clicked()), PrototypeEditor, SLOT(SavePrototype()));
        QObject::connect(buttonAddPrototype, SIGNAL(clicked()), PrototypeEditor, SLOT(AddNewPrototype()));
        QObject::connect(buttonRemovePrototype, SIGNAL(clicked()), PrototypeEditor, SLOT(RemovePrototype()));

        QMetaObject::connectSlotsByName(PrototypeEditor);
    } // setupUi

    void retranslateUi(QWidget *PrototypeEditor)
    {
        PrototypeEditor->setWindowTitle(QApplication::translate("PrototypeEditor", "Form", nullptr));
        buttonSavePrototype->setText(QApplication::translate("PrototypeEditor", "Save Prototype", nullptr));
        label->setText(QApplication::translate("PrototypeEditor", "PrototypeList", nullptr));
        buttonAddPrototype->setText(QApplication::translate("PrototypeEditor", "New Prototype", nullptr));
        buttonRemovePrototype->setText(QApplication::translate("PrototypeEditor", "Remove Prototype", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PrototypeEditor: public Ui_PrototypeEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTOTYPEEDITOR_H
