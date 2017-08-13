#ifndef PARAGRAPHSETTINGS_H
#define PARAGRAPHSETTINGS_H
#include<QtWidgets>
#include "PagesTextEdit.h"

class ParagraphSettings:public QWidget
{
    Q_OBJECT
public:
    ParagraphSettings(QWidget *parent = 0);
    PagesTextEdit *text3;
    QActionGroup *grp;
    QAction *justifyLeft;
    QAction *justifyRight;
    QAction *justifyCenter;
    QAction *justifyFull;
    QAction *line1_0C;
    QAction *line1_5C;
    QAction *line2C;
    QAction *indentM;
    QAction *indentL;
public:
    void changeAlign();//对齐的信号与槽连接
    void changeLineSpacing();//行距的信号与槽连接
    void changeIndent();//缩进方式的信号与槽连接
private slots:
    void align(QAction *);//对齐方式
    void cursorPositionChanged();//光标所在段落的对其方式，设置相应的对齐按钮为按下状态
    void lineSpacing1_0();//单倍行距
    void lineSpacing1_5();//1.5倍行距
    void lineSpacing2_0();//2倍行距
    void indentMore();//增大缩进
    void indentLess();//减少缩进
private:
    void lineSpacing(double);//行距
};

#endif // PARAGRAPHSETTINGS_H
