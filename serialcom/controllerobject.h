#ifndef CONTROLLEROBJECT_H
#define CONTROLLEROBJECT_H

#include <QObject>
#include <QString>
#include <QElapsedTimer>
#include <QTimer>

enum CONTROLLER_STATE
{
    IDEL_CONTROLLER_STATE,
    LOGON_CONTROLLER_STATE
};

class ControllerObject : public QObject
{
    Q_OBJECT
public:
    explicit ControllerObject(QObject *parent = 0);

signals:
    void newSMS(QString phoneNumber, QString type );


public slots:
    void setMessage( QString phoneNumber, QString message );
    void checkTime();

private:
    void processCMD( QString cmd );

    QString m_masterPhoneNum;
    QString m_password;

    QTimer* m_timer;
    CONTROLLER_STATE m_stage;
    QElapsedTimer m_lastActiveTime;

    void savePassword();
    void loadPassword();
};

#endif // CONTROLLEROBJECT_H
