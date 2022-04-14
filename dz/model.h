#ifndef MODEL_H
#define MODEL_H
#include <QAbstractTableModel>

struct Student {
  int id;
  QString fio;
  int course;
};

class Model:public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Columns {
        cId,
        cFio,
        cCourse,
        cCount
    };

    Model(QObject * parent = nullptr);

    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

     bool setData(const QModelIndex &index,
                          const QVariant &value,
                          int role = Qt::EditRole);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    void addStudent(int id, const QString &fio, int course);
    void removeStudent(int row);
    void editStudent(int row, int id, const QString &fio, int course);

    QString serializeXML();
    void deserializeXML(const QString &xml);
private:
    QList<Student> _students;
};

#endif // MODEL_H
