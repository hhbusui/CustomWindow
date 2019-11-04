#include "fontawesome.h"
#include "ui_fontawesome.h"

FontAwesome::FontAwesome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontAwesome)
{
    ui->setupUi(this);
    m_iconFont = CustomWindow::loadFont(QString(":/other/font/fontawesome-webfont.ttf"));

    win = new CustomWindow();
    win->show();
    win->_main_vlayout->addWidget(this);
    win->setTopHeight(40);
    win->setIconShow(false);
    win->setIconMargin(20);
    win->setMaxAndMinAndCloseShow(false, true, true);
    win->setDBClickMax(false);
//    win->setWinFixedSize(400, 300);

    ui->btnDemo->setFont(m_iconFont);

    ui->btnDemo->setText(QChar(0xf00d));
    ui->btnDemo->setStyleSheet("color:green;");

}

FontAwesome::~FontAwesome()
{
    delete ui;
}

QFont FontAwesome::LoadFontAwesome(QString filePath)
{
    int fontId = QFontDatabase::addApplicationFont(filePath);
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont iconFont = QFont(fontName);
    return iconFont;
}

void FontAwesome::on_btnDemo_clicked()
{

    cusDialog = new CustomWindow(this);
    cusDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    cusDialog->setWindowModality(Qt::WindowModal);
    cusDialog->setTitle(QString("提示消息"));
    cusDialog->setCenterIsAbleMove(false);
    cusDialog->setDialog("确认关闭吗？", true, true);
    connect(cusDialog, &CustomWindow::s_dialogBtnOk, this, &FontAwesome::btnOk_clicked);

}

void FontAwesome::btnOk_clicked()
{
    qDebug() << "line__" << __LINE__ << ":  " <<  "ok  demo  ....";
}
