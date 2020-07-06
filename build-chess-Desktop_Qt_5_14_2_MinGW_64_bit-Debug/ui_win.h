/********************************************************************************
** Form generated from reading UI file 'win.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIN_H
#define UI_WIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_win
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *win)
    {
        if (win->objectName().isEmpty())
            win->setObjectName(QString::fromUtf8("win"));
        win->resize(380, 137);
        gridLayout = new QGridLayout(win);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(139, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        label = new QLabel(win);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 1, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(145, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 0, 1, 2);

        pushButton = new QPushButton(win);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(106, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 3, 1, 2);


        retranslateUi(win);

        QMetaObject::connectSlotsByName(win);
    } // setupUi

    void retranslateUi(QWidget *win)
    {
        win->setWindowTitle(QCoreApplication::translate("win", "Form", nullptr));
        label->setText(QCoreApplication::translate("win", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("win", "\345\206\215\346\235\245\344\270\200\345\261\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class win: public Ui_win {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIN_H
