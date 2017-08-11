#ifndef FRAMEANALYSIS_H
#define FRAMEANALYSIS_H
#include "PagesTextEdit.h"

class FrameAnalysis
{
public:
    FrameAnalysis();
    PagesTextEdit *text5;
public:
    void parsingContentXml();//解析Content.xml
private:
    void parsingPageSize();//解析页面大小
//    void parsingPicture();//解析图片资源
private:
    QString height;
    QString heightB;
    QString variable;
    bool judge = true;
};

#endif // FRAMEANALYSIS_H
