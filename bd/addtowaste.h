#ifndef ADDTOWASTE_H
#define ADDTOWASTE_H
#include "login.h"
#include <QDialog>

namespace Ui {
class addToWaste;
}

class addToWaste : public QDialog
{
    Q_OBJECT

public:
    explicit addToWaste(QWidget *parent = nullptr);
    ~addToWaste();
    login* log;
private slots:

    void on_add_to_waste_clicked();

private:
    Ui::addToWaste *ui;
};

#endif // ADDTOWASTE_H
