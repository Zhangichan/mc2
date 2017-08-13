#ifndef FONTSTYLE_H
#define FONTSTYLE_H
#include "PagesTextEdit.h"
#include<QtWidgets>
#include<QComboBox>
class FontStyle:public QWidget
{
    Q_OBJECT
public:
    FontStyle(QWidget *parent = 0);
    PagesTextEdit *text;
    QAction *color;
    QFontComboBox *fontbox;
    QComboBox *sizebox;
    QAction *bold;
    QAction *italics;
    QAction *underline;
    QAction *strickout;
    QAction *online;
    QAction *superscript;
    QAction *subscript;
public:
    void changFontStyle();//字体样式的信号与槽连接
public slots:
    void fontColor();//字体颜色
    void font(QString f);//字体
    void fontSize(QString num);//字体大小
    void fontBold();//字体加粗
    void fontItalic();//字体设为斜体
    void fontUnderline();//字体设置下划线
    void fontStrikeout();//字体设置删除线
    void fontOverline();//字体设置上划线
    void fontSuperscript();//字体设置为上标
    void fontSubscript();//字体设置为下标
private:
    void mergeFormat( QTextCharFormat);//使格式作用于选区内的字符，若没有选区则作用于光标所在处的字符
};

#endif // FONTSTYLE_H
