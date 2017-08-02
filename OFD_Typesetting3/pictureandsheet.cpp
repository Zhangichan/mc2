#include "pictureandsheet.h"

PictureAndSheet::PictureAndSheet(QWidget *parent):QWidget(parent)
{

}
//插入图片
void PictureAndSheet::insertPicture()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
                                                ".", tr("Bitmap Files (*.bmp)\n"
                                                        "JPEG (*.jpg *jpeg)\n"
                                                        "GIF (*.gif)\n"
                                                        "PNG (*.png)\n"));
    QUrl Uri ( QString ( "file://%1" ).arg ( file ) );
    QImage image = QImageReader ( file ).read();

    QTextDocument * textDocument =text4->document();
    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
    QTextCursor cursor = text4->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth( image.width() );
    imageFormat.setHeight( image.height() );
    imageFormat.setName( Uri.toString() );
    cursor.insertImage(imageFormat);
}
//连接插入图片的信号与槽
void PictureAndSheet::beginInsertPicture()
{
    connect(pic,SIGNAL(triggered()),this,SLOT(insertPicture()));
}
//连接插入表格的信号与槽
void PictureAndSheet::beginInsertTable()
{
    connect(drawTable,SIGNAL(triggered()),this,SLOT(drawTableWidget()));
}
//绘制表格的一个窗口显示
void PictureAndSheet::drawTableWidget()
{
    tabledlg = new QDialog(this);
    tabledlg->setWindowTitle(tr("绘制表格"));

    QLabel *label1 = new QLabel(tabledlg);
    label1->setText(tr("表格尺寸------------------------------------"));

    QLabel *label2 = new QLabel(tabledlg);
    label2->setText(tr("  行数: "));
    QSpinBox *rowsSpinBox = new QSpinBox(tabledlg);
    rowsSpinBox->setRange(1,100);
    connect(rowsSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setCurrentRows(int)));

    QLabel *label3 = new QLabel(tabledlg);
    label3->setText(tr("  列数: "));
    QSpinBox *linesSpinBox = new QSpinBox(tabledlg);
    linesSpinBox->setRange(1,100);
    connect(linesSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setCurrentLines(int)));

    QPushButton *makeSureButton = new QPushButton(tabledlg);
    makeSureButton->setText(tr("确定"));
    connect(makeSureButton,SIGNAL(clicked()),this,SLOT(beginDrawTable()));

    QPushButton *concelButton = new QPushButton(tabledlg);
    concelButton->setText(tr("取消"));
    connect(concelButton,SIGNAL(clicked()),this,SLOT(closeTableDlg()));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(label1);

    QHBoxLayout *centerLayout = new QHBoxLayout;
    centerLayout->addWidget(label2);
    centerLayout->addWidget(rowsSpinBox);
    centerLayout->addWidget(label3);
    centerLayout->addWidget(linesSpinBox);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(makeSureButton);
    bottomLayout->addWidget(concelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(centerLayout);
    mainLayout->addLayout(bottomLayout);
    tabledlg->setLayout(mainLayout);
    tabledlg->show();
}
//设置所要绘制的表的行数
void PictureAndSheet::setCurrentRows(int rows)
{
    tableRows = rows;
}
//设置所要绘制的表的列数
void PictureAndSheet::setCurrentLines(int lines)
{
    tableLines = lines;
}
//绘画表格到文本编辑器上
void PictureAndSheet::beginDrawTable()
{
    QTextCursor cursor = text4->textCursor();
    QTextTableFormat fmt;
    fmt.setCellSpacing(2);
    fmt.setCellPadding(10);
    cursor.insertTable(tableRows,tableLines,fmt);
}
//关闭表格对话框
void PictureAndSheet::closeTableDlg()
{
    tabledlg->close();
}
