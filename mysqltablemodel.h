#ifndef MYSQLTABLEMODEL_H
#define MYSQLTABLEMODEL_H

#include <QSqlRelationalTableModel>

class MySqlTableModel: public QSqlRelationalTableModel
{
public:
    MySqlTableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());

protected:
    QString selectStatement() const;
};

#endif // MYSQLTABLEMODEL_H
