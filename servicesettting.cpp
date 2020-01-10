#include "servicesettting.h"

ServiceSettting::ServiceSettting(QObject *parent) : QObject(parent)
{




}
void ServiceSettting::setBaseUrl(QString baseUrl)
{
    m_strBaseUrl = baseUrl;
}

void ServiceSettting::setRegRootItemName(QString rootItemName)
{
    m_strRootItemName = rootItemName;
}

void ServiceSettting::setRegChildItemName(QString childItemName)
{
    m_strChildItemName = childItemName;
}

void ServiceSettting::setRegItemInfos(QString itemName, QString itemValue)
{
    m_strItemName = itemName;
    m_strItemValue = itemValue;
}

void ServiceSettting::setWriteReg()
{
    QSettings settings(m_strBaseUrl, QSettings::NativeFormat);
    QString itemName;

    if(m_strChildItemName.isEmpty())
    {
        itemName = QString("%1/%2").arg(m_strRootItemName)
                .arg(m_strItemName);
    }
    else
    {
        itemName = QString("%1/%2/%3").arg(m_strRootItemName)
                .arg(m_strChildItemName).arg(m_strItemName);
    }
    settings.setValue(itemName, m_strItemValue);

}

void ServiceSettting::setDelReg(QString regUrl, QString regKey)
{
    QSettings settings(regUrl);

    settings.remove(regKey);
}




void ServiceSettting::setConfFileName(QString fileName)
{
    m_strConfFileName = fileName;
}

void ServiceSettting::setConfGroupName(QString groupName)
{
    m_strConfGroupName = groupName;
}

void ServiceSettting::setConfGroupItemInfo(QString name, QString value)
{
    m_strConfItemName = name;
    m_strConfItemValue = value;
}

void ServiceSettting::setConfGroupItemInfo(QString name, QStringList value)
{
    m_strConfItemName = name;
    m_listConfItmeValue = value;
}

void ServiceSettting::setWriteConf()
{
    QSettings settings(m_strConfFileName);

    settings.beginGroup(m_strConfGroupName);

    if(m_listConfItmeValue.isEmpty())
    {
        settings.setValue(m_strConfItemName, m_strConfItemValue);
    }
    else
    {
        settings.setValue(m_strConfItemName, m_strConfItemValue);
    }

    settings.endGroup();

}

void ServiceSettting::setDelConf(QString filePath, QString key)
{
    QSettings settings(filePath);

    settings.remove(key);
}



/********** 文件操作 ***********/
bool ServiceSettting::setFileCopy(QString oldFileName, QString fileName)
{
    bool copyIsOk = false;

    if(QFile::exists(oldFileName))
    {
        bool isOk = QFile::copy(oldFileName, fileName);

        if(!isOk)
        {
            copyIsOk = QFile::exists(fileName) ? true : false;
        }
        else
        {
            copyIsOk = false;
        }
    }
    else
    {
        copyIsOk = false;
    }

    return copyIsOk;
}

bool ServiceSettting::setFileDel(QString fileName)
{
    return QFile::remove(fileName);
}

bool ServiceSettting::setFileMove(QString oldFileName, QString fileName)
{
    return QFile::rename(oldFileName, fileName);
}

/********** 执行cmd命令 ***********/
QString ServiceSettting::setCmdProcess(QString cmd)
{
    QProcess process;
    process.start(cmd);

    process.waitForFinished(10000);
    QByteArray byteRet = process.readAllStandardOutput();
    QString strRet = QString::fromLocal8Bit(byteRet);
    return strRet;
}


/******** 注册服务 **********/
void ServiceSettting::setServiceAdd(QString appName, QString appPath, QString serviceName)
{
    appPath = appPath.lastIndexOf("\\\\") == 0 || appPath.lastIndexOf("/") == 0  ?
                appPath.mid(0, appPath.length()) :
                appPath;
    // 复制文件
    m_StrExeDir = QCoreApplication::applicationDirPath();

    bool instsrvCpyOk = setFileCopy(m_StrExeDir + "/instsrv.exe", "C:\\Windows\\instsrv.exe");
    if(instsrvCpyOk)
    {
        bool srvanyCpyOk = setFileCopy(m_StrExeDir + "/srvany.exe", "C:\\Windows\\srvany.exe");
        if(srvanyCpyOk)
        {
            // 执行添加服务cmd
            QString cmd = "C:\\Windows\\instsrv.exe " + serviceName + " C:\\Windows\\srvany.exe";
            QString strRet = setCmdProcess(cmd);

            if(strRet.contains("successfuly"))
            {
                // 写入注册表
                setBaseUrl("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Services");
                setRegRootItemName(serviceName);
                setRegChildItemName("Parameters");
                setRegItemInfos("Application", appPath + "/" + appName);
                setWriteReg();

                // 执行启动服务cmd
                QString startCmd = "C:\\Windows\\System32\\sc.exe start " + serviceName;
                QString strStartRet = setCmdProcess(startCmd);

                if(strStartRet.contains(serviceName))
                {
                    qDebug() << "Service is Created And Start is ok!";
                }
                else
                {
                    qDebug() << "Service is Created And Start is Error!";
                }

            }
            else if(strRet.contains("already"))
            {
                qDebug() << "Service is already Created!";
            }
            else
            {
                qDebug() << "Service is Created Error!";
            }
        }
        else
        {
            qDebug() << "Copy srvany is Error!";
        }
    }
    else
    {
        qDebug() << "Copy instsrv is Error!";
    }

}

void ServiceSettting::setServiceDel(QString serviceName)
{
    // 停止服务
    QString stopCmd = "C:/Windows/System32/sc.exe stop " + serviceName;
    QString strStopRet = setCmdProcess(stopCmd);

    if(strStopRet.contains(serviceName) ||
            strStopRet.contains("1062"))
    {
        // 移除服务
        QString removeCmd = "C:/Windows/instsrv.exe " + serviceName + " remove";
        QString strRemoveRet = setCmdProcess(removeCmd);

        if(strRemoveRet.contains("successfully"))
        {
            qDebug() << "Service Del Success!";
        }
        else
        {
            qDebug() << "Service Del Fail!";
        }
    }
    else
    {
        qDebug() << "Service Stop Fail!";
    }
}
