#ifndef IRCCHAT_H
#define IRCCHAT_H

#include <QObject>
#include <QByteArray>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
#include <QList>
#include <QTimer>

#include "twitchircconnectiondata.h"
#include "twitchchatsubscriber.h"

class TwitchIrcChat : public QObject
{
    Q_OBJECT

public:
    explicit TwitchIrcChat( QObject *parent );
    virtual ~TwitchIrcChat() override;

    bool connectToChannel( const QString &channel, const TwitchIrcConnectionData &connectionData );
    void disconnectFromChannel( const QString &channel );

    const QString& getCurrentChannel() const;
    QVector<QString> getDataLines() const;
    QTcpSocket* getSocket() const;

    void subscribeChat( TwitchChatSubscriber *subscriber );

    void write( const QString &text );

    bool isJoinedCurrentChannel() const;

    QString getCurrentUser() const;

signals:
    void twitchChannelConnection( bool successfullyConnected );

private slots:
    void onReadyReadSocket();
    void disconnectFromServer();
    void handleChannelJoin();
    void timerStart();

private:
    void send( const QByteArray &message ) const;

    bool successfullyJoined();

    QTcpSocket *socket;
    QString currentUser;
    QString currentChannel;
    QString connectedHost;
    quint16 connectedPort;
    bool joinedCurrentChannel;

    QTimer timer;

    TwitchChatSubscriber* chatSubsriber;
};

#endif // IRCCHAT_H
