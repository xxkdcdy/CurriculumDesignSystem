#include "chart.h"


chart::chart(QWidget* parent) : QWidget(parent){

    //图表设计
    series = new QPieSeries();
    series->append("Jane", 1);
    series->append("Joe", 2);
    series->append("Andy", 3);
    series->append("Barbara", 4);
    series->append("Axel", 5);
    //![1]

    //![2]
    QPieSlice *slice = series->slices().at(1);
    slice->setLabelVisible();
    //![2]

    //![3]
    myChart = new QChart();
    myChart->addSeries(series);
    myChart->setTitle("尚未初始化  请从菜单栏选择项目进行数据显示");
    myChart->legend()->hide();
    //![3]

    //![4]
    chartView = new QChartView(myChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //布局设计
    widget = new QWidget;
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(chartView,0,0);

    widget->setLayout(gridLayout);
}



void chart::allStudents(){
    QVector<Student*> list;
    Student* stu;
    stuNumber = 0;
    QSqlQuery query;
    query.exec("select * from student");
    while(query.next()){
        stu = new Student;
        stu->setSno(query.value(0).toString());
        stu->setName(query.value(1).toString());
        stu->setSex(query.value(2).toString());
        stu->setAge(query.value(3).toInt());
        stu->setMyclass(query.value(4).toString());
        stu->setMajor(query.value(5).toString());
        stu->setTopic(query.value(6).toString());
        stu->setScore(query.value(7).toInt());
        qDebug() << stu->getAge() << stu->getSno() << stu->getScore();
        list.append(stu);
        stuNumber++;
    }
    this->stu = new Student*[this->stuNumber];
    for(int i = 0; i < this->stuNumber; i++){
        this->stu[i] = list.front();
        list.pop_front();
        qDebug() << this->stu[i]->getAge() << this->stu[i]->getSno() << this->stu[i]->getScore();
    }
}

void chart::allDesigns(){
    QVector<design*> list;
    design* tmp;
    desNumber = 0;
    QSqlQuery query;
    query.exec("select * from design");
    while(query.next()){
        tmp = new design;
        tmp->setId(query.value(0).toString());
        tmp->setDname(query.value(1).toString());
        tmp->setKeyword(query.value(2).toString());
        tmp->setTec(query.value(3).toString());
        tmp->setNumber(query.value(4).toInt());
        tmp->setTeacher(query.value(5).toString());
        qDebug() << tmp->getNumber() << tmp->getId() << tmp->getDname();
        list.append(tmp);
        desNumber++;
    }
    this->des = new design*[this->desNumber];
    for(int i = 0; i < this->desNumber; i++){
        this->des[i] = list.front();
        list.pop_front();
        qDebug() << this->des[i]->getNumber() << this->des[i]->getId() << this->des[i]->getDname();
    }
}

void chart::vitalByTopic(){
    this->allDesigns();
    this->allStudents();
    //数量统计
    int* stuNum = new int[this->desNumber];
    for(int i = 0; i < this->desNumber; i++) stuNum[i] = 0; //初始化
    for(int i = 0; i < this->stuNumber; i++){
        for(int j = 0; j < this->desNumber; j++){
            if(stu[i]->getTopic() == des[j]->getId()){
                stuNum[j]++;
                break;
            }
        }
    }

    //设置图表
    series = new QPieSeries();
    for(int i = 0; i < this->desNumber; i++){
        series->append(QObject::tr("%1   %2").arg(des[i]->getDname()).arg(QString::number(stuNum[i])),stuNum[i]);
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
        qDebug() << stuNum[i];
    }

    myChart->setTitle("按课题统计");
    myChart->removeAllSeries();
    myChart->addSeries(series);
}

void chart::vitalByClass(){
    this->allDesigns();
    this->allStudents();
    //数据准备
    int classNum = this->stuNumber;
    QString allClass[this->stuNumber];
    for(int i = 0 ; i < this->stuNumber; i++){
        allClass[i] = stu[i]->getMyclass();    //初始化数组
    }
    for(int i = 0; i < this->stuNumber; i++){
        for(int j = i + 1; j < classNum; j++){
            if(allClass[i] == allClass[j]){
                classNum--;
                for(int k = j; k < classNum; k++)
                    allClass[k] = allClass[k+1];
            }
        }
    }

    //数量统计
    int* stuNumByClass = new int[classNum];
    for(int i = 0; i < classNum; i++) stuNumByClass[i] = 0; //初始化
    for(int i = 0; i < this->stuNumber; i++){
        for(int j = 0; j < classNum; j++){
            if(stu[i]->getMyclass() == allClass[j]){
                stuNumByClass[j]++;
                break;
            }
        }
    }

    //设置图表
    series = new QPieSeries();
    for(int i = 0; i < classNum; i++){
        series->append(QObject::tr("%1   %2").arg(allClass[i]).arg(QString::number(stuNumByClass[i])),stuNumByClass[i]);
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
    }

    myChart->setTitle("按班级统计");
    myChart->removeAllSeries();
    myChart->addSeries(series);
}

void chart::vitalByScore(){
    this->allDesigns();
    this->allStudents();
    //数据准备
    int scoreNum = this->stuNumber;
    int allScore[this->stuNumber];
    for(int i = 0 ; i < this->stuNumber; i++){
        allScore[i] = stu[i]->getScore();    //初始化数组
    }
    for(int i = 0; i < this->stuNumber; i++){
        for(int j = i + 1; j < scoreNum; j++){
            if(allScore[i] == allScore[j]){
                scoreNum--;
                for(int k = j; k < scoreNum; k++)
                    allScore[k] = allScore[k+1];
            }
        }
    }

    //数量统计
    int* stuNumByScore = new int[scoreNum];
    for(int i = 0; i < scoreNum; i++) stuNumByScore[i] = 0; //初始化
    for(int i = 0; i < this->stuNumber; i++){
        for(int j = 0; j < scoreNum; j++){
            if(stu[i]->getScore() == allScore[j]){
                stuNumByScore[j]++;
                break;
            }
        }
    }

    //设置图表
    series = new QPieSeries();
    for(int i = 0; i < scoreNum; i++){
        series->append(QObject::tr("%1   %2").arg(QString::number(allScore[i])).arg(QString::number(stuNumByScore[i])),stuNumByScore[i]);
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
    }

    myChart->setTitle("按成绩统计");
    myChart->removeAllSeries();
    myChart->addSeries(series);
}

//获取当前课程和课题信息，用于传值
int chart::getStuMessage(Student **&stu){
    this->allStudents();
    this->allDesigns();

    stu = this->stu;
    return this->stuNumber;
}

int chart::getDesMessage(design **&des){
    this->allStudents();
    this->allDesigns();

    des = this->des;
    return this->desNumber;
}
