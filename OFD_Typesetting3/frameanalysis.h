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
};

#endif // FRAMEANALYSIS_H
