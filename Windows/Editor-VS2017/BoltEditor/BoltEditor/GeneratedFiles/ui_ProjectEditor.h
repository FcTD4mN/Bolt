/********************************************************************************
** Form generated from reading UI file 'ProjectEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTEDITOR_H
#define UI_PROJECTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectEditor
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *widget;

    void setupUi(QWidget *ProjectEditor)
    {
        if (ProjectEditor->objectName().isEmpty())
            ProjectEditor->setObjectName(QStringLiteral("ProjectEditor"));
        ProjectEditor->resize(542, 532);
        horizontalLayout = new QHBoxLayout(ProjectEditor);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(ProjectEditor);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);

        widget = new QWidget(ProjectEditor);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout->addWidget(widget);


        retranslateUi(ProjectEditor);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ProjectEditor);
    } // setupUi

    void retranslateUi(QWidget *ProjectEditor)
    {
        ProjectEditor->setWindowTitle(QApplication::translate("ProjectEditor", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ProjectEditor", "Properties", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ProjectEditor", "Screens", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectEditor: public Ui_ProjectEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTEDITOR_H
