#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addStudent_triggered();

    void on_removeStudent_triggered();

    void on_editStudent_triggered();

    void on_pushButton_clicked();

    void on_saveXML_triggered();

    void on_readXML_triggered();

private:
    Model * _model;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
