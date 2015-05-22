#include "mainwidget.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    m_controller = new ControllerObject;
    m_gpsWgt = new GPSWidget;
    m_gsmWgt = new GSMWidget;


    ///////////////////////////////////////////////

    QGroupBox* gpsGroupBox = new QGroupBox("GPS");
    m_gpsWgt = new GPSWidget;

    QVBoxLayout* gpsLayout = new QVBoxLayout;
    gpsLayout->addWidget( m_gpsWgt );
    gpsGroupBox->setLayout(gpsLayout);


    QGroupBox* gsmGroupBox = new QGroupBox("GSM");
    m_gsmWgt = new GSMWidget;

    QVBoxLayout* gsmLayout = new QVBoxLayout;
    gsmLayout->addWidget( m_gsmWgt );
    gsmGroupBox->setLayout(gsmLayout);


    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget( gpsGroupBox );
    mainLayout->addWidget( gsmGroupBox );

    setLayout( mainLayout );

    /////////////////////////////////////////
    connect( m_gsmWgt, SIGNAL(newSMS(QString,QString)),
             m_controller, SLOT(setMessage(QString,QString)));
    connect( m_controller, SIGNAL(newSMS(QString,QString)),
             this, SLOT(sendSMS(QString,QString)));
}

void MainWidget::sendSMS(QString phoneNumber, QString type)
{
    QString data;
    if( type == "Logon" )
    {
        data = QString("Logon");
        m_gsmWgt->sendSMS( phoneNumber, data.toUtf8() );
    }
    else if( type == "GPS" )
    {
        QString lat = QString("%1").arg(abs(m_gpsWgt->m_info->lat));
        if(m_gpsWgt->m_info->lat > 0)
        {
            lat += "N";
        }
        else
        {
            lat += "S";
        }

        QString lon = QString("%1").arg(abs(m_gpsWgt->m_info->lon));
        if(m_gpsWgt->m_info->lat > 0)
        {
            lon += "E";
        }
        else
        {
            lon += "W";
        }

        data = QString("%1, %2").arg(lat).arg(lon);
        m_gsmWgt->sendSMS( phoneNumber, data.toUtf8() );
    }
    else if( type == "Logout" )
    {
        data = QString("Logout");
        m_gsmWgt->sendSMS( phoneNumber, data.toUtf8() );
    }
    else if( type == "NewPassword" )
    {
        data = QString("Password Accepted");
        m_gsmWgt->sendSMS( phoneNumber, data.toUtf8() );
    }

}
