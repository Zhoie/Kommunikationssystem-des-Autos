#include "controllerobject.h"
#include <QDebug>
#include <QSettings>
#include <QRegExp>

ControllerObject::ControllerObject(QObject *parent) :
    QObject(parent)
{
    m_stage = IDEL_CONTROLLER_STATE;
//    m_password = "password";

    m_lastActiveTime.invalidate();


    m_timer = new QTimer;
    m_timer->setInterval( 1000 );
    m_timer->start();

    connect( m_timer, SIGNAL(timeout()), this, SLOT(checkTime()));

    loadPassword();
}

void ControllerObject::setMessage(QString phoneNumber, QString message)
{
    qDebug() << "Controller" << phoneNumber << message << message.toUtf8().toHex();
    switch( m_stage )
    {
        case IDEL_CONTROLLER_STATE:
        if( message == m_password )
        {
            m_masterPhoneNum = phoneNumber;

            m_stage = LOGON_CONTROLLER_STATE;
            m_lastActiveTime.restart();

            qDebug() << phoneNumber << "Logon";

            emit newSMS(m_masterPhoneNum, "Logon");
        }
        else
        {
            qDebug() << "password incorrect!";
        }
        break;
    case LOGON_CONTROLLER_STATE:
        if(phoneNumber == m_masterPhoneNum )
        {
            m_lastActiveTime.restart();
            processCMD( message );
        }
        break;
    }
}

void ControllerObject::checkTime()
{

    qDebug() << "chec Time" << m_lastActiveTime.isValid() << m_lastActiveTime.elapsed();
    if( m_lastActiveTime.isValid() && m_lastActiveTime.elapsed() > 1000 * 60 * 1 )
        processCMD("logout");
}

void ControllerObject::processCMD(QString cmd)
{
    qDebug() << "Process CMD: " << cmd;
    if( cmd == "1" )
    {
        emit newSMS(m_masterPhoneNum, "GPS");
    }
    else if( cmd.startsWith("=") )
    {
        m_password = cmd.right( cmd.length() -1 );
        qDebug() << "NewPassword:" << m_password;
        savePassword();
        emit newSMS(m_masterPhoneNum, "NewPassword");
    }
    else if( cmd == "logout" )
    {
        m_stage = IDEL_CONTROLLER_STATE;
        m_lastActiveTime.invalidate();
        emit newSMS(m_masterPhoneNum, "Logout");
    }
}

void ControllerObject::savePassword()
{
    QSettings settings("conf.ini", QSettings::IniFormat);
    settings.setValue("Password", m_password);
}

void ControllerObject::loadPassword()
{
    QSettings settings("conf.ini", QSettings::IniFormat);
    m_password = settings.value("Password", "password").toString();
}
