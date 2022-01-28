/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QMessageBox>


QSqlQuery query;
QSqlDatabase db;
QSqlQueryModel*model;



//增加
void addStudent(const QString sno, const QString sname, const QString sex, int age,const QString myclass,
                 const QString major, const QString topic, int score)
{
    QString insert_buf;
    QSqlQuery query;
    insert_buf=QObject::tr("insert into student values('%1','%2','%3',%4,'%5','%6','%7',%8)")
            .arg(sno,sname,sex,QString::number(age),myclass,major,topic,QString::number(score));
    query.exec(insert_buf);
    qDebug() << insert_buf;
}

void addStudent_without_score(const QString sno, const QString sname, const QString sex, int age,const QString myclass,
                 const QString major, const QString topic)
{
    QString insert_buf;
    QSqlQuery query;
    insert_buf=QObject::tr("insert into student(sno,sname,sex,age,class,major,topic) values('%1','%2','%3',%4,'%5','%6','%7')")
            .arg(sno,sname,sex,QString::number(age),myclass,major,topic);
    query.exec(insert_buf);
    qDebug() << insert_buf;
}

void addStudent_without_score_topic(const QString sno, const QString sname, const QString sex, int age,const QString myclass,
                 const QString major)
{
    QString insert_buf;
    QSqlQuery query;
    insert_buf=QObject::tr("insert into student(sno,sname,sex,age,class,major) values('%1','%2','%3',%4,'%5','%6')")
            .arg(sno,sname,sex,QString::number(age),myclass,major);
    query.exec(insert_buf);
    qDebug() << insert_buf;
}

void addDesign(const QString id,const QString dname,const QString keyword,
               const QString tec, int number, const QString teacher){
    QString insert_buf;
    QSqlQuery query;
    insert_buf=QObject::tr("insert into design values('%1','%2','%3','%4',%5,'%6')")
            .arg(id,dname,keyword,tec,QString::number(number),teacher);
    query.exec(insert_buf);
    qDebug() << insert_buf;
}

//删除
bool deleteStudent(QString sno)
{
    QString delete_buf;
    QSqlQuery query;
    delete_buf=QObject::tr("DELETE FROM student WHERE sno='%1'").arg(sno);
    qDebug() << delete_buf;
    if(query.exec(delete_buf))
        return true;
    else
        return false;

}

void deleteDesign(QString id)
{
    QString delete_buf;
    QSqlQuery query;
    delete_buf=QObject::tr("DELETE FROM student WHERE topic='%1'").arg(id);
    query.exec(delete_buf);
    delete_buf=QObject::tr("DELETE FROM design WHERE id='%1'").arg(id);
    query.exec(delete_buf);
    qDebug() << delete_buf;
}

//查询
bool selectStudentBySno(QString sno){
    query.exec(QObject::tr("select * from student where sno = '%1'").arg(sno));
    if(query.next())
        return true;
    else
        return false;
}

bool selectDesignById(QString id){
    query.exec(QObject::tr("select * from design where id = '%1'").arg(id));
    if(query.next())
        return true;
    else
        return false;
}

#endif
