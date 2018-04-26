/********************************************************************************
** Form generated from reading UI file 'ComponentEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPONENTEDITOR_H
#define UI_COMPONENTEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComponentEditor
{
public:
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *editComponentName;
    QLabel *label_2;
    QTreeView *treeViewComponent;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QListView *listViewAllComponents;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QWidget *ComponentEditor)
    {
        if (ComponentEditor->objectName().isEmpty())
            ComponentEditor->setObjectName(QStringLiteral("ComponentEditor"));
        ComponentEditor->resize(621, 395);
        horizontalLayout_2 = new QHBoxLayout(ComponentEditor);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        splitter = new QSplitter(ComponentEditor);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setMidLineWidth(5);
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        editComponentName = new QLineEdit(widget);
        editComponentName->setObjectName(QStringLiteral("editComponentName"));

        horizontalLayout->addWidget(editComponentName);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        treeViewComponent = new QTreeView(widget);
        treeViewComponent->setObjectName(QStringLiteral("treeViewComponent"));

        verticalLayout->addWidget(treeViewComponent);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_4->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_4);

        splitter->addWidget(widget);
        widget1 = new QWidget(splitter);
        widget1->setObjectName(QStringLiteral("widget1"));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        listViewAllComponents = new QListView(widget1);
        listViewAllComponents->setObjectName(QStringLiteral("listViewAllComponents"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listViewAllComponents->sizePolicy().hasHeightForWidth());
        listViewAllComponents->setSizePolicy(sizePolicy);
        listViewAllComponents->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(listViewAllComponents);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pushButton_3 = new QPushButton(widget1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_6->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(widget1);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_6->addWidget(pushButton_4);


        verticalLayout_2->addLayout(horizontalLayout_6);

        splitter->addWidget(widget1);

        horizontalLayout_2->addWidget(splitter);


        retranslateUi(ComponentEditor);
        QObject::connect(listViewAllComponents, SIGNAL(doubleClicked(QModelIndex)), ComponentEditor, SLOT(ComponentEditionAsked(QModelIndex)));

        QMetaObject::connectSlotsByName(ComponentEditor);
    } // setupUi

    void retranslateUi(QWidget *ComponentEditor)
    {
        ComponentEditor->setWindowTitle(QApplication::translate("ComponentEditor", "Form", nullptr));
        label->setText(QApplication::translate("ComponentEditor", "Component Name ", nullptr));
        label_2->setText(QApplication::translate("ComponentEditor", "Component's Variables", nullptr));
        pushButton->setText(QApplication::translate("ComponentEditor", "Save Component", nullptr));
        pushButton_2->setText(QApplication::translate("ComponentEditor", "Save Component As", nullptr));
        label_3->setText(QApplication::translate("ComponentEditor", "Component List", nullptr));
        pushButton_3->setText(QApplication::translate("ComponentEditor", "AddComponent", nullptr));
        pushButton_4->setText(QApplication::translate("ComponentEditor", "RemoveComponent", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ComponentEditor: public Ui_ComponentEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPONENTEDITOR_H
