#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "errors.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void on_LoadFile_clicked();
    void on_SaveFile_clicked();
    void on_GetFileInfo_clicked();
    void on_GetProgramInfo_clicked();

    void on_buttonMove_clicked();
    void on_buttonTurn_clicked();
    void on_buttonScale_clicked();

    err_t draw();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
