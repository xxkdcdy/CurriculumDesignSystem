#ifndef CHART_H
#define CHART_H

#include <QtCharts>
#include <QWidget>
#include <QDebug>
#include "student.h"
#include "design.h"
#include <QSqlQuery>

class chart : public QWidget{
    Q_OBJECT
public:
    chart() {}
    chart(QWidget* parent);
    QWidget* getWidget() {return this->widget;}
    void allStudents();     //查询所有学生信息
    void allDesigns();      //查询所有课题信息
    void vitalByTopic();    //按照课题选择统计
    void vitalByClass();    //按照班级统计
    void vitalByScore();    //按照分数统计

protected:
    int getStuMessage(Student **& stu);    //获取当前学生信息
    int getDesMessage(design**& des);     //获取当前课题信息
private:
    QChartView * chartView;
    QWidget* widget;
    QPieSeries * series;
    QChart * myChart;

    //数据处理部分
    Student** stu;
    int stuNumber;
    design** des;
    int desNumber;
};

#endif // CHART_H
