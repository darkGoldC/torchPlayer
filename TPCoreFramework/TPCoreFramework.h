#ifndef TPCOREFRAMEWORK_H
#define TPCOREFRAMEWORK_H

#include <QObject>
#include "TP_CoreDefine.h"
#include "ITPCoreFramework.h"


class TPCORESHARED_EXPORT TPCoreFramework : public QObject, public ITPCoreFramework
{
    Q_OBJECT
public:
    explicit TPCoreFramework(QObject *parent = nullptr);
    void    initWork() override;
    QObject *getObject() override;
    void    startWork() override;
    void    stopWork() override;
    void    pauseWork() override;
    double  getProcess() override;
    void    seekProcess(const double nValue) override;
    bool    openVideo(const QString strUrl, ITPVideoWidget *pWidget) override;
signals:

private:

};

#endif // TPCOREFRAMEWORK_H
