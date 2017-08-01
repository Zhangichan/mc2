#ifndef PICTUREANDSHEET_H
#define PICTUREANDSHEET_H
#include<QtWidgets>
#include "PagesTextEdit.h"

class PictureAndSheet:public QWidget
{
    Q_OBJECT
public:
    PictureAndSheet(QWidget *parent = 0);
    PagesTextEdit *text4;
    QAction *pic;
    QAction *drawTable;
public:
    void beginInsertPicture();//连接插入图片的信号与槽
    void beginInsertTable();//连接插入表格的信号与槽
private:
    //表格对话框
    QDialog *tabledlg;
    //表的行和列
    int tableRows = 1;
    int tableLines = 1;
private slots:
    void insertPicture();//插入图片
    void drawTableWidget();//绘制表格的一个窗口显示
    void setCurrentRows(int rows);//设置所要绘制的表的行数
    void setCurrentLines(int lines);//设置所要绘制的表的列数
    void beginDrawTable();//绘画表格到文本编辑器上
    void closeTableDlg();//关闭表格对话框

};

#endif // PICTUREANDSHEET_H
