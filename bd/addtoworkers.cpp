#include "addtoworkers.h"
#include "ui_addtoworkers.h"

addtoworkers::addtoworkers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addtoworkers)
{
    ui->setupUi(this);
    log = new login();
}

addtoworkers::~addtoworkers()
{
    delete ui;
}

void addtoworkers::on_pushButton_clicked()
{
    QSqlQuery* query = new QSqlQuery(log->db);
    QString name=ui->lineEdit->text(),spec=ui->lineEdit_2->text(),
            salary = ui->lineEdit_3->text();
    query->prepare("exec insert_into_workers @w_name = '"+name+"', @specialization = '"+spec+"', @salary = "+salary);
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
