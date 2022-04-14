#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    logwin = new login();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    logwin->show();
}




void MainWindow::on_received_table_clicked()
{
    if(logwin->db.isOpen())
    {
     QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery* query = new QSqlQuery(logwin->db);
    query->prepare("exec select_from_received");
    query->exec();
    model->setQuery(*query);
    ui->tableView->setModel(model);
    logwin->isReceivedOpen = true;
    logwin->isWasteOpen = false;
    logwin->isExpensesOpen = false;
    logwin->isWorkersOpen = false;
    } else
    {
        logwin->mes->setText("BD is not connected");
        logwin->mes->show();
    }
}

void MainWindow::on_waste_table_clicked()
{
    if(logwin->db.isOpen())
    {
     QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery* query = new QSqlQuery(logwin->db);
    query->prepare("exec select_from_waste");
    query->exec();
    model->setQuery(*query);
    ui->tableView->setModel(model);
    logwin->isReceivedOpen = false;
    logwin->isWasteOpen = true;
    logwin->isExpensesOpen = false;
    logwin->isWorkersOpen = false;
    } else
    {
        logwin->mes->setText("BD is not connected");
        logwin->mes->show();
    }
}


void MainWindow::on_expenses_table_clicked()
{
    if(logwin->db.isOpen())
    {
     QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery* query = new QSqlQuery(logwin->db);
    query->prepare("exec select_from_total_expenses");
    query->exec();
    model->setQuery(*query);
    ui->tableView->setModel(model);
    logwin->isReceivedOpen = false;
    logwin->isWasteOpen = false;
    logwin->isExpensesOpen = true;
    logwin->isWorkersOpen = false;
    } else
    {
        logwin->mes->setText("BD is not connected");
        logwin->mes->show();
    }
}

void MainWindow::on_workers_table_clicked()
{
    if(logwin->db.isOpen())
    {
     QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery* query = new QSqlQuery(logwin->db);
    query->prepare("exec select_from_workers");
    query->exec();
    model->setQuery(*query);
    ui->tableView->setModel(model);
    logwin->isReceivedOpen = false;
    logwin->isWasteOpen = false;
    logwin->isExpensesOpen = false;
    logwin->isWorkersOpen = true;
    } else
    {
        logwin->mes->setText("BD is not connected");
        logwin->mes->show();
    }
}

void MainWindow::on_add_to_table_clicked()
{
    if(logwin->isReceivedOpen)
    {
        received = new addToReceived();
        received->show();
    } else if (logwin->isWasteOpen)
    {
       waste = new addToWaste();
       waste->show();
    }  else if (logwin->isWorkersOpen)
    {
       workers = new addtoworkers();
       workers->show();
    } else if (logwin->isExpensesOpen)
    {
        logwin->mes->setText("You can't add an entry to this table");
        logwin->mes->show();
    } else {
        logwin->mes->setText("BD is not connected or Table is not chosen");
        logwin->mes->show();
    }
}

void MainWindow::on_edit_button_clicked()
{
    QString currentTable = "";
    edit = new edit_window();
    QSqlQuery* query = new QSqlQuery(logwin->db);
        QString key ="";
    int currentIndex = ui->tableView->currentIndex().row()+1;
    if(currentIndex > 0)
    {
            if(logwin->isReceivedOpen)
            {
                currentTable = "received";
            } else if(logwin->isWasteOpen)
            {
              currentTable = "waste";
              edit->ui->lineEdit->hide();
              edit->ui->lineEdit_4->hide();
            } else if(logwin->isExpensesOpen)
            {
                currentTable="total_expenses";
                edit->ui->lineEdit->hide();
                edit->ui->lineEdit_2->hide();
                edit->ui->lineEdit_3->hide();
                edit->ui->lineEdit_4->hide();
            } else if (logwin->isWorkersOpen) {
                currentTable="workers";
                edit->ui->lineEdit->hide();
            }
        //заполнение правого lable значениями выделенной строки
        query->prepare("exec select_from_"+currentTable);
        query->exec();
        for (int i = 0;i<currentIndex;i++)
        {
            query->next();
        }
        key = query->value(0).toString();
         QSqlQuery* query2 = new QSqlQuery(logwin->db);
         query2->exec("exec column_size @table_name='"+currentTable+"'");
         query2->next();
         int c_size = query2->value(0).toInt();
         switch (c_size)
        {
         case 3:
             edit->ui->lineEdit_4->hide();
             break;
          case 2:
            edit->ui->lineEdit_4->hide();
            edit->ui->lineEdit_3->hide();
            break;
        }

        QString lable2="";
         for (int i = 0;i<c_size;i++)
        {
            lable2.append( query->value(i).toString() + "\n" + "\n");
            edit->ui->label_2->setFont(QFont( "Helvetica", 13) );
            edit->ui->label_2->setText(lable2);
        }
         //заполнение названий столбиков в левый label
        query->next();
        QString test="";
        query->prepare("exec list_table @table_name = '"+currentTable+"'");
        query->exec();
        while (query->next())
        test.append( query->value(0).toString() + "\n" + "\n");
        edit->ui->label->setFont(QFont( "Helvetica", 13) );
        edit->ui->label->setText(test);
       if(currentTable!="total_expenses")
       edit->show();
       else if (currentTable=="total_expenses")
           {
               logwin->mes->setText("This Table cant be changed");
               logwin->mes->show();
           }
    }
    else {
        logwin->mes->setText("The string is not chosen");
        logwin->mes->show();
    }
    edit->loadData(currentTable, key);
}




void MainWindow::on_delete_from_table_clicked()
{
    del = new are_u_sure();
    QString currentTable = "";
    QSqlQuery* query = new QSqlQuery(logwin->db);
        QString key ="";
    int currentIndex = ui->tableView->currentIndex().row()+1;

    if(currentIndex > 0)
    {
            if(logwin->isReceivedOpen)
            {
                currentTable = "received";
            } else if(logwin->isWasteOpen)
            {
              currentTable = "waste";

            } else if(logwin->isExpensesOpen)
            {
                currentTable="total_expenses";

            } else if (logwin->isWorkersOpen) {
                currentTable="workers";
            }

    query->prepare("exec select_from_"+currentTable);
    query->exec();
    for (int i = 0;i<currentIndex;i++)
        {
            query->next();
        }

     key = query->value(0).toString();
     del->getData(currentTable, key);
       del->show();
    } else {
        logwin->mes->setText("The string is not chosen");
        logwin->mes->show();
    }
}

void MainWindow::on_pushButton_clicked()
{
     QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery* query = new QSqlQuery(logwin->db);
    query->prepare("exec case_received");
    query->exec();
    model->setQuery(*query);
    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
   QSqlQuery* query = new QSqlQuery(logwin->db);
   query->prepare("exec view_all");
   query->exec();
   model->setQuery(*query);
   ui->tableView->setModel(model);
   query->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
   QSqlQuery* query = new QSqlQuery(logwin->db);
   query->prepare("exec select_waste_cor");
   query->exec();
   model->setQuery(*query);
   ui->tableView->setModel(model);
   query->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
   QSqlQuery* query = new QSqlQuery(logwin->db);
   query->prepare("exec select_received_cor");
   query->exec();
   model->setQuery(*query);
   ui->tableView->setModel(model);
   query->clear();
}

void MainWindow::on_pushButton_5_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
   QSqlQuery* query = new QSqlQuery(logwin->db);
   query->prepare("exec from_nonecorel");
   query->exec();
   model->setQuery(*query);
   ui->tableView->setModel(model);
   query->clear();
}


void MainWindow::on_pushButton_6_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
   QSqlQuery* query = new QSqlQuery(logwin->db);
   query->prepare("exec select_noncor");
   query->exec();
   model->setQuery(*query);
   ui->tableView->setModel(model);
   query->clear();
}

void MainWindow::on_pushButton_7_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
   QSqlQuery* query = new QSqlQuery(logwin->db);
   query->prepare("exec where_notcor");
   query->exec();
   model->setQuery(*query);
   ui->tableView->setModel(model);
   query->clear();
}
