#include "papersize.h"

PaperSize::PaperSize(QWidget *parent):QWidget(parent)
{
}
//A1纸张
void PaperSize::A1()
{
    text2->setPageFormat(QPageSize::A1);
    text2->setPageMargins(QMarginsF(20.0, 20.0, 20.0, 20.0));
}
//A2纸张
void PaperSize::A2()
{
    text2->setPageFormat(QPageSize::A2);
    text2->setPageMargins(QMarginsF(20.0, 20.0, 20.0, 20.0));
}
//A3纸张
void PaperSize::A3()
{
    text2->setPageFormat(QPageSize::A3);
    text2->setPageMargins(QMarginsF(20.0, 20.0, 20.0, 20.0));
}
//A4纸张
void PaperSize::A4()
{
    text2->setPageFormat(QPageSize::A4);
    text2->setPageMargins(QMarginsF(20.0, 20.0, 20.0, 20.0));
}
//A5纸张
void PaperSize::A5()
{
    text2->setPageFormat(QPageSize::A5);
    text2->setPageMargins(QMarginsF(20.0, 20.0, 20.0, 20.0));
}
//A6纸张
void PaperSize::A6()
{
    text2->setPageFormat(QPageSize::A6);
    text2->setPageMargins(QMarginsF(20.0, 20.0, 20.0, 20.0));
}
//纸张大小的信号与槽连接
void PaperSize::changePageSize()
{
    connect(acA1,SIGNAL(triggered()),this,SLOT(A1()));
    connect(acA2,SIGNAL(triggered()),this,SLOT(A2()));
    connect(acA3,SIGNAL(triggered()),this,SLOT(A3()));
    connect(acA4,SIGNAL(triggered()),this,SLOT(A4()));
    connect(acA5,SIGNAL(triggered()),this,SLOT(A5()));
    connect(acA6,SIGNAL(triggered()),this,SLOT(A6()));
}
