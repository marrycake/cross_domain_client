#pragma once
#include <QtNetwork>
#include <iostream>
#include <QMap>
class QHttpmanger
{
public:
    static QString UrlRequestGet(const QString &url)
    {
        QNetworkAccessManager qnam;
        const QUrl aurl(url);
        QNetworkRequest qnr(aurl);
        qnr.setRawHeader("Content-Type", "application/json");

        QNetworkReply *reply = qnam.get(qnr);

        QEventLoop eventloop;
        QObject::connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
        eventloop.exec(QEventLoop::ExcludeUserInputEvents);

        QTextCodec *codec = QTextCodec::codecForName("utf8");
        QString replyData = codec->toUnicode(reply->readAll());

        if (reply->error() != QNetworkReply::NoError)
        {
            std::cout << "Network request failed:" << reply->errorString().toStdString() << std::endl;
        }

        reply->deleteLater();
        reply = nullptr;

        return replyData;
    }

    static QString UrlRequestGet(const QString &url, const QMap<QString, QString> &externalHeaders)
    {
        QNetworkAccessManager qnam;
        const QUrl aurl(url);
        QNetworkRequest qnr(aurl);
        qnr.setRawHeader("Content-Type", "application/json");
        for (auto it = externalHeaders.cbegin(); it != externalHeaders.cend(); ++it)
        {
            qnr.setRawHeader(it.key().toUtf8(), it.value().toUtf8());
        }

        QNetworkReply *reply = qnam.get(qnr);

        QEventLoop eventloop;
        QObject::connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
        eventloop.exec(QEventLoop::ExcludeUserInputEvents);

        QTextCodec *codec = QTextCodec::codecForName("utf8");
        QString replyData = codec->toUnicode(reply->readAll());

        if (reply->error() != QNetworkReply::NoError)
        {
            std::cout << "Network request failed:" << reply->errorString().toStdString() << std::endl;
        }

        reply->deleteLater();
        reply = nullptr;

        return replyData;
    }

    static QString UrlRequestPost(const QString &url, const QString &post_data)
    {
        QNetworkAccessManager qnam;
        const QUrl aurl(url);
        QNetworkRequest qnr(aurl);
        qnr.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

        QNetworkReply *reply = qnam.post(qnr, post_data.toUtf8());

        QEventLoop eventloop;
        QObject::connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
        eventloop.exec(QEventLoop::ExcludeUserInputEvents);

        QTextCodec *codec = QTextCodec::codecForName("utf8");
        QString replyData = codec->toUnicode(reply->readAll());

        reply->deleteLater();
        reply = nullptr;

        return replyData;
    }

    static QString UrlRequestPost(const QString &url, const QString &post_data, const QMap<QString, QString> &externalHeaders)
    {
        QNetworkAccessManager qnam;
        const QUrl aurl(url);
        QNetworkRequest qnr(aurl);
        qnr.setRawHeader("Content-Type", "application/x-www-form-urlencoded");
        for (auto it = externalHeaders.cbegin(); it != externalHeaders.cend(); ++it)
        {
            qnr.setRawHeader(it.key().toUtf8(), it.value().toUtf8());
        }
        QNetworkReply *reply = qnam.post(qnr, post_data.toUtf8());

        QEventLoop eventloop;
        QObject::connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
        eventloop.exec(QEventLoop::ExcludeUserInputEvents);

        QTextCodec *codec = QTextCodec::codecForName("utf8");
        QString replyData = codec->toUnicode(reply->readAll());

        reply->deleteLater();
        reply = nullptr;

        return replyData;
    }
};
