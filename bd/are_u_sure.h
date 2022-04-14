#ifndef ARE_U_SURE_H
#define ARE_U_SURE_H
#include "login.h"
#include <QDialog>

namespace Ui {
class are_u_sure;
}

class are_u_sure : public QDialog
{
    Q_OBJECT

public:
    explicit are_u_sure(QWidget *parent = nullptr);
    ~are_u_sure();
      QString table;
      QString key;
    void getData(QString,QString);
    login* log;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::are_u_sure *ui;
};

#endif // ARE_U_SURE_H
