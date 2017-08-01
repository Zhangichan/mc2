/*
 * 修改人：何亚梅
 * 修改了ui里面的内容
 * 重新设定了物理原点，解决文字定位问题
 * 修改了页码的显示问题
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include<QToolButton>
#include<QMessageBox>
#include <QVBoxLayout>
#include<quazip5/JlCompress.h>
#include<QFileDialog>
#include<QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textEdit = new PagesTextEdit(this);
    QTextDocument* doc = new QTextDocument;
    doc->setDefaultFont(QFont("Courier", 10));
    textEdit->setDocument(doc);
    setPageSize();//设置默认TextEdit大小
    setCentralWidget (textEdit);

    createToolBars();//创建部分工具栏
    createStatusBar();//创建状态栏

    instantiationFontStyle();//初始化FontStyle
    instantiationParagraphSettings();//初始化ParagraphSettings
    instantiationPaperSize();//初始化PaperSize
    instantiationOfdFrame();//初始化OfdFrame
    instantiationPictureAndSheet();//初始化PictureAndSheet
    instantiationFrameAnalysis();//初始化FrameAnalysis

    basicConnectFunction();
}
MainWindow::~MainWindow()
{
    delete ui;
}
//设置默认TextEdit大小
void MainWindow::setPageSize()
{
    textEdit->setPageFormat(QPageSize::A4);
    textEdit->setPageMargins(QMarginsF(20, 20, 20, 20));
    textEdit->setUsePageMode(true);
    textEdit->setPageNumbersAlignment(Qt::AlignTop | Qt::AlignHCenter);
}
//显示页码
void MainWindow::setPageNumber()
{
        textEdit->setShowPageNumbers(true);

}
//初始化FontStyle
void MainWindow::instantiationFontStyle()
{
    fontstyle = new FontStyle;
    fontstyle->text = textEdit;
    fontstyle->color = ui->action_color;
    fontstyle->fontbox = pFontBox;
    fontstyle->sizebox = pSizeBox;
    fontstyle->bold = ui->action_bold;
    fontstyle->italics = ui->action_italics;
    fontstyle->underline = ui->action_underline;
    fontstyle->strickout = ui->action_strickout;
    fontstyle->online = ui->action_online;
    fontstyle->superscript = ui->action_superscript;
    fontstyle->subscript = ui->action_subscript;
    fontstyle->changFontStyle();
}
//初始化ParagraphSettings
void MainWindow::instantiationParagraphSettings()
{
    paragraphsettings = new ParagraphSettings;
    paragraphsettings->text3 = textEdit;
    paragraphsettings->justifyLeft = ui->action_justifyLeft;
    paragraphsettings->justifyRight = ui->action_justifyRight;
    paragraphsettings->justifyCenter = ui->action_justifyCenter;
    paragraphsettings->justifyFull = ui->action_justifyFull;
    paragraphsettings->line1_0C = ui->action1_0_C;
    paragraphsettings->line1_5C = ui->action1_5_C;
    paragraphsettings->line2C = ui->action2_C;
    paragraphsettings->changeAlign();
    paragraphsettings->changeLineSpacing();
}
//初始化PaperSize
void MainWindow::instantiationPaperSize()
{
    papersize = new PaperSize;
    papersize->text2 = textEdit;
    papersize->acA1 = ui->action_A1;
    papersize->acA2 = ui->action_A2;
    papersize->acA3 = ui->action_A3;
    papersize->acA4 = ui->action_A4;
    papersize->acA5 = ui->action_A5;
    papersize->acA6 = ui->action_A6;
    papersize->changePageSize();
}
//初始化OfdFrame
void MainWindow::instantiationOfdFrame()
{
    ofdframe = new OfdFrame;
    ofdframe->text1 = textEdit;
}
//初始化PictureAndSheet
void MainWindow::instantiationPictureAndSheet()
{
    picandsheet = new PictureAndSheet;
    picandsheet->text4 = textEdit;
    picandsheet->pic = ui->action_images;
    picandsheet->drawTable = ui->action_drawTable;
    picandsheet->beginInsertPicture();
    picandsheet->beginInsertTable();
}
//初始化FrameAnalysis
void MainWindow::instantiationFrameAnalysis()
{
    frameanalysis = new FrameAnalysis;
    frameanalysis->text5 = textEdit;
}
//创建部分工具栏
void MainWindow::createToolBars()
{
    QToolButton *toolBtn = new QToolButton(this);
    toolBtn->addAction(ui->action_drawTable);
    toolBtn->setIcon(QIcon(":/images/insert-table.svg"));
    QMenu *insertTable = new QMenu(this);
    insertTable->addAction(ui->action_drawTable);
    toolBtn->setMenu(insertTable);
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolBar->addWidget(toolBtn);

    //添加工具栏设置字体
    QLabel * pLabel1;
    pLabel1 = new QLabel( tr( "字体:" ) );
    pFontBox = new QFontComboBox();
    pFontBox->setFontFilters( QFontComboBox::ScalableFonts );
    ui->toolBar_2->addWidget( pLabel1 );
    ui->toolBar_2->addWidget( pFontBox );

    //添加工具栏设置字体大小
    QLabel * pLabel2;
    pLabel2 = new QLabel( tr( "字号:" ) );
    pSizeBox = new QComboBox();
    ui->toolBar_2->addWidget( pLabel2 );
    ui->toolBar_2->addWidget( pSizeBox );
    QFontDatabase db;
    foreach( int nSize, db.standardSizes() )
    pSizeBox->addItem( QString::number( nSize ) );


    //添加工具栏字体加粗、斜体、下划线、删除线、上划线、居左、居中、居右、两端对齐
    ui->toolBar_2->addAction(ui->action_bold);
    ui->toolBar_2->addAction(ui->action_italics);
    ui->toolBar_2->addAction(ui->action_underline);
    ui->toolBar_2->addAction(ui->action_strickout);
    ui->toolBar_2->addAction(ui->action_online);
    ui->toolBar_2->addSeparator();
    ui->toolBar_2->addAction(ui->action_superscript);
    ui->toolBar_2->addAction(ui->action_subscript);
    ui->toolBar_2->addSeparator();

    ui->toolBar_2->addAction(ui->action_justifyLeft);
    ui->toolBar_2->addAction(ui->action_justifyCenter);
    ui->toolBar_2->addAction(ui->action_justifyRight);
    ui->toolBar_2->addAction(ui->action_justifyFull);
    ui->toolBar_2->addSeparator();
    //添加工具栏改变行距
    QToolButton *toolBtn3 = new QToolButton(this);
    toolBtn3->addAction(ui->action_lineSpacing);
    toolBtn3->setIcon(QIcon(":/images/text_line_spacing.svg"));
    QMenu *lineSpacingMenu = new QMenu(this);
    lineSpacingMenu->addAction(ui->action1_0_C);  //gaigaigaigaigaigaigaigaigaigaigai
                                                  //增加action1_0_C
    lineSpacingMenu->addAction(ui->action1_5_C);
    lineSpacingMenu->addAction(ui->action2_C);
    toolBtn3->setMenu(lineSpacingMenu);
    toolBtn3->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolBar_2->addWidget(toolBtn3);
}
//设置当前文本的文件名
void MainWindow::setCurrentFile(const QString &fileName)
{
    currentName = fileName;
    textEdit->document()->setModified(false);
    this->setWindowModified(false);
    QString shownName = currentName;
    if (currentName.isEmpty())
        shownName = "untitled.ofd";
    setWindowTitle (shownName);
}
//判断当前文本是否保存
bool MainWindow::maybeSave()
{
    if(textEdit->document()->isModified())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this,
                                   "warning","the document has been modified,Do you want to save your change",QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel
                                   );
        if(ret == QMessageBox::Save)
            return slotSave();
        if(ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}
//压缩文件
bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
    {
        QMessageBox::critical(this,
                              "critical",
                              "cannot write file"
                              );
        return false;
    }
    else
    {
        setCurrentFile(fileName);
        JlCompress::compressDir(fileName,"./ofd",true);//压缩
        return true;
    }
}
//解压文件
void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::critical(this,
                              "critical",
                              "cannot read file"
                              );
        return;
    }
    else
    {
        //清空编辑器
        textEdit->clear();
        JlCompress::extractDir(fileName,"./ofd");//解压
        frameanalysis->parsingContentXml();//解析Content.xml
        setCurrentFile(fileName);
    }
}
//新建文本的槽
void MainWindow::slotNew()
{
    if(textEdit->document()->isEmpty())
    {
        textEdit->clear();
        setCurrentFile("");
    }
    else{
        if(maybeSave())
        {
            textEdit->clear();
            setCurrentFile("");
        }
    }
}
//打开文本的槽
void MainWindow::slotOpen()
{
    if(textEdit->document()->isEmpty())
    {
        QString fileName = QFileDialog::getOpenFileName(this);
        if(!fileName.isEmpty())
            loadFile(fileName);
    }
    else{
        if(maybeSave())
        {
            QString fileName = QFileDialog::getOpenFileName(this);
            if(!fileName.isEmpty())
                textEdit->clear();
            loadFile(fileName);
        }
    }
}
//保存文本的槽
bool MainWindow::slotSave()
{
    if(currentName.isEmpty())
        return slotSaveAs();
    else
        return saveFile(currentName);
}
//另存为文本的槽
bool MainWindow::slotSaveAs()
{
    QString fileName =QFileDialog::getSaveFileName(this);
    if(fileName.isEmpty())
        return false;
    else
        return saveFile(fileName);
}
//关闭文件的槽
void MainWindow::slotClose()
{
    if(maybeSave())
        textEdit->document()->clear();
    setCurrentFile("untitled.ofd");
}
//查找文本
void MainWindow::textFind()
{
    // 创建对话框
    QDialog *dlg = new QDialog(this);
    // 创建行编辑器
    lineEdit = new QLineEdit(dlg);
    // 创建按钮
    QPushButton *btn = new QPushButton(dlg);
    btn->setText(tr("查找"));
    // 关联信号与槽
    connect(btn,SIGNAL(clicked()),this,SLOT(findNext()));
    // 创建垂直布局管理器
    QVBoxLayout *layout = new QVBoxLayout;
    // 添加部件
    layout->addWidget(lineEdit);
    layout->addWidget(btn);
    // 在对话框中使用布局管理器
    dlg->setLayout(layout);
    dlg->show();
}
//查找下一个
void MainWindow::findNext()
{
    // 使用查找函数查找指定字符串，查找方式为向后查找
    QString string = lineEdit->text();
    bool isfind = textEdit->find(string, QTextDocument::FindBackward);

    // 如果查找成功，输出字符串所在行和列的编号
    if(isfind){
        qDebug() << tr("行号:%1 列号:%2")
                    .arg(textEdit->textCursor().blockNumber())
                    .arg(textEdit->textCursor().columnNumber());
    }
}
//撤销
void MainWindow::Undo()
{
    textEdit->undo();
}
//恢复
void MainWindow::Redo()
{
    textEdit->redo();
}
void MainWindow::about()
{
    QMessageBox::about(this, tr("About"),
                       tr("<h2> 开发小组：mc^2</h2>"
                          "<p>小组成员：张姿婵、何亚梅、陈诗"
                          "<p>来自：重庆师范大学"
                          "<p>开发环境操作系统：Chakra"
                          "<p>开发语言：C++ "
                          "<p>集成开发框架：Qt5.8 "));
}
void MainWindow::aboutOFD()
{
    QMessageBox::about(this, tr("About OFD Typesetting System"),
                       tr("<h2>OFD Typesetting System 1.0</h2>"
                          "<p>OFD 排版系统是一款现代化、易用的公文排版系统，可用于文字排版处理."
                          "<p>采用xml机制对文档内的数据进行描述，达到数据保存和呈现比较稳定的效果."));
}
//创建状态栏
void MainWindow::createStatusBar()
{
    lineLabel = new QLabel;
    lineLabel->setMinimumSize(400,15);

    QLabel *wordLabel=new QLabel(this);
    wordLabel->setMinimumSize(900,15);

    statusBar()->addWidget(lineLabel);
    statusBar()->addWidget(wordLabel);
    lineLabel->setText(tr("行：1,列：0"));
    connect(textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(currentLine()));
    wordLabel->setText(tr("行选择 插入"));

}
//显示行号和列号
void MainWindow::currentLine()
{

    const QTextCursor cursor = textEdit->textCursor();//当前光标位置
    int RowNum = textEdit->document()->blockCount();

    int ColNum = cursor.columnNumber();

    lineLabel->setText(tr("行：%1,列：%2").arg(RowNum).arg(ColNum));
}
//信号与槽的连接
void MainWindow::basicConnectFunction()
{
    //连接新建的信号与槽
    connect(ui->action_new,SIGNAL(triggered()),this,SLOT(slotNew()));
    //连接打开的信号与槽
    connect(ui->action_open,SIGNAL(triggered()),this,SLOT(slotOpen()));
    //OFD框架的创建---------------------------------------------------------
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(slotOnText()));
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(slotWriteDocPhysicalBoxToXml()));
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(slotWriteDocMaxUnitIDToXml()));
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(slotWriteContentPhysicalBoxToXml()));
    connect(ui->action_saveAs,SIGNAL(triggered()),this,SLOT(slotOnText()));
    //---------------------------------------------------------------------
    //连接保存的信号与槽
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(slotSave()));
    //连接另存的信号与槽
    connect(ui->action_saveAs,SIGNAL(triggered()),this,SLOT(slotSaveAs()));
    //连接关闭的信号与槽
    connect(ui->action_close,SIGNAL(triggered()),this,SLOT(slotClose()));
    //连接退出的信号与槽
    connect(ui->action_exit,SIGNAL(triggered()),qApp,SLOT(quit()));
    //连接撤销的信号与槽
    connect(ui->action_undo,SIGNAL(triggered()),this,SLOT(Undo()));
    //连接恢复的信号与槽
    connect(ui->action_redo,SIGNAL(triggered()),this,SLOT(Redo()));
    //连接复制的信号与槽
    connect(ui->action_copy, SIGNAL(triggered()), textEdit, SLOT(copy()));
    //连接剪切的信号与槽
    connect(ui->action_cut, SIGNAL(triggered()),textEdit, SLOT(cut()));
    //连接粘贴的信号与槽
    connect(ui->action_paste, SIGNAL(triggered()),textEdit, SLOT(paste()));
    //连接查找的信号与槽
    connect(ui->action_find, SIGNAL(triggered()), this, SLOT(textFind()));
    //连接显示页码的信号和槽
    connect(ui->action_pageNumber_2, SIGNAL(triggered()), this, SLOT(setPageNumber()));
    //连接about的信号与槽
    connect(ui->action_about, SIGNAL(triggered()), this, SLOT(about()));
    //连接about的信号与槽
    connect(ui->action_aboutOFD, SIGNAL(triggered()), this, SLOT(aboutOFD()));
}
//创建OFD的四个槽函数(调用类OfdFrame的成员函数)------------------------
void MainWindow::slotOnText()
{
    ofdframe->onText();
}
void MainWindow::slotWriteDocPhysicalBoxToXml()
{
    ofdframe->writeDocPhysicalBoxToXml();
}
void MainWindow::slotWriteDocMaxUnitIDToXml()
{
    ofdframe->writeDocMaxUnitIDToXml();
}
void MainWindow::slotWriteContentPhysicalBoxToXml()
{
    ofdframe->writeContentPhysicalBoxToXml();
}
//---------------------------------------------------------------

