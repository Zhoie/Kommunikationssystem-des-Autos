#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "gpswidget.h"
#include "gsmwidget.h"
#include "controllerobject.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:

public slots:
    void sendSMS(QString phoneNumber, QString type);

private:
    ControllerObject* m_controller;
    GPSWidget* m_gpsWgt;
    GSMWidget* m_gsmWgt;
};

#endif // MAINWIDGET_H
