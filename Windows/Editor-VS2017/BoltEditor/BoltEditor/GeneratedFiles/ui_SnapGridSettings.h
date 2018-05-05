/********************************************************************************
** Form generated from reading UI file 'SnapGridSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNAPGRIDSETTINGS_H
#define UI_SNAPGRIDSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogSnapGridSettings
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxCellWidth;
    QSpinBox *spinBoxCellHeight;
    QDialogButtonBox *buttonDialogs;

    void setupUi(QDialog *DialogSnapGridSettings)
    {
        if (DialogSnapGridSettings->objectName().isEmpty())
            DialogSnapGridSettings->setObjectName(QStringLiteral("DialogSnapGridSettings"));
        DialogSnapGridSettings->resize(226, 130);
        verticalLayout = new QVBoxLayout(DialogSnapGridSettings);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(DialogSnapGridSettings);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(DialogSnapGridSettings);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        spinBoxCellWidth = new QSpinBox(DialogSnapGridSettings);
        spinBoxCellWidth->setObjectName(QStringLiteral("spinBoxCellWidth"));
        spinBoxCellWidth->setMaximum(9999);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBoxCellWidth);

        spinBoxCellHeight = new QSpinBox(DialogSnapGridSettings);
        spinBoxCellHeight->setObjectName(QStringLiteral("spinBoxCellHeight"));
        spinBoxCellHeight->setMaximum(9999);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxCellHeight);


        verticalLayout->addLayout(formLayout);

        buttonDialogs = new QDialogButtonBox(DialogSnapGridSettings);
        buttonDialogs->setObjectName(QStringLiteral("buttonDialogs"));
        buttonDialogs->setOrientation(Qt::Horizontal);
        buttonDialogs->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonDialogs);


        retranslateUi(DialogSnapGridSettings);
        QObject::connect(buttonDialogs, SIGNAL(accepted()), DialogSnapGridSettings, SLOT(accept()));
        QObject::connect(buttonDialogs, SIGNAL(rejected()), DialogSnapGridSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSnapGridSettings);
    } // setupUi

    void retranslateUi(QDialog *DialogSnapGridSettings)
    {
        DialogSnapGridSettings->setWindowTitle(QApplication::translate("DialogSnapGridSettings", "SnapGrid Settings", nullptr));
        label->setText(QApplication::translate("DialogSnapGridSettings", "CellWidth", nullptr));
        label_2->setText(QApplication::translate("DialogSnapGridSettings", "CellHeight", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSnapGridSettings: public Ui_DialogSnapGridSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAPGRIDSETTINGS_H
