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
#include <QtWidgets/QTreeWidget>
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
    QTreeWidget *treeWidget;

    void setupUi(QWidget *EntityProperty)
    {
        if (EntityProperty->objectName().isEmpty())
            EntityProperty->setObjectName(QStringLiteral("EntityProperty"));
        EntityProperty->resize(283, 199);
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

        treeWidget = new QTreeWidget(EntityProperty);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);


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

#endif // UI_ENTITYPROPERTYWIDGET_H
