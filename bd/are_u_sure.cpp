#include "are_u_sure.h"
#include "ui_are_u_sure.h"

are_u_sure::are_u_sure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::are_u_sure)
{
    ui->setupUi(this);
    log = new login();

}

are_u_sure::~are_u_sure()
{
    delete ui;
}

void are_u_sure::getData(QString _currentTable, QString _key)
{
    table = _currentTable;
    key = _key;
}

void are_u_sure::on_pushButton_2_clicked()
{
    this->hide();
}

void are_u_sure::on_pushButton_clicked()
{
     QSqlQuery* query = new QSqlQuery(log->db);

      if(table=="received")
      {
          query->prepare("exec delete_from_received @key='"+key+"'");
      } else if(table=="waste")
      {
          query->prepare("exec delete_from_waste @key='"+key+"'");
      } else if(table=="total_expenses")
      {
          query->prepare("exec delete_from_expenses @key="+key);
      } else if(table=="workers")
      {
          query->prepare("exec delete_from_workers @key='"+key+"'");
      }

      if (query->exec())
      {
          log->mes->setText("The Note has been deleted");
          log->mes->show();
      } else
      {
          log->mes->setText("Something is wrong :(");
          log->mes->show();
      }
      this->hide();
}
