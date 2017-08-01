#include "fontstyle.h"
#include<QColorDialog>
#include<QTextCharFormat>

FontStyle::FontStyle(QWidget *parent):QWidget(parent)
{
}
//使格式作用于选区内的字符，若没有选区则作用于光标所在处的字符
void FontStyle::mergeFormat(QTextCharFormat format)
{
    QTextCursor cursor = text->textCursor();

    if (!cursor.hasSelection())
        cursor.select( QTextCursor::WordUnderCursor );
    text->mergeCurrentCharFormat(format);
}
//字体颜色
void FontStyle::fontColor()
{
    QColor color = QColorDialog::getColor(Qt::black);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        mergeFormat(fmt);
    }
}
//字体
void FontStyle::font(QString f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormat(fmt);
}
//字体大小
void FontStyle::fontSize(QString num)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize( num.toFloat() );
    mergeFormat(fmt);
}
//字体加粗
void FontStyle::fontBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(bold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormat( fmt );
}
//字体设为斜体
void FontStyle::fontItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(italics->isChecked());
    mergeFormat(fmt);
}
//字体设置下划线
void FontStyle::fontUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(underline->isChecked());
    mergeFormat( fmt );
}
//字体设置删除线
void FontStyle::fontStrikeout()
{
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(strickout->isChecked());
    mergeFormat(fmt);
}
//字体设置上划线
void FontStyle::fontOverline()
{
    QTextCharFormat fmt;
    fmt.setFontOverline(online->isChecked());
    mergeFormat(fmt);
}
//字体设置为上标
void FontStyle::fontSuperscript()
{
    QTextCharFormat fmt;
    fmt.setVerticalAlignment(superscript->isChecked() ? QTextCharFormat::AlignSuperScript :QTextCharFormat::AlignNormal);
    mergeFormat(fmt);
}
//字体设置为下标
void FontStyle::fontSubscript()
{
    QTextCharFormat fmt;
    fmt.setVerticalAlignment(subscript->isChecked() ? QTextCharFormat::AlignSubScript : QTextCharFormat::AlignNormal);
    mergeFormat(fmt);
}
//字体样式的信号与槽连接
void FontStyle::changFontStyle()
{
    connect(color,SIGNAL(triggered()),this,SLOT(fontColor()));
    connect(fontbox,SIGNAL(activated(QString)),this,SLOT(font(QString)));
    connect(sizebox,SIGNAL(activated(QString)),this,SLOT(fontSize(QString)));
    connect(bold,SIGNAL(triggered()),this,SLOT(fontBold()));
    connect(italics,SIGNAL(triggered()),this,SLOT(fontItalic()));
    connect(underline,SIGNAL(triggered()),this,SLOT(fontUnderline()));
    connect(strickout,SIGNAL(triggered()),this,SLOT(fontStrikeout()));
    connect(online,SIGNAL(triggered()),this,SLOT(fontOverline()));
    connect(superscript,SIGNAL(triggered()),this,SLOT(fontSuperscript()));
    connect(subscript,SIGNAL(triggered()),this,SLOT(fontSubscript()));
}
