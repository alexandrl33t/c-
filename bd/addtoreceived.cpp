#include "addtoreceived.h"
#include "ui_addtoreceived.h"
#include <QtSql>

addToReceived::addToReceived(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addToReceived)
{
    ui->setupUi(this);
    log = new login();
}

addToReceived::~addToReceived()
{
    delete ui;
}

void addToReceived::on_add_received_clicked()
{

    QSqlQuery* query = new QSqlQuery(log->db);
    QString name=ui->lineEdit->text(),supplier=ui->lineEdit_3->text(),
            ammount = ui->lineEdit_2->text(), price=ui->lineEdit_4->text();
    query->prepare("exec add_to_received @p_name = '"+name+"', @ammount = "+ammount+", @supplier = '"+supplier+"', @price = "+price);
   if (query->exec())
   {
       log->mes->setText("OK! Data has been saved");
       log->mes->show();

       this->hide();
   } else {
       log->mes->setText("Error... Try again");
       log->mes->show();
   }
}
