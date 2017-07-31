#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextFormat>
#include "widget.h"

class QTextFragment;
class QLabel;
class QComboBox;

namespace Ui {
class MainWindow;
}

class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createOfdXml();
    void createOfdStructure();


private:
    Ui::MainWindow *ui;

    //显示中心部件
    Widget *widget;


    void createToolBars();  //创建工具栏
    void connectFunction();   //链接函数
    void createFileDir(QString);   //创建文件目录


    QString currentName = "untitled.ofd";  //当前文本的文件名
    bool maybeSave();     //判断当前文本是否保存
    void setCurrentFile(const QString &);  //设置当前文本的文件名
    bool saveFile(const QString &);  //保存文本
    void loadFile(const QString &);  //打开文本
    void mergeFormat( QTextCharFormat);//使格式作用于选区内的字符，若没有选区则作用于光标所在处的字符

    QLineEdit *lineEdit;

    //改改改改改改改改改改改改改改改改改改改改改改改改改改改改
    //表格对话框
    QDialog *tabledlg;
    //表的行和列
    int tableRows = 1;
    int tableLines = 1;

    void processTextContent(QTextFragment, QTextCharFormat);  //处理文本内容
    void writeTextToXml(QString,QTextCharFormat,int);
    void writeTextToPublicResXml(QTextCharFormat);
    void writeImageToContent(/*QString,*/QTextImageFormat);
    void writeResToDocument();
    void processImageFragment(QTextImageFormat);
    void createContentXml();
    void createPublicResXml();
    void createDocumentRes();
    bool deleteDir(const QString &);
    //000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    bool DelDir(const QString&);

    void createDocument();
    void parsingPageSize();//解析页面大小
    void parsingContentXml();//解析Content.xml
    void nextContent();

    void paging();
    void addDoucumentPart();
    void addMediasToRes(QString, QString);

    QLabel *lineLabel;
    QLabel *wordLabel;
    void createStatusBar();   //显示行和列
    void changePage();

    PageMetrics m_pageMetrics;
    bool compare = false;
    //000000000000000000000000000000000000000000000000000000000000000000000000000000
    bool flag = true;
    void lineSpacing(double);  //gaigaigaigaigaigaigaigaigaigaigaigaigaigai
//    QString boundary(QString , QTextCharFormat );  //gaigaigaigaigaigaigaigaigaigaigai



private slots:
    void textFind(); //查找文本
    void findNext(); //查找下一个
    void slotFont(QString f );  //字体
    void slotSize(QString num );   //字号
    void slotCurrentFormatChanged(const QTextCharFormat & fmt );   //当前格式改变
    void Undo();  //撤销
    void Redo();  //恢复
    void slotBold();   //加粗
    void slotUnderline();   //下划线
    void slotStrikeout();   //删除线
    void slotOverline();    //
    void slotSuperscript();  //上标
    void slotSubscript();  //下标
    void slotItalic();    //斜体
    void setFontColor();    //字体颜色
    void slotAlign(QAction *);   //排列、匹配
    void slotCursorPositionChanged();   //鼠标位置改变
     bool onText();        //文本处理

    void slotNew();       //新建文本的槽
    void slotOpen();      //打开文本的槽

    void slotClose();

    bool slotSave();      //保存文本的槽
    bool slotSaveAs();    //另存为文本的槽
    void insertImage();   //插入图片

    void currentLine();   //显示行号和列号
    void about();
    void aboutOFD();
    void slotA1();
    void slotA2();
    void slotA3();
    void slotA4();
    void slotA5();
    void slotA6();
    void writeDocPhysicalBoxToXml();
    void writeDocMaxUnitIDToXml();
    void writeContentPhysicalBoxToXml();
    void slotPageNumber();

    //绘制表格对话框
    void slotDrawTableWidgt();
    //设置所要绘制的表的行数和列数
    void slotSetCurrentRows(int rows);
    void slotSetCurrentLines(int lines);
    //开始绘画表格
    void slotBeginDrawTable();
    //关闭表格对话框
    void slotCloseTableDlg();

    void lineSpacing1_0();  //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
    void lineSpacing1_5();  //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
    void lineSpacing2_0();  //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
};

#endif // MAINWINDOW_H
