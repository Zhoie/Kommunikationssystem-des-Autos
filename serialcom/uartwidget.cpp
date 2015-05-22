#include "uartwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

UartWidget::UartWidget(QWidget *parent) :
    QWidget(parent)
{
    m_gps = NULL;
    //////////////////////
    m_textEdit = new QTextEdit;

    m_openBtn = new QPushButton("Open");
    m_closeBtn = new QPushButton("Close");

    m_buttons = new QDialogButtonBox(Qt::Horizontal);
    m_buttons->addButton( m_openBtn, QDialogButtonBox::ActionRole );
    m_buttons->addButton( m_closeBtn, QDialogButtonBox::ActionRole );


    m_inputText = new QLineEdit;
    m_sendBtn = new QPushButton("Send");

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget( m_inputText );
    hLayout->addWidget( m_sendBtn );


    QVBoxLayout* mainLayout = new QVBoxLayout();

    mainLayout->addWidget( m_buttons );
    mainLayout->addWidget( m_textEdit );
    mainLayout->addLayout( hLayout );

    setLayout( mainLayout );


    ///////////////////////////////
    m_openBtn->setEnabled( true );
    m_closeBtn->setEnabled( false );
    m_sendBtn->setEnabled( false );

    ///////////////////////////
    connect( m_openBtn, SIGNAL(clicked()), this, SLOT(openGPS()));
    connect( m_closeBtn, SIGNAL(clicked()), this, SLOT(closeGPS()));
    connect( m_sendBtn, SIGNAL(clicked()), this, SLOT(writeEditContext()));

}

void UartWidget::openGPS()
{
    m_gps = new UartObject;

    if(  m_gps->open( m_comPort ) )
    {
        m_openBtn->setEnabled( false );
        m_closeBtn->setEnabled( true );
        m_sendBtn->setEnabled( true );

        connect( m_gps, SIGNAL(dataArray(QByteArray)), this, SLOT(newUartData(QByteArray)));

        emit portOpened();
    }
}

void UartWidget::closeGPS()
{
    m_gps->close();

    m_openBtn->setEnabled( true );
    m_closeBtn->setEnabled( false );
    m_sendBtn->setEnabled( false );

    emit portClosed();
}

void UartWidget::newUartData(QByteArray data)
{
    m_textEdit->append( QString::fromUtf8( data ) );

    process( data );
}

void UartWidget::writeEditContext()
{
    QByteArray data = m_inputText->text().toUtf8();

    writeUart( data + '\r' );
}

void UartWidget::writeUart(const QByteArray &data)
{
    if( m_gps != NULL )
        m_gps->write( data );
}
