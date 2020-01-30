#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    this->ui->spinScale->setValue(this->ui->renderArea->GetScale());
    this->ui->spinIntervalLength->setValue(this->ui->renderArea->GetIntervalLength());
}

void MainWindow::on_btnAstroid_clicked()
{
    this->ui->renderArea->SetShape(RenderArea::Astroid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnCycloid_clicked()
{
    this->ui->renderArea->SetShape(RenderArea::Cycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHuygens_clicked()
{
    this->ui->renderArea->SetShape(RenderArea::HuygensCycloid);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_btnHypo_clicked()
{
    this->ui->renderArea->SetShape(RenderArea::HypoCycloid);
    this->ui->renderArea->repaint();
    update_ui();
}


void MainWindow::on_btnLine_clicked()
{
    this->ui->renderArea->SetShape(RenderArea::Line);
    this->ui->renderArea->repaint();
    update_ui();
}

void MainWindow::on_spinScale_valueChanged(double scale)
{
    this->ui->renderArea->SetScale(scale);
}

void MainWindow::on_spinIntervalLength_valueChanged(double length)
{
    this->ui->renderArea->SetIntervalLength(length);
}
