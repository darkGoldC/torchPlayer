#ifndef TPAPPLICATION_H
#define TPAPPLICATION_H

#include <QObject>
#include <QApplication>
#include "TPMainController.h"

class TPApplication : public QApplication
{
    Q_OBJECT
public:
    bool            notify(QObject *reciver, QEvent *e);
    explicit TPApplication(int &argc, char **argv);
    void    initController();
    void    initUI();
    void    initCore();
signals:

private:

};

#endif // TPAPPLICATION_H
