/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QCustomPlot *qcp_gr;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QComboBox *comboBox_serial_ports;
    QLineEdit *lineEdit_command;
    QLabel *label_serial_ports;
    QLabel *label_command;
    QPushButton *pushButton_send_command;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_5;
    QLabel *label_v_from;
    QDoubleSpinBox *doubleSpinBox_v_from;
    QLabel *label_v_to;
    QDoubleSpinBox *doubleSpinBox_v_to;
    QLabel *label_v_by;
    QDoubleSpinBox *doubleSpinBox_v_by;
    QPushButton *pushButton_start_run;
    QPushButton *pushButton__stop_run;
    QPushButton *pushButton_clear_plot;
    QProgressBar *progressBar;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(744, 512);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        qcp_gr = new QCustomPlot(centralWidget);
        qcp_gr->setObjectName(QStringLiteral("qcp_gr"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qcp_gr->sizePolicy().hasHeightForWidth());
        qcp_gr->setSizePolicy(sizePolicy);
        qcp_gr->setMinimumSize(QSize(400, 400));

        gridLayout_3->addWidget(qcp_gr, 0, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        comboBox_serial_ports = new QComboBox(centralWidget);
        comboBox_serial_ports->setObjectName(QStringLiteral("comboBox_serial_ports"));

        gridLayout->addWidget(comboBox_serial_ports, 0, 2, 1, 1);

        lineEdit_command = new QLineEdit(centralWidget);
        lineEdit_command->setObjectName(QStringLiteral("lineEdit_command"));

        gridLayout->addWidget(lineEdit_command, 1, 1, 1, 2);

        label_serial_ports = new QLabel(centralWidget);
        label_serial_ports->setObjectName(QStringLiteral("label_serial_ports"));

        gridLayout->addWidget(label_serial_ports, 0, 0, 1, 1);

        label_command = new QLabel(centralWidget);
        label_command->setObjectName(QStringLiteral("label_command"));

        gridLayout->addWidget(label_command, 1, 0, 1, 1);

        pushButton_send_command = new QPushButton(centralWidget);
        pushButton_send_command->setObjectName(QStringLiteral("pushButton_send_command"));

        gridLayout->addWidget(pushButton_send_command, 2, 0, 1, 3);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 3, 0, 1, 3);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_v_from = new QLabel(centralWidget);
        label_v_from->setObjectName(QStringLiteral("label_v_from"));

        gridLayout_5->addWidget(label_v_from, 0, 0, 1, 1);

        doubleSpinBox_v_from = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_v_from->setObjectName(QStringLiteral("doubleSpinBox_v_from"));
        doubleSpinBox_v_from->setMinimum(-5);
        doubleSpinBox_v_from->setMaximum(5);
        doubleSpinBox_v_from->setSingleStep(0.1);
        doubleSpinBox_v_from->setValue(-1);

        gridLayout_5->addWidget(doubleSpinBox_v_from, 0, 1, 1, 1);

        label_v_to = new QLabel(centralWidget);
        label_v_to->setObjectName(QStringLiteral("label_v_to"));

        gridLayout_5->addWidget(label_v_to, 1, 0, 1, 1);

        doubleSpinBox_v_to = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_v_to->setObjectName(QStringLiteral("doubleSpinBox_v_to"));
        doubleSpinBox_v_to->setMinimum(-5);
        doubleSpinBox_v_to->setMaximum(5);
        doubleSpinBox_v_to->setSingleStep(0.1);
        doubleSpinBox_v_to->setValue(1);

        gridLayout_5->addWidget(doubleSpinBox_v_to, 1, 1, 1, 1);

        label_v_by = new QLabel(centralWidget);
        label_v_by->setObjectName(QStringLiteral("label_v_by"));

        gridLayout_5->addWidget(label_v_by, 2, 0, 1, 1);

        doubleSpinBox_v_by = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_v_by->setObjectName(QStringLiteral("doubleSpinBox_v_by"));
        doubleSpinBox_v_by->setMaximum(1);
        doubleSpinBox_v_by->setSingleStep(0.05);
        doubleSpinBox_v_by->setValue(0.2);

        gridLayout_5->addWidget(doubleSpinBox_v_by, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_5);

        pushButton_start_run = new QPushButton(centralWidget);
        pushButton_start_run->setObjectName(QStringLiteral("pushButton_start_run"));

        verticalLayout->addWidget(pushButton_start_run);

        pushButton__stop_run = new QPushButton(centralWidget);
        pushButton__stop_run->setObjectName(QStringLiteral("pushButton__stop_run"));

        verticalLayout->addWidget(pushButton__stop_run);


        gridLayout_2->addLayout(verticalLayout, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 2, 1);

        pushButton_clear_plot = new QPushButton(centralWidget);
        pushButton_clear_plot->setObjectName(QStringLiteral("pushButton_clear_plot"));

        gridLayout_3->addWidget(pushButton_clear_plot, 1, 1, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        gridLayout_4->addWidget(progressBar, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 744, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_serial_ports->setText(QApplication::translate("MainWindow", "Serial ports:", 0));
        label_command->setText(QApplication::translate("MainWindow", "Command;", 0));
        pushButton_send_command->setText(QApplication::translate("MainWindow", "Send Command", 0));
        label_v_from->setText(QApplication::translate("MainWindow", "from", 0));
        label_v_to->setText(QApplication::translate("MainWindow", "to", 0));
        label_v_by->setText(QApplication::translate("MainWindow", "by", 0));
        pushButton_start_run->setText(QApplication::translate("MainWindow", "Start", 0));
        pushButton__stop_run->setText(QApplication::translate("MainWindow", "Stop", 0));
        pushButton_clear_plot->setText(QApplication::translate("MainWindow", "Clear Plot", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
