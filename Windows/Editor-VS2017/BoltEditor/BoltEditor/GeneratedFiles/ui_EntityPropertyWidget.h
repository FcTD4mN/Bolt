/********************************************************************************
** Form generated from reading UI file 'EntityPropertyWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTITYPROPERTYWIDGET_H
#define UI_ENTITYPROPERTYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EntityProperty
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelEntityName;
    QLineEdit *editEntityName;
    QLabel *labelComponents;
    QTreeView *treeView;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonAddComponent;
    QPushButton *buttonRemoveComponent;

    void setupUi(QWidget *EntityProperty)
    {
        if (EntityProperty->objectName().isEmpty())
            EntityProperty->setObjectName(QStringLiteral("EntityProperty"));
        EntityProperty->resize(471, 428);
        verticalLayout_2 = new QVBoxLayout(EntityProperty);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelEntityName = new QLabel(EntityProperty);
        labelEntityName->setObjectName(QStringLiteral("labelEntityName"));

        horizontalLayout->addWidget(labelEntityName);

        editEntityName = new QLineEdit(EntityProperty);
        editEntityName->setObjectName(QStringLiteral("editEntityName"));

        horizontalLayout->addWidget(editEntityName);


        verticalLayout->addLayout(horizontalLayout);

        labelComponents = new QLabel(EntityProperty);
        labelComponents->setObjectName(QStringLiteral("labelComponents"));
        labelComponents->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelComponents);

        treeView = new QTreeView(EntityProperty);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setAlternatingRowColors(true);
        treeView->setSelectionBehavior(QAbstractItemView::SelectItems);
        treeView->setAllColumnsShowFocus(true);

        verticalLayout->addWidget(treeView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        buttonAddComponent = new QPushButton(EntityProperty);
        buttonAddComponent->setObjectName(QStringLiteral("buttonAddComponent"));

        horizontalLayout_2->addWidget(buttonAddComponent);

        buttonRemoveComponent = new QPushButton(EntityProperty);
        buttonRemoveComponent->setObjectName(QStringLiteral("buttonRemoveComponent"));
        buttonRemoveComponent->setEnabled(true);

        horizontalLayout_2->addWidget(buttonRemoveComponent);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(EntityProperty);
        QObject::connect(buttonAddComponent, SIGNAL(clicked()), EntityProperty, SLOT(addEmptyComponent()));
        QObject::connect(buttonRemoveComponent, SIGNAL(clicked()), EntityProperty, SLOT(removeComponent()));
        QObject::connect(editEntityName, SIGNAL(editingFinished()), EntityProperty, SLOT(EntityIDChanged()));

        QMetaObject::connectSlotsByName(EntityProperty);
    } // setupUi

    void retranslateUi(QWidget *EntityProperty)
    {
        EntityProperty->setWindowTitle(QApplication::translate("EntityProperty", "Form", nullptr));
        labelEntityName->setText(QApplication::translate("EntityProperty", "EntityID :", nullptr));
        labelComponents->setText(QApplication::translate("EntityProperty", "Entity's components", nullptr));
        buttonAddComponent->setText(QApplication::translate("EntityProperty", "AddComponent", nullptr));
        buttonRemoveComponent->setText(QApplication::translate("EntityProperty", "RemoveComponent", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EntityProperty: public Ui_EntityProperty {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTITYPROPERTYWIDGET_H
