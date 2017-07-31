#ifndef FONTSTYLE_H
#define FONTSTYLE_H

#include "PagesTextEdit.h"

namespace Ui {
class MainWindow;
}

class FontStyle
{

public:
    FontStyle();
    void FontColor();
    void FontBold();

private:
    void mergeFormat( QTextCharFormat);//使格式作用于选区内的字符，若没有选区则作用于光标所在处的字符
    Ui::MainWindow *ui;
};

#endif // FONTSTYLE_H
