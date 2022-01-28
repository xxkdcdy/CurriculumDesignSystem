#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "initdb.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QColorDialog>
#include <QListWidget>
#include <QSqlRelationalDelegate>
#include <QtWidgets>
#include <QtCharts>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //on_studentTabWidget_currentChanged(0);
    tabIndex = 0;
    this->ui->studentTabWidget->removeTab(3);
    c = new chart(parent);
    f = new file();
    this->ui->studentTabWidget->addTab(c->getWidget(),QString("统计"));
    this->pageCur = 0;   //第一页
    this->recordNum = 5; // 每页显示3条记录
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_2_triggered()
{
    exit(0);
}



void MainWindow::on_studentTabWidget_currentChanged(int index)
{
    this->tabIndex = index;
    qDebug() << index;
    if(index == 0){
        this->createSql("student");
    }
    else if(index == 1){
        this->createSql("design");
    }
    else if(index == 3){
        c->vitalByTopic();
    }
}

void MainWindow::init(){
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( QString("CurriculumDesignSystem.db"));
    bool ok=db.open();
    if(ok)
       QMessageBox::information(this,"Information","open sucessfully");
    else
       QMessageBox::information(this,"Information","open fail");
    query = QSqlQuery(db);//连接数据库
}

void MainWindow::createSql(QString name){
    //创建数据库表
    bool query_OK = false;
    query.exec("PRAGMA foreign_keys = ON");
    query_OK= query.exec("create table design(id varchar primary key,dname varchar,keyword varchar,tec varchar,number int,teacher varchar)");
    if(query_OK)
    {
        qDebug()<< "create table success!";
    }
    else
    {
        qDebug()<< "create table fail!"  << db.lastError();
    }
    query_OK= query.exec("create table student(sno varchar primary key,sname varchar,sex varchar,age int,class varchar,major varchar,topic varchar,score int,FOREIGN KEY (topic) REFERENCES design(id))");
    if(query_OK)
    {
        qDebug()<< "create table success!";
    }
    else
    {
        qDebug()<< "create table fail!"  << db.lastError();
    }


    //创建关系
    if(name == "student"){
        //学生为主表
        this->relation = new QSqlRelationalTableModel(this);
        relation->setEditStrategy(QSqlTableModel::OnFieldChange);   //属性变化时写入数据库
        relation->setTable("student");
        relation->setRelation(6, QSqlRelation ( "design" , "id" , "dname" ));   //设置外码
        relation->select();
        relation->setHeaderData(0,Qt::Horizontal,tr("学号"));
        relation->setHeaderData(1,Qt::Horizontal,tr("姓名"));
        relation->setHeaderData(2,Qt::Horizontal,tr("性别"));
        relation->setHeaderData(3,Qt::Horizontal,tr("年龄"));
        relation->setHeaderData(4,Qt::Horizontal,tr("班级"));
        relation->setHeaderData(5,Qt::Horizontal,tr("专业"));
        relation->setHeaderData(6,Qt::Horizontal,tr("题目"));
        relation->setHeaderData(7,Qt::Horizontal,tr("分数"));
        this->ui->stuTable->setItemDelegate(new QSqlRelationalDelegate(ui->stuTable));
        ui->stuTable->setModel(relation);
    }
    if(name == "design"){
        //课设题目为主表
        this->relation = new QSqlRelationalTableModel(this);
        relation->setEditStrategy(QSqlTableModel::OnFieldChange);   //属性变化时写入数据库
        relation->setTable("design");
        relation->select();
        relation->setHeaderData(0,Qt::Horizontal,tr("编号"));
        relation->setHeaderData(1,Qt::Horizontal,tr("名称"));
        relation->setHeaderData(2,Qt::Horizontal,tr("关键词"));
        relation->setHeaderData(3,Qt::Horizontal,tr("实现技术"));
        relation->setHeaderData(4,Qt::Horizontal,tr("人员数"));
        relation->setHeaderData(5,Qt::Horizontal,tr("指导教师"));
        ui->courseTable->setModel(relation);
    }
}


//测试按钮
void MainWindow::on_pushButton_addStudent_clicked()
{
    addStudent("3180904019","cdy","male",20,"1902","software","1",90);
    addStudent("3180904016","wcs","male",20,"1902","software","1",90);
    addStudent("3180601001","lxg","Male",22,"1801","computer","1",92);
    addStudent("3180304567","dsy","Male",21,"1802","Internet","1",94);
    addStudent("3190200001","cdy","Male",21,"1902","software","1",94);
    addStudent("3190702074","yge","Female",24,"1903","communication","2",96);
    addStudent("3200501383","mbg","Female",19,"2001","communication","2",88);
    addStudent("31720010876","zsy","Female",23,"1704","calculation","3",99);
    addStudent("3190909898","lm","Female",20,"1903","software","3",98);
    addStudent("32010038630","lbw","Male",21,"2005","Internet","3",91);
    addStudent("3180803074","gz","Female",18,"1805","intelligence","4",100);
    this->relation->select();
}

void MainWindow::on_pushButton_addDesign_clicked()
{
    addDesign("1","随机测试","测试","ART",4,"hrb");
    addDesign("2","稻穗分割","分割","Kmeans",2,"lz");
    addDesign("3","学生管理系统","学生管理","J2EE",3,"ll");
    addDesign("4","网站建设","网站","HTML",1,"lh");
    this->relation->select();
}

QString MainWindow::getCurrentIndex(){
    int tmp;
    if(tabIndex == 0)
        tmp = this->ui->stuTable->currentIndex().row();
    else if(tabIndex == 1)
        tmp = this->ui->courseTable->currentIndex().row();
    QString name = this->relation->data(relation->index(tmp,0)).toString();
    if(name == "")
        QMessageBox::information(this,"Information","请指定行！");
    else
        return name;
}

void MainWindow::on_pushButton_deleteStudent_clicked()
{
    deleteStudent(this->getCurrentIndex());
    this->relation->select();
}

void MainWindow::on_pushButton_deleteDesign_clicked()
{
    deleteDesign(this->getCurrentIndex());
    this->relation->select();
}

void MainWindow::on_add_Student_clicked()
{
    //检查主键是否重复
    QString sno = this->ui->snoEdit->text();
    if(selectStudentBySno(sno)){
        QMessageBox::information(this,"Information","请注意学号唯一性！");
        return;
    }

    QString name = this->ui->nameEdit->text();
    QString sex = this->ui->sexEdit->currentText();
    QString age = this->ui->ageEdit->text();
    QString myclass = this->ui->classEdit->text();
    QString major = this->ui->majorEdit->text();
    QString topic = this->ui->topicEdit->text();
    QString score = this->ui->scoreEdit->text();
    //检查外码是否合适
    if(!selectDesignById(topic)){
        QMessageBox::information(this,"Information","请注意该课题编号不存在！");
        return;
    }

    if(sno != "" && name != "" && sex != "" && age != ""
            && myclass !="" && major !="" && topic != ""){
        if(score != ""){
            addStudent(sno,name,sex,age.toInt(),myclass,major,topic,score.toInt());
        }
        else if(score == ""){
            addStudent_without_score(sno,name,sex,age.toInt(),myclass,major,topic);
        }
        QMessageBox::information(this,"Information","添加成功！");
        c->vitalByTopic();
        }
    else{
        QMessageBox::information(this,"Information","请填写完整信息！");
    }
}

void MainWindow::on_add_Design_clicked()
{
    QString id = this->ui->idEdit->text();
    //检查主键是否重复
    if(selectDesignById(id)){
        QMessageBox::information(this,"Information","请注意编号唯一性！");
        return;
    }


    QString dname = this->ui->dnameEdit->text();
    QString keyword = this->ui->keywordEdit->text();
    QString tec = this->ui->tecEdit->text();
    QString number = this->ui->numberEdit->text();
    QString teacher = this->ui->teacherEdit->text();
    if(id != "" && dname != "" && keyword != "" && tec != "" && number != ""
            && teacher != ""){
        addDesign(id,dname,keyword,tec,number.toInt(),teacher);
        QMessageBox::information(this,"Information","添加成功！");
        c->vitalByTopic();
        }
    else{
        QMessageBox::information(this,"Information","请填写完整信息！");
    }
}

void MainWindow::on_Select_by_sno_clicked()
{
    QString sno = this->ui->snoEdit->text();
    query.exec(QObject::tr("select * from student where sno = '%1'").arg(sno));
    if(query.next()){
        this->ui->nameEdit->setText(query.value(1).toString());
        this->ui->sexEdit->setCurrentText(query.value(2).toString());
        this->ui->ageEdit->setValue(query.value(3).toInt());
        this->ui->classEdit->setText(query.value(4).toString());
        this->ui->majorEdit->setText(query.value(5).toString());
        this->ui->topicEdit->setText(query.value(6).toString());
        this->ui->scoreEdit->setText(query.value(7).toString());
    }
    else{
        QMessageBox::information(this,"Information","未查到相关信息！");
    }
}

void MainWindow::on_Select_by_name_clicked()
{
    QString name = this->ui->nameEdit->text();
    query.exec(QObject::tr("select * from student where sname = '%1'").arg(name));
    if(query.next()){
        this->ui->snoEdit->setText(query.value(0).toString());
        this->ui->sexEdit->setCurrentText(query.value(2).toString());
        this->ui->ageEdit->setValue(query.value(3).toInt());
        this->ui->classEdit->setText(query.value(4).toString());
        this->ui->majorEdit->setText(query.value(5).toString());
        this->ui->topicEdit->setText(query.value(6).toString());
        this->ui->scoreEdit->setText(query.value(7).toString());
    }
    else{
        QMessageBox::information(this,"Information","未查到相关信息！");
    }
}

void MainWindow::on_Clear_student_clicked()
{
    this->ui->snoEdit->setText("");
    this->ui->nameEdit->setText("");
    this->ui->sexEdit->setCurrentText("");
    this->ui->ageEdit->setValue(0);
    this->ui->classEdit->setText("");
    this->ui->majorEdit->setText("");
    this->ui->topicEdit->setText("");
    this->ui->scoreEdit->setText("");
}

void MainWindow::on_Select_by_id_clicked()
{
    QString id = this->ui->idEdit->text();
    query.exec(QObject::tr("select * from design where id = '%1'").arg(id));
    if(query.next()){
        this->ui->dnameEdit->setText(query.value(1).toString());
        this->ui->keywordEdit->setText(query.value(2).toString());
        this->ui->tecEdit->setText(query.value(3).toString());
        this->ui->numberEdit->setValue(query.value(4).toInt());
        this->ui->teacherEdit->setText(query.value(5).toString());
    }
    else{
        QMessageBox::information(this,"Information","未查到相关信息！");
    }
}



void MainWindow::on_Select_by_dname_clicked()
{
    QString dname = this->ui->dnameEdit->text();
    query.exec(QObject::tr("select * from design where dname = '%1'").arg(dname));
    if(query.next()){
        this->ui->idEdit->setText(query.value(0).toString());
        this->ui->keywordEdit->setText(query.value(2).toString());
        this->ui->tecEdit->setText(query.value(3).toString());
        this->ui->numberEdit->setValue(query.value(4).toInt());
        this->ui->teacherEdit->setText(query.value(5).toString());
    }
    else{
        QMessageBox::information(this,"Information","未查到相关信息！");
    }
}

void MainWindow::on_Clear_design_clicked()
{
    this->ui->idEdit->setText("");
    this->ui->dnameEdit->setText("");
    this->ui->keywordEdit->setText("");
    this->ui->tecEdit->setText("");
    this->ui->numberEdit->setValue(0);
    this->ui->teacherEdit->setText("");
}

void MainWindow::on_alter_Student_clicked()
{
    //检查主键，删除原先的记录
    QString sno = this->ui->snoEdit->text();
    if(!selectStudentBySno(sno)){
        QMessageBox::information(this,"Information","该学号不存在，无法修改！");
        return;
    }
    QString name = this->ui->nameEdit->text();
    QString sex = this->ui->sexEdit->currentText();
    QString age = this->ui->ageEdit->text();
    QString myclass = this->ui->classEdit->text();
    QString major = this->ui->majorEdit->text();
    QString topic = this->ui->topicEdit->text();
    QString score = this->ui->scoreEdit->text();
    //检查外码是否合适
    if(!selectDesignById(topic)){
        QMessageBox::information(this,"Information","请注意该课题编号不存在！");
        return;
    }

    if(sno != "" && name != "" && sex != "" && age != ""
            && myclass !="" && major !="" && topic != ""){
        if(score != ""){
            deleteStudent(sno);
            addStudent(sno,name,sex,age.toInt(),myclass,major,topic,score.toInt());
        }
        else if(score == ""){
            deleteStudent(sno);
            addStudent_without_score(sno,name,sex,age.toInt(),myclass,major,topic);
        }
        QMessageBox::information(this,"Information","修改成功！");
        c->vitalByTopic();
        }
    else{
        QMessageBox::information(this,"Information","请填写完整信息！");
    }
}

void MainWindow::on_alter_Design_clicked()
{
    QString id = this->ui->idEdit->text();
    //检查主键是否重复
    if(!selectDesignById(id)){
        QMessageBox::information(this,"Information","未找到编号，无法修改！");
        return;
    }


    QString dname = this->ui->dnameEdit->text();
    QString keyword = this->ui->keywordEdit->text();
    QString tec = this->ui->tecEdit->text();
    QString number = this->ui->numberEdit->text();
    QString teacher = this->ui->teacherEdit->text();
    if(id != "" && dname != "" && keyword != "" && tec != "" && number != ""
            && teacher != ""){
        deleteDesign(id);
        addDesign(id,dname,keyword,tec,number.toInt(),teacher);
        QMessageBox::information(this,"Information","修改成功！");
        c->vitalByTopic();
        }
    else{
        QMessageBox::information(this,"Information","请填写完整信息！");
    }
}

void MainWindow::on_action_4_triggered()
{
    c->vitalByTopic();
}

void MainWindow::on_action_triggered()
{
    query.exec("delete from student");
    relation->select();
    c->allStudents();
    c->allDesigns();
    c->vitalByTopic();
}

void MainWindow::on_action_3_triggered()
{
    on_action_triggered();
    query.exec("delete from design");
    relation->select();
    c->allStudents();
    c->allDesigns();
    c->vitalByTopic();
}

void MainWindow::on_vital_Class_tab_triggered()
{
    c->vitalByClass();
}

void MainWindow::on_vital_Score_Tab_triggered()
{
    c->vitalByScore();
}

void MainWindow::on_add_File_stu_triggered()
{
    if(f->writeStuMessage())
        QMessageBox::information(this,"Information","成功导出学生文件！");
    else
        QMessageBox::information(this,"Information","导出学生文件失败！");
}

void MainWindow::on_add_File_des_triggered()
{
    if(f->writeDesMessage())
        QMessageBox::information(this,"Information","成功导出课题文件！");
    else
        QMessageBox::information(this,"Information","导出课题文件失败！");
}

void MainWindow::on_action_7_triggered()
{
    if(f->readStuMessage())
        QMessageBox::information(this,"Information","成功导入学生文件！");
    else
        QMessageBox::information(this,"Information","导入学生文件失败！");
    relation->select();
}



void MainWindow::on_action_8_triggered()
{
    if(f->readDesMessage())
        QMessageBox::information(this,"Information","成功导入课题文件！");
    else
        QMessageBox::information(this,"Information","导入课题文件失败！");
    relation->select();
}

void MainWindow::on_nextPage_student_clicked()
{
    int num = 0;
    query.exec("select * from student");
    while(query.next()){
        num++;
    }
    int cur = num/this->recordNum;

    this->pageCur++;
    if(this->pageCur > cur){
        QMessageBox::information(this,"Information","最后一页！");
        this->pageCur--;
    }
    QSqlQueryModel* model;
    model = new QSqlQueryModel(this);
    //model->setQuery("select * from student limit 5,5");
    model->setQuery(QObject::tr("select * from student limit %1,%2")
                    .arg(QString::number(this->pageCur * this->recordNum),QString::number(this->recordNum)));

    ui->stuTable->setModel(model);
    ui->pageEdit->setText(QObject::tr("第%1页，共%2页").arg(QString::number(this->pageCur+1),QString::number(cur+1)));
}

void MainWindow::on_lastPage_student_clicked()
{
    int num = 0;
    query.exec("select * from student");
    while(query.next()){
        num++;
    }
    int cur = num/this->recordNum;

    this->pageCur--;
    if(this->pageCur < 0){
        QMessageBox::information(this,"Information","第一页！");
        this->pageCur++;
    }
    QSqlQueryModel* model;
    model = new QSqlQueryModel(this);
    //model->setQuery("select * from student limit 5,5");
    model->setQuery(QObject::tr("select * from student limit %1,%2")
                    .arg(QString::number(this->pageCur * this->recordNum),QString::number(this->recordNum)));


    ui->stuTable->setModel(model);
    ui->pageEdit->setText(QObject::tr("第%1页，共%2页").arg(QString::number(this->pageCur+1),QString::number(cur+1)));
}
