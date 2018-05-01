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
#include <QtWidgets/QSpacerItem>
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
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *editComponentName;
    QLabel *label_2;
    QTreeView *treeViewComponent;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonAddVariable;
    QPushButton *buttonRemoveVariable;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *layoutWidget1;
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
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        editComponentName = new QLineEdit(layoutWidget);
        editComponentName->setObjectName(QStringLiteral("editComponentName"));

        horizontalLayout->addWidget(editComponentName);


        verticalLayout->addLayout(horizontalLayout);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        treeViewComponent = new QTreeView(layoutWidget);
        treeViewComponent->setObjectName(QStringLiteral("treeViewComponent"));

        verticalLayout->addWidget(treeViewComponent);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonAddVariable = new QPushButton(layoutWidget);
        buttonAddVariable->setObjectName(QStringLiteral("buttonAddVariable"));

        horizontalLayout_3->addWidget(buttonAddVariable);

        buttonRemoveVariable = new QPushButton(layoutWidget);
        buttonRemoveVariable->setObjectName(QStringLiteral("buttonRemoveVariable"));

        horizontalLayout_3->addWidget(buttonRemoveVariable);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_4->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_4);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        listViewAllComponents = new QListView(layoutWidget1);
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
        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_6->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_6->addWidget(pushButton_4);


        verticalLayout_2->addLayout(horizontalLayout_6);

        splitter->addWidget(layoutWidget1);

        horizontalLayout_2->addWidget(splitter);


        retranslateUi(ComponentEditor);
        QObject::connect(listViewAllComponents, SIGNAL(doubleClicked(QModelIndex)), ComponentEditor, SLOT(ComponentEditionAsked(QModelIndex)));
        QObject::connect(buttonAddVariable, SIGNAL(clicked()), ComponentEditor, SLOT(AddNewVariable()));
        QObject::connect(buttonRemoveVariable, SIGNAL(clicked()), ComponentEditor, SLOT(RemoveVariable()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), ComponentEditor, SLOT(AddNewComponent()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), ComponentEditor, SLOT(RemoveComponent()));
        QObject::connect(editComponentName, SIGNAL(editingFinished()), ComponentEditor, SLOT(ComponentNameChanged()));
        QObject::connect(pushButton, SIGNAL(clicked()), ComponentEditor, SLOT(SaveComponent()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), ComponentEditor, SLOT(SaveComponentAs()));

        QMetaObject::connectSlotsByName(ComponentEditor);
    } // setupUi

    void retranslateUi(QWidget *ComponentEditor)
    {
        ComponentEditor->setWindowTitle(QApplication::translate("ComponentEditor", "Form", nullptr));
        label->setText(QApplication::translate("ComponentEditor", "Component Name ", nullptr));
        label_2->setText(QApplication::translate("ComponentEditor", "Component's Variables", nullptr));
        buttonAddVariable->setText(QApplication::translate("ComponentEditor", "AddVariable", nullptr));
        buttonRemoveVariable->setText(QApplication::translate("ComponentEditor", "RemoveVariable", nullptr));
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
