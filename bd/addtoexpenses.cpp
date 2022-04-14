#include "addtoexpenses.h"
#include "ui_addtoexpenses.h"

addtoexpenses::addtoexpenses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addtoexpenses)
{
    ui->setupUi(this);
    log = new login();
    QSqlQuery* query = new QSqlQuery(log->db);
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQueryModel *model2 = new QSqlQueryModel();
    query->prepare("exec select_workers_from_workers");
    query->exec();
    model->setQuery(*query);
    ui->comboBox->setModel(model);
    query->next();
    query->prepare("exec select_product_from_waste");
    query->exec();
    model2->setQuery(*query);
    ui->comboBox_2->setModel(model2);
}

addtoexpenses::~addtoexpenses()
{
    delete ui;
}


void addtoexpenses::on_pushButton_clicked()
{
    QString who_sold = ui->comboBox->currentText(), product_name = ui->comboBox_2->currentText();
    QSqlQuery* query = new QSqlQuery(log->db);
    query->prepare("exec add_to_expenses @who_sold = "+who_sold+", @product_name = "+product_name);
    if (query->exec())
    {
        log->mes->setText("OK! Data has been saved");
        log->mes->show();
        this->hide();
    } else {
        log->mes->setText("Error... Try again");
        log->mes->show();
    }
    qDebug() << query->lastError();
}
