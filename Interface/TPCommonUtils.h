#ifdef WIN32
  #pragma execution_character_set("utf-8")
#endif

#ifndef TPCOMMMONUTILS_H
#define TPCOMMMONUTILS_H

#include "TP_BaseDefine.h"
#include <QJsonObject>
#include <QWidget>
#include <QObject>
#include <QDateTime>
#include <QMetaEnum>
#include <QJsonDocument>
#include <QLineEdit>
#include <QJsonArray>
#include <QThread>
#include <QTextCodec>
#include <QPluginLoader>

class TPBASESHARED_EXPORT TPCommonUtils
{
public:
    explicit TPCommonUtils();

    static QByteArray  utf2gbk(const QString& strGBK);
    static QByteArray  gbk2utf(const char* szGBK);

    //汉字首字母加空格分隔
    static QString      headerToWithEmpty(QString strSrc);

    template<typename T>
    static QString enumToString(int nValue)
    {
        QMetaEnum metaEnum = QMetaEnum::fromType<T>();
        return QString(metaEnum.valueToKey(nValue));
    }

    template<typename T>
    static T* loadOnePlugin(const QString& strPuginPath)
    {
        QPluginLoader pluginLoader(strPuginPath);
        QObject *plugin = pluginLoader.instance();
        T* t = qobject_cast<T*>(plugin);
        if (t == Q_NULLPTR)
        {
            qRztInfo() << pluginLoader.errorString();
        }
        return t;
    }

    template<typename T>
    static void     pushPop(QVector<T>& vec, const T& t)
    {
        for(auto it = vec.begin(); it != vec.end();)
        {
            if(*it == t)
                it=vec.erase(it);    //删除元素，返回值指向已删除元素的下一个位置
            else
                ++it;    //指向下一个位置
        }
        vec.push_front(t);
    }

    //支持list vecotr, 其他未测试，要支持erease函数才可以
    template<typename T>
    static void  rztUnique(T& v)
    {
        for (auto iterM = v.begin(); iterM != v.end();)
        {
            auto vFind = *iterM;
            auto iter = std::remove_if(++iterM, v.end(), [&](const typename T::value_type a){
                return a == vFind;
            });


            if (iter != v.end())
            {
                v.erase(iter, v.end());
            }
        }
    }

    static void         makeDir(const QString &strDir);
    static bool         copyDir(const QString &strSourceDir, const QString &strDestDir, const bool& bRemoveExist);

    static bool         strIsNull(const QJsonValue& v);
    static QString      toString(const QRect& rc);
    static QString      readAll(const QString& strFile);
    static QRect        fromString(const QString& str);

    static QString      removeAZ(const QString& str);

    static QString      removeNumer(const QString &str);
    static QString      removeAZfromStr(const QString &str);
    static void         trimLeft(QString& strContent, const QString& strSpecial);

    static QJsonObject  jsonStringtoObject(QString& strJson);
    static QJsonArray   jsonStringToArray(QString& strJson);
    static QString      jsonObjectToString(const QJsonObject& jsonObj, const QJsonDocument::JsonFormat& fmt = QJsonDocument::Indented);
    static QString      jsonObjectToString(const QJsonArray& jar, const QJsonDocument::JsonFormat& fmt = QJsonDocument::Indented);
    static QStringList  jarrayToStringList(const QJsonArray& jar);
    static QJsonObject  readJsonFromFile(const QString& strFile);
    static QJsonArray   readJsonArrayFromFile(const QString& strFile);

    static bool         saveStrToFile(const QString strFile, const QString& strData);
    static bool         savaJsonToFile(const QString strFile, const QJsonObject& json);
    static bool         savaJsonArrayToFile(const QString strFile, const QJsonArray& jarData);

    static bool         isDigital(const QString& str);

    static QString      sendCmd(const QString& str);
    static void         updateStyle(QWidget *wdg);
    static void         updateSingleStyle(QWidget *wdg);

    static QString      secondToTimeString(const qint64 &nSec, const int nType = 0);

    static QByteArray   toByteArray(const QString& str, const QString &strSpliter);

    static QDateTime    toTimeLength(const int &nSec);
    static void         deleteItem(QLayout* layout);//删除item ,QWidget同时要 disconnect delete
    static QString     getLocalIP();

    static QString      md5(const QString &strPwd);

    static QString      timeToShow(const qint64 &nTime);
    static void         regExpIP(QLineEdit *lineEdit);
    static bool         regExpIP(const QString &strText);

    static void         regExpOnlyNum(QLineEdit *lineEdit, const int nStart,const int nEnd);

    static void         regExpOnlyDouble(QLineEdit *lineEdit);

    static void         regExpPort(QLineEdit *lineEdit);

    static void         regExpPwd(QLineEdit *lineEdit);


    static bool         indexOfAZ(const QString& strNumber, const QString &strAZ);

    static void         regExpText(QLineEdit *lineEdit);
    static void         regExpAddressBook(QLineEdit *lineEdit);
    static void         regExpText(QLineEdit *lineEdit, const int nStart, const int nEnd);

    static void         toCopyBuffer(char* szBuffer, const QString& str);
    static QByteArray   toByteArray(const QString& str);

    static  int         createGuid();
};

#endif
