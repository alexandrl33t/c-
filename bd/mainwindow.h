#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "ui_login.h"
#include "addtowaste.h"
#include "ui_addtowaste.h"
#include "addtoworkers.h"
#include "ui_addtoworkers.h"
#include "addtoreceived.h"
#include "ui_addtoreceived.h"
#include "edit_window.h"
#include "ui_edit_window.h"
#include "are_u_sure.h"
#include "ui_are_u_sure.h"
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    addToWaste* waste;
    addtoworkers* workers;
    addToReceived* received;
    login* logwin;
    edit_window* edit;
    are_u_sure* del;
private slots:
    void on_action_triggered();

    void on_received_table_clicked();

    void on_waste_table_clicked();


    void on_workers_table_clicked();
    void on_add_to_table_clicked();

    void on_expenses_table_clicked();

    void on_edit_button_clicked();

    void on_delete_from_table_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
