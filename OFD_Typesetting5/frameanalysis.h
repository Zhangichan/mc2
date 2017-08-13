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
     QString x;
     qreal xmm;
     QString y;
     QString yBefore;
     QString variableY;
     bool judge = true;
};

#endif // FRAMEANALYSIS_H
