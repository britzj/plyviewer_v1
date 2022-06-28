/********************************************************************************
** Form generated from reading UI file 'viewer.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWER_H
#define UI_VIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_viewerClass
{
public:
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionView_Help;
    QAction *actionAbout;
    QAction *actionUnload;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *buttCalcBound;
    QPushButton *buttViewMesh;
    QCheckBox *cbBoundingBox;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *viewerClass)
    {
        if (viewerClass->objectName().isEmpty())
            viewerClass->setObjectName(QStringLiteral("viewerClass"));
        viewerClass->resize(500, 350);
        viewerClass->setMinimumSize(QSize(500, 350));
        actionOpen = new QAction(viewerClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionQuit = new QAction(viewerClass);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionView_Help = new QAction(viewerClass);
        actionView_Help->setObjectName(QStringLiteral("actionView_Help"));
        actionAbout = new QAction(viewerClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionUnload = new QAction(viewerClass);
        actionUnload->setObjectName(QStringLiteral("actionUnload"));
        centralWidget = new QWidget(viewerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        buttCalcBound = new QPushButton(centralWidget);
        buttCalcBound->setObjectName(QStringLiteral("buttCalcBound"));

        verticalLayout->addWidget(buttCalcBound);

        buttViewMesh = new QPushButton(centralWidget);
        buttViewMesh->setObjectName(QStringLiteral("buttViewMesh"));

        verticalLayout->addWidget(buttViewMesh);

        cbBoundingBox = new QCheckBox(centralWidget);
        cbBoundingBox->setObjectName(QStringLiteral("cbBoundingBox"));

        verticalLayout->addWidget(cbBoundingBox);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);

        viewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(viewerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 500, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        viewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(viewerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        viewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(viewerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        viewerClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionUnload);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionAbout);

        retranslateUi(viewerClass);
        QObject::connect(actionQuit, SIGNAL(triggered()), viewerClass, SLOT(close()));

        QMetaObject::connectSlotsByName(viewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *viewerClass)
    {
        viewerClass->setWindowTitle(QApplication::translate("viewerClass", "plyViewer", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("viewerClass", "Open", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("viewerClass", "Quit", Q_NULLPTR));
        actionView_Help->setText(QApplication::translate("viewerClass", "View Help", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("viewerClass", "About", Q_NULLPTR));
        actionUnload->setText(QApplication::translate("viewerClass", "Unload", Q_NULLPTR));
        buttCalcBound->setText(QApplication::translate("viewerClass", "Calculate boundaries", Q_NULLPTR));
        buttViewMesh->setText(QApplication::translate("viewerClass", "View mesh", Q_NULLPTR));
        cbBoundingBox->setText(QApplication::translate("viewerClass", "Show bounding box", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("viewerClass", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("viewerClass", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class viewerClass: public Ui_viewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWER_H
