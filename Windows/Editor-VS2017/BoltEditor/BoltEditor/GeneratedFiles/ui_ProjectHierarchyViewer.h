/********************************************************************************
** Form generated from reading UI file 'ProjectHierarchyViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTHIERARCHYVIEWER_H
#define UI_PROJECTHIERARCHYVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectHierarchyViewer
{
public:
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;

    void setupUi(QWidget *ProjectHierarchyViewer)
    {
        if (ProjectHierarchyViewer->objectName().isEmpty())
            ProjectHierarchyViewer->setObjectName(QStringLiteral("ProjectHierarchyViewer"));
        ProjectHierarchyViewer->resize(408, 557);
        verticalLayout = new QVBoxLayout(ProjectHierarchyViewer);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeView = new QTreeView(ProjectHierarchyViewer);
        treeView->setObjectName(QStringLiteral("treeView"));

        verticalLayout->addWidget(treeView);


        retranslateUi(ProjectHierarchyViewer);

        QMetaObject::connectSlotsByName(ProjectHierarchyViewer);
    } // setupUi

    void retranslateUi(QWidget *ProjectHierarchyViewer)
    {
        ProjectHierarchyViewer->setWindowTitle(QApplication::translate("ProjectHierarchyViewer", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectHierarchyViewer: public Ui_ProjectHierarchyViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTHIERARCHYVIEWER_H
