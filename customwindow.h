#ifndef CUSTOMWINDOW_H
#define CUSTOMWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QPainter>
#include <QMouseEvent>
#include <QRect>
#include <QPoint>
#include <QSize>
#include <QMargins>
#include <QGraphicsDropShadowEffect>
#include <QFile>
#include <QFontDatabase>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QDialog>
#include <QDebug>

//# pragma execution_character_set("utf-8")


enum Direction { TOP = 0, BOTTOM = 1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };



class CustomWindow : public QWidget
{
    Q_OBJECT

public:
    CustomWindow(QWidget *parent = 0);
    ~CustomWindow();

    void setBgColor(int r = 91, int g = 155, int b = 213);
    void setWinRadius(int radius = 5);

    void setWinMargin(int margin);
    void setWinMargin(int top, int right, int bottom, int left);
    void setWinSize(int width, int height);
    void setWinMinSize(int width, int height);
    void setWinMaxSize(int width, int height);
    void setWinIsDrag(bool isDrag);

    void setWinFixedSize(int width, int height);
    void setWinFixedSize(int width, int height, bool isDrag);

    void setTopStyleSheet(QString qssStr);
    void setTopBgColor(QString bgColor);
    void setTopHeight(int height);

    void setIcon(const QPixmap &icon);
    void setIconSize(int width, int height);
    void setIconShow(bool isShow);
    void setIconMargin(int left);

    void setTitle(const QString title);
    void setTitleStyleSheet(const QString qssStr);

    void setMaxAndMinAndCloseShow(bool minShow, bool maxShow, bool closeShow);

    void setMinBtnIcon(const QPixmap &icon);
    void setMaxBtnIcon(const QPixmap &icon);
    void setCloseBtnIcon(const QPixmap &icon);

    void setTopBtnIcon(const QPixmap &closeIcon);
    void setTopBtnIcon(const QPixmap &minIcon, const QPixmap &closeIcon);
    void setTopBtnIcon(const QPixmap &minIcon, const QPixmap &maxIcon, const QPixmap &closeIcon);

    void setMinStyleSheet(const QString qssStr);
    void setManStyleSheet(const QString qssStr);
    void setCloseStyleSheet(const QString qssStr);

    void setTopBtnStyleSheet(const QString qssMinStr, const QString qssMaxStr, const QString qssCloseStr);
    void setDBClickMax(bool dbclickMax);
    void setCenterIsAbleMove(bool isAbleMove);


    void setDialog(QString tipsText, bool okShow, bool cancelShow);


public:

    static void loadQss(const QString &path);
    static QFont loadFont(const QString path);



signals:
    void  s_dialogBtnOk();


private:

    void InitSettings();
    void InitUi();
    void InitUiAfter();
    void MainSignals();

    void saveRestoreInfo(const QPoint point, const QSize size);
    void getRestoreInfo(QPoint& point, QSize& size);

    void on_btnMin_clicked();
    void on_btnMax_clicked();
    void on_btnClose_clicked();

    void maxAndRestore();
    void getMouseStyle(const QPoint &cursorPos);


    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void leaveEvent(QEvent *);

    void setStyle();
    int setRGBARange(int r);

    void InitAlertWinUI(QString tipsText, bool okShow, bool cancelShow);
    void on_dialogBtnOk_clicked();
    void on_dialoBtnClose_clicked();

    void dropShadowEffect(QWidget *widget);
    void setBtnQssStyleOne(QWidget* widget, QString btnClass);


public:
    // 对外暴露的接口
    QVBoxLayout* _main_vlayout;


private:
    // UI界面
    QWidget* _top_widget;
    QWidget* _main_widget;

    QVBoxLayout* _wrap_vlayout;
    QHBoxLayout* _top_hlayout;
    QHBoxLayout* _top_left_hlayout;
    QHBoxLayout* _top_right_hlayout;
    QHBoxLayout* _top_right_btns_hlayout;
    QSpacerItem* _top_black;

    QLabel* _lbl_icon;
    QLabel* _lbl_title;

    QPushButton* _btn_min;
    QPushButton* _btn_max;
    QPushButton* _btn_close;

    // 获取外部接口的值
    QColor _main_color;
    QString _widget_color;
    QString _widget_color_hover;

    QString _app_title;

    int _win_radius;
    int _icon_width;
    int _top_height;

    // margin设置
    int _top_margin;
    int _right_margin;
    int _bottom_margin;
    int _left_margin;

    // 最大最小化
    bool _is_max;
    QPoint _m_restorePos;
    QSize  _m_restoreSize;
    bool _dbclick_max;
    bool _center_is_move;

    // 移动,改变大小
    bool _is_pressed;
    Direction _dirpos;
    QPoint _start_point;




};

#endif // CUSTOMWINDOW_H
