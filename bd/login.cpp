#include "login.h"
#include "ui_login.h"
#include <QTableView>
#include <QSqlQueryModel>


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit->setText("LAPTOP-A4B6INCK\\SQLEXPRESS");
    ui->lineEdit_3->setText("myBD");
    ui->lineEdit_4->setText("alexandr");
    mes = new QMessageBox();
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER="+ui->lineEdit->text()+";DATABASE="+ui->lineEdit_3->text()+";");
    db.setUserName(ui->lineEdit_4->text());
    db.setPassword(ui->lineEdit_2->text());

    if(db.open())
    {
        this->hide();
        mes->setText("Connected");
    } else mes->setText("Not Connected. Please, try again.");
    mes->show();
}

/*QSqlQueryModel* tableModel = new QSqlQueryModel();
tableModel->setQuery(*query);
ui->tableView->setModel(tableModel);*/
