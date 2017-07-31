#include "widget.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSplitter>
#include <QScrollArea>
#include "QMainWindow"


Widget::Widget(QWidget *parent) : QWidget(parent)
{
    textEdit = new PagesTextEdit;
    QMainWindow *window = new QMainWindow;
    QVBoxLayout *layout = new QVBoxLayout(this);
//    PagesTextEdit w;
    QTextDocument* doc = new QTextDocument;
    doc->setDefaultFont(QFont("Courier", 12));
    textEdit->setDocument(doc);

    setPageSize();

//    textEdit->resize(600, 400);
//    textEdit->show();
    layout->addWidget(textEdit);
    window->setLayout(layout);

//    textEdit = new QTextEdit;
//    textEdit_2 = new QTextEdit;
////    QMainWindow *window = new QMainWindow;
//    widget1 = new QWidget(this);
//    QVBoxLayout *layout = new QVBoxLayout(this);
//    QSplitter *splitterMain = new QSplitter(Qt::Vertical, 0);
//    textEdit = new QTextEdit(splitterMain);
//    textEdit->setAlignment(Qt::AlignCenter);
//    textEdit_2 = new QTextEdit(splitterMain);
//    textEdit_2->setAlignment(Qt::AlignCenter);

//    textEdit->setGeometry(120,100,500,500);
//    textEdit_2->setGeometry(120,700,1024,1096);

////    QList<int> list;
////    list << 400;//设置接收窗口的像素值
////    list << 0;  //设置第二个窗口的像素值
////    splitterMain->setSizes(list);

//    layout->addWidget(textEdit_2);
//    layout->addWidget(textEdit);
////    window->setLayout(layout);
//    widget1->setLayout(layout);


}

void Widget::setPageSize()
{

    textEdit->setPageFormat(QPageSize::A4);
    textEdit->setPageMargins(QMarginsF(20, 20, 20, 20));
    textEdit->setUsePageMode(true);
    textEdit->setPageNumbersAlignment(Qt::AlignTop | Qt::AlignHCenter);


}

