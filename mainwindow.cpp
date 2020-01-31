#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    update_ui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_ui() {
    ui->spinScale->setValue(this->ui->renderArea->GetScale());
    ui->spinIntervalLength->setValue(this->ui->renderArea->GetIntervalLength());
    ui->spinCount->setValue(this->ui->renderArea->GetStepCount());
}

// curve buttons
void MainWindow::on_btnAstroid_clicked()
{
    ui->renderArea->SetShape(RenderArea::Astroid);
    ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnCycloid_clicked()
{
    ui->renderArea->SetShape(RenderArea::Cycloid);
    ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHuygens_clicked()
{
    ui->renderArea->SetShape(RenderArea::HuygensCycloid);
    ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHypo_clicked()
{
    ui->renderArea->SetShape(RenderArea::HypoCycloid);
    ui->renderArea->repaint();
    update_ui();
}


void MainWindow::on_btnLine_clicked()
{
    ui->renderArea->SetShape(RenderArea::Line);
    ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnCircle_clicked()
{
    ui->renderArea->SetShape(RenderArea::Circle);
    ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnEllipse_clicked()
{
    ui->renderArea->SetShape(RenderArea::Ellipse);
    ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnFancy_clicked()
{
    ui->renderArea->SetShape(RenderArea::Fancy);
    ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnStarfish_clicked()
{
    ui->renderArea->SetShape(RenderArea::Starfish);
    ui->renderArea->repaint();
    update_ui();
}


// Spiners
void MainWindow::on_spinScale_valueChanged(double scale)
{
    ui->renderArea->SetScale(scale);
}

void MainWindow::on_spinIntervalLength_valueChanged(double length)
{
    ui->renderArea->SetIntervalLength(length);
}

void MainWindow::on_spinCount_valueChanged(int stepCount)
{
    ui->renderArea->SetStepCount(stepCount);
}

// Color buttons
void MainWindow::on_btnBackgroundColor_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->GetBackgroundColor(),
                                          this,
                                          "Select color");
    ui->renderArea->SetBackgroundColor(color);
}

void MainWindow::on_btnLineColor_clicked()
{
    QColor color = QColorDialog::getColor(ui->renderArea->GetShapeColor(),
                                          this,
                                          "Select color");
    ui->renderArea->SetShapeColor(color);
}

