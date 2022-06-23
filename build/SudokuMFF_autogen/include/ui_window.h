/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QWidget *centralwidget;
    QTableWidget *sudokuTable;
    QPushButton *resetButton;
    QPushButton *solveButton;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QLabel *currentLevel;
    QPushButton *decrementLevel;
    QPushButton *incrementLevel;
    QPushButton *hintButton;

    void setupUi(QMainWindow *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QString::fromUtf8("Window"));
        Window->resize(750, 500);
        Window->setMinimumSize(QSize(750, 500));
        Window->setMaximumSize(QSize(750, 500));
        QFont font;
        font.setKerning(true);
        Window->setFont(font);
        centralwidget = new QWidget(Window);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sudokuTable = new QTableWidget(centralwidget);
        if (sudokuTable->columnCount() < 9)
            sudokuTable->setColumnCount(9);
        if (sudokuTable->rowCount() < 9)
            sudokuTable->setRowCount(9);
        sudokuTable->setObjectName(QString::fromUtf8("sudokuTable"));
        sudokuTable->setGeometry(QRect(150, 20, 450, 450));
        QFont font1;
        font1.setPointSize(25);
        font1.setKerning(true);
        sudokuTable->setFont(font1);
        sudokuTable->setLineWidth(1);
        sudokuTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        sudokuTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        sudokuTable->setAutoScroll(false);
        sudokuTable->setEditTriggers(QAbstractItemView::AnyKeyPressed);
        sudokuTable->setProperty("showDropIndicator", QVariant(false));
        sudokuTable->setDragDropOverwriteMode(false);
        sudokuTable->setSelectionMode(QAbstractItemView::SingleSelection);
        sudokuTable->setTextElideMode(Qt::ElideRight);
        sudokuTable->setShowGrid(true);
        sudokuTable->setGridStyle(Qt::DashLine);
        sudokuTable->setWordWrap(true);
        sudokuTable->setCornerButtonEnabled(true);
        sudokuTable->setRowCount(9);
        sudokuTable->setColumnCount(9);
        sudokuTable->horizontalHeader()->setVisible(false);
        sudokuTable->horizontalHeader()->setMinimumSectionSize(31);
        sudokuTable->horizontalHeader()->setDefaultSectionSize(50);
        sudokuTable->horizontalHeader()->setHighlightSections(true);
        sudokuTable->verticalHeader()->setVisible(false);
        sudokuTable->verticalHeader()->setDefaultSectionSize(50);
        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(630, 90, 100, 32));
        solveButton = new QPushButton(centralwidget);
        solveButton->setObjectName(QString::fromUtf8("solveButton"));
        solveButton->setGeometry(QRect(630, 30, 100, 32));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(280, 20, 40, 451));
        line->setLineWidth(3);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(430, 20, 40, 451));
        line_2->setLineWidth(3);
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(150, 160, 451, 16));
        line_3->setLineWidth(3);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(150, 310, 451, 16));
        line_4->setLineWidth(3);
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        currentLevel = new QLabel(centralwidget);
        currentLevel->setObjectName(QString::fromUtf8("currentLevel"));
        currentLevel->setGeometry(QRect(350, 476, 51, 21));
        currentLevel->setAlignment(Qt::AlignCenter);
        decrementLevel = new QPushButton(centralwidget);
        decrementLevel->setObjectName(QString::fromUtf8("decrementLevel"));
        decrementLevel->setGeometry(QRect(300, 470, 51, 32));
        incrementLevel = new QPushButton(centralwidget);
        incrementLevel->setObjectName(QString::fromUtf8("incrementLevel"));
        incrementLevel->setGeometry(QRect(400, 470, 51, 32));
        hintButton = new QPushButton(centralwidget);
        hintButton->setObjectName(QString::fromUtf8("hintButton"));
        hintButton->setGeometry(QRect(630, 60, 100, 32));
        Window->setCentralWidget(centralwidget);

        retranslateUi(Window);

        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QMainWindow *Window)
    {
        Window->setWindowTitle(QCoreApplication::translate("Window", "Window", nullptr));
        resetButton->setText(QCoreApplication::translate("Window", "Reset", nullptr));
        solveButton->setText(QCoreApplication::translate("Window", "Solve", nullptr));
        currentLevel->setText(QCoreApplication::translate("Window", "0", nullptr));
        decrementLevel->setText(QCoreApplication::translate("Window", "-", nullptr));
        incrementLevel->setText(QCoreApplication::translate("Window", "+", nullptr));
        hintButton->setText(QCoreApplication::translate("Window", "Hint", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
