/********************************************************************************
** Form generated from reading UI file 'monitor.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONITOR_H
#define UI_MONITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Monitor
{
public:
    QAction *actionIniciar_Monitores;
    QAction *actionSair;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *boxDisco;
    QGraphicsView *graficoDisco;
    QHBoxLayout *horizontalLayout;
    QGroupBox *boxHoneypot;
    QListWidget *listHoney;
    QGroupBox *boxEntropia;
    QListWidget *listEntropia;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuArquivo;

    void setupUi(QMainWindow *Monitor)
    {
        if (Monitor->objectName().isEmpty())
            Monitor->setObjectName(QString::fromUtf8("Monitor"));
        Monitor->resize(600, 400);
        actionIniciar_Monitores = new QAction(Monitor);
        actionIniciar_Monitores->setObjectName(QString::fromUtf8("actionIniciar_Monitores"));
        actionSair = new QAction(Monitor);
        actionSair->setObjectName(QString::fromUtf8("actionSair"));
        centralWidget = new QWidget(Monitor);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 581, 341));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        boxDisco = new QGroupBox(layoutWidget);
        boxDisco->setObjectName(QString::fromUtf8("boxDisco"));
        graficoDisco = new QGraphicsView(boxDisco);
        graficoDisco->setObjectName(QString::fromUtf8("graficoDisco"));
        graficoDisco->setGeometry(QRect(10, 20, 561, 141));

        verticalLayout_2->addWidget(boxDisco);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        boxHoneypot = new QGroupBox(layoutWidget);
        boxHoneypot->setObjectName(QString::fromUtf8("boxHoneypot"));
        listHoney = new QListWidget(boxHoneypot);
        listHoney->setObjectName(QString::fromUtf8("listHoney"));
        listHoney->setGeometry(QRect(10, 20, 271, 141));

        horizontalLayout->addWidget(boxHoneypot);

        boxEntropia = new QGroupBox(layoutWidget);
        boxEntropia->setObjectName(QString::fromUtf8("boxEntropia"));
        listEntropia = new QListWidget(boxEntropia);
        listEntropia->setObjectName(QString::fromUtf8("listEntropia"));
        listEntropia->setGeometry(QRect(10, 20, 271, 141));

        horizontalLayout->addWidget(boxEntropia);


        verticalLayout_2->addLayout(horizontalLayout);

        Monitor->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Monitor);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Monitor->setStatusBar(statusBar);
        menuBar = new QMenuBar(Monitor);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 20));
        menuBar->setDefaultUp(false);
        menuArquivo = new QMenu(menuBar);
        menuArquivo->setObjectName(QString::fromUtf8("menuArquivo"));
        Monitor->setMenuBar(menuBar);

        menuBar->addAction(menuArquivo->menuAction());
        menuArquivo->addAction(actionIniciar_Monitores);
        menuArquivo->addSeparator();
        menuArquivo->addAction(actionSair);

        retranslateUi(Monitor);

        QMetaObject::connectSlotsByName(Monitor);
    } // setupUi

    void retranslateUi(QMainWindow *Monitor)
    {
        Monitor->setWindowTitle(QCoreApplication::translate("Monitor", "Monitor", nullptr));
        actionIniciar_Monitores->setText(QCoreApplication::translate("Monitor", "Iniciar Monitores", nullptr));
        actionSair->setText(QCoreApplication::translate("Monitor", "Sair", nullptr));
        boxDisco->setTitle(QCoreApplication::translate("Monitor", "Monitor de Disco", nullptr));
        boxHoneypot->setTitle(QCoreApplication::translate("Monitor", "Monitor Honeypot", nullptr));
        boxEntropia->setTitle(QCoreApplication::translate("Monitor", "Monitor de Entropia", nullptr));
        menuArquivo->setTitle(QCoreApplication::translate("Monitor", "Arquivo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Monitor: public Ui_Monitor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONITOR_H
