#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "chart.h"

using namespace std;

class file : protected chart
{
public:
    file();
    bool writeStuMessage();   //导出学生文件
    bool writeDesMessage();   //导出课题文件
    bool readStuMessage();    //导入学生文件
    bool readDesMessage();    //导入课题文件
};

#endif // FILE_H
