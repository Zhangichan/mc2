#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include "PagesTextEdit.h"

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    PagesTextEdit *textEdit;

private:
    void setPageSize();



};

#endif // WIDGET_H
