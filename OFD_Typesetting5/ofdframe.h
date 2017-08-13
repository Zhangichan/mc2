#ifndef OFDFRAME_H
#define OFDFRAME_H
#include<QString>
#include<vector>
#include<QTextFragment>
#include "PagesTextEdit.h"
class OfdFrame
{
public:
    OfdFrame();
    PagesTextEdit *text1;
public:
    //以下四个供MainWindow调用，作为槽函数
    bool onText();//文本处理
    void writeDocPhysicalBoxToXml();//重置PhysicalBox到Document.xml
    void writeDocMaxUnitIDToXml();//重置MaxUnitID到Document.xml
    void writeContentPhysicalBoxToXml();//Content.xml文件中PhysicalBox的添加
    bool DelDir(const QString&);//删除DocumentRes.xml和Res文件的函数
private:
    int returnNumber;//回车数
    int Time_NM;//回车判断哨兵
    int PageNumber;//页数
    std::vector<QString> PathName;//存放页数
    int FIRST_ID;//ID跟踪
    int time_ID[11];//存放字体名
    std::vector<int> temporary;//存放所有ID
    //boundary(x,y,width,height)
    qreal mmx;
    qreal mmy;
    qreal mmBoundaryWidth;
    qreal mmBoundaryHeigth;
    qreal ty;
    //(X,Y)
    float X = 0.0;
    float Y = 0.0;
    int ResID;//图片ID
    size_t Temporary_NM = 0;//检查重复图片哨兵
    std::vector<int> ImaID;//存放所有图片ID
    std::vector<QString> ImaPath;//图片路径
    qreal mmFirstHeigthOfLine = 0.0; //每行第一个字符高度
    qreal mmEndYOfLine = 0.0;  //每行最终保留的mmy值

    std::vector<qreal> maxHeigth;
    qreal maxH = 0.0;
    qreal lastMaxH = 0.0;
    qreal mmx0;
    int n = 0;  //初始化行号
    int returnNumber0;//回车数
    int Time_NM0;//回车判断哨兵

    std::vector<qreal> textWidthOfLine;
    qreal mmx1 = 0.0;
    qreal mmAllWidth = 0.0 ;
    qreal mmLastAllWith = 0.0;
    int returnNumber1;//回车数
    int Time_NM1;//回车判断哨兵
    bool first = true;

    bool compare = false;
    bool flag = true;
    PageMetrics m_pageMetrics;
private:
    void createOfdStructure();//创建OFD框架基本结构
    void createFileDir(QString);//创建目录，在createOfdStructure()中调用
    void createOfdXml();//创建0FD.xml
    void createPublicResXml();//创建PublicRes.xml
    void createDocument();//创建Document.xml
    void createContentXml();//创建Content.xml
    bool deleteDir(const QString &);//删除Pages下的文件的函数

    std::vector<qreal> getMaxBoundaryHeigthOfLine();//获取一行中最大的行高
    std::vector<qreal> getTextWidthOfLine(); //获取每行字符文本的总宽度

    //文字处理---------------------------------------------------------------------------------
    void processTextContent(QTextFragment, QTextCharFormat);//处理内容中的文字部分(单个字读取)
    void writeTextToXml(QString,QTextCharFormat,int);//读入属性到Conten.xml文件中
    void nextContent();//分页机制
    void paging();//为分页创建Page_N
    void addDocumentPart();//每增添一页，添加相应的page资源到Document.xml中
    void writeTextToPublicResXml(QTextCharFormat);//读入属性到PublicRes.xml文件中
    //----------------------------------------------------------------------------------------

    //图片处理--------------------------------------------------------------------------------------
    void processImageFragment(QTextImageFormat);//处理内容中的图片部分
    void createDocumentRes();//创建DocumentRes.xml
    void writeResToDocument();//将DocumentRes.xml以属性写入Document.xml文件中
    void addMediasToRes(QString, QString);//将图片信息写入DocumentRes.xml文件中
    void writeImageToContent(/*QString,*/QTextImageFormat);//将图片信息写入Content.xml文件中
    //---------------------------------------------------------------------------------------------
};

#endif // OFDFRAME_H
