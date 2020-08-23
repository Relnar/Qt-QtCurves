#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinScale->setValue(ui->renderArea->scale());
    ui->spinIntervalLength->setValue(ui->renderArea->intervalLength());
    ui->spinCount->setValue(ui->renderArea->stepCount());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_ui()
{
    ui->spinScale->setValue(ui->renderArea->scale());
    ui->spinIntervalLength->setValue(ui->renderArea->intervalLength());
    ui->spinCount->setValue(ui->renderArea->stepCount());

    ui->renderArea->repaint();
}

void MainWindow::on_btnAstroid_clicked()
{
    ui->renderArea->setShape(RenderArea::Astroid);
    update_ui();
}

void MainWindow::on_btnCycloid_clicked()
{
    ui->renderArea->setShape(RenderArea::Cycloid);
    update_ui();
}

void MainWindow::on_bthHuygens_clicked()
{
    ui->renderArea->setShape(RenderArea::HuygenCycloid);
    update_ui();
}

void MainWindow::on_btnHypoCycloid_clicked()
{
    ui->renderArea->setShape(RenderArea::HypoCycloid);
    update_ui();
}

void MainWindow::on_btnLine_clicked()
{
    ui->renderArea->setShape(RenderArea::Line);
    update_ui();
}

void MainWindow::on_btnCircle_clicked()
{
    ui->renderArea->setShape(RenderArea::Circle);
    update_ui();
}

void MainWindow::on_spinScale_valueChanged(double scale)
{
    ui->renderArea->setScale(scale);
    ui->renderArea->repaint();
}

void MainWindow::on_spinIntervalLength_valueChanged(double intervalLength)
{
    ui->renderArea->setIntervalLength(intervalLength);
    ui->renderArea->repaint();
}

void MainWindow::on_spinCount_valueChanged(int stepCount)
{
    ui->renderArea->setStepCount(stepCount);
    ui->renderArea->repaint();
}

void MainWindow::on_btnBackground_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->backgroundColor(), this, "Select color");
    ui->renderArea->setBackgroundColor(color);
}

void MainWindow::on_btnLineColor_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->lineColor(), this, "Select color");
    ui->renderArea->setLineColor(color);
}
