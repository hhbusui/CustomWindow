#include "customwindow.h"

//91,155,213

CustomWindow::CustomWindow(QWidget *parent)
    : QWidget(parent)
    ,_win_radius(5)
    ,_top_margin(5)
    ,_right_margin(5)
    ,_bottom_margin(5)
    ,_left_margin(5)
    ,_icon_width(30)
    ,_top_height(40)
    ,_center_is_move(true)
    ,_is_max(false)
    ,_is_pressed(false)
    ,_dirpos(NONE)
    ,_main_color(QColor(91, 155, 213))
    ,_widget_color("rgb(91, 155, 213)") // #5e9ed5cc
    ,_widget_color_hover("rgb(107, 177, 236)") // rgba(107, 177, 236, 1)
{


    InitSettings();
    InitUi();
}

CustomWindow::~CustomWindow()
{

}


void CustomWindow::setBgColor(int r, int g, int b)
{
    r = setRGBARange(r);
    g = setRGBARange(g);
    b = setRGBARange(b);

    _main_color = QColor(r, g, b);
}

void CustomWindow::setWinRadius(int radius)
{
    _win_radius = radius > 20 ? 10 : radius;
}

void CustomWindow::setWinMargin(int margin)
{
    _top_margin = margin;
    _right_margin = margin;
    _bottom_margin = margin;
    _left_margin = margin;
}



void CustomWindow::setWinMargin(int top, int right, int bottom, int left)
{
    _top_margin = top;
    _right_margin = right;
    _bottom_margin = bottom;
    _left_margin = left;
}

void CustomWindow::setWinSize(int width, int height)
{
    this->resize(width, height);
}

void CustomWindow::setWinMinSize(int width, int height)
{
    this->setMinimumSize(width, height);
}

void CustomWindow::setWinMaxSize(int width, int height)
{
    this->setMaximumSize(width, height);
}

void CustomWindow::setWinIsDrag(bool isDrag)
{
    this->setMouseTracking(isDrag);
}

void CustomWindow::setWinFixedSize(int width, int height)
{
    this->resize(width, height);
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);
}

void CustomWindow::setWinFixedSize(int width, int height, bool isDrag = true)
{
    this->resize(width, height);
    this->setMinimumSize(width, height);
    this->setMaximumSize(width, height);
    this->setMouseTracking(isDrag);
}

void CustomWindow::setTopStyleSheet(QString qssStr)
{
    _top_widget->setStyleSheet(qssStr);
}

void CustomWindow::setTopBgColor(QString bgColor = "#FFF")
{
    _top_widget->setStyleSheet("background:" + bgColor + ";");
}

void CustomWindow::setTopHeight(int height = 32)
{
    _top_widget->setFixedHeight(height);
}

void CustomWindow::setIcon(const QPixmap& icon)
{
    _lbl_icon->setPixmap(icon);
}

void CustomWindow::setIconSize(int width, int height)
{
    _lbl_icon->setFixedSize(width, height);
}

void CustomWindow::setIconShow(bool isShow)
{
    isShow ? _lbl_icon->show() : _lbl_icon->hide();
}

void CustomWindow::setIconMargin(int left)
{
    _top_hlayout->setContentsMargins(left, 0, 10, 10);
}

void CustomWindow::setTitle(const QString title)
{
    _lbl_title->setText(title);

}

void CustomWindow::setTitleStyleSheet(const QString qssStr)
{
    _lbl_title->setStyleSheet(qssStr);
}

void CustomWindow::setMaxAndMinAndCloseShow(bool minShow = true, bool maxShow = true, bool closeShow = true)
{
    minShow ? _btn_min->show() : _btn_min->hide();
    maxShow ? _btn_max->show() : _btn_max->hide();
    closeShow ? _btn_close->show() : _btn_close->hide();
}

void CustomWindow::setMinBtnIcon(const QPixmap &icon)
{
    _btn_min->setIcon(icon);
}

void CustomWindow::setMaxBtnIcon(const QPixmap &icon)
{
    _btn_max->setIcon(icon);
}

void CustomWindow::setCloseBtnIcon(const QPixmap &icon)
{
    _btn_close->setIcon(icon);
}

void CustomWindow::setTopBtnIcon(const QPixmap &closeIcon)
{
    _btn_min->setIcon(closeIcon);
}

void CustomWindow::setTopBtnIcon(const QPixmap &minIcon, const QPixmap &closeIcon)
{
    _btn_min->setIcon(minIcon);
    _btn_max->setIcon(closeIcon);
}

void CustomWindow::setTopBtnIcon(const QPixmap &minIcon, const QPixmap &maxIcon, const QPixmap &closeIcon)
{
    _btn_min->setIcon(minIcon);
    _btn_max->setIcon(maxIcon);
    _btn_close->setIcon(closeIcon);
}

void CustomWindow::setMinStyleSheet(const QString qssStr)
{
    _btn_close->setStyleSheet(qssStr);
}

void CustomWindow::setManStyleSheet(const QString qssStr)
{
    _btn_max->setStyleSheet(qssStr);
}

void CustomWindow::setCloseStyleSheet(const QString qssStr)
{
    _btn_close->setStyleSheet(qssStr);
}

void CustomWindow::setTopBtnStyleSheet(const QString qssMinStr, const QString qssMaxStr, const QString qssCloseStr)
{
    _btn_close->setStyleSheet(qssMinStr);
    _btn_max->setStyleSheet(qssMaxStr);
    _btn_close->setStyleSheet(qssCloseStr);
}

void CustomWindow::setDBClickMax(bool dbclickMax)
{
    _dbclick_max = dbclickMax;
}

void CustomWindow::setCenterIsAbleMove(bool isAbleMove)
{
    _center_is_move = isAbleMove;
}

void CustomWindow::setDialog(QString tipsText, bool okShow, bool cancelShow)
{
    setMaxAndMinAndCloseShow(false, false, true);
    setWinFixedSize(300, 200, false);
    setDBClickMax(false);

    InitAlertWinUI(tipsText, okShow, cancelShow);


}

void CustomWindow::loadQss(const QString &path)
{
    QFile qss(path);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

QFont CustomWindow::loadFont(const QString path)
{
    int fontId = QFontDatabase::addApplicationFont(path);
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont iconFont = QFont(fontName);
    return iconFont;
}


void CustomWindow::InitSettings()
{

    this->setAttribute(Qt::WA_TranslucentBackground, true); // 设置背景透明
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);
    this->resize(QSize(600, 400));
    this->setMinimumSize(QSize(200, 200));
    this->setMouseTracking(true); // 追踪鼠标
    this->setObjectName("wrap_widget");
}

void CustomWindow::InitUi()
{
    _top_widget = new QWidget();
    _top_widget->setObjectName("top_widget");
    _top_widget->setFixedHeight(_top_height);
    _top_widget->setMouseTracking(true);
    _top_widget->setContentsMargins(0,10,0,0);

    _main_widget = new QWidget();
    _main_widget->setObjectName("main_widget");
    _main_widget->setFocusPolicy(Qt::NoFocus);
    _main_widget->setMouseTracking(true);


    _wrap_vlayout = new QVBoxLayout();
    _top_hlayout = new QHBoxLayout();
    _top_left_hlayout = new QHBoxLayout();
    _top_black = new QSpacerItem(20, 20);
    _top_right_hlayout = new QHBoxLayout();
    _top_right_btns_hlayout = new QHBoxLayout();
    _main_vlayout = new QVBoxLayout();

    _lbl_icon = new QLabel();
    _lbl_title = new QLabel();
    _btn_min = new QPushButton();
    _btn_max = new QPushButton();
    _btn_close = new QPushButton();

    _lbl_title->setText(QString::fromLocal8Bit("主窗口"));
    _lbl_title->setStyleSheet("color:#fff;font-size:12px;font-family:Consolas,微软雅黑;border:none;");

    _lbl_icon->setFixedWidth(_icon_width - 10);
    _btn_min->setObjectName("btn_min");
    _btn_max->setObjectName("btn_max");
    _btn_close->setObjectName("btn_close");
    _btn_min->setFixedWidth(_icon_width);
    _btn_max->setFixedWidth(_icon_width);
    _btn_close->setFixedWidth(_icon_width);

    _btn_min->setStyleSheet("#btn_min{background:transparent;border:none;}QPushButton#btn_min:hover{background:#66666680;border:none;}");
    _btn_max->setStyleSheet("#btn_max{background:transparent;border:none;}QPushButton#btn_max:hover{background:#66666680;border:none;}");
    _btn_close->setStyleSheet("QPushButton#btn_close{background:transparent;border:none;}QPushButton#btn_close:hover{background:#D55D5F;border:none;}");



    _wrap_vlayout->addWidget(_top_widget);
    _wrap_vlayout->addWidget(_main_widget);
    _wrap_vlayout->setSpacing(0);
    _wrap_vlayout->setStretch(0, 1);
    _wrap_vlayout->setStretch(0, 23);


    _top_hlayout->addWidget(_lbl_icon);
    _top_hlayout->addLayout(_top_left_hlayout);
    _top_hlayout->addLayout(_top_right_hlayout);

    _top_hlayout->setStretch(0, 1);
    _top_hlayout->setStretch(1, 20);
    _top_hlayout->setStretch(2, 3);
    _top_hlayout->setSpacing(0);
    _top_hlayout->setContentsMargins(10, 0, 10, 10);

    _top_widget->setFixedHeight(_top_height);
    _top_widget->setStyleSheet("#top_widget {background:" + _widget_color + ";border:none;color:#fff;font-size:16px;}");
    _main_widget->setStyleSheet("#main_widget{border:none; background:#fff; padding: 20px}");


    _top_left_hlayout->addWidget(_lbl_title);
    _top_left_hlayout->addSpacerItem(_top_black);
    _top_right_btns_hlayout->addStretch();
    _top_right_btns_hlayout->setSpacing(0);
    _top_right_btns_hlayout->addWidget(_btn_min);
    _top_right_btns_hlayout->addWidget(_btn_max);
    _top_right_btns_hlayout->addWidget(_btn_close);
    _top_right_hlayout->addLayout(_top_right_btns_hlayout);

    _top_widget->setLayout(_top_hlayout);
    this->setLayout(_wrap_vlayout);

    QPixmap _lbl_icon_s = style()->standardPixmap(QStyle::SP_TitleBarMenuButton);
    _lbl_icon->setPixmap(_lbl_icon_s);

    QPixmap _btn_min_icon = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    _btn_min->setIcon(_btn_min_icon);
    _btn_min->setToolTip(QString::fromLocal8Bit("最小化"));
    _btn_min->setCursor(Qt::PointingHandCursor);

    QPixmap _btn_max_icon = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
    _btn_max->setIcon(_btn_max_icon);
    _btn_max->setToolTip(QString::fromLocal8Bit("最大化"));
    _btn_max->setCursor(Qt::PointingHandCursor);

    QPixmap _btn_close_icon = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    _btn_close->setIcon(_btn_close_icon);
    _btn_close->setToolTip(QString::fromLocal8Bit("关闭"));
    _btn_close->setCursor(Qt::PointingHandCursor);

    _main_widget->setLayout(_main_vlayout);



    MainSignals();
    setStyle();
    InitUiAfter();
}

void CustomWindow::InitUiAfter()
{
    _wrap_vlayout->setContentsMargins(_left_margin, _top_margin, _right_margin, _bottom_margin);
}

void CustomWindow::MainSignals()
{
    connect(_btn_min, &QPushButton::clicked, this, &CustomWindow::on_btnMin_clicked);
    connect(_btn_max, &QPushButton::clicked, this, &CustomWindow::on_btnMax_clicked);
    connect(_btn_close, &QPushButton::clicked, this, &CustomWindow::on_btnClose_clicked);

}

void CustomWindow::saveRestoreInfo(const QPoint point, const QSize size)
{
    _m_restorePos = point;
    _m_restoreSize = size;
}

// 获取窗口最大化前窗口的位置以及大小;
void CustomWindow::getRestoreInfo(QPoint& point, QSize& size)
{
    point = _m_restorePos;
    size = _m_restoreSize;
}



void CustomWindow::on_btnMin_clicked()
{
    this->showMinimized();
}

void CustomWindow::on_btnMax_clicked()
{
    maxAndRestore();
}

void CustomWindow::on_btnClose_clicked()
{
    //    emit sys_quit();
    this->close();
}

void CustomWindow::maxAndRestore()
{
    if(_is_max) {
        //        _top_widget->setFixedHeight(_top_height);
        this->setGeometry(QRect(_m_restorePos, _m_restoreSize));

        _is_max = false;
        _m_restorePos = this->pos();
        _m_restoreSize = QSize(0, 0);



        QPixmap btn_max_icon = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
        _btn_max->setIcon(btn_max_icon);
        _btn_max->setToolTip(QString::fromLocal8Bit("最大化"));

    } else {

        _m_restorePos = this->pos();
        _m_restoreSize = QSize(this->width(), this->height());
        //        _top_widget->setFixedHeight(_top_height + 4);

        QRect desktopRect = QApplication::desktop()->availableGeometry();
        QRect FactRect = QRect(desktopRect.x() - 5, desktopRect.y() - 5, desktopRect.width() + 10, desktopRect.height() + 10);

        setGeometry(FactRect);
        QPixmap btn_max_icon = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
        _btn_max->setIcon(btn_max_icon);
        _btn_max->setToolTip(QString::fromLocal8Bit("向下还原"));
        _is_max = true;
    }
}

void CustomWindow::getMouseStyle(const  QPoint &cursorPos)
{
    // 四个角Rect;
    QRect m_leftTopRect = QRect(0, 0, _left_margin, _top_margin);
    QRect m_leftBottomRect = QRect(0, this->height() - _bottom_margin, _left_margin, _bottom_margin);
    QRect m_rightTopRect = QRect(this->width() - _right_margin, 0, _right_margin, _top_margin);
    QRect m_rightBottomRect = QRect(this->width() - _right_margin, this->height() - _bottom_margin, _right_margin, _bottom_margin);

    // 四条边Rect;
    QRect m_topBorderRect = QRect(_left_margin, 0, this->width() - (_left_margin + _right_margin), _top_margin);
    QRect m_rightBorderRect = QRect(this->width() - _right_margin, _top_margin, _right_margin, this->height() - (_top_margin + _bottom_margin));
    QRect m_bottomBorderRect = QRect(_left_margin, this->height() - _bottom_margin, this->width() - (_left_margin + _right_margin), _bottom_margin);
    QRect m_leftBorderRect = QRect(0, _top_margin, _left_margin, this->height() - (_top_margin + _bottom_margin));

    if (m_leftTopRect.contains(cursorPos))
    {
        _dirpos = LEFTTOP;
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (m_rightTopRect.contains(cursorPos))
    {
        _dirpos = RIGHTTOP;
        setCursor(Qt::SizeBDiagCursor);
    }
    else if (m_rightBottomRect.contains(cursorPos))
    {
        _dirpos = RIGHTBOTTOM;
        setCursor(Qt::SizeFDiagCursor);
    }
    else if (m_leftBottomRect.contains(cursorPos))
    {
        _dirpos = LEFTBOTTOM;
        setCursor(Qt::SizeBDiagCursor);

    }
    else if (m_topBorderRect.contains(cursorPos))
    {
        _dirpos = TOP;
        setCursor(Qt::SizeVerCursor);

    }
    else if (m_rightBorderRect.contains(cursorPos))
    {
        _dirpos = RIGHT;
        setCursor(Qt::SizeHorCursor);
    }
    else if (m_bottomBorderRect.contains(cursorPos))
    {
        _dirpos = BOTTOM;
        setCursor(Qt::SizeVerCursor);

    }
    else if (m_leftBorderRect.contains(cursorPos))
    {
        _dirpos = LEFT;
        setCursor(Qt::SizeHorCursor);
    }
    else
    {
        _dirpos = NONE;
        setCursor(Qt::ArrowCursor);
    }

}

void CustomWindow::paintEvent(QPaintEvent *event)
{
    /* QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

    painter.setBrush(QBrush(_main_color));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width());
    rect.setHeight(rect.height());
    painter.drawRoundedRect(rect, _win_radius, _win_radius);
    {
        QPainterPath painterPath;
        painterPath.addRoundedRect(rect, _win_radius, _win_radius);
        painter.drawPath(painterPath);
    }
    QWidget::paintEvent(event);*/

    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0,0,0,0);
    int arr[10] = {150,120,80,50,40,30,20,10,5,5};
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        if(i == 5) {
            path.addRect(10-i-1, 10-i-1, this->width()-(10-i)*2, this->height()-(10-i)*2);
        } else {
            path.addRoundedRect(10-i-1, 10-i-1, this->width()-(10-i)*2, this->height()-(10-i)*2, 0, 0);
        }
        color.setAlpha(arr[i]);
        painter.setPen(color);
        painter.drawPath(path);

    }
    QWidget::paintEvent(event);

}

void CustomWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(Qt::LeftButton == event->button()) {
        QPoint curPoint = event->pos();
        if(_dbclick_max && curPoint.y() < _top_margin + _top_height) {
            maxAndRestore();
        }
    }

}


void CustomWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        _is_pressed = false;
        if(_dirpos != NONE) {
            this->releaseMouse();
            this->setCursor(QCursor(Qt::ArrowCursor));
        }
    }
}

void CustomWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint curPoint = event->pos();
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(!_is_max) {
        if(_is_pressed) {
            if(_dirpos != NONE) {
                QRect rMove(tl, rb);
                switch (_dirpos) {
                case TOP:
                    if(rb.y() - gloPoint.y() <= this->minimumHeight())
                        rMove.setY(tl.y());
                    else
                        rMove.setY(gloPoint.y());
                    break;
                case BOTTOM:
                    rMove.setHeight(gloPoint.y() - tl.y());
                    break;
                case LEFT:
                    if(rb.x() - gloPoint.x() <= this->minimumWidth())
                        rMove.setX(tl.x());
                    else
                        rMove.setX(gloPoint.x());
                    break;
                case RIGHT:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    break;
                case LEFTTOP:
                    if(rb.x() - gloPoint.x() <= this->minimumWidth())
                        rMove.setX(tl.x());
                    else
                        rMove.setX(gloPoint.x());
                    if(rb.y() - gloPoint.y() <= this->minimumHeight())
                        rMove.setY(tl.y());
                    else
                        rMove.setY(gloPoint.y());
                    break;
                case LEFTBOTTOM:
                    if(rb.x() - gloPoint.x() <= this->minimumWidth()) {
                        rMove.setWidth(gloPoint.x() - tl.x());
                    } else {
                        rMove.setX(gloPoint.x());
                        rMove.setHeight(gloPoint.y() - tl.y());
                    }

                    if(rb.y() - gloPoint.y() <= this->minimumHeight()) {
                        rMove.setY(tl.y());
                    } else {
                        rMove.setX(gloPoint.x());
                        rMove.setHeight(gloPoint.y() - tl.y());
                    }
                    break;
                case RIGHTBOTTOM:
                    rMove.setWidth(gloPoint.x() - tl.x());
                    rMove.setHeight(gloPoint.y() - tl.y());
                    break;
                case RIGHTTOP:

                    if(rb.x() - gloPoint.x() <= this->minimumWidth()) {
                        rMove.setWidth(gloPoint.x() - tl.x());
                    } else {
                        rMove.setWidth(gloPoint.x() - tl.x());
                        rMove.setY(gloPoint.y());
                    }

                    if(rb.y() - gloPoint.y() <= this->minimumHeight()) {
                        rMove.setY(tl.y());
                    } else {
                        rMove.setWidth(gloPoint.x() - tl.x());
                        rMove.setY(gloPoint.y());
                    }
                    break;
                default:
                    break;
                }

                setGeometry(rMove);
            } else {
                if(_center_is_move) {
                    move(gloPoint - _start_point);
                    event->accept();
                } else {
                    if(curPoint.y() < _top_margin + _top_height) {
                        move(gloPoint - _start_point);
                        event->accept();
                    }
                }

            }
        } else {
            getMouseStyle(curPoint);
        }

    }
    QWidget::mouseMoveEvent(event);
}

void CustomWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        _is_pressed = true;
        if(_dirpos != NONE) {
            this->mouseGrabber();
        } else {
            _start_point = event->globalPos() - this->frameGeometry().topLeft();
        }

    } else if(event->button() == Qt::RightButton) {

    } else {
        QWidget::mousePressEvent(event);
    }

}

void CustomWindow::leaveEvent(QEvent *)
{
    setCursor(Qt::ArrowCursor);
}

void CustomWindow::setStyle()
{

    QString mainBgColor = QString("rgb(91,155,213)");
    QString fontColor = QString("rgb(255,255,255)");

    //    this->setStyleSheet("#wrap_widget { background:"+mainBgColor +";color:" + fontColor + ";border-radius:20px;}");

    //    _main_widget->setStyleSheet("#main_widget {background:#fff;}");
}

int CustomWindow::setRGBARange(int r)
{
    return r > 255 && r < 0 ? 255 : r;
}

void CustomWindow::InitAlertWinUI(QString tipsText, bool okShow, bool cancelShow)
{

    QWidget* center_widget = new QWidget();
    QWidget* bottom_widget = new QWidget();
    QHBoxLayout* center_layout = new QHBoxLayout();
    QHBoxLayout* bottom_layout = new QHBoxLayout();
    QSpacerItem* center_left_space = new QSpacerItem(80,20);
    QSpacerItem* center_rigth_space = new QSpacerItem(20,20);
    QLabel* lbl_icon = new QLabel("ICON");
    QLabel* lbl_title = new QLabel(tipsText);

    lbl_icon->hide();
    lbl_title->setStyleSheet("color:#000;font-size:12x;font-weight:100;font-family:Consolas,微软雅黑;border:none;");

    QSpacerItem* bottom_left_space = new QSpacerItem(20,20);
    QSpacerItem* bottom_rigth_space = new QSpacerItem(20,20);
    center_layout->addSpacerItem(center_left_space);
    center_layout->addWidget(lbl_icon);
    center_layout->addWidget(lbl_title);
    center_layout->addSpacerItem(center_rigth_space);
    center_widget->setLayout(center_layout);

    bottom_layout->addSpacerItem(bottom_left_space);
    if(okShow) {
        QPushButton* btn_ok = new QPushButton(QStringLiteral("确定"));
        btn_ok->setFixedWidth(80);
        btn_ok->setObjectName("btn_ok");
        dropShadowEffect(btn_ok);
        setBtnQssStyleOne(btn_ok, "#btn_ok");
        bottom_layout->addWidget(btn_ok);
        connect(btn_ok, &QPushButton::clicked, this, &CustomWindow::on_dialogBtnOk_clicked);
    }

    if(cancelShow) {
        QPushButton* btn_cancel = new QPushButton(QStringLiteral("关闭"));
        btn_cancel->setFixedWidth(80);
        btn_cancel->setObjectName("btn_cancel");
        dropShadowEffect(btn_cancel);
        setBtnQssStyleOne(btn_cancel, "#btn_cancel");
        bottom_layout->addWidget(btn_cancel);
        connect(btn_cancel, &QPushButton::clicked, this, &CustomWindow::on_btnClose_clicked);

    }
    bottom_layout->addSpacerItem(bottom_rigth_space);
    bottom_widget->setLayout(bottom_layout);

    _main_vlayout->addWidget(center_widget);
    _main_vlayout->addWidget(bottom_widget);
    this->show();






}

void CustomWindow::on_dialogBtnOk_clicked()
{
    emit s_dialogBtnOk();
    this->close();

}

void CustomWindow::on_dialoBtnClose_clicked()
{
    this->close();
}

void CustomWindow::dropShadowEffect(QWidget* widget)
{
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(6);
    effect->setColor(QColor(0, 0, 0, 100));
    effect->setOffset(0,0);
    widget->setGraphicsEffect(effect);
}

void CustomWindow::setBtnQssStyleOne(QWidget* widget, QString btnClass)
{
    widget->setStyleSheet(""+btnClass+"{background:" + _widget_color + ";"+
                          "padding:10px 20px;color:#fff;border-radius:18px;"+
                          "border-radius: 3px;text-align:center;}"+btnClass+":hover{"+
                          "background-color: " + _widget_color_hover + ";}");
}
