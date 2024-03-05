#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

#include "errors.h"
#include "requests.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

    connect(ui->GetFileInfo, &QAction::triggered, this, &MainWindow::on_GetFileInfo_clicked);
    connect(ui->GetProgramInfo, &QAction::triggered, this, &MainWindow::on_GetProgramInfo_clicked);

    connect(ui->LoadFile, &QAction::triggered, this, &MainWindow::on_LoadFile_clicked);
    connect(ui->SaveFile, &QAction::triggered, this, &MainWindow::on_SaveFile_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_GetFileInfo_clicked()
{
    QMessageBox::information(0, "Требования к входному файлу", "");
}

void MainWindow::on_GetProgramInfo_clicked()
{
    QMessageBox::information(0, "Информация о программe", "3D Viewer — программа просмотра каркасных 3D моделей.\n");
}

err_t MainWindow::draw()
{
    QRect contents_rect = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(contents_rect);

    request_t request;
    request.action = DRAW;
    request.scene = {
        .scene  = ui->graphicsView->scene(),
        .width  = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height()
    };

    return requests_handler(request);
}


void MainWindow::on_LoadFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName();

    request_t request;
    request.action = LOAD;
    request.filename = filename.toUtf8().data();

    err_t rc = requests_handler(request);
    if (rc == SUCCESS)
        rc = draw();

    if (rc != SUCCESS)
        error_message(rc);
}


void MainWindow::on_SaveFile_clicked()
{
    QString filename = QFileDialog::getSaveFileName();

    request_t request;
    request.action = SAVE;
    request.filename = filename.toUtf8().data();

    err_t rc = requests_handler(request);
    if (rc == SUCCESS)
        rc = draw();

    if (rc != SUCCESS)
        error_message(rc);
}


void MainWindow::on_buttonMove_clicked()
{
    request_t request;
    request.action = MOVE;
    request.move = {
        .dx = ui->InputXMoving->value(),
        .dy = ui->InputYMoving->value(),
        .dz = ui->InputZMoving->value()
    };

    err_t rc = requests_handler(request);
    if (rc == SUCCESS)
        rc = draw();

    if (rc != SUCCESS)
        error_message(rc);
}


void MainWindow::on_buttonTurn_clicked()
{
    request_t request;
    request.action = ROTATE;
    request.rotate = {
        .angleX = ui->InputXTurn->value(),
        .angleY = ui->InputYTurn->value(),
        .angleZ = ui->InputZTurn->value()
    };

    err_t rc = requests_handler(request);
    if (rc == SUCCESS)
        rc = draw();

    if (rc != SUCCESS)
        error_message(rc);
}


void MainWindow::on_buttonScale_clicked()
{
    request_t request;
    request.action = SCALE;
    request.scale = {
        .kx = ui->InputXScale->value(),
        .ky = ui->InputYScale->value(),
        .kz = ui->InputZScale->value()
    };

    err_t rc = requests_handler(request);
    if (rc == SUCCESS)
        rc = draw();

    if (rc != SUCCESS)
        error_message(rc);
}
