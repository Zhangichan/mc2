#ifndef PAGESTEXTEDIT_H
#define PAGESTEXTEDIT_H

#include <QTextEdit>

#include "PageMetrics.h"


class PagesTextEdit : public QTextEdit
{
	Q_OBJECT

public:
	explicit PagesTextEdit(QWidget* parent = 0);

    void setPageFormat(QPageSize::PageSizeId _pageFormat); //设置页面大小

    void setPageMargins(const QMarginsF& _margins);  //设置页面边缘

    bool usePageMode() const;  //使用的页面风格
    PageMetrics m_pageMetrics;   //页面度量

public slots:

    void setUsePageMode(bool _use);   //设置页面风格

    void setAddSpaceToBottom(bool _addSpace);   //添加空间到按钮中去

    void setShowPageNumbers(bool _show);    //设置页码

    void setPageNumbersAlignment(Qt::Alignment _align);   //设置页码队列

protected:

    void paintEvent(QPaintEvent* _event);   //描绘事件

    void resizeEvent(QResizeEvent* _event);   //调整大小事件

private:

    void updateViewportMargins();   //更新视口边缘

    void updateVerticalScrollRange();   //更新垂直滚动幅度

    void paintPagesView();    //描绘页面视图

    void paintPageNumbers();    //描绘整体页码

    void paintPageNumber(QPainter* _painter, const QRectF& _rect, bool _isHeader, int _number);   //描绘单页页码

private slots:

    void aboutVerticalScrollRangeChanged(int _minimum, int _maximum);  //关于垂直卷轴幅度的变化

    void aboutDocumentChanged();   //关于文档的变化

    void aboutUpdateDocumentGeometry();   //关于更新文档的几何大小

private:

    QTextDocument* m_document;   //定义一个容纳有结构的富文本类型的容器对象

    bool m_usePageMode;   //页面风格

    bool m_addBottomSpace;   //添加按钮

    bool m_showPageNumbers;   //显示页码

    Qt::Alignment m_pageNumbersAlignment;   //页码队列
};

#endif // PAGESTEXTEDIT_H
