#include "fontawesome.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    /*
     * 加载字体
     * QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    int index = QFontDatabase::addApplicationFont("/usr/local/Qt-5.3.1/lib/fonts/simfang.ttf");
    if(index != -1)
    {
        QStringList fontList(QFontDatabase::applicationFontFamilies(index));
        if(fontList.count() > 0)
        {
            QFont font_zh(fontList.at(0));
            font_zh.setBold(false);
            app.setFont(font_zh);
        }
    }*/











    FontAwesome f;
    f.show();

    return a.exec();
}
