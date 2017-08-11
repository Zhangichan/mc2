#include "paragraphsettings.h"

ParagraphSettings::ParagraphSettings(QWidget *parent):QWidget(parent)
{
}
//对齐方式
void ParagraphSettings::align(QAction *act)
{
    if ( act == justifyLeft )
        text3->setAlignment( Qt::AlignLeft );

    if ( act == justifyCenter )
        text3->setAlignment( Qt::AlignCenter );

    if ( act == justifyFull )
        text3->setAlignment( Qt::AlignJustify );

    if ( act == justifyRight )
        text3->setAlignment( Qt::AlignRight );
}
//光标所在段落的对其方式，设置相应的对齐按钮为按下状态
void ParagraphSettings::cursorPositionChanged()
{
    if (text3->alignment() == Qt::AlignLeft)
        justifyLeft->setChecked(true);

    if (text3->alignment() == Qt::AlignCenter)

        justifyCenter->setChecked(true);

    if (text3->alignment() == Qt::AlignJustify)

        justifyFull->setChecked(true);

    if (text3->alignment() == Qt::AlignRight)

        justifyRight->setChecked(true);
}
//对齐的信号与槽连接
void ParagraphSettings::changeAlign()
{
    grp = new QActionGroup(this);
    grp->addAction(justifyLeft);
    grp->addAction(justifyCenter);
    grp->addAction(justifyRight);
    grp->addAction(justifyFull);
    connect(grp,SIGNAL(triggered(QAction*)),this,SLOT(align(QAction*)));
    connect(text3,SIGNAL(cursorPositionChanged()),this, SLOT(cursorPositionChanged()));
}
//单倍行距
void ParagraphSettings::lineSpacing1_0()
{
    double n = 1.0;
    lineSpacing(n);
}
//1.5倍行距
void ParagraphSettings::lineSpacing1_5()
{
    double n = 1.5;
    lineSpacing(n);
}
//2倍行距
void ParagraphSettings::lineSpacing2_0()
{
    double n = 2.0;
    lineSpacing(n);
}
//行距
void ParagraphSettings::lineSpacing(double n)
{
    QTextCursor textCursor = text3->textCursor();
    QTextBlockFormat textBlockFormat;

    QTextDocument *editorDocument = text3->document();

    //当需要进行文档结构导航时，从根框架开始(根框架提供了访问整个文档结构的能力)
    QTextFrame *root = editorDocument->rootFrame();//定位到根框架

    QTextFrame::iterator i;//迭代器，遍历框架中的所有子框架和文本块
    for(i = root->begin();!(i.atEnd());++i)
    {
        QTextBlock currentBlock = i.currentBlock();//获取当前文本块
        if(currentBlock.isValid())//如果文本块有效
        {
            QTextBlock::iterator j;//遍历当前文本块
            for(j = currentBlock.begin();!(j.atEnd());++j)
            {
                QTextFragment currentFragment = j.fragment();//获取当前文本片段
                if(currentFragment.isValid())//如果当前文本片段有效
                {
                    QTextCharFormat textFormat = currentFragment.charFormat().toCharFormat();//片段样式转换
                    double fontMSize_n = 0.0;
                    QString text = text3->toPlainText();

                    QStringList number_list = text.split("\n");

                    for (int i = 0; i < number_list.size(); ++i)
                    {
                        QFontMetrics fm(textFormat.font());

                        double leading = fm.leading();
                        double CHeig = fm.height();
                        double l = CHeig + leading;

                        if(n==1.0)
                        {
                            fontMSize_n = l;
                        }else if(n==1.5)
                        {
                            fontMSize_n = l + l/2;
                        }else if(n==2.0)
                        {
                            fontMSize_n = 2*l;
                        }
                        textBlockFormat.setLineHeight(fontMSize_n, QTextBlockFormat::FixedHeight);//设置行高
                        textCursor.setBlockFormat(textBlockFormat);
                        text3->setTextCursor(textCursor);
                    }
                }
            }
        }
    }
}
//行距的信号与槽连接
void ParagraphSettings::changeLineSpacing()
{
    connect(line1_0C,SIGNAL(triggered()),this,SLOT(lineSpacing1_0()));
    connect(line1_5C,SIGNAL(triggered()),this,SLOT(lineSpacing1_5()));
    connect(line2C,SIGNAL(triggered()),this,SLOT(lineSpacing2_0()));
}
//增大缩进
void ParagraphSettings::indentMore()
{
    QTextCursor cursor = text3->textCursor();
    QTextBlockFormat currentBlockFmt = cursor.blockFormat();   //返回光标选定的段落格式
    QTextBlockFormat blockFmt;
    blockFmt.setIndent(currentBlockFmt.indent() + 1);   //设定缩进值
    cursor.setBlockFormat(blockFmt);      //设定实现
    text3->setTextCursor(cursor);
}
//减少缩进
void ParagraphSettings::indentLess()
{
    QTextCursor cursor = text3->textCursor();
    QTextBlockFormat currentBlockFmt = cursor.blockFormat();   //返回光标选定的段落格式
    QTextBlockFormat blockFmt;
    blockFmt.setIndent(currentBlockFmt.indent() - 1);   //设定缩进值
    cursor.setBlockFormat(blockFmt);      //设定实现
    text3->setTextCursor(cursor);
}
//缩进方式的信号与槽连接
void ParagraphSettings::changeIndent()
{
    connect(indentM,SIGNAL(triggered()),this,SLOT(indentMore()));
    connect(indentL,SIGNAL(triggered()),this,SLOT(indentLess()));
}
