#include "finddialog.h"
#include<QtGui>
#include <QHBoxLayout>
#include<QVBoxLayout>
FindDialog::FindDialog(QWidget *parent):QDialog(parent)
{
   setWindowTitle(tr("查找与替换"));
   setupWidget();
   setConnect();
}
void FindDialog::setupWidget()
{
    scLabel=new QLabel(this);
    scLabel->setText(tr("查找内容:"));
    reLabel=new QLabel(this);
    reLabel->setText(tr("替换为  :"));
    scEdit=new QLineEdit(this);
    reEdit=new QLineEdit(this);
    scButton=new QPushButton(this);
    scButton->setText(tr("查找"));
    repAllButton=new QPushButton(this);
    repAllButton->setText(tr("替换全部"));
    cancelButton=new QPushButton(this);
    cancelButton->setText(tr("关闭"));
    QHBoxLayout *topLayout=new QHBoxLayout;
    topLayout->addWidget(scLabel);
    topLayout->addWidget(scEdit);
    topLayout->addWidget(scButton);
    QHBoxLayout *midLayout=new QHBoxLayout;
    midLayout->addWidget(reLabel);
    midLayout->addWidget(reEdit);
    midLayout->addWidget(repAllButton);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(midLayout);
    mainLayout->addWidget(cancelButton);
    this->setLayout(mainLayout);
}
void FindDialog::setConnect()
{
    connect(scButton,SIGNAL(clicked()),this,SLOT(search()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(repAllButton,SIGNAL(clicked()),this,SLOT(sendAll()));
}
//SLOTS
void FindDialog::search()
{
    QString string = scEdit->text();
    bool isfind = text6->find(string, QTextDocument::FindBackward);
    if(isfind){
        QPalette palette = text6->palette();
        palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
        text6->setPalette(palette);
    }
}
void FindDialog::sendAll()
{
    emit sigAll(scEdit->text(),reEdit->text());
}
