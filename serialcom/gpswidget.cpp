#include "gpswidget.h"
#include <QDebug>



GPSWidget::GPSWidget(QWidget *parent) :
    UartWidget(parent)
{
    m_comPort = "COM5";
    m_buf.clear();

    m_info = new nmeaINFO;
    m_parser = new nmeaPARSER;

    nmea_zero_INFO(m_info);
    nmea_parser_init(m_parser);
}

GPSWidget::~GPSWidget()
{
    nmea_parser_destroy(m_parser);

    delete m_info;
    delete m_parser;
}

void GPSWidget::process(QByteArray msg)
{
    qDebug() << "GPS" << msg;


    while( msg.contains("\r\n") )
    {
        int index = msg.indexOf("\r\n");

        m_buf.append( msg.left(index + 2) );
        parseFrame( m_buf );
        m_buf.clear();

        msg = msg.mid(index + 2);
    }

    m_buf.append( msg );

}

void GPSWidget::parseFrame(QString frame)
{
    qDebug() << frame;

    nmea_parse(m_parser, frame.toUtf8().data() , frame.size(), m_info);


    qDebug() << "lan: " << m_info->lat << "lon" << m_info->lon;
}
