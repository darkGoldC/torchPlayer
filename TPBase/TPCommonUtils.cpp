#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

#include "TPCommonUtils.h"
#include <QJsonDocument>
#include <QFile>
#include <QHostAddress>
#include <QNetworkInterface>

#include <QCryptographicHash>
#include <QProcess>

#include <QList>
#include <QStyle>
#include <QDateTime>
#include <QRegExpValidator>
#include <QLayoutItem>
#include <QtConcurrent/QtConcurrent>
#include <QLayout>
#define ONEDAYTIME  24*60*60


TPCommonUtils::TPCommonUtils()
{

}

QByteArray TPCommonUtils::utf2gbk(const QString &strGBK)
{
    static QMutex s_mutexCodec;

    s_mutexCodec.lock();
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    QByteArray byRet = gbk->fromUnicode(utf8->toUnicode(strGBK.toUtf8()));
    s_mutexCodec.unlock();

    return byRet;
}


QByteArray TPCommonUtils::gbk2utf(const char* szGBK)
{
    QTextCodec *gbk = QTextCodec::codecForName("GB18030");
    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
    return utf8->fromUnicode(gbk->toUnicode(QByteArray(szGBK)));
}

QString TPCommonUtils::headerToWithEmpty(QString strSrc)
{
    if(strSrc.size() > 50)
    {
        return "";
    }

    QChar tempStr[100] = {0};
    for(int index = 0; index < strSrc.size(); index++)
    {
        tempStr[index*2] = strSrc.at(index).toUpper();
        tempStr[index*2+1] = QChar(' ');
    }
    return QString(tempStr);
}


void TPCommonUtils::makeDir(const QString &strDir)
{
    QDir dirSys(strDir);
    if (!dirSys.exists())
    {
        dirSys.mkpath(strDir);
    }
}

bool TPCommonUtils::copyDir(const QString &strSourceDir, const QString &strDestDir, const bool& bRemoveExist)
{
    QDir sourceDir(strSourceDir);
    QDir targetDir(strDestDir);
    makeDir(strDestDir);

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
        {
            continue;
        }

        if(fileInfo.isDir())
        {
            if(!copyDir(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()), bRemoveExist))
            {
                return false;
            }
        }
        else
        {
            bool bCopy = true;
            if(targetDir.exists(fileInfo.fileName()))
            {
                if (bRemoveExist)
                {
                    targetDir.remove(fileInfo.fileName());
                }
                else
                {
                    bCopy = false;
                }
            }

            if(bCopy)
            {
                QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()));
            }
        }
    }
    return true;
}

bool TPCommonUtils::strIsNull(const QJsonValue &v)
{
    QString str = v.toString().toUpper();
    str = str.trimmed();
    return str.isEmpty() || str == "NULL";
}

QString TPCommonUtils::toString(const QRect &rc)
{
    return QString("(%1,%2,%3,%4)")
            .arg(rc.left())
            .arg(rc.top())
            .arg(rc.width())
            .arg(rc.height());
}

QString TPCommonUtils::readAll(const QString &strFile)
{
    QString strRet;

    QFile file(strFile);
    if (file.open(QIODevice::ReadOnly))
    {
        strRet = file.readAll();
        file.close();
    }

    return strRet;
}

QRect TPCommonUtils::fromString(const QString &str)
{
    QRect rcRet;
    QString strTemp = str;
    strTemp.replace(" ", "");
    strTemp.replace("(", "");
    strTemp.replace(")", "");
    QStringList lst = strTemp.split(",");
    if (lst.size() == 4)
    {
        rcRet = QRect(lst[0].toInt(), lst[1].toInt(), lst[2].toInt(), lst[3].toInt());
    }

    return rcRet;
}

QString TPCommonUtils::removeAZ(const QString &str)
{
    QString strRet = str;
    for (int i = strRet.length() - 1; i >= 0; i--)
    {
        if (strRet[i] < '0' || strRet[i] > '9')
        {
            strRet.remove(i, 1);
        }
    }

    return strRet;
}

QString TPCommonUtils::removeNumer(const QString &str)
{
    QString strRet = str;
    for (int i = strRet.length() - 1; i >= 0; i--)
    {
        if (strRet[i] > '0' || strRet[i] < '9')
        {
            strRet.remove(i, 1);
        }
    }

    return strRet;
}

QString TPCommonUtils::removeAZfromStr(const QString &str)
{
    QString strRet = str;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
           strRet = str.left(i);
           break;
        }
    }

    return strRet;
}



void TPCommonUtils::trimLeft(QString &strContent, const QString &strSpecial)
{
    for (int i = 0; i < strSpecial.size(); i++)
    {
        //多个特殊字符
        while (strContent.left(1) == strSpecial.at(i))
        {
            strContent.remove(0, 1);
        }
    }
}

QJsonObject TPCommonUtils::jsonStringtoObject(QString &strJson)
{
    QJsonDocument doc = QJsonDocument::fromJson(strJson.toUtf8());
    return doc.object();
}

QJsonArray TPCommonUtils::jsonStringToArray(QString &strJson)
{
    QJsonDocument doc = QJsonDocument::fromJson(strJson.toUtf8());
    return doc.array();
}

QString TPCommonUtils::jsonObjectToString(const QJsonArray& jar, const QJsonDocument::JsonFormat& fmt)
{
    QString strRet;
    QJsonDocument doc(jar);
    strRet = QString(doc.toJson(fmt));
    return strRet;
}

QStringList TPCommonUtils::jarrayToStringList(const QJsonArray &jar)
{
    QStringList lstRet;
    for (int i = 0; i < jar.size(); i++)
    {
        lstRet.push_back(jar[i].toString());
    }
    return lstRet;
}

QString TPCommonUtils::jsonObjectToString(const QJsonObject &jsonObj, const QJsonDocument::JsonFormat& fmt)
{
    QString strRet;
    QJsonDocument doc(jsonObj);
    if (!jsonObj.isEmpty())
    {
        strRet = QString(doc.toJson(fmt));
    }
    return strRet;
}


QJsonObject TPCommonUtils::readJsonFromFile(const QString &strFile)
{
    QString strAll;

    QFile file(strFile);
    if (file.open(QFile::ReadOnly))
    {

        QString strTemp = file.readAll();
        strAll = strTemp.toUtf8();
        //        strAll= QLatin1String(file.readAll());
        file.close();
    }
    else
    {
        //qTPInfo () << "read file fail" << strFile;
    }

    return jsonStringtoObject(strAll);
}

QJsonArray TPCommonUtils::readJsonArrayFromFile(const QString &strFile)
{
    QString strAll;

    QFile file(strFile);
    qint64 nDateTime = QDateTime::currentMSecsSinceEpoch();
    if (file.open(QFile::ReadOnly))
    {

        QString strTemp = file.readAll();
        strAll = strTemp.toUtf8();
        //        strAll= QLatin1String(file.readAll());
        file.close();
    }
    else
    {
        //qTPInfo () << "read file fail" << strFile;
    }

    //qDebug () << strFile << strAll.length() << nDateTime << QDateTime::currentMSecsSinceEpoch();

    return jsonStringToArray(strAll);
}

void TPCommonUtils::deleteItem(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        //setParent为NULL，防止删除之后界面不消失
        if(child->widget())
        {
            child->widget()->setParent(nullptr);
            delete child->widget();
        }
        else if (child->layout())
        {
            deleteItem(child->layout());
            child->layout()->deleteLater();
        }
        else if (child->spacerItem())
        {
            //delete child->spacerItem();
        }

        delete child;
    }
}

bool TPCommonUtils::savaJsonToFile(const QString strFile, const QJsonObject &json)
{
    QString strData = jsonObjectToString(json);
    return saveStrToFile(strFile, strData);
}

bool TPCommonUtils::savaJsonArrayToFile(const QString strFile, const QJsonArray &jarData)
{
    QString strData = jsonObjectToString(jarData);
    return saveStrToFile(strFile, strData);
}


bool TPCommonUtils::saveStrToFile(const QString strFile, const QString &strData)
{
    bool bRet = false;

    QFile file(strFile);
    if (file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        bRet = true;
        QTextStream in(&file);
        in.setCodec("UTF-8");
        in << strData;
        in.setGenerateByteOrderMark(false);
        file.close();
    }
    else
    {
        //qTPInfo () << "open file failed" << strFile;
    }

    return bRet;
}


bool TPCommonUtils::indexOfAZ(const QString& strNumber, const QString &strAZ)
{
    QString strTemp = strNumber;
    int nPos = strTemp.indexOf(strAZ);
    if (nPos == -1)
    {
        return false;
    }

    strTemp.remove(strAZ);

    return isDigital(strTemp);
}

bool TPCommonUtils::isDigital(const QString &str)
{
    if (str.length() == 0)
    {
        return false;
    }

    bool bRet = true;
    QByteArray byData = str.toUtf8();
    for (int i = 0; i < byData.length(); i++)
    {
        if (byData[i] < '0' || byData[i] > '9')
        {
            bRet = false;
        }
    }

    return bRet;
}

QString TPCommonUtils::sendCmd(const QString &str)
{
    QProcess process;
    process.start(str);
    process.waitForStarted();
    process.waitForFinished();
    QString strCmdResult = QString::fromLocal8Bit(process.readAllStandardOutput());
    return strCmdResult;
}

void TPCommonUtils::updateStyle(QWidget *wdg)
{
    QList<QWidget*> vecWdg = wdg->findChildren<QWidget*>();

    wdg->style()->unpolish(wdg);
    wdg->style()->polish(wdg);

    for (int i = 0; i < vecWdg.count(); i++)
    {
        vecWdg.at(i)->style()->unpolish(vecWdg.at(i));
        vecWdg.at(i)->style()->polish(vecWdg.at(i));
    }
    wdg->update();
}

void TPCommonUtils::updateSingleStyle(QWidget *wdg)
{
    if(wdg == Q_NULLPTR)
    {
        return;
    }

    wdg->style()->unpolish(wdg);
    wdg->style()->polish(wdg);
    wdg->update();
}

QString TPCommonUtils::secondToTimeString(const qint64 &nSec, const int nType)
{
    QString strHour;
    QString strMin;
    QString strSec;
    QString strTempTime;

    if (nSec > 3600 * 10)
    {
        strHour = QString::number((nSec / 3600));
    }
    else//10小时以内
    {
        strHour  = QString("0" + QString::number((nSec / 3600)%10)) ;
    }

    if ((nSec / 60)%60 < 10)
    {
        strMin = QString("0" + QString::number((nSec / 60)%60)) ;
    }
    else
    {
        strMin = QString::number((nSec / 60)%60);
    }

    if (nSec % 60 < 10)
    {
        strSec = QString("0" + QString::number(nSec % 60)) ;
    }
    else
    {
        strSec = QString::number(nSec % 60);
    }

    if (nType == 0)
    {
        strTempTime = QString(strHour + ":" + strMin + ":" + strSec);
    }
    else if (nType == 1)
    {
        strTempTime = QString(strHour + "时" + strMin + "分" + strSec + "秒");
    }

    return  strTempTime;
}

QByteArray TPCommonUtils::toByteArray(const QString &str, const QString &strSpliter)
{
    QByteArray byRet;

    QStringList lstVec = str.split(strSpliter);
    for (auto& a: lstVec)
    {
        bool bOk = false;
        uint bV = a.toUInt(&bOk, 16);
        if (bOk)
        {
            byRet.append(char(bV));
        }
    }

    return byRet;
}

QDateTime TPCommonUtils::toTimeLength(const int &nSec)
{
    QDateTime m_time;
    //    m_time.setHMS(0, 0, 0, 0);
    return m_time.addSecs(nSec);
}

QString TPCommonUtils::getLocalIP()
{
    QString strRet;

    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            //IPv4地址
            if (address.toString().contains("127.0."))
            {
                continue;
            }
            strRet = address.toString();
        }
    }

    return strRet;
}



QString TPCommonUtils::md5(const QString &strPwd)
{
    return QCryptographicHash::hash ( strPwd.toUtf8(), QCryptographicHash::Md5 ).toHex();
}

QString TPCommonUtils::timeToShow(const qint64 &nTime)
{
    QString showTime;
    qint64 nCurTime = QDateTime::fromString(QDate::currentDate().toString("yyyy/MM/dd"), "yyyy/MM/dd").toSecsSinceEpoch();

    if (nCurTime - nTime <= 0)//today
    {
        showTime = QDateTime::fromSecsSinceEpoch(nTime).toString("HH:mm");
    }
    else if (nCurTime - nTime  > 0 && nCurTime - nTime <= ONEDAYTIME)
    {
        showTime = "昨天";
    }
    else if (nCurTime - nTime > ONEDAYTIME && nCurTime - nTime <= ONEDAYTIME*8)
    {
        showTime = QDateTime::fromSecsSinceEpoch(nTime).toString("dddd");
    }
    else
    {
        showTime = QDateTime::fromSecsSinceEpoch(nTime).toString("yyyy/MM/dd");
    }

    return showTime;
}

void TPCommonUtils::regExpIP(QLineEdit *lineEdit)
{
    QRegExp regExpIP("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
    lineEdit->setValidator(new QRegExpValidator(regExpIP, lineEdit));
}

bool TPCommonUtils::regExpIP(const QString &strText)
{
    QRegExp regExpIP("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
    return regExpIP.exactMatch(strText);
}

void TPCommonUtils::regExpOnlyNum(QLineEdit *lineEdit, const int nStart, const int nEnd)
{
    QString strNum = QString("^[0-9]{%1,%2}$").arg(nStart).arg(nEnd);
    QRegExp regExpNum(strNum);
    lineEdit->setValidator(new QRegExpValidator(regExpNum, lineEdit));
}

void TPCommonUtils::regExpOnlyDouble(QLineEdit *lineEdit)
{
    QDoubleValidator *validator = new QDoubleValidator(0.0, 100.0, 1, lineEdit);
    lineEdit->setValidator(validator);
}

void TPCommonUtils::regExpPort(QLineEdit *lineEdit)
{
    QRegExp regExpNetPort("((6553[0-5])|[655[0-2][0-9]|65[0-4][0-9]{2}|6[0-4][0-9]{3}|[1-5][0-9]{4}|[1-9][0-9]{3}|[1-9][0-9]{2}|[1-9][0-9]|[0-9])");
    lineEdit->setValidator(new QRegExpValidator(regExpNetPort, lineEdit));
}

void TPCommonUtils::regExpPwd(QLineEdit *lineEdit)
{
    QRegExp regExpPwd(QString("^[-A-Za-z0-9_]{6,12}$"));
    lineEdit->setValidator(new QRegExpValidator(regExpPwd, lineEdit));
}

void TPCommonUtils::regExpText(QLineEdit *lineEdit, const int nStart, const int nEnd)
{
    QRegExp regExpPwd(QString("^[A-Za-z0-9]{%1,%2}$").arg(nStart).arg(nEnd));
    lineEdit->setValidator(new QRegExpValidator(regExpPwd, lineEdit));
}

void TPCommonUtils::regExpText(QLineEdit *lineEdit)
{
    QRegExp regExpText(QString("^[\u4e00-\u9fa5A-Za-z0-9]{15}$"));
    lineEdit->setValidator(new QRegExpValidator(regExpText, lineEdit));
}

void TPCommonUtils::regExpAddressBook(QLineEdit *lineEdit)
{
    QRegExp regExpText(QString("^[\u4e00-\u9fa5A-Za-z0-9 ]{30}$ "));
    lineEdit->setValidator(new QRegExpValidator(regExpText, lineEdit));
}



void TPCommonUtils::toCopyBuffer(char *szBuffer, const QString &str)
{
#ifdef WIN32
    strcpy(szBuffer, utf2gbk(str).data());
#else
    strcpy(szBuffer, str.toUtf8().data());
#endif
}

QByteArray TPCommonUtils::toByteArray(const QString &str)
{
    QByteArray arRet;
#ifdef WIN32
    arRet = TPCommonUtils::utf2gbk(str);
#else
    arRet = str.toUtf8();
#endif
    return arRet;
}

int TPCommonUtils::createGuid()
{
    QUuid uuid = QUuid::createUuid();
    int id = 0;
    id += (uuid.data4[0] << 17) + (uuid.data4[0] % 11 * 11);
    id += (uuid.data4[1] << 11) + (uuid.data4[1] % 13 * 13);
    id += (uuid.data4[2] << 13) + (uuid.data4[2] % 3 * 3);
    id += (uuid.data4[3] << 3) + (uuid.data4[3] % 19 * 19);
    id += (uuid.data4[4] << 17) + (uuid.data4[4] % 7 * 7);
    id += (uuid.data4[5] << 19) + (uuid.data4[5] % 23 * 23);
    id += (uuid.data4[6] << 23) + (uuid.data4[6] % 5 * 5);
    id += (uuid.data4[7] << 5) + (uuid.data4[7] % 17 * 17);

    return  abs(id);
}

