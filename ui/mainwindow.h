//
// Created by user on 11.07.2024.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
            void on_browseFile1Button_clicked();
    void on_browseFile2Button_clicked();
    void on_browseOutputButton_clicked();
    void on_processButton_clicked();

private:
    Ui::MainWindow *ui;
    QString file1Path;
    QString file2Path;
    QString outputPath;
};

#endif // MAINWINDOW_H
