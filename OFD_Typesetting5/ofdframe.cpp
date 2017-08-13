#include "ofdframe.h"
#include <QDir>
#include <QUuid>
#include <QDate>
#include <QtXml>
#include <QTextDocument>
#include <QTextFrame>
#include <algorithm>
#include <QGraphicsTextItem>
#include <QSizePolicy>
#include <QUrl>
#include <QTextStream>
#include<QApplication>
#include<QDesktopWidget>
QString m_filepath = "./";
OfdFrame::OfdFrame()
{
    createOfdStructure();//创建OFD框架基本结构
    createOfdXml();//创建0FD.xml
}
//在构造函数中使用----------------------------------------------------
//1.创建OFD框架基本结构
void OfdFrame::createOfdStructure()
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
//2.创建0FD.xml
void OfdFrame::createOfdXml()
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
//    QString creator = windowTitle();

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
//    QDomElement doccreator = docO.createElement("ofd:Creator");//创建文档的应用程序
//    docinfo.appendChild(doccreator);

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

//    text = docO.createTextNode(creator);
//    doccreator.appendChild(text);

    QFile ofdfile("./ofd/OFD.xml");
    if(!ofdfile.open(QIODevice::WriteOnly | QIODevice::Truncate))return;
    QTextStream outO(&ofdfile);
    docO.save(outO,4);
    ofdfile.close();
}
//-----------------------------------------------------------------

//1.在createOfdStructure()中调用--------------------
//创建目录
void OfdFrame::createFileDir(QString filepath)
{
    QDir *temp = new QDir;
    temp->mkdir(filepath);
}
//-------------------------------------------------

//在MainWindow中的Connect中调用-----------------------------------------------------------------------------------------------------
//1.文本处理
bool OfdFrame::onText()
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
    QFileInfo resFileInfo(m_filepath + "ofd/Doc_0/Res");
    QDir resXmlInfo(m_filepath + "ofd/Doc_0");
    if(resFileInfo.isDir())
    {
        if(!DelDir("./ofd/Doc_0/Res"))//Res存在即删除
        {
        }
    }
    if(resXmlInfo.exists())//DcumentRes.xml存在即删除
    {
            QFile file;
            file.remove("./ofd/Doc_0/DocumentRes.xml");
    }
    if(!deleteDir("./ofd/Doc_0/Pages"))
    {
        createContentXml();
        mmx = 0.0;
        mmy = 0.0;
        mmBoundaryWidth = 0.0;
        mmBoundaryHeigth = 0.0;
        compare = false;
        Time_NM = 1;
        returnNumber = 0;
        ty = 0.0;

        mmx0 = 0.0;
        maxH = 0.0;
        lastMaxH = 0.0;
        Time_NM0 = 1;
        returnNumber0 = 0;

        mmx1 = 0.0;
        mmAllWidth = 0.0;
        mmLastAllWith = 0.0;
        Time_NM1 = 1;
        returnNumber1 = 0;

    }
    QTextDocument *editorDocument = text1->document();
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
//2.重置PhysicalBox到Document.xml
void OfdFrame::writeDocPhysicalBoxToXml()
{
    int originX = text1->geometry().x();
    int originY = text1->geometry().y()-94;

    int Width = text1->m_pageMetrics.mmPageSize().width();
    int Height = text1->m_pageMetrics.mmPageSize().height();

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
//3.重置MaxUnitID到Document.xml
void OfdFrame::writeDocMaxUnitIDToXml()
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
//4.添加PhysicalBox到Content.xml
void OfdFrame::writeContentPhysicalBoxToXml()
{
    int originX = text1->geometry().x();
    int originY = text1->geometry().y()-94;

    int Width = text1->m_pageMetrics.mmPageSize().width();
    int Height = text1->m_pageMetrics.mmPageSize().height();

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
//--------------------------------------------------------------------------------------------------------------------------------

//在onText中调用-------------------------------------------------------------------
//1.创建PublicRes.xml
void OfdFrame::createPublicResXml()
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
//2.创建Document.xml(在分页时也会调用，即在nextContent中)
void OfdFrame::createDocument()
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
//3.创建Content.xml
void OfdFrame::createContentXml()
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
//4.删除Pages下的文件的函数
bool OfdFrame::deleteDir(const QString &dirName)
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
//5.删除DocumentRes.xml和Res文件的函数
bool OfdFrame::DelDir(const QString &path)
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
//6.处理内容中的文字部分(单个字读取)
void OfdFrame::processTextContent(QTextFragment current, QTextCharFormat textFormat)
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
//7.处理内容中的图片部分
void OfdFrame::processImageFragment(QTextImageFormat imageFormat)
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
//--------------------------------------------------------------------------------

std::vector<qreal> OfdFrame::getMaxBoundaryHeigthOfLine()
{
    QTextDocument *editorDocument = text1->document();
    //当需要进行文档结构导航时，从根框架开始(根框架提供了访问整个文档结构的能力)
    QTextFrame *root = editorDocument->rootFrame();//定位到根框架

    QTextFrame::iterator i;//迭代器，遍历框架中的所有子框架和文本块
    for(i = root->begin();!(i.atEnd());++i)
    {
        QTextBlock currentBlock = i.currentBlock();//获取当前文本块
        ++returnNumber0; //每一个片段即包含一个回车符
        if(currentBlock.isValid())//如果文本块有效
        {
            QTextBlock::iterator j;//遍历当前文本块
            for(j = currentBlock.begin();!(j.atEnd());++j)
            {
                QTextFragment currentFragment = j.fragment();//获取当前文本片段
                if(currentFragment.isValid())//如果当前文本片段有效
                {
                    QTextCharFormat textFormat = currentFragment.charFormat().toCharFormat();//片段样式转换

                    QFontMetrics fm(textFormat.font());

                    int originX = text1->geometry().x();

                    qreal x1 = originX + text1->m_pageMetrics.mmPageMargins().left();

                    QString str1 = currentFragment.text();//得到当前片段的文本内容
                    QString content;
                    int i;
                    for(i=0; i<str1.length(); i++)
                    {
                        content = str1.mid(i,1);//进行截取

                        qreal mmBWidth0 =fm.width(content);
                        qreal mmBWidth =mmBWidth0/qApp->desktop()->logicalDpiX()*25.4;

                        qreal mmCHeigth0 = fm.lineSpacing();
                        qreal mmCHeigth = mmCHeigth0/qApp->desktop()->logicalDpiY()*25.4;

                        qreal mmLineWidget =text1->m_pageMetrics.mmPageSize().width()-text1->m_pageMetrics.mmPageMargins().left()-text1->m_pageMetrics.mmPageMargins().right();

                        qreal mmRightMargin =  text1->m_pageMetrics.mmPageMargins().right();

                        if(maxH == 0.0){  //对第一个字符串片段定位

                            mmx0 = x1;
                            maxH = mmCHeigth;

                        }else{

                            if(mmx0< mmLineWidget+mmRightMargin-5.69)
                            {
                                lastMaxH = maxH;
                                if(mmCHeigth > maxH)
                                {
                                    lastMaxH = maxH;
                                    maxH = mmCHeigth;
                                }
                                if(Time_NM0 != returnNumber0)
                                {
                                    maxHeigth.push_back(lastMaxH);
                                    mmx0 = x1;
                                    maxH = mmCHeigth;
                                    ++Time_NM0;//每换一行都要加
                                }

                            }else{

                                lastMaxH = maxH;
                                if(mmCHeigth > maxH)
                                {
                                    lastMaxH = maxH;
                                    maxH = mmCHeigth;
                                }
                                mmx0 = x1;
                                maxHeigth.push_back(lastMaxH);
                                maxH = mmCHeigth;
                                lastMaxH = 0.0;
                            }
                        }
                        mmx0 += mmBWidth;
                    }
                }
            }
        }
    }
    return maxHeigth;
}

std::vector<qreal> OfdFrame::getTextWidthOfLine()
{
    QTextDocument *editorDocument = text1->document();
    //当需要进行文档结构导航时，从根框架开始(根框架提供了访问整个文档结构的能力)
    QTextFrame *root = editorDocument->rootFrame();//定位到根框架

    QTextFrame::iterator i;//迭代器，遍历框架中的所有子框架和文本块
    for(i = root->begin();!(i.atEnd());++i)
    {
        QTextBlock currentBlock = i.currentBlock();//获取当前文本块
        ++returnNumber1; //每一个片段即包含一个回车符
        if(currentBlock.isValid())//如果文本块有效
        {
            QTextBlock::iterator j;//遍历当前文本块
            for(j = currentBlock.begin();!(j.atEnd());++j)
            {
                QTextFragment currentFragment = j.fragment();//获取当前文本片段
                if(currentFragment.isValid())//如果当前文本片段有效
                {
                    QTextCharFormat textFormat = currentFragment.charFormat().toCharFormat();//片段样式转换

                    QFontMetrics fm(textFormat.font());

                    int originX = text1->geometry().x();

                    qreal x1 = originX + text1->m_pageMetrics.mmPageMargins().left();

                    QString str1 = currentFragment.text();//得到当前片段的文本内容
                    QString content;
                    int i;
                    for(i=0; i<str1.length(); i++)
                    {
                        content = str1.mid(i,1);//进行截取

                        qreal mmBWidth0 =fm.width(content);
                        qreal mmBWidth =mmBWidth0/qApp->desktop()->logicalDpiX()*25.4;


                        qreal mmLineWidget =text1->m_pageMetrics.mmPageSize().width()-text1->m_pageMetrics.mmPageMargins().left()-text1->m_pageMetrics.mmPageMargins().right();

                        qreal mmRightMargin =  text1->m_pageMetrics.mmPageMargins().left();

                        if(mmx1 == 0.0){  //对第一个字符串片段定位

                            mmx1 = x1;
                            mmAllWidth = mmBWidth;

                        }else{

                            if(mmx1< mmLineWidget+mmRightMargin-5.69) //判断小于一行
                            {
                                mmLastAllWith = mmAllWidth;
                                mmAllWidth += mmBWidth;


                                if(Time_NM1 != returnNumber1)
                                {
                                    textWidthOfLine.push_back(mmLastAllWith);
                                    mmx1 = x1;
                                    mmAllWidth = mmBWidth;
                                    ++Time_NM1;//每换一行都要加
                                }

                            }else{  //满行的情况

                                mmLastAllWith = mmAllWidth;
                                mmAllWidth += mmBWidth;

                                mmx1 = x1;
                                textWidthOfLine.push_back(mmLastAllWith);
                                mmAllWidth = mmBWidth;
                                mmLastAllWith = 0.0;
                            }
                        }
                        mmx1 += mmBWidth;
                    }
                }
            }
        }
    }
    return textWidthOfLine;
}

//在processTextContent中调用--------------
//1.读入属性到Conten.xml文件中
void OfdFrame::writeTextToXml(QString content, QTextCharFormat textFormat,int number)
{
    //Size
    QString fontfamily = textFormat.fontFamily();
    qreal size = textFormat.fontPointSize();

    //Value
    qreal size1 = double(int((size/2.845)*100))/100.0;  //字号转换成毫米
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
    int originX = text1->geometry().x();
    int originY = text1->geometry().y()-94;

    qreal x1 = originX + text1->m_pageMetrics.mmPageMargins().left();
    qreal y1 = originY + text1->m_pageMetrics.mmPageMargins().top();

    qreal mmBWidth0 =fm.width(content);
    qreal mmBWidth =mmBWidth0/qApp->desktop()->logicalDpiX()*25.4;

    //此处改成了leading（）
    qreal s = fm.leading();
    qreal mmCHeigth0 = fm.height();
    //    qreal mmCHeigth0 = fm.lineSpacing();
    qreal space = s/qApp->desktop()->logicalDpiY()*25.4;
    qreal mmCHeigth1 = mmCHeigth0/qApp->desktop()->logicalDpiY()*25.4;
    qreal mmCHeigth = space + mmCHeigth1;

    qreal mmLineWidget =text1->m_pageMetrics.mmPageSize().width()-text1->m_pageMetrics.mmPageMargins().left()-text1->m_pageMetrics.mmPageMargins().right();

    qreal mmRightMargin =  text1->m_pageMetrics.mmPageMargins().right();
    qreal mmBottomMargin = text1->m_pageMetrics.mmPageMargins().bottom();

    qreal textWidth = 0.0;
    if(first){
        textWidth = getTextWidthOfLine().at(n);
        first = false;
    }else {
        textWidth = getTextWidthOfLine().at(n+1);
    }
    qreal x2 = x1 + (mmLineWidget-5.69-textWidth)/2;
    qreal x3 = x1 + mmLineWidget-5.69-textWidth;

    qreal xn;
    if(text1->alignment() == Qt::AlignCenter)
    {
        xn = x2;
    }else if(text1->alignment() == Qt::AlignRight)
    {
        xn = x3;
    }else if(text1->alignment() == Qt::AlignLeft){
        xn = x1;
    }


    qreal mmPaHeigth = text1->m_pageMetrics.mmPageSize().height();

    if(mmBoundaryWidth == 0.0&&mmBoundaryHeigth==0.0){  //对第一个字符串片段定位

        //==========================================================
        mmx = xn;
        mmy = y1 + getMaxBoundaryHeigthOfLine().at(n) - mmCHeigth1;
        mmEndYOfLine = mmy;
        mmFirstHeigthOfLine = mmCHeigth1;


        mmBoundaryWidth = mmBWidth;
    }else{
        if((mmx< mmLineWidget+mmRightMargin-5.69) )  //针对一行未满的情况讨论
        {
            if(Time_NM == returnNumber)   //未索引到换行，mmy的值与之前的不变
            {
                //==================================================
                mmy = y1 +  getMaxBoundaryHeigthOfLine().at(n) - mmCHeigth1;
                if(compare){
                     mmEndYOfLine = ty;

                    if(mmCHeigth1 != mmFirstHeigthOfLine)
                    {

                        mmy =  ty + mmFirstHeigthOfLine - mmCHeigth1;
                    }else{
                        mmy = ty;
//                        mmEndYOfLine = mmy;
                    }

                }
                mmBoundaryWidth = mmBWidth;
            }else{  //索引到换行，mmy的值改变

                //==================================================
                mmx = xn;
                n += 1;
                mmy = mmEndYOfLine + mmFirstHeigthOfLine +getMaxBoundaryHeigthOfLine().at(n)-mmCHeigth1;

                mmBoundaryWidth = mmBWidth;

                //================================
                mmFirstHeigthOfLine = mmCHeigth1;

                compare = true;
                ty = mmy;
                ++Time_NM;//每换一行都要加


                if((mmPaHeigth-mmBottomMargin) < mmy+mmCHeigth)//判断分页机制  (多加了个mmCHeigth)
                {
                    compare = false;

                    //==================================================
                    mmx = xn;
                    mmy = y1 + getMaxBoundaryHeigthOfLine().at(n) - mmCHeigth1;

                    nextContent();
                }
            }
        }else{//判断加纵行数反对

            //==================================================
            mmx = xn;
            n += 1;
            mmy = mmEndYOfLine + mmFirstHeigthOfLine +getMaxBoundaryHeigthOfLine().at(n)-mmCHeigth1;

            mmBoundaryWidth = mmBWidth;

            //================================
            mmFirstHeigthOfLine = mmCHeigth1;

            compare = true;
            ty = mmy;
            if((mmPaHeigth-mmBottomMargin) < mmy+mmCHeigth)//判断分页机制 (多加了个mmCHeigth)
            {
                compare = false;

                //==================================================
                mmx = xn;
                mmy = y1 + getMaxBoundaryHeigthOfLine().at(n) - mmCHeigth1;

                nextContent();
            }
        }
    }
    mmBoundaryHeigth = getMaxBoundaryHeigthOfLine().at(n);

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
//--------------------------------------

//在writeTextToXml中调用-------------------------------------------------------
//1.分页机制
void OfdFrame::nextContent()
{
    paging();
    addDocumentPart();
    createContentXml();
}
//2.读入属性到PublicRes.xml文件中
void OfdFrame::writeTextToPublicResXml(QTextCharFormat textFormat)
{
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
//----------------------------------------------------------------------------

//在nextContent中调用-----------------------------------------------------------------------------------------------
//1.为分页创建Page_N
void OfdFrame::paging()
{
    QString pg = "Page_";
    ++PageNumber;//页码递增
    QString PN = QString::number(PageNumber,10);
    pg = pg + PN;
    PathName.push_back(pg);//如：page_0
    createFileDir(m_filepath + ("ofd/Doc_0/Pages/" + pg));
}
//2.每增添一页，添加相应的page资源到Document.xml中
void OfdFrame::addDocumentPart()
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
//-----------------------------------------------------------------------------------------------------------------

//在processImageFragment中调用------------
//1.创建DocumentRes.xml
void OfdFrame::createDocumentRes()
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
//2.将DocumentRes.xml以属性写入Document.xml文件中
void OfdFrame::writeResToDocument()
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
//3.将图片信息写入DocumentRes.xml文件中
void OfdFrame::addMediasToRes(QString imageName, QString format)
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
//4.将图片信息写入Content.xml文件中
void OfdFrame::writeImageToContent(QTextImageFormat imageFormat)
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
    int originX = text1->geometry().x();
    int originY = text1->geometry().y()-94;

    //(x1,y1)为出血框顶点位置
    double x1 = originX + text1->m_pageMetrics.mmPageMargins().left();
    double y1 = originY + text1->m_pageMetrics.mmPageMargins().top();

    //获取图片的宽度
    double mmBWidth0 = imageFormat.width();
//    double mmBWidth0 =fm.width(fileName);
    double mmBWidth =mmBWidth0/qApp->desktop()->logicalDpiX()*25.4;

    //获取图片的高度
    double mmCHeigth0 = imageFormat.height();
//    double mmCHeigth0 = fm.lineSpacing();
    double mmCHeigth = mmCHeigth0/qApp->desktop()->logicalDpiY()*25.4;

    //编辑区域的宽度 = 当前页面宽度-两边边缘宽度
    double mmLineWidget =text1->m_pageMetrics.mmPageSize().width()-text1->m_pageMetrics.mmPageMargins().left()-text1->m_pageMetrics.mmPageMargins().right();

    //获取右边缘的距离、上边缘
    double mmRightMargin =  text1->m_pageMetrics.mmPageMargins().right();
    double mmBottomMargin = text1->m_pageMetrics.mmPageMargins().bottom();

    //获取当前页面的高度
    double mmPaHeigth = text1->m_pageMetrics.mmPageSize().height();

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

     int zero = 0;
     QString ctm = QString("%1 %2 %3 %4 %5 %6").arg(QString::number(mmBoundaryWidth,10,2),QString::number(zero,10),QString::number(zero,10), QString::number(mmBoundaryHeigth,10,2),QString::number(zero,10),QString::number(zero,10));

    imageObject.setAttribute("Boundary",boundary);
    imageObject.setAttribute("CTM",ctm);

    QDomNodeList oldList = root.elementsByTagName("ofd:Layer");
    QDomElement a = oldList.at(0).toElement();
    a.appendChild(imageObject);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}
//--------------------------------------
