#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QSqlQuery>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    QMessageBox* mes;
    QSqlDatabase db;
    QSqlQuery *query;
    bool isReceivedOpen = false;
    bool isWasteOpen = false;
    bool isExpensesOpen = false;
    bool isWorkersOpen = false;
private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
