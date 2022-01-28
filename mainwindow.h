#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquerymodel.h>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include "chart.h"
#include "file.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();     //建立数据库连接
    void createSql(QString name);    //创建数据库
    void show_view(QString name);    //显示数据
    QString getCurrentIndex();            //获取主键信息
    int getTabIndex() {return this->tabIndex;}  //获取当前显示的tab

private slots:

    void on_action_2_triggered();

    void on_studentTabWidget_currentChanged(int index);

    void on_pushButton_addStudent_clicked();

    void on_pushButton_deleteStudent_clicked();

    void on_pushButton_deleteDesign_clicked();

    void on_pushButton_addDesign_clicked();

    void on_add_Student_clicked();

    void on_add_Design_clicked();

    void on_Select_by_sno_clicked();

    void on_Select_by_id_clicked();

    void on_Select_by_name_clicked();

    void on_Select_by_dname_clicked();

    void on_Clear_student_clicked();

    void on_Clear_design_clicked();

    void on_alter_Student_clicked();

    void on_alter_Design_clicked();

    void on_action_4_triggered();

    void on_action_triggered();

    void on_action_3_triggered();

    void on_vital_Class_tab_triggered();

    void on_vital_Score_Tab_triggered();

    void on_add_File_stu_triggered();

    void on_add_File_des_triggered();

    void on_action_7_triggered();

    void on_action_8_triggered();

    void on_nextPage_student_clicked();

    void on_lastPage_student_clicked();

private:
    Ui::MainWindow *ui;    //ui设计师界面设计
    QSqlRelationalTableModel* relation;   //数据库关系模型
    int tabIndex;  //记录tab的序号
    chart* c;      //图表类，用于统计
    file* f;       //文件类，用于文件读写

    int pageCur;   //页码
    int recordNum; //每行显示的个数
};

#endif // MAINWINDOW_H
