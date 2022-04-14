#include "model.h"
#include <QColor>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
Model::Model(QObject *parent):QAbstractTableModel(parent)
{

}

int Model::columnCount(const QModelIndex &parent) const
{
    return cCount;
}

int Model::rowCount(const QModelIndex &parent) const
{
    return _students.size();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch (index.column()) {
        case cId:
            return _students[index.row()].id;
        case cFio:
            return _students[index.row()].fio;
        case cCourse:
            return _students[index.row()].course;
        }
    }
    /*if (role == Qt::ToolTipRole)
    {
        switch (index.column()) {
        case cId:
            return QString("Student: ")+_students[index.row()].fio;
        }
    }*/

    return QVariant();
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            switch (section) {
            case cId:
                return "ID";
            case cFio:
                return "FIO";
            case cCourse:
                return "COURSE";
            }
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

bool Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch (index.column()) {
        case cId:
              _students[index.row()].id = value.toInt();
        break;
        case cFio:
            _students[index.row()].fio = value.toString();
        break;
        case cCourse:
            _students[index.row()].course = value.toInt();
        break;
    }
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags Model::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

void Model::addStudent(int id, const QString &fio, int course)
{
    beginInsertRows(QModelIndex(),_students.size(),_students.size());
    Student stud;
    stud.id = id;
    stud.fio = fio;
    stud.course = course;
    _students.append(stud);
    endInsertRows();
}

void Model::removeStudent(int row)
{
    beginRemoveRows(QModelIndex(),row,row);
    _students.removeAt(row);
    endRemoveRows();
}

void Model::editStudent(int row, int id, const QString &fio, int course)
{
    Student stud;
    stud.id = id;
    stud.fio = fio;
    stud.course = course;
    _students[row] = stud;
    emit dataChanged(index(row, cId), index(row, cFio));
}

QString Model::serializeXML()
{
    QDomDocument document;
    QDomElement root = document.createElement("StudentDataBase");

    document.appendChild(root);

    for(Student s: _students)
    {
        QDomElement studentNode = document.createElement("Student");
        studentNode.setAttribute("course", s.course);
        studentNode.setAttribute("id", s.id);
        QDomElement fioNode = document.createElement("FIO");
        fioNode.appendChild(document.createTextNode(s.fio));
        studentNode.appendChild(fioNode);


        root.appendChild(studentNode);
    }

    return document.toString();
}

void Model::deserializeXML(const QString &xml)
{
    beginResetModel();
    _students.clear();

    QDomDocument document;
    if(!document.setContent(xml))
        return;

    QDomElement root = document.firstChildElement("StudentDataBase");

    QDomElement studentNode = root.firstChildElement("Student");

    while (!studentNode.isNull()){
        Student s;

        s.id = studentNode.attributeNode("id").value().toInt();
        s.course = studentNode.attributeNode("course").value().toInt();

        QDomElement fioNode = studentNode.firstChildElement("FIO");
        s.fio = fioNode.firstChild().nodeValue();

        _students.append(s);
        studentNode = studentNode.nextSiblingElement("Student");
    }
    endResetModel();
}
