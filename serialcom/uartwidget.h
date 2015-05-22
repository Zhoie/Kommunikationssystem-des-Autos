#ifndef UARTWIDGET_H
#define UARTWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLineEdit>

#include "uartobject.h"

class UartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UartWidget(QWidget *parent = 0);

signals:
    void portOpened();
    void portClosed();

public slots:
    void openGPS();
    void closeGPS();

    void newUartData( QByteArray data );
    void writeEditContext();

protected:
    virtual void process( QByteArray msg ) = 0;
    QString m_comPort;

    void writeUart( const QByteArray& data );

private:
    UartObject* m_gps;


    // ui
    QTextEdit* m_textEdit;
    QDialogButtonBox* m_buttons;

    QPushButton* m_openBtn;
    QPushButton* m_closeBtn;

    QLineEdit* m_inputText;
    QPushButton* m_sendBtn;

};

#endif // UARTWIDGET_H
