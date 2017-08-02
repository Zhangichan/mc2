#ifndef PAPERSIZE_H
#define PAPERSIZE_H
#include<QtWidgets>
#include "PagesTextEdit.h"

class PaperSize:public QWidget
{
     Q_OBJECT
public:
    PaperSize(QWidget *parent = 0);
    PagesTextEdit *text2;
    QAction *acA1;
    QAction *acA2;
    QAction *acA3;
    QAction *acA4;
    QAction *acA5;
    QAction *acA6;
public:
    void changePageSize();//纸张大小的信号与槽连接
private slots:
    void A1();//A1纸张
    void A2();//A2纸张
    void A3();//A3纸张
    void A4();//A4纸张
    void A5();//A5纸张
    void A6();//A6纸张
};

#endif // PAPERSIZE_H
