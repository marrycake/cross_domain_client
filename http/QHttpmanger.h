#pragma once
#include <qchar.h>
#include <qmap.h>

#include <QMap>
#include <QtNetwork>
#include <iostream>

class QHttpmanger {
 public:
  static QString UrlRequestGet(const QString &url) {
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

    if (reply->error() != QNetworkReply::NoError) {
      std::cout << "Network request failed:"
                << reply->errorString().toStdString() << std::endl;
    }

    reply->deleteLater();
    reply = nullptr;

    return replyData;
  }

  static QString UrlRequestGet(const QString &url,
                               const QMap<QString, QString> &externalHeaders) {
    QNetworkAccessManager qnam;
    const QUrl aurl(url);
    QNetworkRequest qnr(aurl);
    qnr.setRawHeader("Content-Type", "application/json");
    for (auto it = externalHeaders.cbegin(); it != externalHeaders.cend();
         ++it) {
      qnr.setRawHeader(it.key().toUtf8(), it.value().toUtf8());
    }

    QNetworkReply *reply = qnam.get(qnr);

    QEventLoop eventloop;
    QObject::connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
    eventloop.exec(QEventLoop::ExcludeUserInputEvents);

    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString replyData = codec->toUnicode(reply->readAll());

    if (reply->error() != QNetworkReply::NoError) {
      std::cout << "Network request failed:"
                << reply->errorString().toStdString() << std::endl;
    }

    reply->deleteLater();
    reply = nullptr;

    return replyData;
  }

  static QString UrlRequestPost(const QString &url, const QString &post_data) {
    QNetworkAccessManager qnam;
    const QUrl aurl(url);
    QNetworkRequest qnr(aurl);
    qnr.setRawHeader("Content-Type", "application/json");

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

  static QString UrlRequestPost(const QString &url, const QString &post_data,
                                const QMap<QString, QString> &externalHeaders) {
    QNetworkAccessManager qnam;
    const QUrl aurl(url);
    QNetworkRequest qnr(aurl);
    qnr.setRawHeader("Content-Type", "application/json");
    for (auto it = externalHeaders.cbegin(); it != externalHeaders.cend();
         ++it) {
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

  static QString UrlRequestPostMultipart(
      const QString &url, const QString &filePath,
      const QMap<QString, QString> &exterlParamters,
      const QMap<QString, QString> &externalHeaders) {
    QNetworkAccessManager qnam;
    const QUrl aurl(url);
    QNetworkRequest qnr(aurl);
    for (auto it = externalHeaders.cbegin(); it != externalHeaders.cend();
         ++it) {
      qnr.setRawHeader(it.key().toUtf8(), it.value().toUtf8());
    }

    QHttpMultiPart *multiPart =
        new QHttpMultiPart(QHttpMultiPart::FormDataType);

    // Prepare the file part
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                       QVariant("form-data; name=\"file\"; filename=\"" +
                                QFileInfo(filePath).fileName() + "\""));
    QFile *file = new QFile(filePath);
    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);

    for (auto it = exterlParamters.cbegin(); it != exterlParamters.cend();
         ++it) {
      QHttpPart httpPart;
      httpPart.setHeader(
          QNetworkRequest::ContentDispositionHeader,
          QVariant("form-data; name=\"" + it.key().toUtf8() + "\""));
      httpPart.setBody(it.value().toUtf8());
      multiPart->append(httpPart);
    }
    QNetworkReply *reply = qnam.post(qnr, multiPart);

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
