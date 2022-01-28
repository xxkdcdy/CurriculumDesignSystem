#include "file.h"


file::file()
{
}

bool file::writeStuMessage(){
    QFile outFile("studata.csv");
    if(!outFile.open(QFile::WriteOnly | QFile::Text))
        return false;

    //写行标题信息
    QString data;
    data = "学号,姓名,性别,年龄,班级,专业,题目,分数\n";
    outFile.write(data.toLocal8Bit());
    Student** stu;
    int stuNum = this->getStuMessage(stu);
    for(int i = 0; i < stuNum; i++){
        data = stu[i]->toString();
        outFile.write(data.toLocal8Bit());
    }
    outFile.close();
    return true;
}

bool file::writeDesMessage(){
    QFile outFile("desdata.csv");
    if(!outFile.open(QFile::WriteOnly | QFile::Text))
        return false;

    //写行标题信息
    QString data;
    data = "编号,课题,关键词,使用技术,人员数,指导教师\n";
    outFile.write(data.toLocal8Bit());
    design** des;
    int desNum = this->getDesMessage(des);
    for(int i = 0; i < desNum; i++){
        data = des[i]->toString();
        outFile.write(data.toLocal8Bit());
    }
    outFile.close();
    return true;
}

bool file::readStuMessage(){
    QFile inFile("studata_r.csv");
    QSqlQuery query;
    if(!inFile.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream stream(&inFile);
    QStringList csvList;
    csvList.clear();
    while (!stream.atEnd())
        csvList.push_back(stream.readLine()); //保存到List当中
    inFile.close();
    int i = 0;
        Q_FOREACH(QString str, csvList)   //遍历List
        {
            i = i + 1;
            QStringList valsplit = str.split(","); //分隔字符串
            if(i > 1)
                {
                    QString sno = valsplit[0];
                    QString name = valsplit[1];
                    QString sex = valsplit[2];
                    QString age = valsplit[3];
                    QString myclass = valsplit[4];
                    QString major = valsplit[5];
                    QString topic = valsplit[6];
                    QString score = valsplit[7];
                    qDebug() << sno;
                    sno = sno.left(sno.length()-2);
                    sno = sno.right(sno.length()-1);
                    qDebug() << sno;
                    query.exec(QObject::tr("insert into student values('%1','%2','%3',%4,'%5','%6','%7',%8)")
                               .arg(sno,name,sex,age,myclass,major,topic,score));
                }
        }
        return true;
}

bool file::readDesMessage(){
    QFile inFile("desdata_r.csv");
    QSqlQuery query;
    if(!inFile.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream stream(&inFile);
    QStringList csvList;
    csvList.clear();
    while (!stream.atEnd())
        csvList.push_back(stream.readLine()); //保存到List当中
    inFile.close();
    int i = 0;
        Q_FOREACH(QString str, csvList)   //遍历List
        {
            i = i + 1;
            QStringList valsplit = str.split(","); //分隔字符串
            if(i > 1)
                {
                    QString id = valsplit[0];
                    QString dname = valsplit[1];
                    QString keyword = valsplit[2];
                    QString tec = valsplit[3];
                    QString number = valsplit[4];
                    QString teacher = valsplit[5];
                    query.exec(QObject::tr("insert into design values('%1','%2','%3','%4',%5,'%6')")
                               .arg(id,dname,keyword,tec,number,teacher));
                }
        }
        return true;
}
