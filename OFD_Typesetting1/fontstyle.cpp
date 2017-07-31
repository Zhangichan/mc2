#include "fontstyle.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QTextCharFormat>

FontStyle::FontStyle()
{
}

void FontStyle::FontColor()
{
    QColor color = QColorDialog::getColor(Qt::black);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        mergeFormat(fmt);
    }
}

void FontStyle::mergeFormat(QTextCharFormat format)
{
    PagesTextEdit *text;
    text = new PagesTextEdit;

    QTextCursor cursor = text->textCursor();

    if (!cursor.hasSelection())
        cursor.select( QTextCursor::WordUnderCursor );
    text->mergeCurrentCharFormat(format);
}

void FontStyle::FontBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->action_bold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormat( fmt );
}
