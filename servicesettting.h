#ifndef SERVICESETTTING_H
#define SERVICESETTTING_H

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QProcess>
#include <QtCore>
#include <QDebug>

class ServiceSettting : public QObject
{
    Q_OBJECT
public:
    explicit ServiceSettting(QObject *parent = nullptr);

public:

    /********** 写入注册表 ***********/

    // 设置写入注册表目录
    void setBaseUrl(QString baseUrl);

    // 写入注册表根节点名称
    void setRegRootItemName(QString rootItemName);

    // 写入注册表根节点下一级的名称
    void setRegChildItemName(QString childItemName);

    // 写入注册表的项，及项的值
    void setRegItemInfos(QString itemName, QString itemValue);

    // 写入注册表
    void setWriteReg();

    // 删除注册表
    void setDelReg(QString regUrl, QString regKey);


    /********** 写入配置文件 ***********/

    // 写入配置文件文件名
    void setConfFileName(QString fileName);

    // 写入配置文件组名
    void setConfGroupName(QString groupName);

    // 写入配置文件组下键值
    void setConfGroupItemInfo(QString name, QString value);
    void setConfGroupItemInfo(QString name, QStringList value);

    // 写入注册表
    void setWriteConf();

    // 删除注册表
    void setDelConf(QString filePath, QString key);


    /********** 文件操作 ***********/

    // 复制文件
    bool setFileCopy(QString oldFileName, QString fileName);

    // 删除文件
    bool setFileDel(QString fileName);

    // 移动文件
    bool setFileMove(QString oldFileName, QString fileName);

    /******** 执行cmd命令 **********/

    QString setCmdProcess(QString cmd);



    /******** 注册服务 **********/
    void setServiceAdd(QString appName, QString appPath, QString serviceName);


    /******** 删除服务 **********/
    void setServiceDel(QString serviceName);

signals:

public slots:


private:

    QString m_strBaseUrl;
    QString m_strRootItemName;
    QString m_strChildItemName;
    QString m_strItemName;
    QString m_strItemValue;

    QString m_strConfFileName;
    QString m_strConfGroupName;
    QString m_strConfItemName;
    QString m_strConfItemValue;

    QString m_StrExeDir;

    QStringList m_listConfItmeValue;

};

#endif // SERVICESETTTING_H
