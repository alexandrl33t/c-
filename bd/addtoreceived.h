#ifndef ADDTORECEIVED_H
#define ADDTORECEIVED_H

#include <QDialog>
#include "login.h"

namespace Ui {
class addToReceived;
}

class addToReceived : public QDialog
{
    Q_OBJECT

public:
    explicit addToReceived(QWidget *parent = nullptr);
    ~addToReceived();
    login* log;

private slots:
    void on_add_received_clicked();

private:
    Ui::addToReceived *ui;
};

#endif // ADDTORECEIVED_H
