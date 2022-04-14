#include "edit_window.h"
#include "ui_edit_window.h"

edit_window::edit_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit_window)
{
    ui->setupUi(this);
    log=new login();
}

edit_window::~edit_window()
{
    delete ui;
}

void edit_window::on_update_button_clicked()
{
    QSqlQuery* query = new QSqlQuery(log->db);
    QString firstLine=ui->lineEdit->text(), secondLine=ui->lineEdit_2->text(), thirdLine=ui->lineEdit_3->text(),fourthLine=ui->lineEdit_4->text();

    if (table == "received")
    {
        query->prepare("exec update_received @key='"+key+"', @firstLine='"+firstLine+"', @secondLine="+secondLine+", @thirdLine = '"+thirdLine+"', @fourthLine="+fourthLine);
    }  else if (table == "waste")
    {
        query->prepare("exec update_waste @key='"+key+"', @secondLine="+secondLine+", @thirdLine = "+thirdLine);
    } else if (table == "workers")
    {
        query->prepare("exec update_workers @key="+key+", @secondLine='"+secondLine+"', @thirdLine = '"+thirdLine+"', @fourthLine="+fourthLine);
    }

     if (query->exec())
     {
         log->mes->setText("Updated!");
         log->mes->show();
     } else
     {
         log->mes->setText("Something is wrong :(");
         log->mes->show();
      }
     this->hide();
}

void edit_window::loadData(QString _currentTable,QString _key)
{
    table = _currentTable;
    key=_key;
}
