#ifndef GPSWIDGET_H
#define GPSWIDGET_H


#include "uartwidget.h"

#include "nmea/nmea.h"

class GPSWidget : public UartWidget
{
    Q_OBJECT
public:
    explicit GPSWidget(QWidget *parent = 0);
    ~GPSWidget();

signals:

public slots:

protected:
    virtual void process( QByteArray msg );

    void parseFrame (QString frame );

private:
    QString m_buf;

public:
    nmeaINFO* m_info;
    nmeaPARSER* m_parser;

};

#endif // GPSWIDGET_H
