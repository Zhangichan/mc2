#include "PagesTextEdit.h"
#include "PageMetrics.h"
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QScrollBar>
#include <QTextFrame>

PagesTextEdit::PagesTextEdit(QWidget *parent) :
	QTextEdit(parent),
	m_document(0),
	m_usePageMode(false),
	m_addBottomSpace(true),
    m_showPageNumbers(false),
	m_pageNumbersAlignment(Qt::AlignTop | Qt::AlignRight)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);   //设置垂直滚动条方针


    aboutDocumentChanged();    //关于文档变化事件
	connect(this, SIGNAL(textChanged()), this, SLOT(aboutDocumentChanged()));

    //将垂直滚动幅度发生变化的信号链接到垂直滚动条中去
	connect(verticalScrollBar(), SIGNAL(rangeChanged(int,int)),
		this, SLOT(aboutVerticalScrollRangeChanged(int,int)));
}

void PagesTextEdit::setPageFormat(QPageSize::PageSizeId _pageFormat)
{
	m_pageMetrics.update(_pageFormat);

    //repaint()是立即重绘
    repaint();
}

//设置页面边缘
void PagesTextEdit::setPageMargins(const QMarginsF& _margins)
{
	m_pageMetrics.update(m_pageMetrics.pageFormat(), _margins);


    repaint();
}

//返回使用的页面风格
bool PagesTextEdit::usePageMode() const
{
	return m_usePageMode;
}

//设置页面风格
void PagesTextEdit::setUsePageMode(bool _use)
{
	if (m_usePageMode != _use) {
		m_usePageMode = _use;


        repaint();
	}
}

void PagesTextEdit::setAddSpaceToBottom(bool _addSpace)
{
	if (m_addBottomSpace != _addSpace) {
		m_addBottomSpace = _addSpace;


        repaint();
	}
}

//设置页码
void PagesTextEdit::setShowPageNumbers(bool _show)
{
	if (m_showPageNumbers != _show) {
		m_showPageNumbers = _show;


        repaint();
	}
}

//设置页码队列
void PagesTextEdit::setPageNumbersAlignment(Qt::Alignment _align)
{
	if (m_pageNumbersAlignment != _align) {
		m_pageNumbersAlignment = _align;


        repaint();
	}
}

//描绘事件
void PagesTextEdit::paintEvent(QPaintEvent* _event)
{
    updateVerticalScrollRange();   //更新垂直滚动幅度

    paintPagesView();   //描绘页面视图

    paintPageNumbers();    //描绘整体页码

    //paintEvent()是一个虚函数槽(slot)，子类可以对父类的paintEvent进行重写
    //paintEvent()是已经被高度优化过的函数，它本身已经自动开启并实现了双缓冲(X11系统需要手动去开启双缓冲)，因此Qt中重绘不会引起任何闪烁。
	QTextEdit::paintEvent(_event);
}

//调整大小事件
void PagesTextEdit::resizeEvent(QResizeEvent* _event)
{
    updateViewportMargins();   //更新视口边缘

    updateVerticalScrollRange();   //更新垂直滚动幅度

    QTextEdit::resizeEvent(_event);   //调用系统描绘事件
}

//更新视口边缘
void PagesTextEdit::updateViewportMargins()
{

	QMargins viewportMargins;

	if (m_usePageMode) {


		int pageWidth = m_pageMetrics.pxPageSize().width();
		int pageHeight = m_pageMetrics.pxPageSize().height();


        const int DEFAULT_TOP_MARGIN = 20;
        const int DEFAULT_BOTTOM_MARGIN = 0;
        {
			int leftMargin = 0;
			int rightMargin = 0;


			if (width() > pageWidth) {
				const int BORDERS_WIDTH = 4;
				const int VERTICAL_SCROLLBAR_WIDTH =
						verticalScrollBar()->isVisible() ? verticalScrollBar()->width() : 0;
				leftMargin = rightMargin =
						(width() - pageWidth - VERTICAL_SCROLLBAR_WIDTH - BORDERS_WIDTH) / 2;
			}

			int topMargin = DEFAULT_TOP_MARGIN;


			int bottomMargin = DEFAULT_BOTTOM_MARGIN;
			int documentHeight = pageHeight * document()->pageCount();
			if ((height() - documentHeight) > (DEFAULT_TOP_MARGIN + DEFAULT_BOTTOM_MARGIN)) {
				const int BORDERS_HEIGHT = 2;
				const int HORIZONTAL_SCROLLBAR_HEIGHT =
						horizontalScrollBar()->isVisible() ? horizontalScrollBar()->height() : 0;
				bottomMargin =
					height() - documentHeight - HORIZONTAL_SCROLLBAR_HEIGHT - DEFAULT_TOP_MARGIN - BORDERS_HEIGHT;
			}


			viewportMargins = QMargins(leftMargin, topMargin, rightMargin, bottomMargin);
        }
	}

	setViewportMargins(viewportMargins);

	aboutUpdateDocumentGeometry();
}

//更新垂直滚动幅度
void PagesTextEdit::updateVerticalScrollRange()
{

	if (m_usePageMode) {

		const int pageHeight = m_pageMetrics.pxPageSize().height();
		const int documentHeight = pageHeight * document()->pageCount();
		const int maximumValue = documentHeight - viewport()->height();
		if (verticalScrollBar()->maximum() != maximumValue) {
			verticalScrollBar()->setMaximum(maximumValue);
		}
	}

	else {
		const int SCROLL_DELTA = 800;
		int maximumValue =
				document()->size().height() - viewport()->size().height()
				+ (m_addBottomSpace ? SCROLL_DELTA : 0);
		if (verticalScrollBar()->maximum() != maximumValue) {
			verticalScrollBar()->setMaximum(maximumValue);
		}
	}
}

//描绘页面视图
void PagesTextEdit::paintPagesView()
{

	if (m_usePageMode) {


		qreal pageWidth = m_pageMetrics.pxPageSize().width();
		qreal pageHeight = m_pageMetrics.pxPageSize().height();

		QPainter p(viewport());
        QPen spacePen(palette().window(), 9);
        QPen borderPen(palette().dark(), 0.5);

		qreal curHeight = pageHeight - (verticalScrollBar()->value() % (int)pageHeight);

//		const int x = pageWidth + (width() % 2 == 0 ? 2 : 1);

//		const int horizontalDelta = horizontalScrollBar()->value();


        if(curHeight - pageHeight >= 0) {

            p.setPen(borderPen);
            p.drawLine(m_pageMetrics.pxPageMargins().left(),m_pageMetrics.pxPageMargins().top(),m_pageMetrics.pxPageMargins().left(),m_pageMetrics.pxPageMargins().top()-16);
            p.drawLine(m_pageMetrics.pxPageMargins().left(),m_pageMetrics.pxPageMargins().top(),m_pageMetrics.pxPageMargins().left()-16,m_pageMetrics.pxPageMargins().top());


            p.drawLine(pageWidth-m_pageMetrics.pxPageMargins().right(),m_pageMetrics.pxPageMargins().top(),pageWidth-m_pageMetrics.pxPageMargins().right(),m_pageMetrics.pxPageMargins().top()-16);
            p.drawLine(pageWidth-m_pageMetrics.pxPageMargins().right(),m_pageMetrics.pxPageMargins().top(),pageWidth-m_pageMetrics.pxPageMargins().right()+16,m_pageMetrics.pxPageMargins().top());

        }


        while(curHeight <= height()) {

            p.setPen(spacePen);
            p.drawLine(0, curHeight-4, width(), curHeight-4);
            p.setPen(borderPen);


            p.drawLine(m_pageMetrics.pxPageMargins().left(),curHeight+m_pageMetrics.pxPageMargins().top(),m_pageMetrics.pxPageMargins().left(),curHeight+m_pageMetrics.pxPageMargins().top()-16);
            p.drawLine(m_pageMetrics.pxPageMargins().left(),curHeight+m_pageMetrics.pxPageMargins().top(),m_pageMetrics.pxPageMargins().left()-16,curHeight+m_pageMetrics.pxPageMargins().top());



            p.drawLine(pageWidth-m_pageMetrics.pxPageMargins().right(),curHeight+m_pageMetrics.pxPageMargins().top(),pageWidth-m_pageMetrics.pxPageMargins().right(),curHeight+m_pageMetrics.pxPageMargins().top()-16);
            p.drawLine(pageWidth-m_pageMetrics.pxPageMargins().right(),curHeight+m_pageMetrics.pxPageMargins().top(),pageWidth-m_pageMetrics.pxPageMargins().right()+16,curHeight+m_pageMetrics.pxPageMargins().top());


            p.drawLine(m_pageMetrics.pxPageMargins().left(),curHeight-m_pageMetrics.pxPageMargins().bottom(),m_pageMetrics.pxPageMargins().left(),curHeight-m_pageMetrics.pxPageMargins().bottom()+16);
            p.drawLine(m_pageMetrics.pxPageMargins().left(),curHeight-m_pageMetrics.pxPageMargins().bottom(),m_pageMetrics.pxPageMargins().left()-16,curHeight-m_pageMetrics.pxPageMargins().bottom());


            p.drawLine(pageWidth-m_pageMetrics.pxPageMargins().right(),curHeight-m_pageMetrics.pxPageMargins().bottom(),pageWidth-m_pageMetrics.pxPageMargins().right(),curHeight-m_pageMetrics.pxPageMargins().bottom()+16);
            p.drawLine(pageWidth-m_pageMetrics.pxPageMargins().right(),curHeight-m_pageMetrics.pxPageMargins().bottom(),pageWidth-m_pageMetrics.pxPageMargins().right()+16,curHeight-m_pageMetrics.pxPageMargins().bottom());


//            p.drawLine(x - horizontalDelta, curHeight - pageHeight, x - horizontalDelta, curHeight - 8);

            curHeight += pageHeight;
        }
	}
}

//描绘整体页码
void PagesTextEdit::paintPageNumbers()
{

    if (m_usePageMode && !m_pageMetrics.pxPageMargins().isNull() && m_showPageNumbers) {


		QSizeF pageSize(m_pageMetrics.pxPageSize());
		QMarginsF pageMargins(m_pageMetrics.pxPageMargins());

		QPainter p(viewport());
		p.setFont(document()->defaultFont());
		p.setPen(QPen(palette().text(), 1));

		qreal curHeight = pageSize.height() - (verticalScrollBar()->value() % (int)pageSize.height());


		qreal leftMarginPosition = pageMargins.left() - horizontalScrollBar()->value();

		qreal marginWidth = pageSize.width() - pageMargins.left() - pageMargins.right();


		int pageNumber = verticalScrollBar()->value() / pageSize.height() + 1;


		if (curHeight - pageMargins.top() >= 0) {
            QRectF topMarginRect(leftMarginPosition, curHeight - pageSize.height(), marginWidth, pageMargins.top());
			paintPageNumber(&p, topMarginRect, true, pageNumber);
		}


		while (curHeight < height()) {

			QRect bottomMarginRect(leftMarginPosition, curHeight - pageMargins.bottom(), marginWidth, pageMargins.bottom());
			paintPageNumber(&p, bottomMarginRect, false, pageNumber);


			++pageNumber;


            QRect topMarginRect(leftMarginPosition, curHeight, marginWidth, pageMargins.top());
			paintPageNumber(&p, topMarginRect, true, pageNumber);

			curHeight += pageSize.height();
		}
	}
}

//描绘单页页码
void PagesTextEdit::paintPageNumber(QPainter* _painter, const QRectF& _rect, bool _isHeader, int _number)
{
    //此处可以修改页码显示的位置
    if (!_isHeader) {

		if (m_pageNumbersAlignment.testFlag(Qt::AlignTop)) {
			_painter->drawText(_rect, Qt::AlignVCenter | (m_pageNumbersAlignment ^ Qt::AlignTop),
				QString::number(_number));
		}
	}

	else {

		if (m_pageNumbersAlignment.testFlag(Qt::AlignBottom)) {
			_painter->drawText(_rect, Qt::AlignVCenter | (m_pageNumbersAlignment ^ Qt::AlignBottom),
				QString::number(_number));
		}
	}
}

//int PagesTextEdit::returnPageNumber()
//{

//    if (m_usePageMode && !m_pageMetrics.pxPageMargins().isNull()) {

//        QSizeF pageSize(m_pageMetrics.pxPageSize());
//        QMarginsF pageMargins(m_pageMetrics.pxPageMargins());

//        qreal curHeight = pageSize.height() - (verticalScrollBar()->value() % (int)pageSize.height());

//         m_pagNumber = verticalScrollBar()->value() / pageSize.height() + 2;

//         if (curHeight - pageMargins.top() >= 0) {
//             return m_pagNumber;

//         }
//         while (curHeight < height()) {

//             return m_pagNumber;

//             ++m_pagNumber;
//             curHeight += pageSize.height();
//         }
//    }
//}



//关于垂直滚动幅度的变化
void PagesTextEdit::aboutVerticalScrollRangeChanged(int _minimum, int _maximum)
{
    Q_UNUSED(_minimum);   //用来避免编译器警告_minimum没有使用

    //更新视口边缘
	updateViewportMargins();


    int scrollValue = verticalScrollBar()->value();  //设置垂直滚动条

    //当滚动条大于最大值时，就更新滚动幅度
	if (scrollValue > _maximum) {
		updateVerticalScrollRange();
	}
}

//关于文档的变化
void PagesTextEdit::aboutDocumentChanged()
{
	if (m_document != document()) {
		m_document = document();

        //如接到页面更新的信号，即更新页面几何大小
        connect(document()->documentLayout(), SIGNAL(update()), this, SLOT(aboutUpdateDocumentGeometry()));
	}
}

//关于更新文档的几何大小
void PagesTextEdit::aboutUpdateDocumentGeometry()
{

	QSizeF documentSize(width() - verticalScrollBar()->width(), -1);
	if (m_usePageMode) {
		int pageWidth = m_pageMetrics.pxPageSize().width();
		int pageHeight = m_pageMetrics.pxPageSize().height();
		documentSize = QSizeF(pageWidth, pageHeight);
	}


	if (document()->pageSize() != documentSize) {
		document()->setPageSize(documentSize);
	}


	if (document()->documentMargin() != 0) {
		document()->setDocumentMargin(0);
	}

	QMarginsF rootFrameMargins = m_pageMetrics.pxPageMargins();
	QTextFrameFormat rootFrameFormat = document()->rootFrame()->frameFormat();
	if (rootFrameFormat.leftMargin() != rootFrameMargins.left()
		|| rootFrameFormat.topMargin() != rootFrameMargins.top()
		|| rootFrameFormat.rightMargin() != rootFrameMargins.right()
        || rootFrameFormat.bottomMargin() !=
            rootFrameMargins.bottom()) {
		rootFrameFormat.setLeftMargin(rootFrameMargins.left());
		rootFrameFormat.setTopMargin(rootFrameMargins.top());
		rootFrameFormat.setRightMargin(rootFrameMargins.right());
		rootFrameFormat.setBottomMargin(rootFrameMargins.bottom());
		document()->rootFrame()->setFrameFormat(rootFrameFormat);
	}
}

