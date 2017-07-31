/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_new;
    QAction *action_open;
    QAction *action_save;
    QAction *action_saveAs;
    QAction *action_exit;
    QAction *action_close;
    QAction *action_copy;
    QAction *action_cut;
    QAction *action_paste;
    QAction *action_images;
    QAction *action_about;
    QAction *action_noneAround;
    QAction *action_beforeAround;
    QAction *action_afterAround;
    QAction *action_parallelAround;
    QAction *action_throughAround;
    QAction *action_bestAround;
    QAction *action_header;
    QAction *action_footer;
    QAction *action_undo;
    QAction *action_redo;
    QAction *action_bold;
    QAction *action_italics;
    QAction *action_underline;
    QAction *action_strickout;
    QAction *action_online;
    QAction *action_fontStyle;
    QAction *action_fontSize;
    QAction *action_newPage;
    QAction *action_newLine;
    QAction *action_aboutOFD;
    QAction *action_insertTable;
    QAction *action_drawTable;
    QAction *action_justifyLeft;
    QAction *action_justifyCenter;
    QAction *action_justifyRight;
    QAction *action_justifyFull;
    QAction *action_kerning;
    QAction *action_lineSpacing;
    QAction *action_superscript;
    QAction *action_subscript;
    QAction *action_A1;
    QAction *action_color;
    QAction *action_A4;
    QAction *action_A3;
    QAction *action_8_259_367;
    QAction *action_16_183_259;
    QAction *action_find;
    QAction *action1_5_C;
    QAction *action2_C;
    QAction *action_paragraphSpacing;
    QAction *action_indentMore;
    QAction *action_indentLess;
    QAction *action_Z;
    QAction *action_insertRowAbove;
    QAction *action_insertRowBelow;
    QAction *action_Row;
    QAction *action_L;
    QAction *action_I_2;
    QAction *action_Column;
    QAction *action_deleteRow;
    QAction *action_deleteColumn;
    QAction *action_deleteTable;
    QAction *action_chooseRow;
    QAction *action_chooseColumn;
    QAction *action_chooseTable;
    QAction *action_cell;
    QAction *action_mergeCell;
    QAction *action_splitCell;
    QAction *action_customSpaced;
    QAction *action_A2;
    QAction *action_A5;
    QAction *action_A6;
    QAction *action;
    QAction *action1_0_C;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *OFDMenue;
    QMenu *editMenue;
    QMenu *insertMenue;
    QMenu *menu_6;
    QMenu *layoutMenue;
    QMenu *paperSize;
    QMenu *helpMenue;
    QMenu *formatMenue;
    QMenu *aligningMenue;
    QMenu *textMenue;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(734, 459);
        action_new = new QAction(MainWindow);
        action_new->setObjectName(QStringLiteral("action_new"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/new.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_new->setIcon(icon);
        action_open = new QAction(MainWindow);
        action_open->setObjectName(QStringLiteral("action_open"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/open.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_open->setIcon(icon1);
        action_save = new QAction(MainWindow);
        action_save->setObjectName(QStringLiteral("action_save"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/document-save-as.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_save->setIcon(icon2);
        action_saveAs = new QAction(MainWindow);
        action_saveAs->setObjectName(QStringLiteral("action_saveAs"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/document-save-all.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_saveAs->setIcon(icon3);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/exit.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_exit->setIcon(icon4);
        action_close = new QAction(MainWindow);
        action_close->setObjectName(QStringLiteral("action_close"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/close.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_close->setIcon(icon5);
        action_copy = new QAction(MainWindow);
        action_copy->setObjectName(QStringLiteral("action_copy"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/edit-copy.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_copy->setIcon(icon6);
        action_cut = new QAction(MainWindow);
        action_cut->setObjectName(QStringLiteral("action_cut"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/edit-cut.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_cut->setIcon(icon7);
        action_paste = new QAction(MainWindow);
        action_paste->setObjectName(QStringLiteral("action_paste"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/edit-paste.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_paste->setIcon(icon8);
        action_images = new QAction(MainWindow);
        action_images->setObjectName(QStringLiteral("action_images"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/insert-image.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_images->setIcon(icon9);
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QStringLiteral("action_about"));
        action_noneAround = new QAction(MainWindow);
        action_noneAround->setObjectName(QStringLiteral("action_noneAround"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/\346\227\240.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_noneAround->setIcon(icon10);
        action_beforeAround = new QAction(MainWindow);
        action_beforeAround->setObjectName(QStringLiteral("action_beforeAround"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/\344\271\213\345\211\215.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_beforeAround->setIcon(icon11);
        action_afterAround = new QAction(MainWindow);
        action_afterAround->setObjectName(QStringLiteral("action_afterAround"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/images/\344\271\213\345\220\216.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_afterAround->setIcon(icon12);
        action_parallelAround = new QAction(MainWindow);
        action_parallelAround->setObjectName(QStringLiteral("action_parallelAround"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/images/\345\271\263\350\241\214.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_parallelAround->setIcon(icon13);
        action_throughAround = new QAction(MainWindow);
        action_throughAround->setObjectName(QStringLiteral("action_throughAround"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/images/\350\264\257\347\251\277.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_throughAround->setIcon(icon14);
        action_bestAround = new QAction(MainWindow);
        action_bestAround->setObjectName(QStringLiteral("action_bestAround"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/images/\346\234\200\344\275\263.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_bestAround->setIcon(icon15);
        action_header = new QAction(MainWindow);
        action_header->setObjectName(QStringLiteral("action_header"));
        action_footer = new QAction(MainWindow);
        action_footer->setObjectName(QStringLiteral("action_footer"));
        action_undo = new QAction(MainWindow);
        action_undo->setObjectName(QStringLiteral("action_undo"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/images/edit-undo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_undo->setIcon(icon16);
        action_redo = new QAction(MainWindow);
        action_redo->setObjectName(QStringLiteral("action_redo"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/images/edit-redo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_redo->setIcon(icon17);
        action_bold = new QAction(MainWindow);
        action_bold->setObjectName(QStringLiteral("action_bold"));
        action_bold->setCheckable(true);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/images/format-text-bold.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_bold->setIcon(icon18);
        action_italics = new QAction(MainWindow);
        action_italics->setObjectName(QStringLiteral("action_italics"));
        action_italics->setCheckable(true);
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/images/format-text-italic.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_italics->setIcon(icon19);
        action_underline = new QAction(MainWindow);
        action_underline->setObjectName(QStringLiteral("action_underline"));
        action_underline->setCheckable(true);
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/images/format-text-underline.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_underline->setIcon(icon20);
        action_strickout = new QAction(MainWindow);
        action_strickout->setObjectName(QStringLiteral("action_strickout"));
        action_strickout->setCheckable(true);
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/images/format-text-strikethrough.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_strickout->setIcon(icon21);
        action_online = new QAction(MainWindow);
        action_online->setObjectName(QStringLiteral("action_online"));
        action_online->setCheckable(true);
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/images/under_line.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_online->setIcon(icon22);
        action_fontStyle = new QAction(MainWindow);
        action_fontStyle->setObjectName(QStringLiteral("action_fontStyle"));
        action_fontSize = new QAction(MainWindow);
        action_fontSize->setObjectName(QStringLiteral("action_fontSize"));
        action_newPage = new QAction(MainWindow);
        action_newPage->setObjectName(QStringLiteral("action_newPage"));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/images/insert-page-break.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_newPage->setIcon(icon23);
        action_newLine = new QAction(MainWindow);
        action_newLine->setObjectName(QStringLiteral("action_newLine"));
        action_aboutOFD = new QAction(MainWindow);
        action_aboutOFD->setObjectName(QStringLiteral("action_aboutOFD"));
        action_insertTable = new QAction(MainWindow);
        action_insertTable->setObjectName(QStringLiteral("action_insertTable"));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/images/insert-table.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_insertTable->setIcon(icon24);
        action_drawTable = new QAction(MainWindow);
        action_drawTable->setObjectName(QStringLiteral("action_drawTable"));
        action_justifyLeft = new QAction(MainWindow);
        action_justifyLeft->setObjectName(QStringLiteral("action_justifyLeft"));
        action_justifyLeft->setCheckable(true);
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/images/format-justify-left.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_justifyLeft->setIcon(icon25);
        action_justifyCenter = new QAction(MainWindow);
        action_justifyCenter->setObjectName(QStringLiteral("action_justifyCenter"));
        action_justifyCenter->setCheckable(true);
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/images/format-justify-center.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_justifyCenter->setIcon(icon26);
        action_justifyRight = new QAction(MainWindow);
        action_justifyRight->setObjectName(QStringLiteral("action_justifyRight"));
        action_justifyRight->setCheckable(true);
        QIcon icon27;
        icon27.addFile(QStringLiteral(":/images/format-justify-right.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_justifyRight->setIcon(icon27);
        action_justifyFull = new QAction(MainWindow);
        action_justifyFull->setObjectName(QStringLiteral("action_justifyFull"));
        action_justifyFull->setCheckable(true);
        QIcon icon28;
        icon28.addFile(QStringLiteral(":/images/format-justify-fill.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_justifyFull->setIcon(icon28);
        action_kerning = new QAction(MainWindow);
        action_kerning->setObjectName(QStringLiteral("action_kerning"));
        QIcon icon29;
        icon29.addFile(QStringLiteral(":/images/text_horz_kern.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_kerning->setIcon(icon29);
        action_lineSpacing = new QAction(MainWindow);
        action_lineSpacing->setObjectName(QStringLiteral("action_lineSpacing"));
        QIcon icon30;
        icon30.addFile(QStringLiteral(":/images/text_line_spacing.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_lineSpacing->setIcon(icon30);
        action_superscript = new QAction(MainWindow);
        action_superscript->setObjectName(QStringLiteral("action_superscript"));
        action_superscript->setCheckable(true);
        QIcon icon31;
        icon31.addFile(QStringLiteral(":/images/format-text-superscript.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_superscript->setIcon(icon31);
        action_subscript = new QAction(MainWindow);
        action_subscript->setObjectName(QStringLiteral("action_subscript"));
        action_subscript->setCheckable(true);
        QIcon icon32;
        icon32.addFile(QStringLiteral(":/images/text_subscript.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_subscript->setIcon(icon32);
        action_A1 = new QAction(MainWindow);
        action_A1->setObjectName(QStringLiteral("action_A1"));
        action_color = new QAction(MainWindow);
        action_color->setObjectName(QStringLiteral("action_color"));
        QIcon icon33;
        icon33.addFile(QStringLiteral(":/images/color-management.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_color->setIcon(icon33);
        action_A4 = new QAction(MainWindow);
        action_A4->setObjectName(QStringLiteral("action_A4"));
        action_A3 = new QAction(MainWindow);
        action_A3->setObjectName(QStringLiteral("action_A3"));
        action_8_259_367 = new QAction(MainWindow);
        action_8_259_367->setObjectName(QStringLiteral("action_8_259_367"));
        action_16_183_259 = new QAction(MainWindow);
        action_16_183_259->setObjectName(QStringLiteral("action_16_183_259"));
        action_find = new QAction(MainWindow);
        action_find->setObjectName(QStringLiteral("action_find"));
        QIcon icon34;
        icon34.addFile(QStringLiteral(":/images/edit-find.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_find->setIcon(icon34);
        action1_5_C = new QAction(MainWindow);
        action1_5_C->setObjectName(QStringLiteral("action1_5_C"));
        action2_C = new QAction(MainWindow);
        action2_C->setObjectName(QStringLiteral("action2_C"));
        action_paragraphSpacing = new QAction(MainWindow);
        action_paragraphSpacing->setObjectName(QStringLiteral("action_paragraphSpacing"));
        action_indentMore = new QAction(MainWindow);
        action_indentMore->setObjectName(QStringLiteral("action_indentMore"));
        QIcon icon35;
        icon35.addFile(QStringLiteral(":/images/format-indent-more.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_indentMore->setIcon(icon35);
        action_indentLess = new QAction(MainWindow);
        action_indentLess->setObjectName(QStringLiteral("action_indentLess"));
        QIcon icon36;
        icon36.addFile(QStringLiteral(":/images/format-indent-less.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_indentLess->setIcon(icon36);
        action_Z = new QAction(MainWindow);
        action_Z->setObjectName(QStringLiteral("action_Z"));
        action_insertRowAbove = new QAction(MainWindow);
        action_insertRowAbove->setObjectName(QStringLiteral("action_insertRowAbove"));
        QIcon icon37;
        icon37.addFile(QStringLiteral(":/images/edit-table-insert-row-above.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_insertRowAbove->setIcon(icon37);
        action_insertRowBelow = new QAction(MainWindow);
        action_insertRowBelow->setObjectName(QStringLiteral("action_insertRowBelow"));
        QIcon icon38;
        icon38.addFile(QStringLiteral(":/images/edit-table-insert-row-below.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_insertRowBelow->setIcon(icon38);
        action_Row = new QAction(MainWindow);
        action_Row->setObjectName(QStringLiteral("action_Row"));
        action_L = new QAction(MainWindow);
        action_L->setObjectName(QStringLiteral("action_L"));
        QIcon icon39;
        icon39.addFile(QStringLiteral(":/images/edit-table-insert-column-left.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_L->setIcon(icon39);
        action_I_2 = new QAction(MainWindow);
        action_I_2->setObjectName(QStringLiteral("action_I_2"));
        QIcon icon40;
        icon40.addFile(QStringLiteral(":/images/edit-table-insert-column-right.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_I_2->setIcon(icon40);
        action_Column = new QAction(MainWindow);
        action_Column->setObjectName(QStringLiteral("action_Column"));
        action_deleteRow = new QAction(MainWindow);
        action_deleteRow->setObjectName(QStringLiteral("action_deleteRow"));
        QIcon icon41;
        icon41.addFile(QStringLiteral(":/images/edit-table-delete-row.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_deleteRow->setIcon(icon41);
        action_deleteColumn = new QAction(MainWindow);
        action_deleteColumn->setObjectName(QStringLiteral("action_deleteColumn"));
        QIcon icon42;
        icon42.addFile(QStringLiteral(":/images/edit-table-delete-column.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_deleteColumn->setIcon(icon42);
        action_deleteTable = new QAction(MainWindow);
        action_deleteTable->setObjectName(QStringLiteral("action_deleteTable"));
        action_chooseRow = new QAction(MainWindow);
        action_chooseRow->setObjectName(QStringLiteral("action_chooseRow"));
        action_chooseColumn = new QAction(MainWindow);
        action_chooseColumn->setObjectName(QStringLiteral("action_chooseColumn"));
        action_chooseTable = new QAction(MainWindow);
        action_chooseTable->setObjectName(QStringLiteral("action_chooseTable"));
        action_cell = new QAction(MainWindow);
        action_cell->setObjectName(QStringLiteral("action_cell"));
        action_mergeCell = new QAction(MainWindow);
        action_mergeCell->setObjectName(QStringLiteral("action_mergeCell"));
        QIcon icon43;
        icon43.addFile(QStringLiteral(":/images/edit-table-cell-merge.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_mergeCell->setIcon(icon43);
        action_splitCell = new QAction(MainWindow);
        action_splitCell->setObjectName(QStringLiteral("action_splitCell"));
        QIcon icon44;
        icon44.addFile(QStringLiteral(":/images/edit-table-cell-split.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_splitCell->setIcon(icon44);
        action_customSpaced = new QAction(MainWindow);
        action_customSpaced->setObjectName(QStringLiteral("action_customSpaced"));
        action_A2 = new QAction(MainWindow);
        action_A2->setObjectName(QStringLiteral("action_A2"));
        action_A5 = new QAction(MainWindow);
        action_A5->setObjectName(QStringLiteral("action_A5"));
        action_A6 = new QAction(MainWindow);
        action_A6->setObjectName(QStringLiteral("action_A6"));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action1_0_C = new QAction(MainWindow);
        action1_0_C->setObjectName(QStringLiteral("action1_0_C"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 734, 20));
        OFDMenue = new QMenu(menuBar);
        OFDMenue->setObjectName(QStringLiteral("OFDMenue"));
        editMenue = new QMenu(menuBar);
        editMenue->setObjectName(QStringLiteral("editMenue"));
        insertMenue = new QMenu(menuBar);
        insertMenue->setObjectName(QStringLiteral("insertMenue"));
        menu_6 = new QMenu(insertMenue);
        menu_6->setObjectName(QStringLiteral("menu_6"));
        layoutMenue = new QMenu(menuBar);
        layoutMenue->setObjectName(QStringLiteral("layoutMenue"));
        paperSize = new QMenu(layoutMenue);
        paperSize->setObjectName(QStringLiteral("paperSize"));
        helpMenue = new QMenu(menuBar);
        helpMenue->setObjectName(QStringLiteral("helpMenue"));
        formatMenue = new QMenu(menuBar);
        formatMenue->setObjectName(QStringLiteral("formatMenue"));
        aligningMenue = new QMenu(formatMenue);
        aligningMenue->setObjectName(QStringLiteral("aligningMenue"));
        textMenue = new QMenu(formatMenue);
        textMenue->setObjectName(QStringLiteral("textMenue"));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(MainWindow);
        toolBar_2->setObjectName(QStringLiteral("toolBar_2"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_2);
        MainWindow->insertToolBarBreak(toolBar_2);

        menuBar->addAction(OFDMenue->menuAction());
        menuBar->addAction(editMenue->menuAction());
        menuBar->addAction(formatMenue->menuAction());
        menuBar->addAction(insertMenue->menuAction());
        menuBar->addAction(layoutMenue->menuAction());
        menuBar->addAction(helpMenue->menuAction());
        OFDMenue->addAction(action_new);
        OFDMenue->addAction(action_open);
        OFDMenue->addAction(action_save);
        OFDMenue->addAction(action_saveAs);
        OFDMenue->addAction(action_close);
        OFDMenue->addAction(action_exit);
        OFDMenue->addSeparator();
        OFDMenue->addSeparator();
        editMenue->addAction(action_undo);
        editMenue->addAction(action_redo);
        editMenue->addSeparator();
        editMenue->addAction(action_copy);
        editMenue->addAction(action_cut);
        editMenue->addAction(action_paste);
        editMenue->addAction(action_find);
        insertMenue->addAction(action_images);
        insertMenue->addAction(menu_6->menuAction());
        insertMenue->addAction(action);
        menu_6->addAction(action_footer);
        layoutMenue->addAction(paperSize->menuAction());
        paperSize->addAction(action_A4);
        paperSize->addAction(action_A3);
        paperSize->addAction(action_A1);
        paperSize->addAction(action_A2);
        paperSize->addAction(action_A5);
        paperSize->addAction(action_A6);
        helpMenue->addAction(action_about);
        helpMenue->addAction(action_aboutOFD);
        formatMenue->addAction(textMenue->menuAction());
        formatMenue->addAction(action_color);
        formatMenue->addSeparator();
        formatMenue->addAction(aligningMenue->menuAction());
        aligningMenue->addAction(action_justifyLeft);
        aligningMenue->addAction(action_justifyCenter);
        aligningMenue->addAction(action_justifyRight);
        aligningMenue->addAction(action_justifyFull);
        textMenue->addAction(action_bold);
        textMenue->addAction(action_italics);
        textMenue->addAction(action_underline);
        textMenue->addAction(action_strickout);
        textMenue->addAction(action_online);
        textMenue->addSeparator();
        textMenue->addAction(action_superscript);
        textMenue->addAction(action_subscript);
        toolBar->addAction(action_new);
        toolBar->addAction(action_open);
        toolBar->addAction(action_save);
        toolBar->addAction(action_saveAs);
        toolBar->addSeparator();
        toolBar->addAction(action_copy);
        toolBar->addAction(action_paste);
        toolBar->addAction(action_cut);
        toolBar->addAction(action_find);
        toolBar->addSeparator();
        toolBar->addAction(action_undo);
        toolBar->addAction(action_redo);
        toolBar->addSeparator();
        toolBar->addAction(action_images);
        toolBar->addAction(action_color);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action_new->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272(&N)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_new->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_open->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200(&O)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_save->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230(&S)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_saveAs->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230(S&aveAs)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_saveAs->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272(&E)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_exit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_close->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255(&C)", Q_NULLPTR));
        action_copy->setText(QApplication::translate("MainWindow", "\345\244\215\345\210\266(&C)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_copy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_cut->setText(QApplication::translate("MainWindow", "\345\211\252\345\210\207(&T)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_cut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_paste->setText(QApplication::translate("MainWindow", "\347\262\230\350\264\264(&P)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_paste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_images->setText(QApplication::translate("MainWindow", "\345\233\276\345\203\217(&I)", Q_NULLPTR));
        action_about->setText(QApplication::translate("MainWindow", "&About(&A)", Q_NULLPTR));
        action_noneAround->setText(QApplication::translate("MainWindow", "\346\227\240\347\216\257\347\273\225(&N)", Q_NULLPTR));
        action_beforeAround->setText(QApplication::translate("MainWindow", "\344\271\213\345\211\215\347\216\257\347\273\225(&B)", Q_NULLPTR));
        action_afterAround->setText(QApplication::translate("MainWindow", "\344\271\213\345\220\216\347\216\257\347\273\225(&A)", Q_NULLPTR));
        action_parallelAround->setText(QApplication::translate("MainWindow", "\345\271\263\350\241\214\347\216\257\347\273\225(&P)", Q_NULLPTR));
        action_throughAround->setText(QApplication::translate("MainWindow", "\350\264\257\347\251\277\347\216\257\347\273\225(&U)", Q_NULLPTR));
        action_bestAround->setText(QApplication::translate("MainWindow", "\346\234\200\344\275\263\347\216\257\347\273\225(&O)", Q_NULLPTR));
        action_header->setText(QApplication::translate("MainWindow", "\351\241\265\347\234\211(&A)", Q_NULLPTR));
        action_footer->setText(QApplication::translate("MainWindow", "\351\241\265\350\204\232(&R)", Q_NULLPTR));
        action_undo->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200(&Z)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_undo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_redo->setText(QApplication::translate("MainWindow", "\346\201\242\345\244\215(&Y)", Q_NULLPTR));
        action_bold->setText(QApplication::translate("MainWindow", "\347\262\227\344\275\223(&A)", Q_NULLPTR));
        action_italics->setText(QApplication::translate("MainWindow", "\346\226\234\344\275\223(&B)", Q_NULLPTR));
        action_underline->setText(QApplication::translate("MainWindow", "\344\270\213\345\210\222\347\272\277(&D)", Q_NULLPTR));
        action_strickout->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\347\272\277(&F)", Q_NULLPTR));
        action_online->setText(QApplication::translate("MainWindow", "\344\270\212\345\210\222\347\272\277(&G)", Q_NULLPTR));
        action_fontStyle->setText(QApplication::translate("MainWindow", "\345\255\227\344\275\223\346\240\267\345\274\217", Q_NULLPTR));
        action_fontSize->setText(QApplication::translate("MainWindow", "\345\255\227\344\275\223\345\244\247\345\260\217", Q_NULLPTR));
        action_newPage->setText(QApplication::translate("MainWindow", "\345\210\206\351\241\265\347\254\246(&p)", Q_NULLPTR));
        action_newLine->setText(QApplication::translate("MainWindow", "\346\215\242\350\241\214\347\254\246(&w)", Q_NULLPTR));
        action_aboutOFD->setText(QApplication::translate("MainWindow", "About &OFD", Q_NULLPTR));
        action_insertTable->setText(QApplication::translate("MainWindow", "\346\217\222\345\205\245\350\241\250\346\240\274", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        action_insertTable->setToolTip(QApplication::translate("MainWindow", "\346\217\222\345\205\245\350\241\250\346\240\274(I)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        action_drawTable->setText(QApplication::translate("MainWindow", "\350\241\250\346\240\274\347\273\230\345\210\266", Q_NULLPTR));
        action_justifyLeft->setText(QApplication::translate("MainWindow", "\345\267\246\345\257\271\351\275\220(&A)", Q_NULLPTR));
        action_justifyCenter->setText(QApplication::translate("MainWindow", "\345\261\205\344\270\255(&B)", Q_NULLPTR));
        action_justifyRight->setText(QApplication::translate("MainWindow", "\345\217\263\345\257\271\351\275\220(&C)", Q_NULLPTR));
        action_justifyFull->setText(QApplication::translate("MainWindow", "\344\270\244\347\253\257\345\257\271\351\275\220(&D)", Q_NULLPTR));
        action_kerning->setText(QApplication::translate("MainWindow", "\345\255\227\350\267\235", Q_NULLPTR));
        action_lineSpacing->setText(QApplication::translate("MainWindow", "\350\241\214\350\267\235:  1(&A)", Q_NULLPTR));
        action_superscript->setText(QApplication::translate("MainWindow", "\344\270\212\346\240\207 ", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_superscript->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+P", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_subscript->setText(QApplication::translate("MainWindow", "\344\270\213\346\240\207", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_subscript->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+B", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_A1->setText(QApplication::translate("MainWindow", "A&1", Q_NULLPTR));
        action_color->setText(QApplication::translate("MainWindow", "\351\242\234\350\211\262(&C)", Q_NULLPTR));
        action_A4->setText(QApplication::translate("MainWindow", "&A4   209\346\257\253\347\261\263\303\227296\346\257\253\347\261\263", Q_NULLPTR));
        action_A3->setText(QApplication::translate("MainWindow", "A3   &296\346\257\253\347\261\263\303\227419.1\346\257\253\347\261\263", Q_NULLPTR));
        action_8_259_367->setText(QApplication::translate("MainWindow", "&8\345\274\200   259\346\257\253\347\261\263\303\227367\346\257\253\347\261\263", Q_NULLPTR));
        action_16_183_259->setText(QApplication::translate("MainWindow", "&16\345\274\200  183\346\257\253\347\261\263\303\227259\346\257\253\347\261\263", Q_NULLPTR));
        action_find->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276(&F)", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_find->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action1_5_C->setText(QApplication::translate("MainWindow", "1.5\345\200\215\350\241\214\350\267\235(&B)", Q_NULLPTR));
        action2_C->setText(QApplication::translate("MainWindow", "2\345\200\215\350\241\214\350\267\235(&C)", Q_NULLPTR));
        action_paragraphSpacing->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\346\256\265\350\220\275\351\227\264\350\267\235(&D)", Q_NULLPTR));
        action_indentMore->setText(QApplication::translate("MainWindow", "\345\242\236\345\244\247\347\274\251\350\277\233(&F)", Q_NULLPTR));
        action_indentLess->setText(QApplication::translate("MainWindow", "\345\207\217\345\260\221\347\274\251\350\277\233(&G)", Q_NULLPTR));
        action_Z->setText(QApplication::translate("MainWindow", "\345\244\247\345\260\217(&Z)", Q_NULLPTR));
        action_insertRowAbove->setText(QApplication::translate("MainWindow", "\344\270\212\346\226\271\346\217\222\345\205\245\350\241\214(&A)", Q_NULLPTR));
        action_insertRowBelow->setText(QApplication::translate("MainWindow", "\344\270\213\346\226\271\346\217\222\345\205\245\350\241\214(&B)", Q_NULLPTR));
        action_Row->setText(QApplication::translate("MainWindow", "      \350\241\214(&R)...", Q_NULLPTR));
        action_L->setText(QApplication::translate("MainWindow", "\345\267\246\344\276\247\346\217\222\345\205\245\345\210\227(&L)", Q_NULLPTR));
        action_I_2->setText(QApplication::translate("MainWindow", "\345\217\263\344\276\247\346\217\222\345\205\245\345\210\227(&I)", Q_NULLPTR));
        action_Column->setText(QApplication::translate("MainWindow", "       \345\210\227(&C)...", Q_NULLPTR));
        action_deleteRow->setText(QApplication::translate("MainWindow", "\350\241\214(&R)", Q_NULLPTR));
        action_deleteColumn->setText(QApplication::translate("MainWindow", "\345\210\227(&C)", Q_NULLPTR));
        action_deleteTable->setText(QApplication::translate("MainWindow", "\350\241\250\346\240\274(&T)", Q_NULLPTR));
        action_chooseRow->setText(QApplication::translate("MainWindow", "\350\241\214(&R)", Q_NULLPTR));
        action_chooseColumn->setText(QApplication::translate("MainWindow", "\345\210\227(&C)", Q_NULLPTR));
        action_chooseTable->setText(QApplication::translate("MainWindow", "\350\241\250\346\240\274(&T)", Q_NULLPTR));
        action_cell->setText(QApplication::translate("MainWindow", "\345\215\225\345\205\203\346\240\274(&E)", Q_NULLPTR));
        action_mergeCell->setText(QApplication::translate("MainWindow", "\345\220\210\345\271\266\345\215\225\345\205\203\346\240\274(&A)", Q_NULLPTR));
        action_splitCell->setText(QApplication::translate("MainWindow", "\346\213\206\345\210\206\345\215\225\345\205\203\346\240\274(&E)", Q_NULLPTR));
        action_customSpaced->setText(QApplication::translate("MainWindow", "\350\207\252\345\256\232\344\271\211\350\241\214\350\267\235(&E)", Q_NULLPTR));
        action_A2->setText(QApplication::translate("MainWindow", "A2", Q_NULLPTR));
        action_A5->setText(QApplication::translate("MainWindow", "A&5", Q_NULLPTR));
        action_A6->setText(QApplication::translate("MainWindow", "A&6", Q_NULLPTR));
        action->setText(QApplication::translate("MainWindow", "&\350\241\250\346\240\274(&T)", Q_NULLPTR));
        action1_0_C->setText(QApplication::translate("MainWindow", "1.0\345\200\215\350\241\214\350\267\235", Q_NULLPTR));
        OFDMenue->setTitle(QApplication::translate("MainWindow", "OFD\346\226\207\344\273\266(&F)", Q_NULLPTR));
        editMenue->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221(&E)", Q_NULLPTR));
        insertMenue->setTitle(QApplication::translate("MainWindow", "\346\217\222\345\205\245(&F)", Q_NULLPTR));
        menu_6->setTitle(QApplication::translate("MainWindow", "\351\241\265\347\234\211\345\222\214\351\241\265\350\204\232(&A)", Q_NULLPTR));
        layoutMenue->setTitle(QApplication::translate("MainWindow", "\351\241\265\351\235\242\345\270\203\345\261\200(&L)", Q_NULLPTR));
        paperSize->setTitle(QApplication::translate("MainWindow", "\347\272\270\345\274\240\345\244\247\345\260\217", Q_NULLPTR));
        helpMenue->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", Q_NULLPTR));
        formatMenue->setTitle(QApplication::translate("MainWindow", "\346\240\274\345\274\217(&O)", Q_NULLPTR));
        aligningMenue->setTitle(QApplication::translate("MainWindow", "\345\257\271\351\275\220(&N)", Q_NULLPTR));
        textMenue->setTitle(QApplication::translate("MainWindow", "\346\226\207\346\234\254(&T)", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
        toolBar_2->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
