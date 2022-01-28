#include "mysqltablemodel.h"

MySqlTableModel::MySqlTableModel(QObject *parent, QSqlDatabase db) :
    QSqlRelationalTableModel(parent, db)
{

}

QString MySqlTableModel::selectStatement() const
{
    //返回需要显示的字段和设置字段顺序
    return "select * from student limit 1 offset 3;";
}
