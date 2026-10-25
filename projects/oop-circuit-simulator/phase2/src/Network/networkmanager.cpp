//
// Created by Asus on 8/13/2025.
//
// =======================================================================
// FILE: networkmanager.cpp
// =======================================================================
#include "networkmanager.h"
#include <QDataStream>
#include <QHostAddress>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent), server(nullptr) {}

void NetworkManager::startServer(quint16 port) {
    if (server) {
        server->close();
        delete server;
    }
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &NetworkManager::onNewConnection);

    if (!server->listen(QHostAddress::Any, port)) {
        emit logMessage("خطا: سرور نتوانست روی پورت " + QString::number(port) + " شروع به کار کند.");
    } else {
        emit logMessage("سرور روی پورت " + QString::number(port) + " فعال شد.");
    }
}

void NetworkManager::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &NetworkManager::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &NetworkManager::onSocketDisconnected);
    emit logMessage("یک کلاینت جدید متصل شد: " + clientSocket->peerAddress().toString());
}

void NetworkManager::onReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    // پیاده‌سازی پروتکل: خواندن سایز و سپس داده
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_6_7); // سازگاری با نسخه Qt

    if (dataSize == 0) {
        // اگر هنوز سایز پیام را نمی‌دانیم، صبر می‌کنیم تا حداقل به اندازه یک qint64 داده برسد
        if (clientSocket->bytesAvailable() < (int)sizeof(qint64))
            return;
        in >> dataSize;
    }

    // اگر کل داده مورد انتظار هنوز نرسیده است، منتظر می‌مانیم
    if (clientSocket->bytesAvailable() < dataSize)
        return;

    QByteArray data;
    in >> data;

    emit dataReceived(data);
    dataSize = 0; // ریست کردن برای پیام بعدی
}

void NetworkManager::onSocketDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    emit logMessage("کلاینت " + clientSocket->peerAddress().toString() + " قطع شد.");
    clientSocket->deleteLater();
}


void NetworkManager::sendData(const QByteArray& data, const QString& ip, quint16 port) {
    QTcpSocket* socket = new QTcpSocket(this);
    // اطمینان از پاک شدن سوکت پس از قطع اتصال
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    socket->connectToHost(ip, port);

    if (socket->waitForConnected(3000)) {
        // پروتکل: ابتدا سایز داده و سپس خود داده را می‌فرستیم
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_7);

        // یک جای خالی برای سایز می‌گذاریم، داده را می‌نویسیم، سپس برمی‌گردیم و سایز را می‌نویسیم
        out << (qint64)0;
        out << data;
        out.device()->seek(0);
        out << (qint64)(block.size() - sizeof(qint64));

        socket->write(block);
        socket->flush();
        socket->waitForBytesWritten(1000);
        emit logMessage("داده با موفقیت ارسال شد.");
    } else {
        emit logMessage("خطا در اتصال به سرور: " + socket->errorString());
    }
    socket->close();
}
