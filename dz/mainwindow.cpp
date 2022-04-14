#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QFileDialog>

#include<QXmlStreamWriter>
#include<QXmlStreamReader>

#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _model = new Model(this);


    ui->tableView->setModel(_model);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addStudent_triggered()
{
       _model->addStudent(1, "uknown", 0);
}

void MainWindow::on_removeStudent_triggered()
{
    _model->removeStudent(ui->tableView->currentIndex().row());
}

void MainWindow::on_editStudent_triggered()
{

}

void MainWindow::on_pushButton_clicked()
{
    _model->editStudent(ui->tableView->currentIndex().row(), 3,
                        "Ivanov Sergey Petrovich", 4);
}

void MainWindow::on_saveXML_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "select file");
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return;



    QByteArray data;

    data = _model->serializeXML().toLatin1();

    file.write(data);
    file.close();
}

void MainWindow::on_readXML_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "select file");
    if(fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QByteArray data = file.readAll();


    _model->deserializeXML(QString(data));

    file.close();
}
