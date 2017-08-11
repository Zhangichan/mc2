#include "frameanalysis.h"
#include<QFile>
#include<QtXml>
#include<QtWidgets>

FrameAnalysis::FrameAnalysis()
{

}
//解析Content.xml
void FrameAnalysis::parsingContentXml()
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

            QTextCursor cursor = text5->textCursor();
            cursor.setCharFormat(fmt);
            if(mytext.isEmpty())
            {
                cursor.insertText(" ");
            }
            else
            {
                QString boundary = e.attribute("Boundary");
                QStringList qls = boundary.split(" ");
                height = qls.at(1);
                if(judge)
                {
                    variable = height;
                    judge = false;
                }
                if(height == variable)
                {
                    cursor.insertText(mytext);
                    heightB = height;
                    variable = "0.00";
                }else{
                    if(height == heightB)
                    {
                        cursor.insertText(mytext);
                        heightB = height;
                    }else{
                        cursor.insertText("\n");
                        cursor.insertText(mytext);
                        heightB = height;
                    }
                }
            }
            text5->setTextCursor(cursor);
            parsingPageSize();
//            parsingPicture();
        }
    }
}
//解析页面大小
void FrameAnalysis::parsingPageSize()
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
        text5->setPageFormat(QPageSize::A6);
        text5->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
    if(a == 148 && b == 210)
    {
        text5->setPageFormat(QPageSize::A5);
        text5->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
    if(a == 210 && b == 297)
    {
        text5->setPageFormat(QPageSize::A4);
        text5->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
    if(a == 297 && b == 420)
    {
        text5->setPageFormat(QPageSize::A3);
        text5->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
    if(a == 420 && b == 594)
    {
        text5->setPageFormat(QPageSize::A2);
        text5->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
    if(a == 594 && b == 841)
    {
        text5->setPageFormat(QPageSize::A1);
        text5->setPageMargins(QMarginsF(25.4, 25.4, 31.75, 31.75));
    }
}
//void FrameAnalysis::parsingPicture()
//{
//    QStringList ls;
//    QDir dir("./ofd/Doc_0/Res");
//    QFileInfoList info_list = dir.entryInfoList(QDir::Files | QDir::AllDirs);
//    foreach(QFileInfo file_info, info_list)
//    {
//        if(file_info.isFile())
//        {
//            ls<<file_info.baseName();
//        }
//    }
//    for(int i = 0;i<ls.size();i++)
//    {
//        QString str = "/root/比赛/OFD_Typesetting/images/title.png";
//        QUrl Uri ( QString ( "file://%1" ).arg ( str ) );
//        QImage image = QImageReader ( str ).read();

//        QTextDocument * textDocument =text5->document();
//        textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
//        QTextCursor cursor = text5->textCursor();
//        QTextImageFormat imageFormat;
//        imageFormat.setWidth( image.width() );
//        imageFormat.setHeight( image.height() );
//        imageFormat.setName( Uri.toString() );
//        cursor.insertImage(imageFormat);
//        text5->setTextCursor(cursor);
//    }
//}
