#include "uartobject.h"

UartObject::UartObject(QObject *parent) :
    QObject(parent)
{
    myCom = NULL;
    m_timer = new QTimer;
    m_timer->setInterval( 1000 );
}

bool UartObject::open( QString portName )
{
//    myCom = new QextSerialPort(portName, QextSerialPort::EventDriven);
    myCom = new QextSerialPort(portName, QextSerialPort::Polling);
    myCom->setBaudRate(BAUD9600);
    myCom->setFlowControl(FLOW_OFF);
    myCom->setParity(PAR_NONE);
    myCom->setDataBits(DATA_8);
    myCom->setStopBits(STOP_2);

    if (myCom->open(QIODevice::ReadWrite) == true)
    {
//        connect(myCom, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

        connect(m_timer, SIGNAL(timeout()), this, SLOT(onReadyRead()));

        qDebug() << "listening for data on" << myCom->portName();

        m_timer->start();

        return true;
    }
    else
    {
        qDebug() << "device failed to open:" << myCom->errorString();

        return false;
    }
}

void UartObject::close()
{
    if( myCom->isOpen() )
    {
        myCom->close();
    }
}

void UartObject::onReadyRead()
{
    QByteArray bytes;
    int a = myCom->bytesAvailable();

    if( a > 0 )
    {
        bytes.resize(a);
        myCom->read(bytes.data(), bytes.size());

        emit dataArray( bytes );
    }

}

void UartObject::write(QByteArray data)
{
    if( myCom != NULL && myCom->isOpen() )
    {
        myCom->write( data );
    }
}
