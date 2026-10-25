// =======================================================================
// FILE: networkmanager.h
// =======================================================================
// این کلاس مسئولیت تمام عملیات شبکه را بر عهده دارد.
// از کلاس‌های QTcpServer و QTcpSocket برای سادگی استفاده می‌کند.
//========================================================================
#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>

class NetworkManager : public QObject {
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

    void startServer(quint16 port);
    void sendData(const QByteArray& data, const QString& ip, quint16 port);

    private slots:
        void onNewConnection();
    void onReadyRead();
    void onSocketDisconnected();

    signals:
        void dataReceived(const QByteArray& data);
    void logMessage(const QString& message);

private:
    QTcpServer* server;
    qint64 dataSize = 0; // برای نگهداری سایز داده‌ای که منتظرش هستیم
};

#endif // NETWORKMANAGER_H
