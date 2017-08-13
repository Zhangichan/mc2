#ifndef FINDDIALOG_H
#define FINDDIALOG_H
#include<QDialog>
#include<QtWidgets>
#include "PagesTextEdit.h"
class QLabel;
class QPushButton;
class QCheckBox;
class QLineEdit;
class FindDialog:public QDialog
{
    Q_OBJECT
public:
    FindDialog(QWidget *parent = 0);
    PagesTextEdit *text6;
private:
    QLabel *scLabel;
    QLabel *reLabel;
    QLineEdit *scEdit;
    QLineEdit *reEdit;
    QPushButton *scButton;
    QPushButton *repAllButton;
    QPushButton *cancelButton;
    void setupWidget();
    void setConnect();
private slots:
    void search();
    void sendAll();
signals:
    void sigAll(QString,QString);
};

#endif // FINDDIALOG_H
