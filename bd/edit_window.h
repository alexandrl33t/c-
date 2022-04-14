#ifndef EDIT_WINDOW_H
#define EDIT_WINDOW_H
#include "login.h"
#include <QDialog>

namespace Ui {
class edit_window;
}

class edit_window : public QDialog
{
    Q_OBJECT

public:
    explicit edit_window(QWidget *parent = nullptr);
    ~edit_window();
     login* log;
       QString table;
       QString key;
     Ui::edit_window *ui;
          void loadData(QString,QString);
private slots:


     void on_update_button_clicked();

private:

};

#endif // EDIT_WINDOW_H
