#ifndef UARTOBJECT_H
#define UARTOBJECT_H

#include <QObject>
#include <QtDebug>
#include <QTimer>

#include "qextserialport.h"

class QextSerialPort;
class QextSerialEnumerator;

class UartObject : public QObject
{
    Q_OBJECT
public:
    explicit UartObject(QObject *parent = 0);

signals:
   void dataArray( QByteArray data );

public slots:
    bool open(QString portName);
    void close();
    void onReadyRead();

    void write( QByteArray data );

private:
    QextSerialPort *myCom;
    QTimer* m_timer;

};

#endif // UARTOBJECT_H
