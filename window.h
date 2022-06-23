#pragma once
#include <QMainWindow>
#include <QTableWidgetItem>
#include "sudoku.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);

    ~Window();

private slots:
    void on_resetButton_clicked();

    void on_solveButton_clicked();

    void on_decrementLevel_clicked();

    void on_incrementLevel_clicked();

    void on_sudokuTable_cellChanged(int row, int column);

    void on_hintButton_clicked();

private:
    Ui::Window *ui;
    Sudoku sudoku;
    void LoadLevelWindow();
    void populateSudokuTable();
    void createLoadedItem(int row, int column);
    void createEmptyItem(int row, int column);
    void sendNoSolutionMessage();
    void sendInvalidBoardMessage();
    void deselectAllCells();
};
