#ifndef FONTAWESOME_H
#define FONTAWESOME_H

#include <QWidget>
#include <QFontDatabase>
#include <QDebug>
#include "customwindow.h"

namespace Ui {
class FontAwesome;
}

class FontAwesome : public QWidget
{
    Q_OBJECT

public:
    explicit FontAwesome(QWidget *parent = 0);
    ~FontAwesome();


    static QFont LoadFontAwesome(QString filePath);

private slots:
    void on_btnDemo_clicked();
    void btnOk_clicked();

private:
    Ui::FontAwesome *ui;

    CustomWindow* win;

    QDialog* dialog;
    CustomWindow* cusDialog;
    QWidget* dialogWidget;

    QFont m_iconFont;

};

#endif // FONTAWESOME_H
