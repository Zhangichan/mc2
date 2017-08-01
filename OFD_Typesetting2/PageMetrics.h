#ifndef PAGEMETRICS_H
#define PAGEMETRICS_H

#include <QString>
#include <QSizeF>
#include <QMarginsF>
#include <QPageSize>

class QPaintDevice;

class PageMetrics
{
public:

    static qreal mmToPx(qreal _mm, bool _x = true);  //毫米转换成像素

    static QPageSize::PageSizeId pageSizeIdFromString(const QString& _from);   //通过字符串得到页面大小的ID

    static QString stringFromPageSizeId(QPageSize::PageSizeId _pageSize);    //通过页面大小ID得到字符串

public:
    PageMetrics(QPageSize::PageSizeId _pageFormat = QPageSize::A4, QMarginsF _mmMargins = QMarginsF());  //设置页面大小默认为A4，初始化边缘宽度为0

    void update(QPageSize::PageSizeId _pageFormat, QMarginsF _mmPageMargins = QMarginsF());   //更新页面

    QPageSize::PageSizeId pageFormat() const;   //页面版式
    QSizeF mmPageSize() const;    //用毫米计量页面的大小
    QMarginsF mmPageMargins() const;   //用毫米计量页面的边缘宽度
    QSizeF pxPageSize() const;   //页面的像素
    QMarginsF pxPageMargins() const;  //页面的边缘像素

private:

    QPageSize::PageSizeId m_pageFormat;   //页面版式

    QSizeF m_mmPageSize;   //页面用毫米展现的大小，QSizeF是QSize的浮点数版本
    QMarginsF m_mmPageMargins;   //页面用毫米展现的边缘宽度

    QSizeF m_pxPageSize;  //页面用像素展现的大小
    QMarginsF m_pxPageMargins;  //页面的边缘像素

};

#endif // PAGEMETRICS_H
