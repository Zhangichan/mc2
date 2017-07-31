/* 修改人：张姿婵
 * 对writeDocMaxUnitIDToXml()函数做了逻辑修改
 * 对onText()函数做了修改
 * 新增DelDir(const QString &）函数对指定文件夹进行删除
 * 所有的全局变量都加了注释，方便阅读
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QComboBox>
#include <QColorDialog>
#include <QLineEdit>
#include <QtWidgets>
#include <QMessageBox>
#include <QTextStream>
#include <QtXml>
#include <QFile>
#include <QTextDocument>
#include <QTextFrame>
#include <string>
#include <algorithm>
#include <QGraphicsTextItem>
#include <QSizePolicy>
#include <QUuid>
#include <QDate>
#include <QUrl>
#include <quazip5/JlCompress.h>


QString m_filepath = "./";

QLabel * pLabel1;
QLabel * pLabel2;
QFontComboBox * pFontBox;
QComboBox * pSizeBox;

int returnNumber;//回车数
int Time_NM;//回车判断哨兵


int PageNumber;//页数
std::vector<QString> PathName;//存放页数

int FIRST_ID;//ID跟踪
int time_ID[11];//存放字体名
std::vector<int> temporary;//存放所有ID

//boundary(x,y,width,height)
double mmx;
double mmy;
double mmBoundaryWidth;
double mmBoundaryHeigth;
double ty;

//(X,Y)
float X = 0.0;
float Y = 0.0;

//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
int ResID;//图片ID
size_t Temporary_NM = 0;//检查重复图片哨兵
std::vector<int> ImaID;//存放所有图片ID
std::vector<QString> ImaPath;//图片路径
//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget = new Widget(this);
    setCentralWidget (widget);

    createOfdStructure();//创建OFD框架
    createOfdXml();//创建OFD.xml

    createToolBars();//创建工具栏
    connectFunction();//连接信号与槽函数
    changePage();
    createStatusBar();//状态栏设置

    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//创建OFD框架
void MainWindow::createOfdStructure()
{
    //创建OFD框架
    QString pg = "Page_";
    QString PN = QString::number(PageNumber,10);//把0转换成字符串
    pg = pg + PN;
    PathName.push_back(pg);

    createFileDir(m_filepath +"ofd");
    createFileDir(m_filepath + "ofd/Doc_0");
    createFileDir(m_filepath + "ofd/Doc_0/Pages");
    createFileDir(m_filepath + "ofd/Doc_0/Pages/Page_0");
}

//创建ofd.xml文件
void MainWindow::createOfdXml()
{
    //OFD.xml
    //获取唯一标识码
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    strId.remove("{").remove("}").remove("-"); //去掉左右花括号和连字符

    //获取当前日期
    QDate current_date = QDate::currentDate();
    QString currentDate = current_date.toString("yyyy-MM-dd");

    //获取创建文档的应用程序
    QString creator = windowTitle();

    QDomDocument docO;
    QDomProcessingInstruction instruction;
    instruction = docO.createProcessingInstruction("xml","version = \"1.0\" encoding = \"UTF-8\"");
    docO.appendChild(instruction);

    QDomElement root = docO.createElementNS("http://www.ofdspec.org","OFD");
    root.setPrefix("ofd");
    QDomAttr doctype = docO.createAttribute("DocType");
    QDomAttr version =docO.createAttribute("Version");
    doctype.setValue(QString("OFD"));
    root.setAttributeNode(doctype);
    version.setValue(QString("1.0"));
    root.setAttributeNode(version);
    docO.appendChild(root);

    QDomElement docbody = docO.createElement("ofd:DocBody");
    root.appendChild(docbody);
    QDomElement docinfo = docO.createElement("ofd:DocInfo");
    docbody.appendChild(docinfo);
    QDomElement docroot = docO.createElement("ofd:DocRoot");
    QDomText roottext = docO.createTextNode("Doc_0/Document.xml");
    docroot.appendChild(roottext);
    docbody.appendChild(docroot);

    QDomElement docid = docO.createElement("ofd:DocID");//创建文档唯一标识
    docinfo.appendChild(docid);
    QDomElement docdate = docO.createElement("ofd:CreationDate");//文档的创建日期
    docinfo.appendChild(docdate);
    QDomElement doccreator = docO.createElement("ofd:Creator");//创建文档的应用程序
    docinfo.appendChild(doccreator);

    QDomElement author = docO.createElement("ofd:Author");//文档的作者
    docinfo.appendChild(author);
    QDomElement title = docO.createElement("ofd:Title");//文档的标题
    docinfo.appendChild(title);
    QDomElement docversion = docO.createElement("ofd:CreatorVersion");//创建文档的应用程序的版本信息
    docinfo.appendChild(docversion);

    QDomText text;
    text = docO.createTextNode(strId);
    docid.appendChild(text);

    text = docO.createTextNode(currentDate);
    docdate.appendChild(text);

    text = docO.createTextNode(creator);
    doccreator.appendChild(text);

    QFile ofdfile("./ofd/OFD.xml");
    if(!ofdfile.open(QIODevice::WriteOnly | QIODevice::Truncate))return;
    QTextStream outO(&ofdfile);
    docO.save(outO,4);
    ofdfile.close();
}

bool MainWindow::deleteDir(const QString &dirName)
{
    QDir directory(dirName);
    if (!directory.exists())//如果文件路径不存在
    {
        return true;
    }

    QString srcPath = QDir::toNativeSeparators(dirName);
    if (!srcPath.endsWith(QDir::separator()))
        srcPath += QDir::separator();

    QStringList fileNames = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    bool error = false;
    for (QStringList::size_type i=0; i != fileNames.size(); ++i)
    {
        QString filePath = srcPath + fileNames.at(i);
        QFileInfo fileInfo(filePath);
        if (fileInfo.isFile() || fileInfo.isSymLink())
        {
            QFile::setPermissions(filePath, QFile::WriteOwner);
            if (!QFile::remove(filePath))
            {
                error = true;
            }
        }
        else if (fileInfo.isDir())
        {
            if (!deleteDir(filePath))
            {
                error = true;
            }
        }
    }

    if (!directory.rmdir(QDir::toNativeSeparators(directory.path())))
    {
        error = true;
    }
    return !error;
}

//00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
bool MainWindow::DelDir(const QString &path)
{
    if (path.isEmpty()){
        return false;
    }
    QDir dir(path);
    if(!dir.exists()){
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot); //设置过滤
    QFileInfoList fileList = dir.entryInfoList(); // 获取所有的文件信息
    foreach (QFileInfo file, fileList){ //遍历文件信息
        if (file.isFile()){ // 是文件，删除
            file.dir().remove(file.fileName());
        }else{ // 递归删除
            DelDir(file.absoluteFilePath());
        }
    }
    return dir.rmpath(dir.absolutePath()); // 删除文件夹
}


//解析Content.xml
void MainWindow::parsingContentXml()
{
    QStringList ls;
    QDir dir("./ofd/Doc_0/Pages");
    QFileInfoList info_list = dir.entryInfoList(QDir::Files | QDir::AllDirs);
    foreach(QFileInfo file_info, info_list)
    {
        if (file_info.isDir())
        {
            ls<<file_info.baseName();
        }
    }
    for(int i = 2;i<ls.size();i++)
    {
        QFile file("./ofd/Doc_0/Pages/" + ls.at(i) + "/Content.xml");
        if (!file.open(QFile::ReadWrite))
            return;
        QDomDocument doc;
        if(!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();
        QDomNodeList listTextObject = doc.elementsByTagName("ofd:TextObject");
        for(int i = 0;i<listTextObject.count();i++)
        {
            QTextCharFormat fmt;
            //字体大小
            QDomElement e = listTextObject.at(i).toElement();
            double fontsize = e.attribute("Size").toDouble();
            qreal myfontsize = fontsize * 2.845;
            //是否设置斜体
            QString italic = e.attribute("Italic");
            if(italic == "true")
            {
                fmt.setFontItalic(true);
            }
            //字体
            QString fontId = e.attribute("Font");//Content.xml里的字体ID
            QString familyName;//最终想要获得的字体名字
            QFile file1("./ofd/Doc_0/PublicRes.xml");
            if (!file1.open(QFile::ReadOnly))return;
            QDomDocument doc1;
            if(!doc1.setContent(&file1))
            {
                file1.close();
                return;
            }
            file1.close();
            QDomNodeList listfontPublic = doc1.elementsByTagName("ofd:Font");

            for(int j = 0;j<listfontPublic.count();j++)
            {
                QDomElement e1 = listfontPublic.at(j).toElement();
                QString fontId1 = e1.attribute("ID");
                if(fontId == fontId1)
                {
                    familyName = e1.attribute("FamilyName");
                }
            }
            //字体颜色
            QDomNode fillcolor= e.firstChild();
            QDomElement color = fillcolor.toElement();
            int a,b,c;
            QString mycolor = color.attribute("Value");
            QStringList mycolorlist = mycolor.split(" ");
            QString str0 = mycolorlist.at(0);
            a = str0.toInt();
            QString str1 = mycolorlist.at(1);
            b = str1.toInt();
            QString str2 = mycolorlist.at(2);
            c= str2.toInt();
            QColor color1;
            color1.setRed(a);
            color1.setGreen(b);
            color1.setBlue(c);

            //内容
            QDomNode textcode = color.nextSibling();
            QString mytext = textcode.toElement().text();

            //将字体颜色大小设置到样式中
            fmt.setFontFamily(familyName);
            fmt.setFontPointSize(myfontsize);
            fmt.setForeground(color1);

            QTextCursor cursor = widget->textEdit->textCursor();
            cursor.setCharFormat(fmt);
            if(mytext.isEmpty())
            {
                cursor.insertText(" ");
            }
            else cursor.insertText(mytext);
            widget->textEdit->setTextCursor(cursor);
            parsingPageSize();
        }
    }
}

//解析页面大小
void MainWindow::parsingPageSize()
{
    QFile file("./ofd/Doc_0/Pages/Page_0/Content.xml");
    if (!file.open(QFile::ReadOnly))
        return;
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    //设置纸张大小
    QDomNodeList listPhysicalBox = doc.elementsByTagName("ofd:PhysicalBox");
    QDomElement physicalBox = listPhysicalBox.at(0).toElement();
    QString pagesize = physicalBox.text();
    QStringList pagesizelist = pagesize.split(" ");
    int a,b;
    a = pagesizelist.at(2).toInt();
    b = pagesizelist.at(3).toInt();
    if(a == 105 && b == 148)
    {
        widget->textEdit->setPageFormat(QPageSize::A6);
        widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
    if(a == 148 && b == 210)
    {
        widget->textEdit->setPageFormat(QPageSize::A5);
        widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
    if(a == 210 && b == 297)
    {
        widget->textEdit->setPageFormat(QPageSize::A4);
        widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
    if(a == 297 && b == 420)
    {
        widget->textEdit->setPageFormat(QPageSize::A3);
        widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
    if(a == 420 && b == 594)
    {
        widget->textEdit->setPageFormat(QPageSize::A2);
        widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
    if(a == 594 && b == 841)
    {
        widget->textEdit->setPageFormat(QPageSize::A1);
        widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
}

bool MainWindow::onText()
{
    FIRST_ID = 1;
    for(int i = 0; i < 11; i++)
    {
        time_ID[i] = 0;
    }

    PageNumber = 0;

    createPublicResXml();
    createDocument();

    //000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
    //每次重新构建,原有的Pages和DocumentRes.xml和Res都要全部删除
    if(!deleteDir("./ofd/Doc_0/Pages"))
    {
        QFileInfo resFileInfo(m_filepath + "ofd/Doc_0/Res");
        QFileInfo resXmlInfo(m_filepath + "ofd/Doc_0/DocumnetRes.xml");

        if(resFileInfo.isDir())
        {
            if(!DelDir("./ofd/Doc_0/Res"))//Res存在即删除
            {
            }
        }
        if(resXmlInfo.isDir())//DcumentRes.xml存在即删除
        {
            QFile file;
            file.remove("./ofd/Doc_0/DocumentRes.xml");
        }
    //00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
        createContentXml();
        mmx = 0.0;
        mmy = 0.0;
        mmBoundaryWidth = 0.0;
        mmBoundaryHeigth = 0.0;
        compare = false;
        Time_NM = 1;
        returnNumber = 0;

        ty = 0.0;
    }

    QTextDocument *editorDocument = widget->textEdit->document();

    //当需要进行文档结构导航时，从根框架开始(根框架提供了访问整个文档结构的能力)
    QTextFrame *root = editorDocument->rootFrame();//定位到根框架

    QTextFrame::iterator i;//迭代器，遍历框架中的所有子框架和文本块
    for(i = root->begin();!(i.atEnd());++i)
    {
        QTextBlock currentBlock = i.currentBlock();//获取当前文本块
        ++returnNumber;//每一个片段即包含一个回车符
        if(currentBlock.isValid())//如果文本块有效
        {
            QTextBlock::iterator j;//遍历当前文本块
            for(j = currentBlock.begin();!(j.atEnd());++j)
            {
                QTextFragment currentFragment = j.fragment();//获取当前文本片段
                if(currentFragment.isValid())//如果当前文本片段有效
                {
                    //对文本片段内的具体数据进行判别:isCharFormat()/isImageFormat()/isTableFormat()
                    if(currentFragment.charFormat().isImageFormat())
                    {
                        //如果是图片格式的数据，先获取图片的名字，再把图片的具体格式信息保存到路径Res文件下
                        QTextImageFormat newImageFormat = currentFragment.charFormat().toImageFormat();
                        if (newImageFormat.isValid())
                        {
                            processImageFragment(newImageFormat);
                        }
                    }
                    if((currentFragment.charFormat().isCharFormat()) && !(currentFragment.charFormat().isImageFormat()))
                    {
                        //如果是字符数据，则读入到content.xml文件中
                        QTextCharFormat textFormat = currentFragment.charFormat().toCharFormat();//片段样式转换
                        if(textFormat.isValid())
                        {
                            processTextContent(currentFragment, textFormat);
                        }
                    }
                }
            }
        }
    }
    return true;
}

//单个字读取
void MainWindow::processTextContent(QTextFragment current, QTextCharFormat textFormat)
{
    QString str1 = current.text();//得到当前片段的文本内容
    QString str2;
    int i;
    for(i=0; i<str1.length(); i++)
    {
        str2 = str1.mid(i,1);//进行截取
        writeTextToXml(str2, textFormat, ++FIRST_ID);//截取后的格式数据(文本内容，文本格式，文本ID)存入xml文件中
    }
}

void MainWindow::createDocument()
{
    QString currentPage = PathName.at(PageNumber);
    QString Loc = "Pages/" + currentPage + "/Content.xml";

    QDomDocument docD;
    QDomProcessingInstruction instruction;
    instruction = docD.createProcessingInstruction("xml","version = \"1.0\" encoding = \"UTF-8\"");
    docD.appendChild(instruction);
    QDomElement document = docD.createElementNS("http://www.ofdspec.org","Document");
    document.setPrefix("ofd");
    docD.appendChild(document);

    QDomElement commonData = docD.createElement("ofd:CommonData");
    document.appendChild(commonData);
    QDomElement maxunitid = docD.createElement("ofd:MaxUnitID");
    commonData.appendChild(maxunitid);
    QDomText pubtext;
    pubtext = docD.createTextNode("3");
    maxunitid.appendChild(pubtext);

    QDomElement pagearea = docD.createElement("ofd:PageArea");
    commonData.appendChild(pagearea);
    QDomElement physicalbox = docD.createElement("ofd:PhysicalBox");
    pagearea.appendChild(physicalbox);
    pubtext = docD.createTextNode("0 0 210 297");
    physicalbox.appendChild(pubtext);

    QDomElement publicres = docD.createElement("ofd:PublicRes");
    pubtext = docD.createTextNode("PublicRes.xml");
    publicres.appendChild(pubtext);
    commonData.appendChild(publicres);
    QDomElement pages = docD.createElement("ofd:Pages");//页树(目前只指定一页)
    document.appendChild(pages);
    QDomElement page = docD.createElement("ofd:Page");
    pages.appendChild(page);
    page.setAttribute("BaseLoc",Loc);
    page.setAttribute("ID",FIRST_ID);//ID=1

    QFile documentfile("./ofd/Doc_0/Document.xml");
    if(!documentfile.open(QIODevice::WriteOnly | QIODevice::Truncate))return;
    QTextStream outD(&documentfile);
    docD.save(outD,4);
    documentfile.close();

}

//创建Content.xml
void MainWindow::createContentXml()
{
    QDomDocument docC;
    //说明
    QDomProcessingInstruction instruction;
    instruction = docC.createProcessingInstruction("xml","version = \"1.0\" encoding = \"UTF-8\" standalone = \"yes\"");
    docC.appendChild(instruction);
    //添加根元素
    QDomElement pageC = docC.createElementNS("http://www.ofdspec.org","Page");
    pageC.setPrefix("ofd");
    docC.appendChild(pageC);

    //添加Area元素
    QDomElement area = docC.createElement("ofd:Area");
    pageC.appendChild(area);
    QDomElement physicalBox = docC.createElement("ofd:PhysicalBox");
    QDomText phytext = docC.createTextNode("0 0 210 297");
    physicalBox.appendChild(phytext);
    area.appendChild(physicalBox);

    //添加Content元素
    QDomElement content = docC.createElement("ofd:Content");
    pageC.appendChild(content);
    //添加Layer元素
    QDomElement layer = docC.createElement("ofd:Layer");

    if(PageNumber == 0)
    {
        layer.setAttribute("ID",++FIRST_ID);//ID=2
    }else{
        layer.setAttribute("ID",++FIRST_ID);//根据Document.xml的页面ID先递增，此处再递增ID
    }

    content.appendChild(layer);

    QString currentPage = PathName.at(PageNumber);
    QFile contentfile("./ofd/Doc_0/Pages/" + currentPage + "/Content.xml");
    if(!contentfile.open(QIODevice::WriteOnly | QIODevice::Truncate))return;
    QTextStream outC(&contentfile);
    docC.save(outC,4);
    contentfile.close();
}

//创建PublicRes.xml
void MainWindow::createPublicResXml()
{
    QDomDocument docP;
    QDomProcessingInstruction instruction;
    instruction = docP.createProcessingInstruction("xml","version = \"1.0\" encoding = \"UTF-8\" standalone = \"yes\"");
    docP.appendChild(instruction);
    QDomElement resp = docP.createElementNS("http://www.ofdspec.org","Res");
    resp.setPrefix("ofd");
    resp.setAttribute("BaseLoc","Res");
    docP.appendChild(resp);
    QDomElement fonts = docP.createElement("ofd:Fonts");
    resp.appendChild(fonts);
    QDomElement colorspaces = docP.createElement("ofd:ColorSpaces");
    resp.appendChild(colorspaces);

    QFile publicresfile("./ofd/Doc_0/PublicRes.xml");
    if(!publicresfile.open(QIODevice::WriteOnly | QIODevice::Truncate))return;
    QTextStream outP(&publicresfile);
    docP.save(outP,4);
    publicresfile.close();

}

//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void MainWindow:: createDocumentRes()
{
    QDomDocument docDR;
    QDomProcessingInstruction instruction;
    instruction = docDR.createProcessingInstruction("xml","version = \"1.0\" encoding = \"UTF-8\" standalone = \"yes\"");
    docDR.appendChild(instruction);
    QDomElement resD = docDR.createElementNS("http://www.ofdspec.org","Res");
    resD.setPrefix("ofd");
    resD.setAttribute("BaseLoc","Res");
    docDR.appendChild(resD);

    QDomElement multiMedias = docDR.createElement("ofd:MultiMedias");
    resD.appendChild(multiMedias);

    QFile documentresfile("./ofd/Doc_0/DocumentRes.xml");
    if(!documentresfile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QTextStream outP(&documentresfile);
    docDR.save(outP,4);
    documentresfile.close();
}

//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void MainWindow::addMediasToRes(QString imageName, QString format)
{
    QFile file("./ofd/Doc_0/DocumentRes.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomNodeList list = doc.elementsByTagName("ofd:MultiMedias");
    QDomElement a = list.at(0).toElement();
    QDomElement multiMedia = doc.createElement("ofd:MultiMedia");
    //ID
    multiMedia.setAttribute("ID",++FIRST_ID);
    ResID = FIRST_ID;
    ImaID.push_back(ResID);

    //Type
    multiMedia.setAttribute("Type","Image");

    //Format
    multiMedia.setAttribute("Format",format);

    QDomElement mediaFile = doc.createElement("ofd:MediaFile");
    QDomText text;
    text = doc.createTextNode(imageName);
    mediaFile.appendChild(text);
    multiMedia.appendChild(mediaFile);
    a.appendChild(multiMedia);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}

//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void MainWindow::writeImageToContent(/*QString fileName,*/QTextImageFormat imageFormat)
{
    QString currentPage = PathName.at(PageNumber);
    QFile file("./ofd/Doc_0/Pages/" + currentPage + "/Content.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomElement imageObject = doc.createElement("ofd:ImageObject");

    //ID
    imageObject.setAttribute("ID",++FIRST_ID);

    //ResourceID
    if(!flag)
    {
        for(size_t i = 0; i < ImaID.size(); i++)
        {
            if(i == Temporary_NM)
            {
                int j = ImaID.at(i);
                imageObject.setAttribute("ResourceID",j);
            }
        }
    }else{
        imageObject.setAttribute("ResourceID",ResID);
    }


    //Boundary
//    QFontMetrics fm(imageFormat.font());

    //(originX,originY)为编辑框的顶点位置
    int originX = widget->textEdit->geometry().x()-6;
    int originY = widget->textEdit->geometry().y()-6;

    //(x1,y1)为出血框顶点位置
    double x1 = originX + widget->textEdit->m_pageMetrics.mmPageMargins().left();
    double y1 = originY + widget->textEdit->m_pageMetrics.mmPageMargins().top();

    //获取图片的宽度
    double mmBWidth0 = imageFormat.width();
//    double mmBWidth0 =fm.width(fileName);
    double mmBWidth =mmBWidth0/qApp->desktop()->logicalDpiX()*25.4;

    //获取图片的高度
    double mmCHeigth0 = imageFormat.height();
//    double mmCHeigth0 = fm.lineSpacing();
    double mmCHeigth = mmCHeigth0/qApp->desktop()->logicalDpiY()*25.4;

    //编辑区域的宽度 = 当前页面宽度-两边边缘宽度
    double mmLineWidget =widget->textEdit->m_pageMetrics.mmPageSize().width()-widget->textEdit->m_pageMetrics.mmPageMargins().left()-widget->textEdit->m_pageMetrics.mmPageMargins().right();

    //获取右边缘的距离、上边缘
    double mmRightMargin =  widget->textEdit->m_pageMetrics.mmPageMargins().right();
    double mmBottomMargin = widget->textEdit->m_pageMetrics.mmPageMargins().bottom();

    //获取当前页面的高度
    double mmPaHeigth = widget->textEdit->m_pageMetrics.mmPageSize().height();

    if(mmBoundaryWidth == 0.0 && mmBoundaryHeigth == 0.0){  //对第一个片段定位

        mmx = x1;
        mmy = y1;
        mmBoundaryWidth = mmBWidth;
        mmBoundaryHeigth = mmCHeigth;

    }else{

        if((mmx< mmLineWidget+mmRightMargin-5.69) )  //针对一行未满的情况讨论
        {
            if(Time_NM == returnNumber)   //未索引到换行，mmy的值与之前的不变
            {
                mmy = y1;
                if(compare){

                    mmy=ty;
                }

                mmBoundaryWidth = mmBWidth;
                mmBoundaryHeigth = mmCHeigth;


            }else{  //索引到换行，mmy的值改变
                mmx = x1;
                mmy = mmy + mmBoundaryHeigth/* + space*/;  //gaigaigaigaigaigaigaigaigaigaigaigaigaigai
                mmBoundaryWidth = mmBWidth;
                mmBoundaryHeigth = mmCHeigth;

                compare = true;
                ty = mmy;

                ++Time_NM;//每换一行都要加

                if((mmPaHeigth-mmBottomMargin) < mmy+mmCHeigth)//判断分页机制  (多加了个mmCHeigth)
                                                                   //gaigaigaigaigaigaigaigaigaigaigaigaigaigai
                {
                    compare = false;
                    mmy = y1;
                    mmx = x1;
                    nextContent();

                }
            }


        }else{//判断加纵行数

            mmx = x1;
            mmy = mmy + mmBoundaryHeigth/* + space*/;    //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai

            mmBoundaryWidth = mmBWidth;
            mmBoundaryHeigth = mmCHeigth;

            compare = true;
            ty = mmy;

            if((mmPaHeigth-mmBottomMargin) < mmy+mmCHeigth)//判断分页机制 (多加了个mmCHeigth)
                                                               //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
            {
                compare = false;
                mmy = y1;
                mmx = x1;
                nextContent();
            }
        }
    }

    QString boundary = QString("%1 %2 %3 %4").arg(QString::number(mmx,10,2), QString::number(mmy,10,2),QString::number(mmBoundaryWidth,10,2), QString::number(mmBoundaryHeigth,10,2));
    mmx += mmBoundaryWidth;

    imageObject.setAttribute("Boundary",boundary);

    QDomNodeList oldList = root.elementsByTagName("ofd:Layer");
    QDomElement a = oldList.at(0).toElement();
    a.appendChild(imageObject);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}

//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void MainWindow::writeResToDocument()
{
    QFile file("./ofd/Doc_0/Document.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomNodeList list = doc.elementsByTagName("ofd:CommonData");
    QDomElement a = list.at(0).toElement();
    QDomElement documentRes = doc.createElement("ofd:DocumentRes");
    QDomText text;
    text = doc.createTextNode("DocumentRes.xml");
    documentRes.appendChild(text);
    a.appendChild(documentRes);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}
//gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
//Content文件内的各种属性读入
void MainWindow::writeTextToXml(QString content, QTextCharFormat textFormat,int number)
{
    //Size
    QString fontfamily = textFormat.fontFamily();
    qreal size = textFormat.fontPointSize();

    //Value
    double size1 = double(int((size/2.845)*100))/100.0;  //字号转换成毫米
    QBrush brush = textFormat.foreground();//获取颜色
    QColor color = brush.color();
    QString msg = QString("%1 %2 %3").arg(QString::number(color.red()), QString::number(color.green()), QString::number(color.blue()));

    //X,Y
    QFontMetrics fm(textFormat.font());

    float x = fm.boundingRect(content).x();
    float y = -fm.boundingRect(content).y();

    X = x/qApp->desktop()->logicalDpiX()*25.4;
    Y = y/qApp->desktop()->logicalDpiY()*25.4;


    //Boundary
    int originX = widget->textEdit->geometry().x()-6;
    int originY = widget->textEdit->geometry().y()-6;


    double x1 = originX + widget->textEdit->m_pageMetrics.mmPageMargins().left();
    double y1 = originY + widget->textEdit->m_pageMetrics.mmPageMargins().top();

    double mmBWidth0 =fm.width(content);
    double mmBWidth =mmBWidth0/qApp->desktop()->logicalDpiX()*25.4;

    //此处改成了leading（）gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
    //    double s = fm.leading();
    //    double mmCHeigth0 = fm.height();
        double mmCHeigth0 = fm.lineSpacing();
    //    double space = s/qApp->desktop()->logicalDpiY()*25.4;
        double mmCHeigth = mmCHeigth0/qApp->desktop()->logicalDpiY()*25.4;

        double mmLineWidget =widget->textEdit->m_pageMetrics.mmPageSize().width()-widget->textEdit->m_pageMetrics.mmPageMargins().left()-widget->textEdit->m_pageMetrics.mmPageMargins().right();

        double mmRightMargin =  widget->textEdit->m_pageMetrics.mmPageMargins().right();
        double mmBottomMargin = widget->textEdit->m_pageMetrics.mmPageMargins().bottom();


        double mmPaHeigth = widget->textEdit->m_pageMetrics.mmPageSize().height();

        if(mmBoundaryWidth == 0.0&&mmBoundaryHeigth==0.0){  //对第一个字符串片段定位

            mmx = x1;
            mmy = y1;
            mmBoundaryWidth = mmBWidth;
            mmBoundaryHeigth = mmCHeigth;

        }else{

            if((mmx< mmLineWidget+mmRightMargin-5.69) )  //针对一行未满的情况讨论
            {
                if(Time_NM == returnNumber)   //未索引到换行，mmy的值与之前的不变
                {
                    mmy = y1;
                    if(compare){

                        mmy=ty;
                    }

                    mmBoundaryWidth = mmBWidth;
                    mmBoundaryHeigth = mmCHeigth;


                }else{  //索引到换行，mmy的值改变
                    mmx = x1;
                    mmy = mmy + mmBoundaryHeigth/* + space*/;  //gaigaigaigaigaigaigaigaigaigaigaigaigaigai
                    mmBoundaryWidth = mmBWidth;
                    mmBoundaryHeigth = mmCHeigth;

                    compare = true;
                    ty = mmy;

                    ++Time_NM;//每换一行都要加

                    if((mmPaHeigth-mmBottomMargin) < mmy+mmCHeigth)//判断分页机制  (多加了个mmCHeigth)
                                                                   //gaigaigaigaigaigaigaigaigaigaigaigaigaigai
                    {
                        compare = false;
                        mmy = y1;
                        mmx = x1;
                        nextContent();

                    }
                }


            }else{//判断加纵行数

                mmx = x1;
                mmy = mmy + mmBoundaryHeigth/* + space*/;    //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai

                mmBoundaryWidth = mmBWidth;
                mmBoundaryHeigth = mmCHeigth;

                compare = true;
                ty = mmy;

                if((mmPaHeigth-mmBottomMargin) < mmy+mmCHeigth)//判断分页机制 (多加了个mmCHeigth)
                                                               //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
                {
                    compare = false;
                    mmy = y1;
                    mmx = x1;
                    nextContent();
                }
            }
        }

        QString boundary = QString("%1 %2 %3 %4").arg(QString::number(mmx,10,2), QString::number(mmy,10,2),QString::number(mmBoundaryWidth,10,2), QString::number(mmBoundaryHeigth,10,2));
        mmx += mmBoundaryWidth;


    //Deltax
    int len = content.length();
    QString tmp = {};
    for(int i = 1; i < len; i++)
    {
        QString variate = (QString("%1").arg(size1)) + " ";
        tmp += variate;
    }
    tmp = tmp.left(tmp.length() - 1);
    QString deltax = tmp;

    QString currentPage = PathName.at(PageNumber);
    QFile file("./ofd/Doc_0/Pages/" + currentPage +"/Content.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomElement textObject = doc.createElement("ofd:TextObject");
    textObject.setAttribute("ID",number);

    writeTextToPublicResXml(textFormat);

    textObject.setAttribute("Boundary",boundary);

    if(fontfamily == "华文行楷")
    {
        textObject.setAttribute("Font",time_ID[0]);
    }
    if(fontfamily == "华文隶书")
    {
        textObject.setAttribute("Font",time_ID[1]);
    }
    if(fontfamily == "华文中宋")
    {
        textObject.setAttribute("Font",time_ID[2]);
    }
    if(fontfamily == "华文楷体")
    {
        textObject.setAttribute("Font",time_ID[3]);
    }
    if(fontfamily == "仿宋")
    {
        textObject.setAttribute("Font",time_ID[4]);
    }
    if(fontfamily == "楷体")
    {
        textObject.setAttribute("Font",time_ID[5]);
    }
    if(fontfamily == "黑体")
    {
        textObject.setAttribute("Font",time_ID[6]);
    }
    if(fontfamily == "方正小标宋")
    {
        textObject.setAttribute("Font",time_ID[7]);
    }
    if(fontfamily == "方正仿宋")
    {
        textObject.setAttribute("Font",time_ID[8]);
    }
    if(fontfamily == "方正黑体")
    {
        textObject.setAttribute("Font",time_ID[9]);
    }

    textObject.setAttribute("Size",size1);

    //Italic
    if(textFormat.fontItalic())
    {
        textObject.setAttribute("Italic","true");
    }else if(!textFormat.fontItalic())
    {
        textObject.setAttribute("Italic","false");
    }

    //Bold
//    if(textFormat.font().bold())
//    {
//        textObject.setAttribute("Bold","true");
//    }else if(!textFormat.fontItalic())
//    {
//        textObject.setAttribute("Bold","false");
//    }

    temporary.push_back(number);

    //ColorSpace
    QDomElement fillColor = doc.createElement("ofd:FillColor");
    fillColor.setAttribute("Value",msg);
    fillColor.setAttribute("ColorSpace",time_ID[10]);

    QDomElement textCode = doc.createElement("ofd:TextCode");
    QString xm = QString::number(X,10,2);
    QString ym = QString::number(Y,10,2);

    textCode.setAttribute("X",xm);
    textCode.setAttribute("Y",ym);
    if(1 != len)
    {
        textCode.setAttribute("Deltax",deltax);
    }

    //text
    QDomText text;
    text = doc.createTextNode(content);
    textCode.appendChild(text);


    QDomNodeList oldList = root.elementsByTagName("ofd:Layer");
    QDomElement a = oldList.at(0).toElement();
    a.appendChild(textObject);
    textObject.appendChild(fillColor);
    textObject.appendChild(textCode);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}

//创建页号和页名
void MainWindow::paging()
{
    QString pg = "Page_";
    ++PageNumber;//页码递增
    QString PN = QString::number(PageNumber,10);
    pg = pg + PN;
    PathName.push_back(pg);//如：page_0
    createFileDir(m_filepath + ("ofd/Doc_0/Pages/" + pg));
}

//下一页Content.xml的写入
void MainWindow::nextContent()
{
    paging();
    addDoucumentPart();
    createContentXml();
}

//每增添一页，添加相应的page资源到Document.xml中
void MainWindow::addDoucumentPart()
{
    QString currentPage = PathName.at(PageNumber);
    QString Loc = "Pages/" + currentPage + "/Content.xml";

    QFile file("./ofd/Doc_0/Document.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomNodeList list = doc.elementsByTagName("ofd:Pages");
    QDomElement a = list.at(0).toElement();
    QDomElement page = doc.createElement("ofd:Page");
    page.setAttribute("ID",++FIRST_ID);
    page.setAttribute("BaseLoc",Loc);

    a.appendChild(page);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();

}

//Content.xml文件中PhysicalBox的添加
void MainWindow::writeContentPhysicalBoxToXml()
{
    int originX = widget->textEdit->geometry().x();
    int originY = widget->textEdit->geometry().y();
    int Width = widget->textEdit->m_pageMetrics.mmPageSize().width();
    int Height = widget->textEdit->m_pageMetrics.mmPageSize().height();

    QString X = QString::number(originX,10,2);//类型转换
    QString Y = QString::number(originY,10,2);//类型转换
    QString W = QString::number(Width,10,2);//类型转换
    QString H = QString::number(Height,10,2);//类型转换

    QString Coord = X + " " + Y + " " + W + " " + H;

    QFile file("./ofd/Doc_0/Pages/Page_0/Content.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomNodeList list0 = doc.elementsByTagName("ofd:PhysicalBox");
    QDomNode node = list0.at(0);
    QDomNode nodeOld = node.firstChild();
    node.firstChild().setNodeValue(Coord);
    QDomNode nodeNew = node.firstChild();
    node.replaceChild(nodeNew,nodeOld);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}

//PublicRes.xml具体属性添加
void MainWindow::writeTextToPublicResXml(QTextCharFormat textFormat)
{
    //PublicRes.xml具体属性添加
    QString fontfamily = textFormat.fontFamily();

    QBrush brush = textFormat.foreground();//获取颜色
    QColor color = brush.color();
    int x = color.red();
    int y = color.green();
    int z = color.blue();
    QString type;
    if( ((x>=0) && (x<=255)) && ((y>=0) && (y<=255)) && ((z>=0) && (z<=255)))
    {
        type = "RGB";
    }

    QFile file("./ofd/Doc_0/PublicRes.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();

    if(fontfamily == "华文行楷")
    {
        if(0 == time_ID[0])
        {
            QDomNodeList list = root.elementsByTagName("ofd:Fonts");
            QDomElement b = list.at(0).toElement();
            QDomElement font = doc.createElement("ofd:Font");

            time_ID[0] = ++FIRST_ID;
            font.setAttribute("ID",time_ID[0]);
            font.setAttribute("FontName",fontfamily);
            font.setAttribute("FamilyName",fontfamily);

            b.appendChild(font);
        }
    }
    if(fontfamily == "华文隶书")
    {
        if(0 == time_ID[1])
        {
            QDomNodeList list = root.elementsByTagName("ofd:Fonts");
            QDomElement b = list.at(0).toElement();
            QDomElement font = doc.createElement("ofd:Font");

            time_ID[1] = ++FIRST_ID;
            font.setAttribute("ID",time_ID[1]);
            font.setAttribute("FontName",fontfamily);
            font.setAttribute("FamilyName",fontfamily);

            b.appendChild(font);
        }
    }
    if(fontfamily == "华文中宋")
    {
        if(0 == time_ID[2])
        {
            QDomNodeList list = root.elementsByTagName("ofd:Fonts");
            QDomElement b = list.at(0).toElement();
            QDomElement font = doc.createElement("ofd:Font");

            time_ID[2] = ++FIRST_ID;
            font.setAttribute("ID",time_ID[2]);
            font.setAttribute("FontName",fontfamily);
            font.setAttribute("FamilyName",fontfamily);

            b.appendChild(font);
        }
    }
    if(fontfamily == "华文楷体")
    {
        if(0 == time_ID[3])
        {
            QDomNodeList list = root.elementsByTagName("ofd:Fonts");
            QDomElement b = list.at(0).toElement();
            QDomElement font = doc.createElement("ofd:Font");

            time_ID[3] = ++FIRST_ID;
            font.setAttribute("ID",time_ID[3]);
            font.setAttribute("FontName",fontfamily);
            font.setAttribute("FamilyName",fontfamily);

            b.appendChild(font);
        }
    }
    if(fontfamily == "仿宋")
    {
        if(0 == time_ID[4])
        {
            QDomNodeList list = root.elementsByTagName("ofd:Fonts");
            QDomElement b = list.at(0).toElement();
            QDomElement font = doc.createElement("ofd:Font");

            time_ID[4] = ++FIRST_ID;
            font.setAttribute("ID",time_ID[4]);
            font.setAttribute("FontName",fontfamily);
            font.setAttribute("FamilyName",fontfamily);

            b.appendChild(font);
        }
    }
    if(fontfamily == "楷体")
    {
        if(0 == time_ID[5])
        {
            QDomNodeList list = root.elementsByTagName("ofd:Fonts");
            QDomElement b = list.at(0).toElement();
            QDomElement font = doc.createElement("ofd:Font");

            time_ID[5] = ++FIRST_ID;
            font.setAttribute("ID",time_ID[5]);
            font.setAttribute("FontName",fontfamily);
            font.setAttribute("FamilyName",fontfamily);

            b.appendChild(font);
        }
    }
    if(fontfamily == "黑体")
    {
        if(0 == time_ID[6])
        {
            QDomNodeList list = root.elementsByTagName("ofd:Fonts");
            QDomElement b = list.at(0).toElement();
            QDomElement font = doc.createElement("ofd:Font");

            time_ID[6] = ++FIRST_ID;
            font.setAttribute("ID",time_ID[6]);
            font.setAttribute("FontName",fontfamily);
            font.setAttribute("FamilyName",fontfamily);

            b.appendChild(font);
        }
    }
    if(fontfamily == "方正小标宋")
    {
        if(0 == time_ID[7])
        {
            QDomNodeList list = root.elementsByTagName("ofd:Fonts");
            QDomElement b = list.at(0).toElement();
            QDomElement font = doc.createElement("ofd:Font");

            time_ID[7] = ++FIRST_ID;
            font.setAttribute("ID",time_ID[7]);
            font.setAttribute("FontName",fontfamily);
            font.setAttribute("FamilyName",fontfamily);

            b.appendChild(font);
        }
    }
    if(fontfamily == "方正仿宋")
    {
        if(0 == time_ID[8])
        {
            QDomNodeList list = root.elementsByTagName("ofd:Fonts");
            QDomElement b = list.at(0).toElement();
            QDomElement font = doc.createElement("ofd:Font");

            time_ID[8] = ++FIRST_ID;
            font.setAttribute("ID",time_ID[8]);
            font.setAttribute("FontName",fontfamily);
            font.setAttribute("FamilyName",fontfamily);

            b.appendChild(font);
        }
    }
    if(fontfamily == "方正黑体")
    {
        if(0 == time_ID[9])
        {
            QDomNodeList list = root.elementsByTagName("ofd:Fonts");
            QDomElement b = list.at(0).toElement();
            QDomElement font = doc.createElement("ofd:Font");

            time_ID[9] = ++FIRST_ID;
            font.setAttribute("ID",time_ID[9]);
            font.setAttribute("FontName",fontfamily);
            font.setAttribute("FamilyName",fontfamily);

            b.appendChild(font);
        }
    }

    if(type == "RGB")//颜色空间为RGB时,其值为(X,Y,Z）
    {
        if(0 == time_ID[10])
        {
            QDomNodeList list1 = doc.elementsByTagName("ofd:ColorSpaces");
            QDomElement c = list1.at(0).toElement();
            QDomElement colorspace = doc.createElement("ofd:ColorSpace");

            time_ID[10] = ++FIRST_ID;
            colorspace.setAttribute("ID",time_ID[10]);
            colorspace.setAttribute("Type",type);

            c.appendChild(colorspace);
        }
    }

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}

//重置PhysicalBox到Document.xml
void MainWindow::writeDocPhysicalBoxToXml()
{
    //重置PhysicalBox到Document.xml
    int originX = widget->textEdit->geometry().x();
    int originY = widget->textEdit->geometry().y();
    int Width = widget->textEdit->m_pageMetrics.mmPageSize().width();
    int Height = widget->textEdit->m_pageMetrics.mmPageSize().height();

    QString X = QString::number(originX,10,2);//类型转换
    QString Y = QString::number(originY,10,2);//类型转换
    QString W = QString::number(Width,10,2);//类型转换
    QString H = QString::number(Height,10,2);//类型转换

    QString Coord = X + " " + Y + " " + W + " " + H;

    QFile file("./ofd/Doc_0/Document.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomNodeList list1 = doc.elementsByTagName("ofd:PhysicalBox");
    QDomNode node1 = list1.at(0);
    QDomNode nodeOld1 = node1.firstChild();
    node1.firstChild().setNodeValue(Coord);
    QDomNode nodeNew1 = node1.firstChild();
    node1.replaceChild(nodeNew1,nodeOld1);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}

//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//重置MaxUnitID到Document.xml
void MainWindow::writeDocMaxUnitIDToXml()
{
    std::vector<int>::iterator maxNum;
    QString MAX_NUMBER;

    if(!temporary.empty())
    {
        maxNum = std::max_element(std::begin(temporary), std::end(temporary));
        int MAX = *maxNum;//获取最大ID
        int MAXID = MAX+1;
        MAX_NUMBER = QString::number(MAXID,10);//类型转换

        QFile file("./ofd/Doc_0/Document.xml");
        if (!file.open(QFile::ReadOnly))
            return;

        QDomDocument doc;
        if(!doc.setContent(&file))
        {
            file.close();
            return;
        }
        file.close();

        QDomNodeList list0 = doc.elementsByTagName("ofd:MaxUnitID");
        QDomNode node = list0.at(0);
        QDomNode nodeOld = node.firstChild();
        node.firstChild().setNodeValue(MAX_NUMBER);
        QDomNode nodeNew = node.firstChild();
        node.replaceChild(nodeNew,nodeOld);

        if(!file.open(QFile::WriteOnly|QFile::Truncate))
            return;
        QTextStream out_stream(&file);
        doc.save(out_stream,4);
        file.close();
    }
}

//0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//图片路径添加和资源添加
void MainWindow::processImageFragment(QTextImageFormat imageFormat)
{
    QString imageFile = imageFormat.name();//获取图片路径
    QStringList imageFileList = imageFile.split("//");
    QString imageFilePath  = imageFileList.at(1);
    QImage image(imageFilePath);//读取该路径指定的图片

    QFileInfo imageFileInfo(imageFile);
    QString imageName = imageFileInfo.fileName();//获取图片名字

    QString format;
    QString str;
    for(int i = 1; i < imageName.length(); i++)
    {
         if(imageName[i] == ".")
         {
              str=imageName.mid(i+1);//进行截取
              format = str.toUpper();
         }
    }

    QFileInfo resFileInfo(m_filepath + "ofd/Doc_0/Res");
    QFileInfo resXmlInfo(m_filepath + "ofd/Doc_0/DocumnetRes.xml");

    //问题一：第二次构建Res目录还在，第一个if判断进不去
    //第二个问题：DocumentRes.xml中的内容依旧是上次构建的内容

    if(!resFileInfo.isDir())//如果目录不存在，则创建目录
    {
        createFileDir(m_filepath + "ofd/Doc_0/Res");

        if(!resXmlInfo.isDir())
        {
             createDocumentRes();
             writeResToDocument();
             addMediasToRes(imageName,format);
             writeImageToContent(/*imageFile,*/imageFormat);
             ImaPath.push_back(imageFilePath);
        }

        QFile file("./ofd/Doc_0/Res/"+imageName);
        if (!file.open(QIODevice::ReadWrite))
        {
            return;
        }
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");
        file.write(ba);

    }else{//目录存在的情况下

        for(size_t j = 0; j < ImaPath.size(); j++)
        {
            if(imageFilePath == ImaPath.at(j))//如果插入的图片与以前一样
            {
                Temporary_NM = j;//为找到该图片的ID做标记
                flag = false;
                writeImageToContent(/*imageFile,*/imageFormat);
            }
        }
        if(flag)
        {
            ImaPath.push_back(imageFilePath);
            addMediasToRes(imageName,format);
            writeImageToContent(/*imageFile,*/imageFormat);
        }

        QFile file("./ofd/Doc_0/Res/"+imageName);
        if (!file.open(QIODevice::ReadWrite))
        {
            return;
        }
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");
        file.write(ba);
    }
}

//创建目录
void MainWindow::createFileDir(QString filepath)
{
    QDir *temp = new QDir;
    temp->mkdir(filepath);
}


void MainWindow::createToolBars()
{
   //改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改
   //添加表格
    QToolButton *toolBtn = new QToolButton(this);
    toolBtn->addAction(ui->action_insertTable);
    toolBtn->setIcon(QIcon(":/images/insert-table.svg"));
    QMenu *insertTable = new QMenu(this);
    insertTable->addAction(ui->action_drawTable);
    toolBtn->setMenu(insertTable);
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolBar->addWidget(toolBtn);
    //改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改

    //添加工具栏设置字体
    pLabel1 = new QLabel( tr( "字体:" ) );
    pFontBox = new QFontComboBox();
    pFontBox->setFontFilters( QFontComboBox::ScalableFonts );
    ui->toolBar_2->addWidget( pLabel1 );
    ui->toolBar_2->addWidget( pFontBox );

    //添加工具栏设置字体大小
    pLabel2 = new QLabel( tr( "字号:" ) );
    pSizeBox = new QComboBox();
    ui->toolBar_2->addWidget( pLabel2 );
    ui->toolBar_2->addWidget( pSizeBox );
    QFontDatabase db;
    foreach( int nSize, db.standardSizes() )
        pSizeBox->addItem( QString::number( nSize ) );


    //添加工具栏字体加粗、斜体、下划线、删除线、上划线、居左、居中、居右、两端对齐
    ui->toolBar_2->addAction(ui->action_bold);
    ui->toolBar_2->addAction(ui->action_italics);
    ui->toolBar_2->addAction(ui->action_underline);
    ui->toolBar_2->addAction(ui->action_strickout);
    ui->toolBar_2->addAction(ui->action_online);
    ui->toolBar_2->addSeparator();
    ui->toolBar_2->addAction(ui->action_superscript);
    ui->toolBar_2->addAction(ui->action_subscript);
    ui->toolBar_2->addSeparator();


    ui->toolBar_2->addAction(ui->action_justifyLeft);
    ui->toolBar_2->addAction(ui->action_justifyCenter);
    ui->toolBar_2->addAction(ui->action_justifyRight);
    ui->toolBar_2->addAction(ui->action_justifyFull);
    ui->toolBar_2->addSeparator();


    //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaiaigaiaigai
    //添加工具栏改变行距
    QToolButton *toolBtn3 = new QToolButton(this);
    toolBtn3->addAction(ui->action_lineSpacing);
    toolBtn3->setIcon(QIcon(":/images/text_line_spacing.svg"));
    QMenu *lineSpacingMenu = new QMenu(this);
    lineSpacingMenu->addAction(ui->action1_0_C);  //gaigaigaigaigaigaigaigaigaigaigai
                                                  //增加action1_0_C
    lineSpacingMenu->addAction(ui->action1_5_C);
    lineSpacingMenu->addAction(ui->action2_C);
    lineSpacingMenu->addAction(ui->action_customSpaced);
    toolBtn3->setMenu(lineSpacingMenu);
    toolBtn3->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolBar_2->addWidget(toolBtn3);
    //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaiaigaiaigai

    ui->toolBar->addAction(ui->action_images);
}

void MainWindow::connectFunction()
{
    //连接复制的信号与槽
    connect(ui->action_copy, SIGNAL(triggered()), widget->textEdit, SLOT(copy()));
    //连接粘贴的信号与槽
    connect(ui->action_paste, SIGNAL(triggered()),widget->textEdit, SLOT(paste()));
    //连接剪切的信号与槽
    connect(ui->action_cut, SIGNAL(triggered()),widget->textEdit, SLOT(cut()));
    //连接查找的信号与槽
    connect(ui->action_find, SIGNAL(triggered()), this, SLOT(textFind()));
    //连接撤销的信号与槽
    connect(ui->action_undo,SIGNAL(triggered()),this,SLOT(Undo()));
    //连接恢复的信号与槽
    connect(ui->action_redo,SIGNAL(triggered()),this,SLOT(Redo()));
    //连接字体设置的信号与槽
    connect(pFontBox, SIGNAL(activated(QString)),this,SLOT(slotFont(QString)));
    //连接字号设置的信号与槽
    connect(pSizeBox, SIGNAL(activated( QString)),this,SLOT(slotSize(QString)));
    //格式控件的显示更新
    connect(widget->textEdit,SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),this,SLOT( slotCurrentFormatChanged(const QTextCharFormat& )));
    //连接粗体的信号与槽
    connect(ui->action_bold, SIGNAL(triggered()), this, SLOT(slotBold()));
    //连接下划线的信号与槽
    connect(ui->action_underline, SIGNAL(triggered()), this, SLOT(slotUnderline()));
    //连接删除线的信号与槽
    connect(ui->action_strickout,SIGNAL(triggered()),this,SLOT(slotStrikeout()));
    //连接上划线的信号与槽
    connect(ui->action_online,SIGNAL(triggered()),this,SLOT(slotOverline()));
    //连接上标的信号与槽
    connect(ui->action_superscript,SIGNAL(triggered()),this,SLOT(slotSuperscript()));
    //连接下标的信号与槽
    connect(ui->action_subscript,SIGNAL(triggered()),this,SLOT(slotSubscript()));
    //连接斜体的信号与槽
    connect(ui->action_italics, SIGNAL(triggered()), this, SLOT(slotItalic()));
    //将设置字体颜色与颜色的信号连接
    connect(ui->action_color,SIGNAL(triggered()),this,SLOT(setFontColor()));
    //设置对齐方式
    QActionGroup *acGrp = new QActionGroup(this);
    acGrp->addAction(ui->action_justifyLeft);
    acGrp->addAction(ui->action_justifyRight);
    acGrp->addAction(ui->action_justifyCenter);
    acGrp->addAction(ui->action_justifyFull);
    connect(acGrp, SIGNAL( triggered( QAction * ) ), this, SLOT( slotAlign( QAction * ) ) );
    connect(widget->textEdit, SIGNAL( cursorPositionChanged() ), this, SLOT( slotCursorPositionChanged() ) );

    //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaiaigaigaiaigaigai
    connect(ui->action1_0_C,SIGNAL(triggered()),this,SLOT(lineSpacing1_0()));
    connect(ui->action1_5_C,SIGNAL(triggered()),this,SLOT(lineSpacing1_5()));
    connect(ui->action2_C,SIGNAL(triggered()),this,SLOT(lineSpacing2_0()));
    //gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaiaigaigaiaigaigai

    connect(ui->action_new,SIGNAL(triggered()),this,SLOT(slotNew()));
    connect(ui->action_open,SIGNAL(triggered()),this,SLOT(slotOpen()));

    connect(ui->action_close,SIGNAL(triggered()),this,SLOT(slotClose()));

    connect(ui->action_exit,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(ui->action_images,SIGNAL(triggered()), this,SLOT(insertImage()));
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(onText()));
     connect(ui->action_saveAs,SIGNAL(triggered()),this,SLOT(onText()));
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(writeDocPhysicalBoxToXml()));
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(writeDocMaxUnitIDToXml()));
    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(writeContentPhysicalBoxToXml()));
    connect(ui->action_footer,SIGNAL(triggered()),this,SLOT(slotPageNumber()));

    connect(ui->action_save,SIGNAL(triggered()),this,SLOT(slotSave()));

    connect(ui->action_saveAs,SIGNAL(triggered()),this,SLOT(slotSaveAs()));

    connect(ui->action_about,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->action_aboutOFD,SIGNAL(triggered()),this,SLOT(aboutOFD()));

    //改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改
    //绘制表格对话框
    connect(ui->action_drawTable,SIGNAL(triggered()),this,SLOT(slotDrawTableWidgt()));
    //改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改
}

//改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改
//绘制表格对话框
void MainWindow::slotDrawTableWidgt()
{
    tabledlg = new QDialog(this);
    tabledlg->setWindowTitle(tr("绘制表格"));

    QLabel *label1 = new QLabel(tabledlg);
    label1->setText(tr("表格尺寸------------------------------------"));

    QLabel *label2 = new QLabel(tabledlg);
    label2->setText(tr("  行数: "));
    QSpinBox *rowsSpinBox = new QSpinBox(tabledlg);
    rowsSpinBox->setRange(1,100);
    connect(rowsSpinBox,SIGNAL(valueChanged(int)),this,SLOT(slotSetCurrentRows(int)));

    QLabel *label3 = new QLabel(tabledlg);
    label3->setText(tr("  列数: "));
    QSpinBox *linesSpinBox = new QSpinBox(tabledlg);
    linesSpinBox->setRange(1,100);
    connect(linesSpinBox,SIGNAL(valueChanged(int)),this,SLOT(slotSetCurrentLines(int)));

    QPushButton *makeSureButton = new QPushButton(tabledlg);
    makeSureButton->setText(tr("确定"));
    connect(makeSureButton,SIGNAL(clicked()),this,SLOT(slotBeginDrawTable()));

    QPushButton *concelButton = new QPushButton(tabledlg);
    concelButton->setText(tr("取消"));
    connect(concelButton,SIGNAL(clicked()),this,SLOT(slotCloseTableDlg()));

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

//改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改
//设置所要绘制的表的行数和列数
void MainWindow::slotSetCurrentRows(int rows)
{
    tableRows = rows;
}
void MainWindow::slotSetCurrentLines(int lines)
{
    tableLines = lines;
}

//改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改
//开始绘画表格
void MainWindow::slotBeginDrawTable()
{
    QTextCursor cursor = widget->textEdit->textCursor();
    QTextTableFormat fmt;
    fmt.setCellSpacing(2);
    fmt.setCellPadding(10);
    cursor.insertTable(tableRows,tableLines,fmt);
}

//改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改改
//关闭表格对话框
void MainWindow::slotCloseTableDlg()
{
    tabledlg->close();
}

// 查找文本
void MainWindow::textFind()
{
    // 创建对话框
    QDialog *dlg = new QDialog(this);
    // 创建行编辑器
    lineEdit = new QLineEdit(dlg);
    // 创建按钮
    QPushButton *btn = new QPushButton(dlg);
    btn->setText(tr("查找"));
    // 关联信号与槽
    connect(btn,SIGNAL(clicked()),this,SLOT(findNext()));
    // 创建垂直布局管理器
    QVBoxLayout *layout = new QVBoxLayout;
    // 添加部件
    layout->addWidget(lineEdit);
    layout->addWidget(btn);
    // 在对话框中使用布局管理器
    dlg->setLayout(layout);
    dlg->show();
}

// 查找下一个
void MainWindow::findNext()
{
    // 使用查找函数查找指定字符串，查找方式为向后查找
    QString string = lineEdit->text();
    bool isfind = widget->textEdit->find(string, QTextDocument::FindBackward);

    // 如果查找成功，输出字符串所在行和列的编号
    if(isfind){
        qDebug() << tr("行号:%1 列号:%2")
                    .arg(widget->textEdit->textCursor().blockNumber())
                    .arg(widget->textEdit->textCursor().columnNumber());
    }
}

//撤销
void MainWindow::Undo()
{
    widget->textEdit->undo();
}

//恢复
void MainWindow::Redo()
{
    widget->textEdit->redo();
}

//设置字体
void MainWindow::slotFont( QString f )

{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormat(fmt);
}

//设置字号
void MainWindow::slotSize( QString num )

{
    QTextCharFormat fmt;
    fmt.setFontPointSize( num.toFloat() );
    mergeFormat(fmt);
}

//当光标所在处的字符格式发生变化时调用，函数根据新的字符格式把工具栏上的各个格式控件的显示更新
void MainWindow::slotCurrentFormatChanged( const QTextCharFormat & fmt )
{
    pFontBox->setCurrentIndex( pFontBox->findText( fmt.fontFamily() ) );
    pSizeBox->setCurrentIndex( pSizeBox->findText( QString::number( fmt.fontPointSize() ) ) );
    ui->action_bold->setChecked( fmt.font().bold() );
    ui->action_italics->setChecked( fmt.fontItalic() );
    ui->action_underline->setChecked( fmt.fontUnderline() );
    ui->action_strickout->setChecked(fmt.fontStrikeOut());
    ui->action_online->setChecked(fmt.fontOverline());
    if(fmt.verticalAlignment() == 1&&!(ui->action_superscript->isChecked())==true)
    {
        ui->action_superscript->setChecked(true);
    }

    if(fmt.verticalAlignment() == 2)
        ui->action_subscript->setChecked(true);
}

//设置光标的选区，使格式作用于选区内的字符，若没有选区则作用于光标所在处的字符
void MainWindow::mergeFormat( QTextCharFormat format )
{
    QTextCursor cursor = widget->textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select( QTextCursor::WordUnderCursor );
    widget->textEdit->mergeCurrentCharFormat(format);
}

//设置粗体
void MainWindow::slotBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->action_bold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormat( fmt );
}

//设置斜体
void MainWindow::slotItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->action_italics->isChecked());
    mergeFormat (fmt);
}

//设置下划线
void MainWindow::slotUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->action_underline->isChecked());
    mergeFormat( fmt );
}

//设置删除线
void MainWindow::slotStrikeout()
{
    QTextCharFormat fmt;
    fmt.setFontStrikeOut(ui->action_strickout->isChecked());
    mergeFormat(fmt);
}

//设置上划线
void MainWindow::slotOverline()
{
    QTextCharFormat fmt;
    fmt.setFontOverline(ui->action_online->isChecked());
    mergeFormat(fmt);
}

//设置上标
void MainWindow::slotSuperscript()
{
    QTextCharFormat fmt;
    fmt.setVerticalAlignment(ui->action_superscript->isChecked() ? QTextCharFormat::AlignSuperScript :QTextCharFormat::AlignNormal);
    mergeFormat(fmt);
}

//设置下标
void MainWindow::slotSubscript()
{
    QTextCharFormat fmt;
    fmt.setVerticalAlignment(ui->action_subscript->isChecked() ? QTextCharFormat::AlignSubScript : QTextCharFormat::AlignNormal);
    mergeFormat(fmt);
}

//实现段落对齐
void MainWindow::slotAlign(QAction *act)
{
    if ( act == ui->action_justifyLeft )
        widget->textEdit->setAlignment( Qt::AlignLeft );

    if ( act == ui->action_justifyCenter )
        widget->textEdit->setAlignment( Qt::AlignCenter );

    if ( act == ui->action_justifyFull )
        widget->textEdit->setAlignment( Qt::AlignJustify );

    if ( act == ui->action_justifyRight )
        widget->textEdit->setAlignment( Qt::AlignRight );
}

//响应文本中发生改变的信号的函数
//完成四个按钮的状态更新，通过调用QTextEdit类的alignment()函数获得当前
//光标所在段落的对其方式，设置相应的对齐按钮为按下状态
void MainWindow::slotCursorPositionChanged()

{

    if (widget->textEdit->alignment() == Qt::AlignLeft)
        ui->action_justifyLeft->setChecked(true);

    if (widget->textEdit->alignment() == Qt::AlignCenter)

        ui->action_justifyCenter->setChecked(true);

    if (widget->textEdit->alignment() == Qt::AlignJustify)

        ui->action_justifyFull->setChecked(true);

    if (widget->textEdit->alignment() == Qt::AlignRight)

        ui->action_justifyRight->setChecked(true);

}

//设置字体颜色
void MainWindow::setFontColor()
{
    QColor color = QColorDialog::getColor(Qt::black,this);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        mergeFormat(fmt);
    }
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentName = fileName;
    widget->textEdit->document()->setModified(false);
    this->setWindowModified(false);
    QString shownName = currentName;
    if (currentName.isEmpty())
        shownName = "untitled.ofd";
    setWindowTitle (shownName);
}

void MainWindow::slotNew()
{
    if(widget->textEdit->document()->isEmpty())
    {
        widget->textEdit->clear();
        setCurrentFile("");
    }
    else{
        if(maybeSave())
        {
            widget->textEdit->clear();
            setCurrentFile("");
        }
    }
}

bool MainWindow::slotSave()
{
    if(currentName.isEmpty())
        return slotSaveAs();
    else
        return saveFile(currentName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
    {
        QMessageBox::critical(this,
                              "critical",
                              "cannot write file"
                              );
        return false;
    }
    else
    {
        setCurrentFile(fileName);
        JlCompress::compressDir(fileName,"./ofd",true);//压缩
        return true;
    }
}

bool MainWindow::slotSaveAs()
{
    QString fileName =QFileDialog::getSaveFileName(this);
    if(fileName.isEmpty())
        return false;
    else
        return saveFile(fileName);
}

bool MainWindow::maybeSave()
{
    if(widget->textEdit->document()->isModified())
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this,
                                   "warning","the document has been modified,Do you want to save your change",QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel
                                   );
        if(ret == QMessageBox::Save)
            return slotSave();
        if(ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::slotOpen()
{
    if(widget->textEdit->document()->isEmpty())
    {
        QString fileName = QFileDialog::getOpenFileName(this);
        if(!fileName.isEmpty())
            loadFile(fileName);
    }
    else{
        if(maybeSave())
        {
            QString fileName = QFileDialog::getOpenFileName(this);
            if(!fileName.isEmpty())
                widget->textEdit->clear();
            loadFile(fileName);
        }
    }
}

void MainWindow::slotClose()
{
    if(maybeSave())
        widget->textEdit->document()->clear();
    setCurrentFile("untitled.ofd");
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::critical(this,
                              "critical",
                              "cannot read file"
                              );
        return;
    }
    else
    {
        //清空编辑器
        widget->textEdit->clear();
        JlCompress::extractDir(fileName,"./ofd");//解压
        parsingContentXml();//解析Content.xml
        setCurrentFile(fileName);
    }
}

void MainWindow::insertImage()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
                                                ".", tr("Bitmap Files (*.bmp)\n"
                                                        "JPEG (*.jpg *jpeg)\n"
                                                        "GIF (*.gif)\n"
                                                        "PNG (*.png)\n"));
    QUrl Uri ( QString ( "file://%1" ).arg ( file ) );
    QImage image = QImageReader ( file ).read();

    QTextDocument * textDocument =widget->textEdit->document();
    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
    QTextCursor cursor = widget->textEdit->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth( image.width() );
    imageFormat.setHeight( image.height() );
    imageFormat.setName( Uri.toString() );
    cursor.insertImage(imageFormat);
}

void MainWindow::createStatusBar()
{
    lineLabel = new QLabel;
    lineLabel->setMinimumSize(400,15);

    wordLabel=new QLabel;
    wordLabel->setMinimumSize(900,15);

    statusBar()->addWidget(lineLabel);
    statusBar()->addWidget(wordLabel);
    lineLabel->setText(tr("行：1,列：0"));
    connect(widget->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(currentLine()));
    wordLabel->setText(tr("行选择 插入"));

}

//显示行号和列号
void MainWindow::currentLine()
{

    const QTextCursor cursor = widget->textEdit->textCursor();//当前光标位置
    int RowNum = widget->textEdit->document()->blockCount();

    int ColNum = cursor.columnNumber();

    lineLabel->setText(tr("行：%1,列：%2").arg(RowNum).arg(ColNum));
}

void MainWindow::changePage()
{
    connect(ui->action_A1,SIGNAL(triggered()),this,SLOT(slotA1()));
    connect(ui->action_A2,SIGNAL(triggered()),this,SLOT(slotA2()));
    connect(ui->action_A3,SIGNAL(triggered()),this,SLOT(slotA3()));
    connect(ui->action_A4,SIGNAL(triggered()),this,SLOT(slotA4()));
    connect(ui->action_A5,SIGNAL(triggered()),this,SLOT(slotA5()));
    connect(ui->action_A6,SIGNAL(triggered()),this,SLOT(slotA6()));

}

void MainWindow::slotA1()
{
    widget->textEdit->setPageFormat(QPageSize::A1);
    widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));

}

void MainWindow::slotA2()
{
    widget->textEdit->setPageFormat(QPageSize::A2);
    widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));

}

void MainWindow::slotA3()
{
    widget->textEdit->setPageFormat(QPageSize::A3);
    widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));

}

void MainWindow::slotA4()
{
    widget->textEdit->setPageFormat(QPageSize::A4);
    widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));

}

void MainWindow::slotA5()
{
    widget->textEdit->setPageFormat(QPageSize::A5);
    widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));

}

void MainWindow::slotA6()
{
    widget->textEdit->setPageFormat(QPageSize::A6);
    widget->textEdit->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
}

void MainWindow::slotPageNumber()
{
    widget->textEdit->setShowPageNumbers(true);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"),
                       tr("<h2> 开发小组：mc^2</h2>"
                          "<p>小组成员：张姿婵、何亚梅、陈诗"
                          "<p>来自：重庆师范大学"
                          "<p>开发环境操作系统：Chakra"
                          "<p>开发语言：C++ "
                          "<p>集成开发框架：Qt5.8 "));
}

void MainWindow::aboutOFD()
{
    QMessageBox::about(this, tr("About OFD Typesetting System"),
                       tr("<h2>OFD Typesetting System 1.0</h2>"
                          "<p>OFD 排版系统是一款现代化、易用的公文排版系统，可用于文字排版处理."
                          "<p>采用xml机制对文档内的数据进行描述，达到数据保存和呈现比较稳定的效果."));
}

//gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
void MainWindow::lineSpacing1_0()
{
    double n = 1.0;
    lineSpacing(n);
}

//gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
void MainWindow::lineSpacing1_5()
{
    double n = 1.5;
    lineSpacing(n);
}

//gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
void MainWindow::lineSpacing2_0()
{
    double n = 2.0;
    lineSpacing(n);
}

//gaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigaigai
void MainWindow::lineSpacing(double n)
{
    QTextCursor textCursor = widget->textEdit->textCursor();
    QTextBlockFormat textBlockFormat;

    QTextDocument *editorDocument = widget->textEdit->document();

    //当需要进行文档结构导航时，从根框架开始(根框架提供了访问整个文档结构的能力)
    QTextFrame *root = editorDocument->rootFrame();//定位到根框架

    QTextFrame::iterator i;//迭代器，遍历框架中的所有子框架和文本块
    for(i = root->begin();!(i.atEnd());++i)
    {
        QTextBlock currentBlock = i.currentBlock();//获取当前文本块
        if(currentBlock.isValid())//如果文本块有效
        {
            QTextBlock::iterator j;//遍历当前文本块
            for(j = currentBlock.begin();!(j.atEnd());++j)
            {
                QTextFragment currentFragment = j.fragment();//获取当前文本片段
                if(currentFragment.isValid())//如果当前文本片段有效
                {
                    QTextCharFormat textFormat = currentFragment.charFormat().toCharFormat();//片段样式转换
                    double fontMSize_n = 0.0;
                    QString text = widget->textEdit->toPlainText();

                    QStringList number_list = text.split("\n");

                    for (int i = 0; i < number_list.size(); ++i)
                    {
                        QFontMetrics fm(textFormat.font());

                        double leading = fm.leading();
                        double CHeig = fm.height();
                        double l = CHeig + leading;

                        if(n==1.0)
                        {
                            fontMSize_n = l;
                        }else if(n==1.5)
                        {
                            fontMSize_n = l + l/2;
                        }else if(n==2.0)
                        {
                            fontMSize_n = 2*l;
                        }
                        textBlockFormat.setLineHeight(fontMSize_n, QTextBlockFormat::FixedHeight);//设置行高
                        textCursor.setBlockFormat(textBlockFormat);
                        widget->textEdit->setTextCursor(textCursor);
                        qDebug() << number_list.at(i).toDouble();
                    }

                }

            }
        }
    }
}


