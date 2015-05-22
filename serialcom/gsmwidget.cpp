#include "GSMWidget.h"


#include <QDebug>
#include <QLayout>

GSMWidget::GSMWidget(QWidget *parent) :
    UartWidget(parent)
{
    m_comPort = "COM1";
    m_stage = IDEL_STAGE;

    m_sendSMSBtn = new QPushButton("Send SMS");
    m_readSMSBtn = new QPushButton("Read SMS");

    layout()->addWidget( m_sendSMSBtn );
    layout()->addWidget( m_readSMSBtn );

    connect(m_sendSMSBtn, SIGNAL(clicked()), this, SLOT(onSendSMS()));
    connect(m_readSMSBtn, SIGNAL(clicked()), this, SLOT(onReadSMS()));

    connect(this, SIGNAL(portOpened()), this, SLOT(initGSM()));
}

void GSMWidget::initGSM()
{
    m_stage = IDEL_STAGE;

    writeUart( QString("AT+CMGF=1\r").toUtf8() );


    //writeUart( QString("AT+CNMI=1,1,0,0,1\r").toUtf8() );
}

void GSMWidget::onSendSMS()
{
    QString data = "hello world";
    sendSMS("10086", data.toUtf8());
}

void GSMWidget::onReadSMS()
{
//    readSMS();

//    deleteSMS();
}

void GSMWidget::process(QByteArray msg)
{
    qDebug() << "GSM" << msg;

    m_buf.append( msg );
    while( m_buf.contains("\r\n") )
    {
        int index = m_buf.indexOf("\r\n");
        parseFrame( m_buf.left(index + 2) );

        m_buf = m_buf.mid(index + 2);
    }
}

void GSMWidget::parseFrame(QString frame)
{
//    qDebug() << "frame:" << frame << frame.toUtf8().toHex();

    if( frame == "\r\n" )
        return;

    frame = frame.left( frame.length() - 2 );
    qDebug() << "frame:" << frame << frame.toUtf8().toHex();

    switch( m_stage )
    {
    case IDEL_STAGE:
        if( frame.contains( "+CMGS:"))
        {
            m_stage = SEND_STAGE;
            qDebug() << "Send feedback";
        }
        else if( frame.contains( "+CMGR:") )
        {
            m_stage = READ_STAGE;
            QStringList list = frame.split(",");
            m_phoneNumber = list.at(1).mid(4, 11);
            qDebug() << "Read feedback : " << m_phoneNumber ;
        }
        else if( frame.contains( "AT+CMGD") )
        {
            m_stage = DELETE_STAGE;
            qDebug() << "Delete feedback";
        }
        else if( frame.contains( "+CMTI:") )
        {
            m_stage = IDEL_STAGE;

       //     comformSMS();

            QStringList list = frame.split(",");
            m_currentIndex = list.at(1).toInt();

            readSMS( m_currentIndex );

            qDebug() << "new Message feedback";
        }
        break;
    case SEND_STAGE:
        if( frame.contains( "OK"))
            m_stage = IDEL_STAGE;
        break;
    case READ_STAGE:
        if( frame.contains( "OK"))
        {
            m_stage = IDEL_STAGE;
            deleteSMS( m_currentIndex );
        }
        else
        {
            qDebug() << "SMS: " << frame;
            if( !frame.isEmpty() )
                m_readFrame = frame;
        }
        break;
    case DELETE_STAGE:
        if( frame.contains( "OK"))
        {
            m_stage = IDEL_STAGE;
            emit newSMS(m_phoneNumber, m_readFrame);    //process the message after delete
        }
        break;
    }
}

void GSMWidget::readSMS( int index )
{
    QString data = QString("AT+CMGR=%1\r").arg(index);
    writeUart( data.toUtf8() );
}

void GSMWidget::deleteSMS( int index )
{
    QString data = QString("AT+CMGD=%1\r").arg(index);
    writeUart( data.toUtf8() );
}

void GSMWidget::comformSMS()
{
    QString data = QString("AT+CNMA\r");
    writeUart( data.toUtf8() );
}

void GSMWidget::sendSMS(const QString &phoneNumber, const QByteArray &sms)
{
    QString data = QString("AT+CMGS=\"%1\"\r").arg(phoneNumber);

    writeUart( data.toUtf8() );

//    data.unicode();

    writeUart( sms + QByteArray::fromHex( "1a")  + QString("\r").toUtf8() );
}
