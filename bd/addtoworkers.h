#ifndef ADDTOWORKERS_H
#define ADDTOWORKERS_H
#include "login.h"
#include <QDialog>

namespace Ui {
class addtoworkers;
}

class addtoworkers : public QDialog
{
    Q_OBJECT

public:
    explicit addtoworkers(QWidget *parent = nullptr);
    ~addtoworkers();
    login* log;
private slots:
    void on_pushButton_clicked();

private:
    Ui::addtoworkers *ui;
};

#endif // ADDTOWORKERS_H
