#ifndef GSMWIDGET_H
#define GSMWIDGET_H


#include "uartwidget.h"

#include <QPushButton>


enum _SMS_STAGE
{
    IDEL_STAGE,
    SEND_STAGE,
    READ_STAGE,
    DELETE_STAGE
};

class GSMWidget : public UartWidget
{
    Q_OBJECT
public:
    explicit GSMWidget(QWidget *parent = 0);

    void sendSMS(const QString &phoneNumber, const QByteArray &sms );
    void readSMS(int index);
    void deleteSMS(int index);
    void comformSMS();

signals:
    void newSMS( QString phoneNumber, QString message );

public slots:
    void initGSM();
    void onSendSMS();
    void onReadSMS();

protected:
    virtual void process( QByteArray msg );


    void parseFrame (QString frame );

private:
    QPushButton* m_sendSMSBtn;
    QPushButton* m_readSMSBtn;

    QString m_phoneNumber;
    QString m_buf;

    QString m_readFrame;

    int m_currentIndex;
    _SMS_STAGE m_stage;
};

#endif // GSMWIDGET_H
