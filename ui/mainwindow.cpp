//
// Created by user on 11.07.2024.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_browseFile1Button_clicked() {
    file1Path = QFileDialog::getOpenFileName(this, "Select First Input File");
    ui->file1LineEdit->setText(file1Path);
}

void MainWindow::on_browseFile2Button_clicked() {
    file2Path = QFileDialog::getOpenFileName(this, "Select Second Input File");
    ui->file2LineEdit->setText(file2Path);
}

void MainWindow::on_browseOutputButton_clicked() {
    outputPath = QFileDialog::getSaveFileName(this, "Select Output File");
    ui->outputLineEdit->setText(outputPath);
}

void MainWindow::on_processButton_clicked() {
    if (file1Path.isEmpty() || file2Path.isEmpty() || outputPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select all file paths");
        return;
    }

    // Example processing code (replace with your actual processing logic)
    QFile file1(file1Path);
    QFile file2(file2Path);
    QFile outputFile(outputPath);

    if (!file1.open(QIODevice::ReadOnly) || !file2.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Failed to open input files");
        return;
    }

    if (!outputFile.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Error", "Failed to open output file");
        return;
    }

    QTextStream in1(&file1);
    QTextStream in2(&file2);
    QTextStream out(&outputFile);

    // Example processing: simply concatenating the contents of the two input files
    out << in1.readAll();
    out << in2.readAll();

    file1.close();
    file2.close();
    outputFile.close();

    QMessageBox::information(this, "Success", "Files processed successfully");
}
