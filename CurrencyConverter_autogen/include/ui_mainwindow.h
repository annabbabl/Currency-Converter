/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QComboBox *from_currency;
    QLineEdit *from_value;
    QVBoxLayout *verticalLayout_3;
    QComboBox *to_currency;
    QLineEdit *result_value;
    QPushButton *convert_button;
    QHBoxLayout *plot_layout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 120, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, -1, -1, -1);
        from_currency = new QComboBox(centralwidget);
        from_currency->setObjectName("from_currency");
        from_currency->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        from_currency->setFont(font);

        verticalLayout_2->addWidget(from_currency);

        from_value = new QLineEdit(centralwidget);
        from_value->setObjectName("from_value");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(40);
        sizePolicy.setHeightForWidth(from_value->sizePolicy().hasHeightForWidth());
        from_value->setSizePolicy(sizePolicy);
        from_value->setMinimumSize(QSize(0, 40));
        QFont font1;
        font1.setPointSize(15);
        from_value->setFont(font1);

        verticalLayout_2->addWidget(from_value);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, -1, -1, -1);
        to_currency = new QComboBox(centralwidget);
        to_currency->setObjectName("to_currency");
        to_currency->setMinimumSize(QSize(0, 50));
        to_currency->setFont(font);

        verticalLayout_3->addWidget(to_currency);

        result_value = new QLineEdit(centralwidget);
        result_value->setObjectName("result_value");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(result_value->sizePolicy().hasHeightForWidth());
        result_value->setSizePolicy(sizePolicy1);
        result_value->setMinimumSize(QSize(0, 40));
        result_value->setFont(font1);
        result_value->setReadOnly(true);

        verticalLayout_3->addWidget(result_value);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        convert_button = new QPushButton(centralwidget);
        convert_button->setObjectName("convert_button");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(convert_button->sizePolicy().hasHeightForWidth());
        convert_button->setSizePolicy(sizePolicy2);
        convert_button->setMinimumSize(QSize(20, 40));

        verticalLayout_4->addWidget(convert_button);


        verticalLayout->addLayout(verticalLayout_4);

        plot_layout = new QHBoxLayout();
        plot_layout->setObjectName("plot_layout");

        verticalLayout->addLayout(plot_layout);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CurrencyConverter", nullptr));
        convert_button->setText(QCoreApplication::translate("MainWindow", "Convert", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
