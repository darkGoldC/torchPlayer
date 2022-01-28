#ifndef TPDATAMAIN_H
#define TPDATAMAIN_H

#include <QObject>
#include "ITPDataMain.h"

class TPDataMain : public QObject, public ITPDataMain
{
    Q_OBJECT
public:
    explicit TPDataMain(QObject *parent = nullptr);

    QObject *getObject() override;
    void    registerObject() override;
signals:

};

#endif // TPDATAMAIN_H
