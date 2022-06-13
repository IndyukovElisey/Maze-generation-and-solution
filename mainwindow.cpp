#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <iostream>
#include <stdlib.h>
#include <QScrollArea>
#include <string>
#include <sstream>
#include "Maze.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->scrollArea->setStyleSheet("background-color:white;");

    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(ui->gridLayout_3);

    on_spinBox_valueChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::blockInterface()
{
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
}

void MainWindow::unBlockInterface()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
}

void MainWindow::on_pushButton_clicked()
{
    blockInterface();

    if(!data.empty())
    {
        data.last()->generate1();
        ui->lineEdit->setText(QString::number(data.last()->getTimeGeneration()));
    }

    unBlockInterface();
}

void MainWindow::on_spinBox_valueChanged()
{
    if(ui->spinBox->value() < 1 || ui->spinBox->value() > 1000)
    {
        QMessageBox msgBox;
        msgBox.setText("Ошибка в размерности лабиринта!");
        msgBox.exec();
    }

    else
    {
        if(!data.empty())
            data.last()->deleteLater();

            ui->scrollArea->setWidgetResizable(true);
            Maze *widget_maze = new Maze(ui->spinBox->value(),ui->spinBox->value(), ui->scrollAreaWidgetContents);
            data.append(widget_maze);

            ui->gridLayout_3->addWidget(widget_maze, 0, 0, 0);
        }

}

void MainWindow::on_pushButton_2_clicked()
{
    blockInterface();

    if(!data.empty())
    {
        data.last()->generate2();
        ui->lineEdit->setText(QString::number(data.last()->getTimeGeneration()));
    }

    unBlockInterface();
}

void MainWindow::on_pushButton_4_clicked()
{
    blockInterface();

    if(!data.empty())
    {
        data.last()->solve1();

        if(data.last()->path_found==1)
            ui->lineEdit_2->setText(QString::number(data.last()->getTimePathfind()));
    }

    unBlockInterface();
}

void MainWindow::on_pushButton_3_clicked()
{
    blockInterface();

    if(!data.empty())
    {
        data.last()->solve2();

        if(data.last()->path_found==1)
            ui->lineEdit_2->setText(QString::number(data.last()->getTimePathfind()));
    }

    unBlockInterface();
}
