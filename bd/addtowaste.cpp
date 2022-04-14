#include "addtowaste.h"
#include "ui_addtowaste.h"

addToWaste::addToWaste(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addToWaste)
{
    ui->setupUi(this);
    log = new login();
    QSqlQuery* query = new QSqlQuery(log->db);
    QSqlQueryModel *model = new QSqlQueryModel();
    query->prepare("exec select_product_from_received");
    query->exec();
    model->setQuery(*query);
    ui->comboBox->setModel(model);
    query->next();
    QSqlQueryModel *model2 = new QSqlQueryModel();
    query->prepare("exec select_workers_from_workers");
    query->exec();
    model2->setQuery(*query);
    ui->comboBox_2->setModel(model2);
}

addToWaste::~addToWaste()
{
    delete ui;
}



void addToWaste::on_add_to_waste_clicked()
{
    QString name = ui->comboBox->currentText(),
            ammount = ui->lineEdit->text(),
            worker = ui->comboBox_2->currentText();
    QSqlQuery* query = new QSqlQuery(log->db);
    query->prepare("exec add_to_sold30 @p_name = '"+name+"', @ammount = "+ammount+", @worker = '"+worker+"'");
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
