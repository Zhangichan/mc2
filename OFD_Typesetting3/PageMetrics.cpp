#include "PageMetrics.h"

#include <QApplication>
#include <QDesktopWidget>


namespace {
    static qreal mmToInches(qreal mm) { return mm * 0.039370147; }  //毫米转换成英寸
}


//毫米转换成像素
qreal PageMetrics::mmToPx(qreal _mm, bool _x)
{
    //logicalDpi为分辨率
	return ::mmToInches(_mm) * (_x ? qApp->desktop()->logicalDpiX() : qApp->desktop()->logicalDpiY());
}

//通过字符串得到页面大小的ID
QPageSize::PageSizeId PageMetrics::pageSizeIdFromString(const QString& _from)
{
	QPageSize::PageSizeId result = QPageSize::A4;

	if (_from == "A0") result = QPageSize::A0;
	else if (_from == "A1") result = QPageSize::A1;
	else if (_from == "A2") result = QPageSize::A2;
	else if (_from == "A3") result = QPageSize::A3;
	else if (_from == "A4") result = QPageSize::A4;
	else if (_from == "A5") result = QPageSize::A5;
	else if (_from == "A6") result = QPageSize::A6;
	else
		Q_ASSERT_X(0, Q_FUNC_INFO, qPrintable("Undefined page size: " + _from));

	return result;
}

//通过页面大小ID得到字符串
QString PageMetrics::stringFromPageSizeId(QPageSize::PageSizeId _pageSize)
{
	QString result;

	switch (_pageSize) {
		case QPageSize::A0: result = "A0"; break;
		case QPageSize::A1: result = "A1"; break;
		case QPageSize::A2: result = "A2"; break;
		case QPageSize::A3: result = "A3"; break;
		case QPageSize::A4: result = "A4"; break;
		case QPageSize::A5: result = "A5"; break;
		case QPageSize::A6: result = "A6"; break;
		default:
			Q_ASSERT_X(0, Q_FUNC_INFO, qPrintable("Undefined page size: " + QString::number(_pageSize)));
	}

	return result;
}

//头文件中已设置页面大小默认为A4，初始化边缘宽度为0
//这里构造函数，实现页面更新
PageMetrics::PageMetrics(QPageSize::PageSizeId _pageFormat, QMarginsF _mmPageMargins)
{
	update(_pageFormat, _mmPageMargins);
}

//更新页面 _pageFormat：页面版式   _mmPageMargins页面边缘宽度
void PageMetrics::update(QPageSize::PageSizeId _pageFormat, QMarginsF _mmPageMargins)
{
    m_pageFormat = _pageFormat;  //初始化页面版式/大小

    m_mmPageSize = QPageSize(m_pageFormat).rect(QPageSize::Millimeter).size();  //初始化页面用毫米展现的大小
    m_mmPageMargins = _mmPageMargins;  //初始化页面用毫米展现的边缘宽度


	const bool x = true, y = false;
    //得到页面用像素展现的大小
	m_pxPageSize =
			QSizeF(mmToPx(m_mmPageSize.width(), x),
				   mmToPx(m_mmPageSize.height(), y));

    //得到页面的边缘像素
    //left（）表示左边缘的横坐标，top（）表示上边缘的纵坐标，right（）表示右边缘的横坐标，buttom（）表示底座的纵坐标（有待验证）
	m_pxPageMargins =
			QMarginsF(mmToPx(m_mmPageMargins.left(), x),
					  mmToPx(m_mmPageMargins.top(), y),
					  mmToPx(m_mmPageMargins.right(), x),
					  mmToPx(m_mmPageMargins.bottom(), y)
					  );
}


//页面版式：A4、A3......
QPageSize::PageSizeId PageMetrics::pageFormat() const
{
	return m_pageFormat;
}

//用毫米计量页面的大小
QSizeF PageMetrics::mmPageSize() const
{
	return m_mmPageSize;
}

//用毫米计量页面的边缘宽度
QMarginsF PageMetrics::mmPageMargins() const
{
	return m_mmPageMargins;
}

//页面的像素
QSizeF PageMetrics::pxPageSize() const
{
	return QSizeF(m_pxPageSize.width(),
				  m_pxPageSize.height());
}

//页面的边缘像素
QMarginsF PageMetrics::pxPageMargins() const
{
	return QMarginsF(m_pxPageMargins.left(),
					 m_pxPageMargins.top(),
					 m_pxPageMargins.right(),
					 m_pxPageMargins.bottom());
}
