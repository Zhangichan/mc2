#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontComboBox>
#include "PagesTextEdit.h"
#include "fontstyle.h"
#include "paragraphsettings.h"
#include "papersize.h"
#include "ofdframe.h"
#include "pictureandsheet.h"
#include "frameanalysis.h"
class QLabel;
class QFontComboBox;
class QComboBox;
class FontStyle;
class ParagraphSettings;
class PaperSize;
class OfdFrame;
class PictureAndSheet;
class FrameAnalysis;
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     Ui::MainWindow *ui;

private:
    //显示中心部件
    PagesTextEdit *textEdit;
    FontStyle *fontstyle;
    ParagraphSettings *paragraphsettings;
    PaperSize *papersize;
    OfdFrame *ofdframe;
    PictureAndSheet *picandsheet;
    FrameAnalysis *frameanalysis;
    //字体编辑框
    QFontComboBox * pFontBox;
    //字体大小编辑框
    QComboBox * pSizeBox;

    //查找功能的行编辑器
    QLineEdit *lineEdit;
    //状态栏的标签
    QLabel *lineLabel;

    void setPageSize();//设置默认的TextEdit的大小
    void instantiationFontStyle();//初始化FontStyle;
    void instantiationParagraphSettings();//初始化ParagraphSettings
    void instantiationPaperSize();//初始化PaperSize
    void instantiationOfdFrame();//初始化OfdFrame
    void instantiationPictureAndSheet();//初始化PictureAndSheet
    void instantiationFrameAnalysis();//初始化FrameAnalysis
    void createToolBars();  //创建工具栏
    void createStatusBar(); //创建状态栏
    void basicConnectFunction();//连接文件基本功能的信号和槽

    QString currentName;  //当前文本的文件名
    void setCurrentFile(const QString &);  //设置当前文本的文件名
    bool maybeSave();     //判断当前文本是否保存
    bool saveFile(const QString &);  //压缩文件
    void loadFile(const QString &);  //解压文件

private slots:
    void slotNew();       //新建文本的槽
    void slotOpen();      //打开文本的槽
    bool slotSave();      //保存文本的槽
    bool slotSaveAs();    //另存为文本的槽
    void slotClose();     //关闭文件的槽
    void textFind(); //查找文本
    void findNext(); //查找下一个
    void Undo();  //撤销
    void Redo();  //恢复
    void setPageNumber();//显示页码
    void about();//关于开发人员的信息
    void aboutOFD();//关于OFD
    void currentLine();   //显示行号和列号（用于状态栏显示）
    //创建OFD的四个槽函数------------------------
    void slotOnText();
    void slotWriteDocPhysicalBoxToXml();
    void slotWriteDocMaxUnitIDToXml();
    void slotWriteContentPhysicalBoxToXml();
    //----------------------------------------
};

#endif // MAINWINDOW_H
