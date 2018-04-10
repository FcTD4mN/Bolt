/********************************************************************************
** Form generated from reading UI file 'Editor.BoltQtUIFiles.EntityPropertyWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QTreeView *treeView;

    void setupUi(QWidget *EntityProperty)
    {
        if (EntityProperty->objectName().isEmpty())
            EntityProperty->setObjectName(QStringLiteral("EntityProperty"));
        EntityProperty->resize(400, 290);
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

        treeView = new QTreeView(EntityProperty);
        treeView->setObjectName(QStringLiteral("treeView"));

        verticalLayout->addWidget(treeView);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(EntityProperty);

        QMetaObject::connectSlotsByName(EntityProperty);
    } // setupUi

    void retranslateUi(QWidget *EntityProperty)
    {
        EntityProperty->setWindowTitle(QApplication::translate("EntityProperty", "Form", nullptr));
        labelEntityName->setText(QApplication::translate("EntityProperty", "EntityName :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EntityProperty: public Ui_EntityProperty {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
